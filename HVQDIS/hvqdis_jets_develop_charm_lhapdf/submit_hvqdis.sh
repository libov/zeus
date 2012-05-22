# This is a wrapper script to run the HVQDIS program for NLO QCD predictions
# of heavy flavour jet production at HERA and heavy flavour contributions to F2 structure function
# Vladyslav Libov, April 2012, libov@mail.desy.de
# Modified:

# selects a file with q2-x grid definition
Q2X_GRID_FILE=./q2_x_grid.txt

# creates a file which is unique for this submission and can be used later
METAFILE=meta_`date | awk '{print $2 $3 "_" $6 "_" $4}' `.txt
echo writing metadata to $METAFILE

rm -f $METAFILE
touch $METAFILE

# queues
QUEUE_F2=M
QUEUE_XSECT=L

#---------------------------------------------------------------------------------------#
#-------------------------------  Function definitions  --------------------------------#
#---------------------------------------------------------------------------------------#

# sets default settings
function setDefaults()
{
    NORDER=2                    #!0:BORN  1:NLO  2:SUM
    ISCALER=3                   #!SEE SUBROUTINE MSCALE FOR DEFINITIONS
    ISCALEF=3                   #!SEE SUBROUTINE MSCALE FOR DEFINITIONS
    IPDF=300000                 #!1,2
    NPTS0=1000000               #!NUMBER OF VEGAS POINTS FOR LO
    ITS0=5                      #!NUMBER OF VEGAS ITERATIONS FOR LO
    NPTS1=1000000               #!NUMBER OF VEGAS POINTS FOR NLO
    ITS1=10                     #!NUMBER OF VEGAS ITERATIONS FOR NLO
    IQUARK=1                    #!1:CHARM  2:BOTTOM
    XM=1.5                      #!QUARK MASS
    EPRO=920                    #!LAB FRAME PROTON ENERGY
    EIEL=27.5                   #!LAB FRAME ELECTRON ENERGY
    Q2MIN=5.                    #!Q2 MIN
    Q2MAX=1000.                 #!Q2 MAX
    XMIN=0.                     #!XBJ MIN
    XMAX=1.                     #!XBJ MAX
    YMIN=0.02                   #!Y MIN
    YMAX=0.7                    #!Y MAX
    ETAMAX=100000               #!ETAMAX
    PTMIN=0                     #!PTMIN
    PTMAX=1500000               #!PTMAX
    IFRAG=0                     #!0: NO FRAG  1: FRAG
    ISL=0                       #!0: NO SL DECAY  1: SL DECAY
    EPS=0.0035                  #!EPSILON FOR PETERSON
    HFRAC=0.2205                #!HADRONIZATION FRACTION
    XMD=2.01                    #!MASS OF HADRON
    SCALFA=1                    #! ren scale factor
    TCFRAG=0                    #! TC's fragmentation functions
    TCSL=1                      #! TC's semi-leptonic functions
    PREF='histograms.histos'    #!OUTPUT FILE PREFIX STRING
    IRUNEM=1                    #!1: ALPHAEM RUNNING 0: NOT
    IFL=1                       #!1: COMPUTE ALL 0: FL=0 2: ONLY FL
}

# creates an HVQDIS config file and writes the current settings
function createConfigFile()
{
    config_file='hvqdis.dat'
    rm -f $config_file
    touch $config_file
    
    echo -e $NORDER"\t\t\t!0:BORN  1:NLO  2:SUM" >> $config_file
    echo -e $ISCALER"\t\t\t!SEE SUBROUTINE MSCALE FOR DEFINITIONS" >> $config_file
    echo -e $ISCALEF"\t\t\t!SEE SUBROUTINE MSCALE FOR DEFINITIONS" >> $config_file
    echo -e $IPDF"\t\t\t!1,2" >> $config_file
    echo -e $NPTS0"\t\t\t!NUMBER OF VEGAS POINTS FOR LO" >> $config_file
    echo -e $ITS0"\t\t\t!NUMBER OF VEGAS ITERATIONS FOR LO" >> $config_file
    echo -e $NPTS1"\t\t\t!NUMBER OF VEGAS POINTS FOR NLO" >> $config_file
    echo -e $ITS1"\t\t\t!NUMBER OF VEGAS ITERATIONS FOR NLO" >> $config_file
    echo -e $IQUARK"\t\t\t!1:CHARM  2:BOTTOM" >> $config_file
    echo -e $XM"\t\t\t!QUARK MASS" >> $config_file
    echo -e $EPRO"\t\t\t!LAB FRAME PROTON ENERGY" >> $config_file
    echo -e $EIEL"\t\t\t!LAB FRAME ELECTRON ENERGY" >> $config_file
    echo -e $Q2MIN"\t\t\t!Q2 MIN" >> $config_file
    echo -e $Q2MAX"\t\t\t!Q2 MAX" >> $config_file
    echo -e $XMIN"\t\t\t!XBJ MIN" >> $config_file
    echo -e $XMAX"\t\t\t!XBJ MAX" >> $config_file
    echo -e $YMIN"\t\t\t!Y MIN" >> $config_file
    echo -e $YMAX"\t\t\t!Y MAX" >> $config_file
    echo -e $ETAMAX"\t\t\t!ETAMAX" >> $config_file
    echo -e $PTMIN"\t\t\t!PTMIN" >> $config_file
    echo -e $PTMAX"\t\t\t!PTMAX" >> $config_file
    echo -e $IFRAG"\t\t\t!0: NO FRAG  1: FRAG" >> $config_file
    echo -e $ISL"\t\t\t!0: NO SL DECAY  1: SL DECAY" >> $config_file
    echo -e $EPS"\t\t\t!EPSILON FOR PETERSON" >> $config_file
    echo -e $HFRAC"\t\t\t!HADRONIZATION FRACTION" >> $config_file
    echo -e $XMD"\t\t\t!MASS OF HADRON" >> $config_file
    echo -e $SCALFA"\t\t\t! ren scale factor" >> $config_file
    echo -e $TCFRAG"\t\t\t! TC's fragmentation functions" >> $config_file
    echo -e $TCSL"\t\t\t! TC's semi-leptonic functions" >> $config_file
    echo -e $PREF"\t!OUTPUT FILE PREFIX STRING" >> $config_file
    echo -e $IRUNEM"\t\t\t!1: ALPHAEM RUNNING 0: NOT" >> $config_file
    echo -e $IFL"\t\t\t!1: COMPUTE ALL 0: FL=0 2: ONLY FL" >> $config_file
}

# creates a wrapper script and submits the job to ZARAH
function submitJob()
{
    wrapper=run_zarah.sh
    rm -f $wrapper
    touch $wrapper
    chmod 777 $wrapper
    
    echo 'source env.sh' >> $wrapper
    echo 'time ./hvq.x < hvqdis.dat > hvqdis.out' >> $wrapper
    echo 'grep "Total      sig (pb):" hvqdis.out > total_cross_section.txt' >> $wrapper

    # submit the job
    job_id=`zarah-jobsub -q $queue -s $wrapper exe/hvq.x $ANALYSIS/env.sh hvqdis.dat | awk '{print $2}'`

    # write data about this job to metafile
    echo $job_id $q2 $x $Q2MIN $Q2MAX $XMIN $XMAX $counter >> $METAFILE
}

#---------------------------------------------------------------------------------------#
#----------------------------  The main part of the script  ----------------------------#
#---------------------------------------------------------------------------------------#

# create a list of strings; each string corresponds to a separate setting for uncertainty evaluation
uncertainty_evaluation=("XM=1.5" "XM=1.35 && IPDF=300029" "XM=1.65 && IPDF=300030" "ISCALER=13 && ISCALEF=13 && IPDF=300031" "ISCALER=23 && ISCALEF=23 && IPDF=300032" "IPDF=300001" "IPDF=300002")

# this counter corresponds to a command (setting) in the array
counter=1

# loop over elements of the array
for i in "${uncertainty_evaluation[@]}"
do
    # set all variables to their default values
    setDefaults
    # now change some variables according to the commands given in the array
    eval $i

    # create a configuration file with current settings
    createConfigFile

    # submit a job with defaults, i.e. for differential xsect. evaluation
    q2=0
    x=0
    queue=$QUEUE_XSECT
    submitJob

    # read q2-x grid file
    while read line; do
        # continue only if the line is not empty
        if [ -n "$line" ]; then

            # skip if the line is commented
            first_token=`echo "$line" | awk '{print $1}'`
            if [[ "$first_token" == '#'* ]]
            then
                continue
            fi

            # get the Q2 and x values
            q2=`echo "$line" | awk '{print $1}'`
            x=`echo "$line" | awk '{print $2}'`

            # calculate small volumes around these Q2, x points as +- 1%
            Q2MIN=`echo "scale=10; $q2*0.99" | bc`
            Q2MAX=`echo "scale=10; $q2*1.01" | bc`
            XMIN=`echo "scale=10; $x*0.99" | bc`
            XMAX=`echo "scale=10; $x*1.01" | bc`
            
            # set also FL to 0 as needed for F2 evaluation
            IFL=0

            # switch off alpha_em running for F2 evaluation
            IRUNEM=0

            # and remove Y cuts
            YMIN=0
            YMAX=1

            # create a configuration file with current settings
            createConfigFile
            
            # set ZARAH queue
            queue=$QUEUE_F2
            # submit a job
            submitJob

        fi
    done < "$Q2X_GRID_FILE" # end loop over q2-x grid file

    #increment the counter (counts uncertainty evaluation settings)
    counter=$(($counter+1))

done # end loop over elements of the array

# clean up
rm -f $config_file
rm -f $wrapper
