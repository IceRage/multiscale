#include "../include/CartesianToPolarConverter.hpp"
#include "../include/GnuplotScriptGenerator.hpp"
#include "../include/NumericRangeManipulator.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

using namespace multiscale;


// Constructor for the class
CartesianToPolarConverter::CartesianToPolarConverter(string inputFilepath, string outputFilepath) {
	this->inputFilepath.assign(inputFilepath);
	this->outputFilepath.assign(outputFilepath);

	nrOfSectors = 0;
	nrOfConcentricCircles = 0;
}

// Destructor for the class
CartesianToPolarConverter::~CartesianToPolarConverter() {
	// Do nothing
}

// Convert the cell from the grid to circular segments
void CartesianToPolarConverter::convert(bool outputToScript) {
	readInputData();
	transformToCircularSegments();

	if (outputToScript) {
		outputResultsAsScript();
	} else {
		outputResultsAsFile();
	}
}

// Read the input data
void CartesianToPolarConverter::readInputData() throw (string) {
	ifstream fin(inputFilepath.c_str());

	assert(fin.is_open());

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

// Read the header line from the input file
void CartesianToPolarConverter::readHeaderLine(ifstream& fin) throw (string) {
	fin >> nrOfConcentricCircles >> nrOfSectors;

	// Validate the header line
	if (nrOfConcentricCircles < 0) throw string(ERR_NEG_DIMENSION);
	if (nrOfSectors < 0)           throw string(ERR_NEG_DIMENSION);
}

// Read the concentrations from the input file
void CartesianToPolarConverter::readConcentrations(ifstream& fin) throw (string) {
	int nrOfConcentrations = ((nrOfConcentricCircles - 1) * nrOfSectors) + 1;

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

// Transform the cells of the grid into circular segments
void CartesianToPolarConverter::transformToCircularSegments() {
	int nrOfConcentrations = ((nrOfConcentricCircles - 1) * nrOfSectors) + 1;

	circularSegments.resize(nrOfConcentrations);

	// Tranform the cell of the grid to the circular segment corresponding
	// to the circle of radius 0
	(circularSegments.at(0)).initialise(0.0, RADIUS_MIN, 0.0, 360.0, concentrations.at(0));

	// Define the constants
	double angle     = 360 / nrOfSectors;
	int    maxRadius = (nrOfConcentricCircles - 1);

	// Transform the rest of the grid to circular segments
	for (int i = 1; i < nrOfConcentrations; i++) {
		int row = (i - 1) / nrOfSectors;
		int col = (i - 1) % nrOfSectors;

		double startRadius = NumericRangeManipulator::convertFromRange(0, maxRadius, RADIUS_MIN, RADIUS_MAX, row);
		double endRadius   = NumericRangeManipulator::convertFromRange(0, maxRadius, RADIUS_MIN, RADIUS_MAX, row + 1);

		(circularSegments.at(i)).initialise(startRadius, endRadius, col * angle, (col + 1) * angle, concentrations.at(i));
	}
}

// Output the results as a text file
void CartesianToPolarConverter::outputResultsAsFile() {
	int nrOfCircularSegments = circularSegments.size();

	ofstream fout((outputFilepath.append(OUTPUT_FILE_EXTENSION)).c_str(), ios_base::trunc);

	assert(fout.is_open());

	// Output the information of the circular segments
	for (int i = 0; i < nrOfCircularSegments; i++) {
		fout << (circularSegments.at(i)).toString() << endl;
	}

	fout.close();
}

// Output the results as a gnuplot script
void CartesianToPolarConverter::outputResultsAsScript() {
	GnuplotScriptGenerator::generateScript(circularSegments, outputFilepath);
}
