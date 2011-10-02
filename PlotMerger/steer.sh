for i in `seq 28 42`; do
	./merger -b full.forCHARM.ET2.v2 -v 2.28.$i -d -r .06e
	cd $FITTER
	fitter full.forCHARM.ET2.v2 2.28.$i .06e
	cd $PLOTMERGER
	./merger -b full.forCHARM.ET2.v2 -v 2.28.$i -d -r .06e -s
#	./plotter full.forCHARM 2.28.$i .06e.scaled
done

#./merger -b full.forCHARM -v 2.28.9 -d -r .06e
#./merger -b full.forCHARM -v 2.28.10 -d -r .06e 

#./merger -b full.forCHARM.ET2 -v 2.29.2 -d -r .06e -s
#./merger -b full.forCHARM.ET2 -v 2.29.3 -d -r .06e -s

#./plotter full.forCHARM 2.28.2 .06e.scaled
#./plotter full.forCHARM.ET2 2.28.3 .06e.scaled
#./plotter full.forCHARM.ET2 2.28.7 .06e.scaled

