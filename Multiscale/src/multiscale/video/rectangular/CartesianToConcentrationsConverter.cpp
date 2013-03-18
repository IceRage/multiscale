#include "multiscale/video/rectangular/CartesianToConcentrationsConverter.hpp"
#include "multiscale/video/rectangular/RectangularGnuplotScriptGenerator.hpp"
#include "multiscale/util/NumericRangeManipulator.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

using namespace multiscale::video;


CartesianToConcentrationsConverter::CartesianToConcentrationsConverter(const string &inputFilepath, const string &outputFilepath) {
    this->inputFilepath.assign(inputFilepath);
    this->outputFilepath.assign(outputFilepath);

    height = 0;
    width = 0;
    simulationTime = 0;
}

CartesianToConcentrationsConverter::~CartesianToConcentrationsConverter() {}

void CartesianToConcentrationsConverter::convert() {
    readInputData();
    outputResults();
}

void CartesianToConcentrationsConverter::readInputData() throw (string) {
    ifstream fin(inputFilepath, ios_base::in);

    if (!fin.is_open()) throw ERR_INPUT_OPEN;

    // Read the header line
    readHeaderLine(fin);

    // Read the concentrations
    readConcentrations(fin);

    // Check if the file contains additional unnecessary data
    // after excluding the line feed character
    fin.get();

    if (fin.peek() != EOF) throw string(ERR_IN_EXTRA_DATA);

    fin.close();
}

void CartesianToConcentrationsConverter::readHeaderLine(ifstream &fin) throw (string) {
    fin >> height >> width >> simulationTime;

    // Validate the header line
    if (height <= 0) throw string(ERR_NONPOS_DIMENSION);
    if (width <= 0)  throw string(ERR_NONPOS_DIMENSION);
    if (simulationTime < 0) throw string(ERR_NEG_SIM_TIME);
}

void CartesianToConcentrationsConverter::readConcentrations(ifstream &fin) throw (string) {
    int nrOfConcentrations = height * width;

    concentrations.resize(nrOfConcentrations);

    double tmp = 0;

    // Read all the concentrations and verify if they are
    // non-negative
    for (int i = 0; i < nrOfConcentrations; i++) {
        fin >> tmp;

        if ((tmp < 0) || (tmp > 1)) throw string(ERR_CONC);

        concentrations[i] = tmp;
    }
}

void CartesianToConcentrationsConverter::outputResults() {
    RectangularGnuplotScriptGenerator::generateScript(concentrations, simulationTime, height, width, outputFilepath);
}
