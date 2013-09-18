EXPECTED_ARGS=2

if [ $# -ne $EXPECTED_ARGS ]
then
	echo "Usage: `basename $0` {binning} {version}"
	echo "Example:"
	echo $0 full.forCHARM 2.31.1
	echo will process 2.31.1
	exit -1
fi

BINNING=$1
VERSION=$2

./merger -b $BINNING -v $VERSION -d
cd $FITTER
./fitter -b $BINNING -v $VERSION -d 
cd $PLOTMERGER
./merger -b $BINNING -v $VERSION -d -s
