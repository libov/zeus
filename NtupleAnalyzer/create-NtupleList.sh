#!/bin/bash
#-----------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------
# creates file with list of available common ntuple files
# input:
# argument1 ($1) : year (available options are listed in the config/samplelist.cfg)
# argument2 ($2) : common ntuple version
# argument3 ($3) : data or mc
# argument3 ($4) : details (optional - if MC)
# output: text file ./$OUTPUT_FILE
#
# Vladyslav Libov, libov@mail.desy.de
#-----------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------
COMMON_NTUPLES_PATH_PREFIX=/acs/z/ntup
#-----------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------
YEAR=$1
COMMON_NTUPLES_VERSION=$2
COMMON_NTUPLES_SUFFIX=$3/root
OUTPUT_FILE=filelists/$3$1$2$4.txt
DETAILS=$4
#-----------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------
echo 'Creating ntuple filelist'

FULL_PATH=$COMMON_NTUPLES_PATH_PREFIX/$YEAR/$COMMON_NTUPLES_VERSION/$COMMON_NTUPLES_SUFFIX
echo "common ntuples are taken from $FULL_PATH"

if [ -e "$OUTPUT_FILE" ]
then
  echo "$OUTPUT_FILE exists. Skipping this sample"
  exit 0
fi

FILE_NUMBER=`ls -1 $FULL_PATH | grep "$DETAILS" | wc -l`
echo $FILE_NUMBER files found in this sample
#echo "ls -1 $FULL_PATH | grep "$DETAILS
for file in `ls -1 $FULL_PATH | grep "$DETAILS"`
do
	echo zeus:/$FULL_PATH/$file >> $OUTPUT_FILE
done

echo 'done'
echo ''
#-----------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------