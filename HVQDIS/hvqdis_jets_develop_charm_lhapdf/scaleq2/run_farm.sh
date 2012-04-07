#!/bin/bash

if [ -d output ]; then
  :
else
  mkdir output
fi
if [ -d Histograms ]; then
  :
else
  mkdir Histograms
fi

mailfile="mail.temp"
#defaults:
q2min=4.
q2max=100000.
xmin=0.
xmax=1.
bmassa=4
bmassb=75
ymin=0.05
ymax=0.7
ptjet=0.0
renscale=2
facscale=2
frag=0.0035
for m in 2
do
  if [ $m = 1 ]; then
    bmassa=4
    bmassb=5
  fi
  if [ $m = 2 ]; then
    bmassa=4
    bmassb=75
  fi
  if [ $m = 3 ]; then
    bmassa=5
    bmassb=0
  fi
  for i in 2 3 4
  do
    if [ -e $mailfile ]; then
      rm $mailfile
    fi
    touch $mailfile
    if [ $i = 1 ]; then
# use the defaults
    :
    fi
    if [ $i = 2 ]; then
      bmassa=4
      bmassb=75
      renscale=2
      facscale=2
    fi
    if [ $i = 3 ]; then
      bmassa=4
      bmassb=75
      renscale=7
      facscale=7
    fi
    if [ $i = 4 ]; then
      bmassa=4
      bmassb=75
      renscale=5
      facscale=5
    fi
    if [ $i = 5 ]; then
      renscale=7
      facscale=7
      bmassa=4
      bmassb=5
    fi
    if [ $i = 6 ]; then
      renscale=7
      facscale=7
      bmassa=5
      bmassb=0
    fi
    if [ $i = 7 ]; then
      bmassa=4
      bmassb=75
      renscale=27
      facscale=7
    fi
    if [ $i = 8 ]; then
      bmassa=4
      bmassb=75
      renscale=7
      facscale=27
    fi
    if [ $i = 9 ]; then
:
    fi
    if [ $i = 10 ]; then
:
    fi
    if [ $i = 11 ]; then
:
    fi
    if [ $i = 12 ]; then
:
    fi
    if [ $i = 13 ]; then
      q2min="39.9"
      q2max="40.1"
      xmin="0.00195"
      xmax="0.00205"
    fi
    if [ $i = 14 ]; then
      q2min="59.8"
      q2max="60.2"
      xmin="0.00195"
      xmax="0.00205"
    fi
    if [ $i = 15 ]; then
      q2min="79.8"
      q2max="80.2"
      xmin="0.00195"
      xmax="0.00205"
    fi
    if [ $i = 16 ]; then
      q2min="109."
      q2max="111."
      xmin="0.00195"
      xmax="0.00205"
    fi
    if [ $i = 17 ]; then
      q2min="119."
      q2max="121."
      xmin="0.00195"
      xmax="0.00205"
    fi
    if [ $i = 18 ]; then
      q2min="54.8"
      q2max="55.2"
      xmin="0.00495"
      xmax="0.00505"
    fi
    if [ $i = 19 ]; then
      q2min="59.8"
      q2max="60.2"
      xmin="0.00495"
      xmax="0.00505"
    fi
    if [ $i = 20 ]; then
      q2min="119."
      q2max="111."
      xmin="0.00495"
      xmax="0.00505"
    fi
    if [ $i = 21 ]; then
      q2min="209."
      q2max="211."
      xmin="0.00495"
      xmax="0.00505"
    fi
    if [ $i = 22 ]; then
      q2min="189."
      q2max="191."
      xmin="0.0129"
      xmax="0.0131"
    fi
    if [ $i = 23 ]; then
      q2min="199."
      q2max="201."
      xmin="0.0129"
      xmax="0.0131"
    fi
    if [ $i = 24 ]; then
      q2min="399."
      q2max="401."
      xmin="0.0129"
      xmax="0.0131"
    fi
    if [ $i = 25 ]; then
      q2min="599."
      q2max="601."
      xmin="0.0129"
      xmax="0.0131"
    fi
    if [ $i = 26 ]; then
      q2min="619."
      q2max="621."
      xmin="0.0129"
      xmax="0.0131"
    fi
    if [ $i = 27 ]; then
      q2min="619."
      q2max="621."
      xmin="0.0319"
      xmax="0.0321"
    fi
    if [ $i = 28 ]; then
      q2min="649."
      q2max="651."
      xmin="0.0319"
      xmax="0.0321"
    fi
    if [ $i = 29 ]; then
      q2min="679."
      q2max="681."
      xmin="0.0319"
      xmax="0.0321"
    fi
    if [ $i = 30 ]; then
      q2min="249."
      q2max="251."
      xmin="0.00495"
      xmax="0.00505"
    fi
    if [ $i = 31 ]; then
      q2min="699."
      q2max="701."
      xmin="0.0129"
      xmax="0.0131"
    fi
    if [ $i = 32 ]; then
      q2min="13.9"
      q2max="14.1"
      xmin="0.000195"
      xmax="0.000205"
    fi
# standard bins
    if [ $i = 101 ]; then
      q2min="4."
      q2max="25."
      xmin="0.0000316"
      xmax="0.000316"
    fi
    if [ $i = 102 ]; then
      q2min="4."
      q2max="25."
      xmin="0.000316"
      xmax="0.001"
    fi
    if [ $i = 103 ]; then
      q2min="4."
      q2max="25."
      xmin="0.001"
      xmax="0.00316"
    fi
#
    if [ $i = 201 ]; then
      q2min="25."
      q2max="100."
      xmin="0.000316"
      xmax="0.001"
    fi
    if [ $i = 202 ]; then
      q2min="25."
      q2max="100."
      xmin="0.001"
      xmax="0.00316"
    fi
    if [ $i = 203 ]; then
      q2min="25."
      q2max="100."
      xmin="0.00316"
      xmax="0.01"
    fi
#
    if [ $i = 301 ]; then
      q2min="100."
      q2max="3162."
      xmin="0.001"
      xmax="0.00316"
    fi
    if [ $i = 302 ]; then
      q2min="100."
      q2max="3162."
      xmin="0.00316"
      xmax="0.01"
    fi
    if [ $i = 303 ]; then
      q2min="100."
      q2max="3162."
      xmin="0.01"
      xmax="0.0316"
    fi
    nametag=${q2min}-${q2max}_${xmin}-${xmax}_r${renscale}_f${facscale}_m${bmassa}.${bmassb}
    outfile=hvqdis_$nametag.dat
    echo "2               ! 0:LO  1:NLO CORRECTIONS ONLY (NO LO)  2:FULL NLO RESULT" > $outfile
    echo $renscale"       ! RENORMALIZATION SCALE" >> $outfile
    echo $facscale"       ! FACTORIZATION   SCALE 1: 4m2  2: Q2 3: Q2+4M2 4:Q2+4M2+pt2  5: pt2+4m2 6: pt2+m2 7: (Q2+M2+pt2)/4" >> $outfile
    echo "5              ! 1: CTEQ4F3  2: CTEQ5F3  3: GRV94  4: GRV98 5: CTEQ5F4   6: CTEQ5L 7: ZEUS-PDf 8: ZEUS-PDF up 9: ZEUS-PDfdown" >> $outfile
    echo "500000          ! NUMBER OF VEGAS POINTS FOR LO     500000" >> $outfile
    echo "2               ! NUMBER OF VEGAS ITERATIONS FOR LO" >> $outfile
    echo "80000           ! NUMBER OF VEGAS POINTS FOR NLO    800000" >> $outfile
    echo "NUMBER OF VEGAS POINTS FOR NLO: 80000 " >> $mailfile
    echo "4               ! NUMBER OF VEGAS ITERATIONS FOR NLO" >> $outfile
    echo "2               ! 1: CHARM 2: BOTTOM" >> $outfile
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
    echo "'f2b_"$nametag".histos'   ! PREF FOR OUTPUT FILES" >> $outfile
  
    run_hvqdis.sh $nametag
    grep "Total      sig (pb):" output/ben_$nametag.out >> $mailfile
    grep "muon+jet+cone sig (pb):" output/ben_$nametag.out >> $mailfile
    mail -s "HVQDIS: $nametag completed" ${USER}@mail.desy.de < $mailfile
  done
done
