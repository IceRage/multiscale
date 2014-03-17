#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

using namespace multiscale::verification;


void ModelCheckingOutputWriter::printIntroductionMessage(const std::string &modelCheckerType,
                                                         const std::string &modelCheckerParameters) {
    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_NAME, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_COPYRIGHT, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printColouredMessage        (TAG_INTRO, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_MODEL_CHECKING_TYPE + modelCheckerType,
                                                 TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_MODEL_CHECKING_PARAMETERS + modelCheckerParameters,
                                                 TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printColouredMessage        (TAG_INTRO, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag (MSG_INTRO_CONTACT, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printInitialisationMessage(const std::string &logicProperty,
                                                           const std::string &tracesFolderPath,
                                                           unsigned long extraEvaluationTime) {
    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_EXECUTION_PARAMETERS, TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printColouredMessage        (TAG_INIT, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_LOGIC_PROPERTIES_PATH + logicProperty,
                                                 TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_TRACES_FOLDER_PATH + tracesFolderPath,
                                                 TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag (MSG_INIT_EXTRA_EVALUATION_TIME +
                                                 StringManipulator::toString(extraEvaluationTime),
                                                 TAG_INIT, ColourCode::CYAN);
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printParsingLogicPropertiesBeginMessage() {
    ConsolePrinter::printMessageWithColouredTag (MSG_PARSING_INTRODUCTION, TAG_PARSING, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage        (TAG_PARSING, ColourCode::GREEN);

    printSeparatorTag();
}

void ModelCheckingOutputWriter::printParsingLogicPropertiesEndMessage() {
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printStartModelCheckingExecutionMessage() {
    ConsolePrinter::printMessageWithColouredTag(MSG_START_MODEL_CHECKING_EXECUTION, TAG_EXECUTE, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage(TAG_EXECUTE, ColourCode::GREEN);
    printSeparatorTag();
    
    ConsolePrinter::printEmptyLine();
    ConsolePrinter::printEmptyLine();
}

void ModelCheckingOutputWriter::printParsingLogicPropertyMessage(const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(StringManipulator::trimRight(logicProperty), TAG_PARSING, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResultsIntroductionMessage() {
    ConsolePrinter::printMessageWithColouredTag(MSG_RESULTS_INTRODUCTION, TAG_RESULT, ColourCode::GREEN);
    ConsolePrinter::printColouredMessage(TAG_RESULT, ColourCode::GREEN);

    printSeparatorTag();
}

void ModelCheckingOutputWriter::printModelCheckingResultMessage(bool doesPropertyHold,
                                                                const std::string &detailedResult,
                                                                const std::string &logicProperty) {
    printLogicPropertyForResult(logicProperty);
    printResultTag();

    printModelCheckingResult(doesPropertyHold);
    printModelCheckingDetailedResult(doesPropertyHold, detailedResult);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printSuccessMessage() {
    ConsolePrinter::printColouredMessage(TAG_SUCCESS, ColourCode::GREEN);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printFailedMessage() {
    ConsolePrinter::printColouredMessage(TAG_FAILED, ColourCode::RED);
    printSeparatorTag();
}

void ModelCheckingOutputWriter::printLogicPropertyForResult(const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(StringManipulator::trimRight(logicProperty),
                                                TAG_RESULT, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResult(bool doesPropertyHold) {
    if (doesPropertyHold) {
        ConsolePrinter::printMessageWithColouredTag(MSG_LOGIC_PROPERTY_HOLDS + MSG_LOGIC_PROPERTY_HOLDS_TRUE,
                                                    TAG_RESULT, ColourCode::GREEN);
    } else {
        ConsolePrinter::printMessageWithColouredTag(MSG_LOGIC_PROPERTY_HOLDS + MSG_LOGIC_PROPERTY_HOLDS_FALSE,
                                                    TAG_RESULT, ColourCode::RED);
    }
}

void ModelCheckingOutputWriter::printModelCheckingDetailedResult(bool doesPropertyHold,
                                                                 const std::string &detailedResult) {
    if (doesPropertyHold) {
        ConsolePrinter::printMessageWithColouredTag(detailedResult, TAG_RESULT, ColourCode::GREEN);
    } else {
        ConsolePrinter::printMessageWithColouredTag(detailedResult, TAG_RESULT, ColourCode::RED);
    }
}

void ModelCheckingOutputWriter::printResultTag() {
    ConsolePrinter::printColouredMessage(TAG_RESULT, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printSeparatorTag() {
    ConsolePrinter::printColouredMessage(TAG_SEPARATOR, ColourCode::GREEN);
}


// Constants
const std::string ModelCheckingOutputWriter::TAG_INTRO      = "[ INTRO    ]";
const std::string ModelCheckingOutputWriter::TAG_INIT       = "[ INIT     ]";
const std::string ModelCheckingOutputWriter::TAG_PARSING    = "[ PARSING  ]";
const std::string ModelCheckingOutputWriter::TAG_EXECUTE    = "[ EXECUTE  ]";
const std::string ModelCheckingOutputWriter::TAG_RESULT     = "[ RESULT   ]";
const std::string ModelCheckingOutputWriter::TAG_SUCCESS    = "[ SUCCESS  ]";
const std::string ModelCheckingOutputWriter::TAG_FAILED     = "[ FAILED   ]";
const std::string ModelCheckingOutputWriter::TAG_SEPARATOR  = "[==========]";

const std::string ModelCheckingOutputWriter::MSG_INTRO_NAME                         = "Mudi 0.6.126 (Multidimensional model checker)";
const std::string ModelCheckingOutputWriter::MSG_INTRO_COPYRIGHT                    = "Copyright Ovidiu Pârvu 2014";
const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_TYPE          = "Model checker type: ";
const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_PARAMETERS    = "Parameters:         ";
const std::string ModelCheckingOutputWriter::MSG_INTRO_CONTACT                      = "For more details, recommendations or suggestions feel free to contact me at <ovidiu.parvu[AT]gmail.com>.";

const std::string ModelCheckingOutputWriter::MSG_INIT_EXECUTION_PARAMETERS  = "Multidimensional model checking input parameters";
const std::string ModelCheckingOutputWriter::MSG_INIT_LOGIC_PROPERTIES_PATH = "Logic properties input file:          ";
const std::string ModelCheckingOutputWriter::MSG_INIT_TRACES_FOLDER_PATH    = "Spatial-temporal traces input folder: ";
const std::string ModelCheckingOutputWriter::MSG_INIT_EXTRA_EVALUATION_TIME = "Extra evaluation time:                ";

const std::string ModelCheckingOutputWriter::MSG_PARSING_INTRODUCTION           = "I am starting to parse logic properties...";

const std::string ModelCheckingOutputWriter::MSG_START_MODEL_CHECKING_EXECUTION = "I am starting the execution of the model checkers...";

const std::string ModelCheckingOutputWriter::MSG_RESULTS_INTRODUCTION           = "I have finished evaluating the logic properties and will display the results...";

const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS          = "The logic property holds: ";
const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS_TRUE     = "TRUE";
const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS_FALSE    = "FALSE";
