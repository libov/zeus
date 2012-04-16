
# number of expected arguments for this script
EXPECTED_ARGS=3

# check that there are as many arguments as expected
if [ $# -ne $EXPECTED_ARGS ]; then
    echo "usage: $0 folder_to_submit iterator_for_1st_loop iterator_for_2nd_loop"
    exit -1
fi

# read command line arguments
folder=$1
iterator1=$2
iterator2=$3

# make sure there's no stuff from the previous time
rm -f $folder/iterator1
rm -f $folder/iterator2

# write user-specified iterator values to files
echo $iterator1 > $folder/iterator1
echo $iterator2 > $folder/iterator2

# submit the job
zarah-jobsub -q M -s $folder/run_farm.sh $folder/iterator1 $folder/iterator2 exe/hvq.x $folder/run_hvqdis.sh $ANALYSIS/env.sh

# clean up
rm $folder/iterator1
rm $folder/iterator2