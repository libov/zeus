EXPECTED_ARGS=4

if [ $# -ne $EXPECTED_ARGS ]
then
	echo "Usage: `basename $0` {binning} {version} {start} {stop}"
	echo "Example:"
	echo $0 full.forCHARM 2.31 1 7
	echo will process 2.31.1 till 2.31.7
	exit -1
fi

BINNING=$1
VERSION=$2
START=$3
STOP=$4

for i in `seq $START $STOP`; do
	./merger -b $BINNING -v $VERSION.$i -d
	cd $FITTER
	./fitter -b $BINNING -v $VERSION.$i -d 
	cd $PLOTMERGER
	./merger -b $BINNING -v $VERSION.$i -d -s
done
