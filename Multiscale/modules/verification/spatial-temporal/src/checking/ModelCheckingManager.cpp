#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingManager.hpp"

using namespace multiscale::verification;


ModelCheckingManager::ModelCheckingManager(const std::string &logicPropertyFilepath,
                                           const std::string &tracesFolderPath,
                                           unsigned long extraEvaluationTime) {
    initialise(logicPropertyFilepath, tracesFolderPath, extraEvaluationTime);
}

ModelCheckingManager::~ModelCheckingManager() {
    abstractSyntaxTrees.clear();
    logicProperties.clear();
    modelCheckers.clear();
}

void ModelCheckingManager::runFrequencyModelChecking() {
    createFrequencyModelCheckers();
    runModelCheckingTasks();
}

void ModelCheckingManager::initialise(const std::string &logicPropertyFilepath,
                                      const std::string &tracesFolderPath,
                                      unsigned long extraEvaluationTime) {
    this->extraEvaluationTime = extraEvaluationTime;
    this->evaluationStartTime = std::chrono::system_clock::now();

    initialiseLogicProperties(logicPropertyFilepath);
    initialiseTraceReader(tracesFolderPath);
}

void ModelCheckingManager::initialiseLogicProperties(const std::string &logicPropertiesFilepath) {
    logicProperties = logicPropertyReader.readLogicPropertiesFromFile(logicPropertiesFilepath);
}

void ModelCheckingManager::initialiseTraceReader(const std::string &tracesFolderPath) {
    traceReader = SpatialTemporalDataReader(tracesFolderPath);
}

void ModelCheckingManager::parseLogicProperties() {
    auto it = logicProperties.begin();

    while (it != logicProperties.end()) {
        if (parseLogicPropertyAndPrintMessages(*it)) {
            it++;
        } else {
            it = logicProperties.erase(it);
        }
    }
}

void ModelCheckingManager::createFrequencyModelCheckers() {
    for (const auto &abstractSyntaxTree : abstractSyntaxTrees) {
        modelCheckers.push_back(
            std::shared_ptr<ModelChecker>(new FrequencyModelChecker(abstractSyntaxTree))
        );
    }
}

void ModelCheckingManager::runModelCheckingTasks() {
    parseLogicProperties();
    runModelCheckers();
    outputModelCheckersResults();
}

bool ModelCheckingManager::parseLogicPropertyAndPrintMessages(const std::string &logicProperty) {
    ModelCheckingOutputWriter::printParsingLogicPropertyMessage(logicProperty);

    bool isParsedSuccessfully = parseLogicProperty(logicProperty);

    printParsingMessage(isParsedSuccessfully);

    return isParsedSuccessfully;
}

bool ModelCheckingManager::parseLogicProperty(const std::string &logicProperty) {
    try {
        return isValidLogicProperty(logicProperty);
    } catch (const InvalidInputException &ex) {
        ExceptionHandler::printErrorMessage(ex);

        return false;
    }
}

bool ModelCheckingManager::isValidLogicProperty(const std::string &logicProperty) {
    AbstractSyntaxTree syntaxTree;

    parser.setLogicalQuery(logicProperty);

    if (parser.parse(syntaxTree)) {
        abstractSyntaxTrees.push_back(syntaxTree);

        return true;
    }

    return false;
}

void ModelCheckingManager::printParsingMessage(bool isParsingSuccessful) {
    if (isParsingSuccessful) {
        ModelCheckingOutputWriter::printSuccessMessage();
    } else {
        ModelCheckingOutputWriter::printFailedMessage();
    }
}

void ModelCheckingManager::runModelCheckers() {
    runModelCheckersForCurrentlyExistingTraces();
    runModelCheckersAndRequestAdditionalTraces();
}

void ModelCheckingManager::runModelCheckersForCurrentlyExistingTraces() {
    bool continueEvaluation = true;

    while ((continueEvaluation) && (traceReader.hasNext())) {
        SpatialTemporalTrace trace = traceReader.getNextSpatialTemporalTrace();

        runModelCheckersForTrace(trace, continueEvaluation);
    }
}

void ModelCheckingManager::runModelCheckersForTrace(const SpatialTemporalTrace &trace,
                                                    bool &continueEvaluation) {
    continueEvaluation = false;

    for (auto &modelChecker : modelCheckers) {
        if (modelChecker->acceptsMoreTraces()) {
            modelChecker->evaluate(trace);

            continueEvaluation = true;
        }
    }
}

void ModelCheckingManager::runModelCheckersAndRequestAdditionalTraces() {
    while ((isEvaluationTimeRemaining()) && (areUnfinishedModelCheckingTasks())) {
        waitBeforeRetry();
        updateTraceReader();
        runModelCheckersForCurrentlyExistingTraces();
    }
}

bool ModelCheckingManager::isEvaluationTimeRemaining() {
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = (currentTime - evaluationStartTime);

    double nrOfMinutes = ((elapsedSeconds.count()) / NR_SECONDS_IN_ONE_MINUTE);

    return (nrOfMinutes < extraEvaluationTime);
}

bool ModelCheckingManager::areUnfinishedModelCheckingTasks() {
    for (const auto &modelChecker : modelCheckers) {
        if (modelChecker->requiresMoreTraces()) {
            return true;
        }
    }

    return false;
}

void ModelCheckingManager::waitBeforeRetry() {
    std::this_thread::sleep_for(std::chrono::seconds(TRACE_INPUT_REFRESH_TIMEOUT));
}

void ModelCheckingManager::updateTraceReader() {
    traceReader.refresh();
}

void ModelCheckingManager::outputModelCheckersResults() {
    for (auto i = 0; i < modelCheckers.size(); i++) {
        ModelCheckingOutputWriter::printModelCheckingResultMessage(
            modelCheckers[i]->doesPropertyHold(),
            modelCheckers[i]->getDetailedResults(),
            logicProperties[i]
        );
    }
}


// Constants

const unsigned long ModelCheckingManager::TRACE_INPUT_REFRESH_TIMEOUT   = 30;
const unsigned long ModelCheckingManager::NR_SECONDS_IN_ONE_MINUTE      = 60;
