# this script runs the fitter with different values of light flavour scaling (default analysis: no scaling, i.e. factor of 1)
# and copies the XML fit result file to a separate file, for later usage with systematics.cxx/TSystematics.cxx
# V.Libov, 17 May 2012

# a list of scaling factor values that are used
scaling_factor=( 0.5 0.6 0.7 0.8 0.9 1.0 1.1 1.2 1.3 1.4 1.5 )

# loop over array, perform the fit for each value of the lf scaling factor
for i in "${scaling_factor[@]}"
do
echo $i
    # charm
    ./fitter -b full.forCHARM -v 2.52.2 -d --scale_lf --lf_scaling_factor $i
    mv $DATABASE_PATH/results.full.forCHARM2.52.2.0405e06e07p.v02.true05e06e0607p.xml $DATABASE_PATH/results.full.forCHARM2.52.2_lf_scaling_$i.0405e06e07p.v02.true05e06e0607p.xml
    # beauty
    ./fitter -b full -v 2.53.2 -d --scale_lf --lf_scaling_factor $i
    mv $DATABASE_PATH/results.full2.53.2.0405e06e07p.v02.true05e06e0607p.xml $DATABASE_PATH/results.full2.53.2_lf_scaling_$i.0405e06e07p.v02.true05e06e0607p.xml
done
