/**
 * This program is used for detecting regions of high intensity in grayscale images considering a circular geometry
 *
 * FORMAT OF INPUT FILE:
 * Images generated with CircularGeometryViewer
 *
 * FORMAT OF OUTPUT FILE:
 * If in debug mode, then also display results. Else only print them in a .csv/xml file.
 *
 * Author: Ovidiu Parvu
 * Date created: 18.03.2013
 * Date modified: 27.03.2013
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/analysis/spatial/RegionDetector.hpp"
#include "multiscale/analysis/spatial/factory/CircularMatFactory.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/program_options.hpp>

#include <iostream>

using namespace std;
using namespace multiscale;
using namespace multiscale::analysis;

namespace po = boost::program_options;
namespace pt = boost::property_tree;

const string CONFIG_FILE = "config/analysis/spatial/circular_region_detector.xml";

const string LABEL_ROOT_COMMENT                      = "<xmlcomment>";
const string LABEL_ALPHA                             = "detector.alpha";
const string LABEL_BETA                              = "detector.beta";
const string LABEL_BLUR_KERNEL_SIZE                  = "detector.blurKernelSize";
const string LABEL_MORPHOLOGICAL_CLOSE_ITERATIONS    = "detector.morphologicalCloseIterations";
const string LABEL_EPSILON                           = "detector.epsilon";
const string LABEL_REGION_AREA_THRESH                = "detector.regionAreaThresh";
const string LABEL_THRESHOLD_VALUE                   = "detector.thresholdValue";

const string ROOT_COMMENT    = "Warning! This xml file was automatically generated by a C++ program using the Boost PropertyTree library.";


// Initialise the arguments configuration
po::variables_map initArgumentsConfig(po::options_description &usageDescription, int argc, char** argv) {
    usageDescription.add_options()("help,h", "display help message\n")
                                  ("input-file,i", po::value<string>(), "provide the path to the input file\n")
                                  ("output-file,o", po::value<string>(), "provide the path of the output file (without extension)\n")
                                  ("debug-mode,d", po::value<bool>()->implicit_value(false), "start the program in debug mode\n");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, usageDescription), vm);
    po::notify(vm);
    return vm;
}

// Print help message if needed
void printHelpInformation(const po::variables_map &vm, const po::options_description &usageDescription) {
    cout << usageDescription << endl;
}

// Print error message if wrong parameters are provided
void printWrongParameters() {
    cout << ERR_MSG << "Wrong input arguments provided." << endl;
    cout << "Run the program with the argument \"--help\" for more information." << endl;
}

// Get the needed parameters
bool areValidParameters(string &inputFilepath, string &outputFilename, bool &debugFlag, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    // Check if the user wants to print help information
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return false;
    }

    // Check if the given parameters are correct
    if ((vm.count("input-file")) && (vm.count("output-file"))) {
        inputFilepath  = vm["input-file"].as<string>();
        outputFilename = vm["output-file"].as<string>();

        if (vm.count("debug-mode")) {
            debugFlag = vm["debug-mode"].as<bool>();
        }

        return true;
    }

    return false;
}

// Load the values of the parameters from the config file
void loadDetectorParameterValues(RegionDetector &detector) {
    pt::ptree propertyTree;

    read_xml(CONFIG_FILE, propertyTree, pt::xml_parser::trim_whitespace);

    detector.setAlpha(propertyTree.get<int>(LABEL_ALPHA));
    detector.setBeta(propertyTree.get<int>(LABEL_BETA));
    detector.setBlurKernelSize(propertyTree.get<int>(LABEL_BLUR_KERNEL_SIZE));
    detector.setMorphologicalCloseIterations(propertyTree.get<int>(LABEL_MORPHOLOGICAL_CLOSE_ITERATIONS));
    detector.setEpsilon(propertyTree.get<int>(LABEL_EPSILON));
    detector.setRegionAreaThresh(propertyTree.get<int>(LABEL_REGION_AREA_THRESH));
    detector.setThresholdValue(propertyTree.get<int>(LABEL_THRESHOLD_VALUE));
}

// Save the values of the parameters to the config file
void saveDetectorParameterValues(RegionDetector &detector) {
    pt::ptree propertyTree;

    propertyTree.put<string>(LABEL_ROOT_COMMENT, ROOT_COMMENT);

    propertyTree.put<int>(LABEL_ALPHA, detector.getAlpha());
    propertyTree.put<int>(LABEL_BETA, detector.getBeta());
    propertyTree.put<int>(LABEL_BLUR_KERNEL_SIZE, detector.getBlurKernelSize());
    propertyTree.put<int>(LABEL_MORPHOLOGICAL_CLOSE_ITERATIONS, detector.getMorphologicalCloseIterations());
    propertyTree.put<int>(LABEL_EPSILON, detector.getEpsilon());
    propertyTree.put<int>(LABEL_REGION_AREA_THRESH, detector.getRegionAreaThresh());
    propertyTree.put<int>(LABEL_THRESHOLD_VALUE, detector.getThresholdValue());

    // Pretty writing of the property tree to the file
    pt::xml_writer_settings<char> settings('\t', 1);
    write_xml(CONFIG_FILE, propertyTree, std::locale(), settings);
}

// Load the values of the parameters from the config file if in debug mode
void loadDetectorParameterValues(RegionDetector &detector, bool debugMode) {
    loadDetectorParameterValues(detector);
}

// Save the values of the parameters to the config file if in debug mode
void saveDetectorParameterValues(RegionDetector &detector, bool debugMode) {
    if (debugMode) {
        saveDetectorParameterValues(detector);
    }
}

// Main function
int main(int argc, char** argv) {
    string inputFilePath;
    string outputFilepath;

    bool debugFlag = false;

    try {
        if (areValidParameters(inputFilePath, outputFilepath, debugFlag, argc, argv)) {
            Mat image = CircularMatFactory().createFromViewerImage(inputFilePath);

            RegionDetector detector(debugFlag);

            loadDetectorParameterValues(detector, debugFlag);

            detector.detect(image);
            detector.outputResults(outputFilepath);

            saveDetectorParameterValues(detector, debugFlag);
        } else {
            printWrongParameters();
        }
    } catch(const exception &e) {
        ExceptionHandler::printErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(...) {
        cerr << "Exception of unknown type!" << endl;
    }

    return EXEC_SUCCESS_CODE;
}
