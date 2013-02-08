#include "multiscale/video/rectangular/RectangularCsvToInputFilesConverter.hpp"
#include "multiscale/util/iterator/NumberIteratorType.hpp"
#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"
#include "multiscale/util/iterator/StandardNumberIterator.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <limits>

using namespace multiscale::video;
using namespace multiscale;
using namespace std;

// Constructor for the class
RectangularCsvToInputFilesConverter::RectangularCsvToInputFilesConverter(string inputFilepath,
                                                             string outputFilepath,
                                                             unsigned int height,
                                                             unsigned int width,
                                                             unsigned int nrOfConcentrationsForPosition,
                                                             NumberIteratorType numberIteratorType) {
    this->inputFilepath                 = inputFilepath;
    this->outputFilepath                = outputFilepath;

    this->height                        = height;
    this->width                         = width;
    this->nrOfConcentrationsForPosition = nrOfConcentrationsForPosition;

    this->concentrationsIndex  = 0;
    this->maximumConcentration = 1;

    initIterators(numberIteratorType);
}

// Destructor for the class
RectangularCsvToInputFilesConverter::~RectangularCsvToInputFilesConverter() {
    delete circlesIterator;
    delete sectorsIterator;
}

// Convert the ".csv" file to input files
void RectangularCsvToInputFilesConverter::convert() {
    ifstream fin;

    validateInput(fin);
    initMaximumConcentration(fin);
    initInputFile(fin);

    string currentLine;

    unsigned int index = 1;

    while (!fin.eof()) {
        getline(fin, currentLine);

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            processLine(currentLine, index++);
        }
    }

    fin.close();
}

// Initialise the input file
void RectangularCsvToInputFilesConverter::initInputFile(ifstream& fin) {
    fin.open(inputFilepath.c_str(), ios_base::in);

    assert(fin.is_open());
}

// Initialise the maximum concentration value
void RectangularCsvToInputFilesConverter::initMaximumConcentration(ifstream& fin) {
    double maximumConcentration = numeric_limits<double>::min();
    string currentLine;

    fin.open(inputFilepath.c_str(), ios_base::in);

    assert(fin.is_open());

    while (!fin.eof()) {
        getline(fin, currentLine);

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            updateMaximumConcentration(currentLine, maximumConcentration);
        }
    }

    fin.close();

    this->maximumConcentration = maximumConcentration;
}

// Initialise the output file
void RectangularCsvToInputFilesConverter::initOutputFile(ofstream& fout, unsigned int index) {
    fout.open(
                (
                    (outputFilepath + OUTPUT_FILE_SEPARATOR) +
                    StringManipulator::toString(index) +
                    OUTPUT_EXTENSION
                ).c_str(),
                ios_base::trunc
            );

    assert(fout.is_open());

    fout << height << OUTPUT_SEPARATOR << width << endl;
}

// Initialise the iterators
void RectangularCsvToInputFilesConverter::initIterators(NumberIteratorType& numberIteratorType) {
    switch (numberIteratorType) {
    case multiscale::STANDARD:
        circlesIterator = new StandardNumberIterator(height);
        sectorsIterator = new StandardNumberIterator(width);
        break;

    case multiscale::LEXICOGRAPHIC:
        circlesIterator = new LexicographicNumberIterator(height);
        sectorsIterator = new LexicographicNumberIterator(width);
        break;
    }
}

// Validate the input file
void RectangularCsvToInputFilesConverter::validateInput(ifstream& fin) {
    unsigned int lineNumber = 0;
    string currentLine;

    fin.open(inputFilepath.c_str(), ios_base::in);

    assert(fin.is_open());

    while (!fin.eof()) {
        getline(fin, currentLine);

        lineNumber++;

        // Consider processing the line only if it has content
        if (!currentLine.empty()) {
            validateInputLine(currentLine, lineNumber);
        }
    }

    fin.close();
}

// Validate the provided line
void RectangularCsvToInputFilesConverter::validateInputLine(string& currentLine, unsigned int lineNumber) {
    vector<string> tokens = StringManipulator::split(currentLine, INPUT_FILE_SEPARATOR);

    if (tokens.size() < (height * width))
        throw ERR_NR_CONCENTRATIONS;

    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        double concentration = atof((*it).c_str());

        if (concentration < 0)
            throw string(ERR_INVALID_CONCENTRATION_LINE)  +
                  StringManipulator::toString<unsigned int>(lineNumber) +
                  string(ERR_INVALID_CONCENTRATION_TOKEN) + (*it);
    }
}

// Process the current line
void RectangularCsvToInputFilesConverter::processLine(string& line, unsigned int outputIndex) {
    ofstream fout;

    initOutputFile(fout, outputIndex);

    vector<double> concentrations = splitLineInConcentrations(line);

    for (unsigned int i = 0; i < height; i++) {
        for (int j = 0; j < (width - 1); j++) {
            fout << concentrations[(i * width) + j] << OUTPUT_SEPARATOR;
        }

        fout << concentrations[(i * width) + width - 1] << endl;
    }
}

// Split the line in concentrations
vector<double> RectangularCsvToInputFilesConverter::splitLineInConcentrations(string line) {
    vector<double> concentrations(height * width);

    vector<string> tokens = StringManipulator::split(line, INPUT_FILE_SEPARATOR);

    concentrationsIndex = 0;

    circlesIterator->reset();

    while (circlesIterator->hasNext()) {
        unsigned int rowIndex = circlesIterator->number();

        sectorsIterator->reset();

        splitLineInConcentrations(concentrations, tokens, rowIndex);
    }

    return concentrations;
}

// Split the line into concentrations
void RectangularCsvToInputFilesConverter::splitLineInConcentrations(vector<double>& concentrations,
                                                                    vector<string>& tokens,
                                                                    unsigned int rowIndex) {
    while (sectorsIterator->hasNext()) {
        unsigned int sectorIndex = sectorsIterator->number();

        double concentration = computeNextPositionConcentration(concentrationsIndex,
                                                                tokens);

        concentrations[((rowIndex - 1) * width) + sectorIndex - 1] = concentration;

        concentrationsIndex++;
    }
}

// Compute the concentration of the next position
double RectangularCsvToInputFilesConverter::computeNextPositionConcentration(int concentrationIndex,
                                                                             vector<string>& tokens) {
    // Read the first concentration
    double concentration = computeScaledConcentration(tokens[(nrOfConcentrationsForPosition * concentrationIndex)]);

    double totalConcentration = concentration;

    // Read the other concentrations if they exist
    for (unsigned int i = 1; i < nrOfConcentrationsForPosition; i++) {
        double tmpConcentration = computeScaledConcentration(tokens[(nrOfConcentrationsForPosition * concentrationIndex) + i]);

        totalConcentration += tmpConcentration;
    }

    // Return normalised concentration
    return (nrOfConcentrationsForPosition == 1) ?
            computeNormalisedConcentration(concentration) :
            computeNormalisedConcentration((concentration/totalConcentration));
}

// Compute the scaled concentration from the given string by applying
// a logit transformation to it
double RectangularCsvToInputFilesConverter::computeScaledConcentration(string concentration) {
    double amount = atof(concentration.c_str());

    double scaledConcentration = computeConcentrationWrtArea(amount);

    // Convert all concentrations which are lower than 1 to 1,
    // such that we don't obtain negative values after applying log
    if (scaledConcentration < 1) {
        scaledConcentration = 1;
    }

    return log2(scaledConcentration);
}

// Compute the concentration of a annular sector given the number of species
// and the level at which the annular sector is positioned
double RectangularCsvToInputFilesConverter::computeConcentrationWrtArea(double amount) {
    return amount / 1;
}

// Compute the normalised concentration by considering the maximum concentration
// and the area of the current annular sector
double RectangularCsvToInputFilesConverter::computeNormalisedConcentration(double concentration) {
    return (concentration / maximumConcentration);
}

// Update the maximum value if any of the concentrations from the
// provided string are greater than it
void RectangularCsvToInputFilesConverter::updateMaximumConcentration(string& currentLine, double& maximumConcentration) {
    vector<double> concentrations = splitLineInConcentrations(currentLine);

    for (vector<double>::iterator it = concentrations.begin(); it != concentrations.end(); it++) {
        if ((*it) > maximumConcentration) {
            maximumConcentration = (*it);
        }
    }
}
