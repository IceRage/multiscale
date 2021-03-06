#!/bin/bash

# If any errors are encountered, then the script will exit
set -e;

# Defining the constants for the script
MOVIE_FRAME_RATE=1;
MOVIE_FLAGS="-same_quant -r ${MOVIE_FRAME_RATE}"

OUT_FOLDER=out;

INPUT_FOLDER=${OUT_FOLDER}/input;
SCRIPT_FOLDER=${OUT_FOLDER}/script;
MOVIE_FOLDER=${OUT_FOLDER}/movie;
IMG_FOLDER=${OUT_FOLDER}/img;

# If the required parameters are not provided, then exit
# REQUIRED PARAMETERS:
#   - Path to the csv file
#   - The number of entities
#   - The maximum number of entities on a grid position at the same time
#   - The number of rows/height (D1)
#   - The number of columns/width (D2)
if [ $# -ne 5 ]; 
then
    echo "Incorrect number of parameters provided."
    echo
    echo "Usage:";
    echo "    RectangularGeometryEntityViewer <path_to_csv_file> <nr_of_entities> <max_pileup> <height> <width>";

    exit 1;
fi

# Get the parameters in separate variables
csvFile=$1;
nrOfEntities=$2;
maxPileup=$3;
height=$4;
width=$5;

# Get the basename of the file, the filename and the extension
csvFileBasename=`basename ${csvFile}`;
csvFilename=${csvFileBasename%.*};
csvExtension=$([[ "$csvFileBaseName" = *.* ]] && echo ".${csvFileBasename##*.}" || echo '');

# Create a folder name for this execution according to time
currentDate=`date +"%F-%T"`;
folderName="${csvFilename}_${currentDate}";

# Inform user of the next action
echo "Creating the output directories...";

# Start the timer for measuring the total execution time
startTime=$(date +%s.%N);

# Create all the required folders for this execution
mkdir -p ${INPUT_FOLDER}/${folderName}
mkdir -p ${SCRIPT_FOLDER}/${folderName}
mkdir -p ${MOVIE_FOLDER}/${folderName}
mkdir -p ${IMG_FOLDER}/${folderName}

# Copy a backup of the csv file to its corresponding input folder
cp ${csvFile} ${INPUT_FOLDER}/${folderName}/${csvFilename}.bak

# Copy the part of the csv file with necessary information to its corresponding input folder
sed 's/^[;,:\t ]\+//g' <${csvFile} | sed 's/[;,:\t ]\+/,/g' | tail -n +2 > ${INPUT_FOLDER}/${folderName}/${csvFileBasename}

# Inform user of the next action
echo "Generating the input files from the .csv file...";

# Run the program for converting the ".csv" file to "Number of time points" input files
# for the MapCartesianToScript program
bin/RectangularMapEntityCsvToInputFiles --input-file "${INPUT_FOLDER}/${folderName}/${csvFileBasename}" --nr-entities ${nrOfEntities} --max-pileup ${maxPileup} --height $height --width $width --output-file "${INPUT_FOLDER}/${folderName}/${csvFilename}";

# Inform user of the next action
echo "Generating in parallel the gnuplot script for each of the input files...";

# Run the MapCartesianToScript for converting each of the generated input files
# into gnuplot scripts
ls -1 ${INPUT_FOLDER}/${folderName}/*.in | parallel bin/MapCartesianToScript --input-file {} --output-file ${SCRIPT_FOLDER}/${folderName}/{/.}

# Inform user of the next action
echo "Running in parallel gnuplot and taking as input each one of the generated scripts...";

# Run gnuplot on each of the generated scripts from the script folder and ignore warnings
cd ${IMG_FOLDER}/${folderName};

ls -1 ../../../${SCRIPT_FOLDER}/${folderName} | parallel gnuplot ../../../${SCRIPT_FOLDER}/${folderName}/{} 2>/dev/null;

cd ../../../;

# Inform user of the next action
echo "Generating the movie from the images...";

# Generate the movie
avconv ${MOVIE_FLAGS} -f image2 -i ${IMG_FOLDER}/${folderName}/${csvFilename}_%d.png ${MOVIE_FOLDER}/${folderName}/${csvFilename}.mp4

# Print end message
echo "The movie was generated successfully.";

# End the timer for measuring the total execution time
endTime=$(date +%s.%N);

# Print the total execution time
echo 
echo "Total execution time: " $(echo "${endTime} - ${startTime}" | bc) " seconds.";
