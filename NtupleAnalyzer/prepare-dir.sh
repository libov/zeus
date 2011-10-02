#! /bin/bash
# $1 = sample name
SAMPLE_NAME=$1
echo 'preparing output directory'
if [ -d $MINI_NTUPLES_PATH/$SAMPLE_NAME ]
then
	echo $MINI_NTUPLES_PATH/$SAMPLE_NAME exists. Moving to  $MINI_NTUPLES_PATH/$SAMPLE_NAME.bak
	rm -rf $MINI_NTUPLES_PATH/$SAMPLE_NAME.bak
	mv $MINI_NTUPLES_PATH/$SAMPLE_NAME $MINI_NTUPLES_PATH/$SAMPLE_NAME.bak
fi
#mkdir $MINI_NTUPLES_PATH2/$SAMPLE_NAME
mkdir $MINI_NTUPLES_PATH/$SAMPLE_NAME
echo 'done'
echo ''
