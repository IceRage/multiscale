#!/bin/bash

###############################################################################
#
# First of all instantiate logic property templates according to the provided 
# list of numeric state variables. Next print out for each logic property 
# template the numeric state variables for which hold the corresponding logic
# property template instance evaluates true considering the given time series
# data.
#
###############################################################################


###############################################################################
#
# Functions definitions
#
###############################################################################

# Instantiate the logic property template
function InstantiateLogicPropertyTemplate() {
    # Instantiate template for each numeric state variable
    for numericStateVariable in "${numericStateVariablesArray[@]}";
    do
        echo "${currentLogicPropertyTemplate}" | sed "s/${NUMERIC_STATE_VARIABLE_PLACEHOLDER}/{${numericStateVariable}}/g";
    done

    # Add current logic property template to array of logic property templates
    logicPropertyTemplates[${nrOfLogicPropertyTemplates}]=${currentLogicPropertyTemplate}

    # Update number of logic property templates
    nrOfLogicPropertyTemplates=$((${nrOfLogicPropertyTemplates} + 1));
}


###############################################################################
#
# Main script body
#
###############################################################################

###############################################################################
# Step 1: Command line parameters validation
###############################################################################

# Check if the number of provided input parameters is correct

if [[ $# -ne 4 ]];
then
    echo "Usage: $0 <logic-properties-templates-input-file> <numeric-state-variables-input-file> <time-series-data-input-file> <logic-properties-output-file>.";

    exit 1;
fi

# Check if the logic properties templates input file is valid

if [[ ! -f $1 ]];
then
    echo "The provided logic properties templates input file ($1) is invalid. Please change.";

    exit 1;
fi

# Check if the numeric state variables input file is valid

if [[ ! -f $2 ]];
then
    echo "The provided numeric state variables input file ($2) is invalid. Please change.";

    exit 1;
fi

# Check if the time series data input file is valid

if [[ ! -f $3 ]];
then
    echo "The provided time series data input file ($3) is invalid. Please change.";

    exit 1;
fi


###############################################################################
#
# Constants definition and variables initialisation
#
###############################################################################

# Constants definition

INFO_TAG="[ INFO     ]";
RESULT_TAG="[ RESULT   ]";

NUMERIC_STATE_VARIABLE_PLACEHOLDER="{{VAR}}";

NUMERIC_CSV_MODEL_CHECKER_SAMPLE_EXECUTABLE="/home/ovidiu/Repositories/git/multiscale/Multiscale/bin/sample/NumericCsvModelCheckerSample";

# Variables initialisation

logicPropertiesTemplatesInputFile=$1;
numericStateVariablesInputFile=$2;
timeSeriesDataInputFile=$3;
logicPropertiesOutputFile=$4;

declare -a logicPropertyTemplates;

nrOfLogicPropertyTemplates=0;
currentLogicPropertyTemplate="";


###############################################################################
# Step 2: Logic property template instantiation
###############################################################################

# Inform the user about the next step
echo "Creating instances of the logic property template(s)...";

# Read the numeric state variables from the provided input file

IFS=$'\n' && numericStateVariablesArray=($(<${numericStateVariablesInputFile})) && IFS=$'\t\n';

# Instantiate the logic properties templates

while read logicPropertyTemplateLine || [[ -n ${logicPropertyTemplateLine} ]];
do
    if [[ (${logicPropertyTemplateLine:0:1} == "#") || (-z ${logicPropertyTemplateLine}) ]];
    then
        # If the logic property template is not empty then instantiate it
        if [[ -n ${currentLogicPropertyTemplate} ]];
        then
            # Instantiate the logic property template
            InstantiateLogicPropertyTemplate

            # Clear the logic property template contents
            currentLogicPropertyTemplate="";
        fi

        # Output the logic property template line    
        echo ${logicPropertyTemplateLine};
    elif [[ ${logicPropertyTemplateLine:0:1} == "P" ]];
    then
        # Set the logic property equal to the logic property template line
        currentLogicPropertyTemplate=${logicPropertyTemplateLine};
    else
        # Add the line to the logic property template
        currentLogicPropertyTemplate="${currentLogicPropertyTemplate}${logicPropertyTemplateLine}";
    fi
done <${logicPropertiesTemplatesInputFile} >${logicPropertiesOutputFile};

# Instantiate last logic property template
if [[ -n ${currentLogicPropertyTemplate} ]];
then
    InstantiateLogicPropertyTemplate >>${logicPropertiesOutputFile};
fi


###############################################################################
# Step 3: Numeric state variable scanning
###############################################################################

# Inform the user about the next step
echo "Running the model checker...";

# Run the numeric state variable scanning procedure and store the results
modelCheckingResults=$(${NUMERIC_CSV_MODEL_CHECKER_SAMPLE_EXECUTABLE} ${timeSeriesDataInputFile} ${logicPropertiesOutputFile} 2>&1);

if [[ ${modelCheckingResults} =~ WARNING|error ]];
then
    # Inform the user that a warning or error message was issued
    echo "An error/warning message (included in the output below) was printed by the model checker. Therefore the numeric state variable scanning procedure has stopped."
    echo "";

    # Print the model checking warning/error message to the console
    echo "${modelCheckingResults}";

    exit 1;
else
    # Store only the true/false results
    IFS=$'\n' && modelCheckingResults=($(echo "${modelCheckingResults}" | egrep -o "^[TF]")) && IFS=$'\n\t'; 
fi


###############################################################################
# Step 4: Output the obtained results
###############################################################################

# Inform the user about the next step
echo "Outputting the results...";

# Create an index for recording the current model checking result index
currentModelCheckingResultIndex=0;

# Output general information about the numeric state variable scanning procedure
echo ""
echo "${INFO_TAG} Results for the numeric state variable scanning procedure";
echo "${INFO_TAG}";
echo "${INFO_TAG} Logic properties templates input file: ${logicPropertiesTemplatesInputFile}";
echo "${INFO_TAG} Numeric state variables input file:    ${numericStateVariablesInputFile}";
echo "${INFO_TAG} Time series data input file:           ${timeSeriesDataInputFile}";
echo "${INFO_TAG} Logic properties output file:          ${logicPropertiesOutputFile}";
echo "${INFO_TAG}";
echo "${INFO_TAG} Model checker executable path: ${NUMERIC_CSV_MODEL_CHECKER_SAMPLE_EXECUTABLE}";
echo "${INFO_TAG}";

# Output the considered numeric state variables
echo -n "${INFO_TAG} Considered numeric state variables:";

for numericStateVariable in ${numericStateVariablesArray[@]};
do
    echo -n " ${numericStateVariable}";
done

# Start new line and leave it blank
echo "";
echo "";

# Output the results for each logic property 
for logicPropertyTemplate in ${logicPropertyTemplates[@]};
do
    # Output logic property template
    echo -n "${RESULT_TAG} Logic property:                 "; 
    echo "${logicPropertyTemplate}";

    # Output message indicating for which numeric state variables the logic property evaluated true
    echo -n "${RESULT_TAG} Numeric state variables (true): ";

    # Output numeric state variables for which logic property holds
    for numericStateVariable in ${numericStateVariablesArray[@]};
    do
        # If the model checking result corresponding to the numeric state 
        # variable is "T" then output the numeric state variable
        if [[ ${modelCheckingResults[${currentModelCheckingResultIndex}]} == "T" ]];
        then
            echo -n "${numericStateVariable} ";
        fi

        # Increment the current model checking result index
        currentModelCheckingResultIndex=$((${currentModelCheckingResultIndex} + 1));
    done

    # Output blank lines
    echo "";
    echo "";
done
