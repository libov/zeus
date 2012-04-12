#!/bin/bash
# get the iterator(s) value for the second loop
iterator=`cat iterator`
mailfile="mail.temp"
counter=1
# first loop is for uncertainty evaluation
for m in 0 1 2 3 4 5 6
do

  # defaults settings:
  q2min=5.
  q2max=1000.
  xmin=0.
  xmax=1.
  bmassa=1
  bmassb=5
  ymin=0.02
  ymax=0.7
  ptjet=0.0
  renscale=3
  facscale=3
  frag=0.0035

  # use the defaults
  if [ $m = 0 ]; then
  :
  fi

  # mass variation
  if [ $m = 1 ]; then
    bmassb=3
  fi
  if [ $m = 2 ]; then
    bmassb=7
  fi

  # scales variation
  if [ $m = 3 ]; then
    renscale=13
  fi
  if [ $m = 4 ]; then
    renscale=23
  fi
  if [ $m = 5 ]; then
    facscale=13
  fi
  if [ $m = 6 ]; then
    facscale=23
  fi

  # second loop is for F2 evaluation in small volumes around (Q2,x) points;
  # in order to evaluate the differential cross-sections and uncertainties,
  # please select 0 here (now from the command line)
  for i in iterator
  do
    if [ -e $mailfile ]; then
      rm $mailfile
    fi
    touch $mailfile
    # default (to be used for evaluation of single and double differential 
    # cross-sections and their uncertainty)
    if [ $i = 0 ]; then
    :
    fi
    # different Q2-x points
    if [ $i = 10 ]; then
        q2min="6.49"
        q2max="6.51"
        xmin="0.000149"
        xmax="0.000151"
    fi
    if [ $i = 11 ]; then
        q2min="6.49"
        q2max="6.51"
        xmin="0.000279"
        xmax="0.000281"
    fi
    if [ $i = 12 ]; then
        q2min="11.9"
        q2max="12.1"
        xmin="0.000429"
        xmax="0.000431"
    fi
    if [ $i = 13 ]; then
        q2min="11.9"
        q2max="12.1"
        xmin="0.000649"
        xmax="0.000651"
    fi
    nametag=0${counter}_${q2min}-${q2max}_${xmin}-${xmax}_r${renscale}_f${facscale}_m${bmassa}.${bmassb}
    outfile=hvqdis_$nametag.dat
    echo "2               ! 0:LO  1:NLO CORRECTIONS ONLY (NO LO)  2:FULL NLO RESULT" > $outfile
    echo $renscale"       ! RENORMALIZATION SCALE" >> $outfile
    echo $facscale"       ! FACTORIZATION   SCALE 1: 4m2  2: Q2 3: Q2+4M2 4:Q2+4M2+pt2  5: pt2+4m2 6: pt2+m2 7: (Q2+M2+pt2)/4" >> $outfile
    echo "40650           ! 1: CTEQ4F3  2: CTEQ5F3  3: GRV94  4: GRV98 5: CTEQ5F4   6: CTEQ5L 7: ZEUS-PDf 8: ZEUS-PDF up 9: ZEUS-PDfdown" >> $outfile
    echo "50000          ! NUMBER OF VEGAS POINTS FOR LO     500000" >> $outfile
    echo "2               ! NUMBER OF VEGAS ITERATIONS FOR LO" >> $outfile
    echo "80000          ! NUMBER OF VEGAS POINTS FOR NLO    800000" >> $outfile
    echo "NUMBER OF VEGAS POINTS FOR NLO: 80000 " >> $mailfile
    echo "4               ! NUMBER OF VEGAS ITERATIONS FOR NLO" >> $outfile
    echo "1               ! 1: CHARM 2: BOTTOM" >> $outfile
    echo $bmassa"."$bmassb"D0          ! QUARK MASS mb=4.75" >> $outfile
    echo "920D0           ! ENERGY OF PROTON" >> $outfile
    echo "27.5D0          ! ENERGY OF INCIDENT ELECTRON" >> $outfile
    echo $q2min"D0         ! Q2 MIN" >> $outfile
    echo $q2max"D0         ! Q2 MAX" >> $outfile
    echo $xmin"D0      ! XBJ MIN" >> $outfile
    echo $xmax"D0      ! XBJ MAX" >> $outfile
    echo $q2min"D0         ! Q2 MIN" >> $mailfile
    echo $q2max"D0         ! Q2 MAX" >> $mailfile
    echo $xmin"D0      ! XBJ MIN" >> $mailfile
    echo $xmax"D0      ! XBJ MAX" >> $mailfile
    echo $ymin"D0          ! Y MIN" >> $outfile
    echo $ymax"D0          ! Y MAX" >> $outfile
    echo "2.5D0           ! |ETA| MAX" >> $outfile
    echo "2.5D0           ! |ETA| MAX" >> $mailfile
    echo $ptjet"D0           ! PT MIN" >> $outfile
    echo "1500000D0       ! PT MAX" >> $outfile
    echo "0               ! 0: NO FRAGMENTATION  1: PETERSON FRAGMENTATION <-- should be off" >> $outfile
    echo "1               ! 0: NO SL DECAY  1: SL DECAY (ONLY WITH IFRAG=1)" >> $outfile
    echo $frag"D0        ! EPSION FOR PETERSON FRAGMENTATION" >> $outfile
    echo "0.2205D0        ! HADRONIZATION FRACTION (ONLY USED WHEN FRAGMENTING) 0.235D0" >> $outfile
    echo "5.278D0         ! MASS OF HEAVY HADRON 5.01" >> $outfile
    echo "1               ! ren scale factor" >> $outfile
    echo "0               ! 0: Peterson 1:Pet (2:Bowler) 3:Kart (4:Lund) 5:SLD 6:F1 7:P8" >> $outfile
    echo "1               ! SL routine 1: Vincenzo 2: Felix  3: Felix dir only 4: charm" >> $outfile
    echo "'0${counter}_histograms.histos'   ! PREF FOR OUTPUT FILES" >> $outfile
    echo "1               !1: ALPHAEM RUNNING 0: NOT" >> $outfile    
    echo "0               !1: COMPUTE ALL 0: FL=0 2: ONLY FL" >> $outfile    

    run_hvqdis.sh $nametag
    grep "Total      sig (pb):" $nametag.out >> $mailfile
    grep "muon+jet+cone sig (pb):" $nametag.out >> $mailfile
    mail -s "HVQDIS: $nametag completed" ${USER}@mail.desy.de < $mailfile
  done
  #increment a counter
  counter=$(($counter+1))
done
