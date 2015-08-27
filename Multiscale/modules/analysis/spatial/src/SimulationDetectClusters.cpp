/**
 * This program is used for detecting clusters in grayscale 2D images considering a rectangular geometry
 *
 * FORMAT OF INPUT FILE:
 * Images generated with RectangularGeometryViewer
 *
 * FORMAT OF OUTPUT FILE:
 * If in debug mode, then also display results. Else only print them in a .csv/xml file.
 *
 * Author: Ovidiu Pârvu
 * Date created: 03.07.2013
 * Date modified: 05.07.2013
 */

#include "multiscale/core/Multiscale.hpp"
#include "multiscale/analysis/spatial/detector/SimulationClusterDetector.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <typeinfo>

using namespace multiscale;
using namespace multiscale::analysis;

namespace po = boost::program_options;
namespace pt = boost::property_tree;

const std::string CONFIG_FILE = "/usr/local/share/mule/config/analysis/spatial/simulation_cluster_detector.xml";

const std::string LABEL_ROOT_COMMENT      = "<xmlcomment>";
const std::string LABEL_EPS               = "detector.eps";
const std::string LABEL_MINPOINTS         = "detector.minPoints";

const std::string ROOT_COMMENT            = "Warning! This xml file was automatically generated by a C++ program using the Boost PropertyTree library.";


// Initialize the arguments configuration
po::variables_map initArgumentsConfig(po::options_description &usageDescription, int argc, char** argv) {
    usageDescription.add_options()("help,h"                                                         , "display help message\n")
                                  ("height,e"           , po::value<unsigned int>()                 , "provide the height of the grid (number of rows)\n")
                                  ("width,w"            , po::value<unsigned int>()                 , "provide the width of the grid (number of columns)\n")
                                  ("input-file,i"       , po::value<std::string>()                  , "provide the path to the input file\n")
                                  ("text-input-file,t"  , po::value<bool>()->implicit_value(true)   , "flag indicating if the input file type is text (true) or image (false); default flag value is true.\n")
                                  ("output-file,o"      , po::value<std::string>()                  , "provide the path of the output file (without extension)\n")
                                  ("max-pileup,m"       , po::value<unsigned int>()                 , "provide the maximum number of entities which can occupy a grid position at the same time\n")
                                  ("debug-mode,d"       , po::value<bool>()->implicit_value(false)  , "start the program in debug mode\n");

    po::variables_map vm;

    po::store(po::parse_command_line(argc, argv, usageDescription), vm);
    po::notify(vm);

    return vm;
}

// Print help message if needed
void printHelpInformation(const po::variables_map &vm, const po::options_description &usageDescription) {
    std::cout << usageDescription << std::endl;
}

// Print error message if wrong parameters are provided
void printWrongParameters() {
    std::cout << ERR_MSG << "Wrong input arguments provided." << std::endl;
    std::cout << "Run the program with the argument \"--help\" for more information." << std::endl;
}

// Get the needed parameters
bool areValidParameters(std::string &inputFilepath, std::string &outputFilepath, bool &isTextInputFile,
                        bool &isDebugMode, unsigned int &height, unsigned int &width,
                        unsigned int &maxPileup, int argc, char** argv) {
    po::options_description usageDescription("Usage");

    po::variables_map vm = initArgumentsConfig(usageDescription, argc, argv);

    // Check if the user wants to print help information
    if (vm.count("help")) {
        printHelpInformation(vm, usageDescription);

        return false;
    }

    // Check if the given parameters are correct
    if ((vm.count("input-file")) && (vm.count("output-file")) &&
        (vm.count("height")) && (vm.count("width")) && (vm.count("max-pileup"))) {
        // Update the input/output file paths
        inputFilepath  = vm["input-file"].as<std::string>();
        outputFilepath = vm["output-file"].as<std::string>();

        // Update the height and the width
        height = vm["height"].as<unsigned int>();
        width = vm["width"].as<unsigned int>();

        // Update the maximum pileup
        maxPileup = vm["max-pileup"].as<unsigned int>();

        // Update the input file type flag
        if (vm.count("text-input-file")) {
            isTextInputFile = vm["text-input-file"].as<bool>();
        }

        // Update the debug mode flag
        if (vm.count("debug-mode")) {
            isDebugMode = vm["debug-mode"].as<bool>();
        }

        return true;
    }

    return false;
}

// Load the values of the parameters from the config file
void loadDetectorParameterValues(SimulationClusterDetector &detector) {
    pt::ptree propertyTree;

    read_xml(CONFIG_FILE, propertyTree, pt::xml_parser::trim_whitespace);

    detector.setEps(propertyTree.get<double>(LABEL_EPS));
    detector.setMinPoints(propertyTree.get<int>(LABEL_MINPOINTS));
}

// Save the values of the parameters to the config file
void saveDetectorParameterValues(SimulationClusterDetector &detector) {
    pt::ptree propertyTree;

    propertyTree.put<std::string>(LABEL_ROOT_COMMENT, ROOT_COMMENT);

    propertyTree.put<double>(LABEL_EPS, detector.getEps());
    propertyTree.put<int>(LABEL_MINPOINTS, detector.getMinPoints());

    // Pretty writing of the property tree to the file
    pt::xml_writer_settings<char> settings('\t', 1);
    write_xml(CONFIG_FILE, propertyTree, std::locale(), settings);
}

// Load the values of the parameters from the config file if in debug mode
void loadDetectorParameterValues(SimulationClusterDetector &detector, bool debugMode) {
    loadDetectorParameterValues(detector);
}

// Save the values of the parameters to the config file if in debug mode
void saveDetectorParameterValues(SimulationClusterDetector &detector, bool debugMode) {
    if (debugMode) {
        saveDetectorParameterValues(detector);
    }
}

// Create a Mat instance from the given input file
cv::Mat createMatFromInputFile(const std::string &inputFilePath, bool isTextInputFile) {
    RectangularMatFactory factory;

    if (isTextInputFile) {
        return factory.createFromTextFile(inputFilePath);
    } else {
        return factory.createFromImageFile(inputFilePath);
    }
}

// Main function
int main(int argc, char** argv) {
    std::string inputFilePath;
    std::string outputFilepath;

    unsigned int maxPileup;

    bool isTextInputFile = true;
    bool isDebugMode     = false;

    unsigned int height;
    unsigned int width;

    try {
        if (areValidParameters(inputFilePath, outputFilepath, isTextInputFile, isDebugMode,
                               height, width, maxPileup, argc, argv)) {
            cv::Mat image = createMatFromInputFile(inputFilePath, isTextInputFile);

            SimulationClusterDetector detector(height, width, maxPileup, isDebugMode);

            loadDetectorParameterValues(detector, isDebugMode);

            detector.detect(image);
            detector.outputResults(outputFilepath);

            saveDetectorParameterValues(detector, isDebugMode);
        } else {
            printWrongParameters();
        }
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);

        return EXEC_ERR_CODE;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return EXEC_SUCCESS_CODE;
}
