#for i in `seq 9 17`; do
#	./fitter full 2.23.$i
#done

#for scale in {0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5}; do
#./fitter full 2.15.2 .0405e06e07p $scale > logs/2.15.2_lfscaled_$scale.log
#cd ../TXMLparser
#./compare_fit_results > logs/2.15.2_bin1_lfscaled_$scale.txt
#cd $FITTER
#done

fitter full.forCHARM 2.28.9 .06e
fitter full.forCHARM 2.28.10 .06e

#fitter full.forCHARM.ET2 2.29.2 .06e
#fitter full.forCHARM.ET2 2.29.3 .06e


