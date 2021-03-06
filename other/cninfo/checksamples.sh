#!/bin/bash

# arguments handling
SAMPLELIST=$1.samples
FILENAME=$1.files
CN_VERSION=$2

# main body of the script
# remove old file
rm -f $FILENAME
# loop over samples, and output list of files for each of the sample 
# using cninfo command
while read SAMPLE
do
	echo "** " $SAMPLE " **" >> $FILENAME
        echo >> $FILENAME
        cninfo -v $CN_VERSION -s $SAMPLE -t root -f >> $FILENAME
        echo >> $FILENAME
        echo >> $FILENAME
done < $SAMPLELIST
