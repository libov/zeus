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
for i in  2 5 9 10 11 13
  do
  if [ -e $mailfile ]; then
    rm $mailfile
  fi
  if [ $i = 1 ]; then
    nametag=8_5
    q2min="7.99"
    q2max="8.01"
    xmin="0.000499"
    xmax="0.000501"
  fi
  if [ $i = 2 ]; then
    nametag=8_10
    q2min="7.99"
    q2max="8.01"
    xmin="0.00099"
    xmax="0.00101"
  fi
  if [ $i = 3 ]; then
    nametag=12_20
    q2min="11.99"
    q2max="12.01"
    xmin="0.00199"
    xmax="0.00201"
  fi
  if [ $i = 4 ]; then
    nametag=60_10
    q2min="59.99"
    q2max="60.01"
    xmin="0.00099"
    xmax="0.00101"
  fi
  if [ $i = 5 ]; then
    nametag=12_1_7
    q2min="11.99"
    q2max="12.01"
    xmin="0.000165"
    xmax="0.000175"
  fi
  if [ $i = 6 ]; then
    nametag=25_4
    q2min="24.99"
    q2max="25.01"
    xmin="0.000399"
    xmax="0.000401"
  fi
  if [ $i = 7 ]; then
    nametag=60_10
    q2min="59.99"
    q2max="60.01"
    xmin="0.000999"
    xmax="0.001001"
  fi
  if [ $i = 8 ]; then
    nametag=110_50
    q2min="109.99"
    q2max="110.01"
    xmin="0.00499"
    xmax="0.00501"
  fi
  if [ $i = 9 ]; then
    nametag=110_100
    q2min="109.99"
    q2max="110.01"
    xmin="0.0099"
    xmax="0.0101"
  fi
  if [ $i = 10 ]; then
    nametag=200_30
    q2min="199.9"
    q2max="200.1"
    xmin="0.00299"
    xmax="0.00301"
  fi
  if [ $i = 11 ]; then
    nametag=200_200
    q2min="199.9"
    q2max="200.1"
    xmin="0.0199"
    xmax="0.0201"
  fi
  if [ $i = 12 ]; then
    nametag=650_100
    q2min="649.9"
    q2max="650.1"
    xmin="0.0099"
    xmax="0.0101"
  fi
  if [ $i = 13 ]; then
    nametag=650_400
    q2min="649.9"
    q2max="650.1"
    xmin="0.0399"
    xmax="0.0401"
  fi
  outfile=hvqdis_$nametag.dat
  echo "2               ! 0:LO  1:NLO CORRECTIONS ONLY (NO LO)  2:FULL NLO RESULT" > $outfile
  echo "5               ! RENORMALIZATION SCALE" >> $outfile
  echo "5               ! FACTORIZATION   SCALE 1: 4m2  2: Q2 3: Q2+4M2 4:Q2+4M2+pt2  5: pt2+4m2 6: pt2+m2" >> $outfile
  echo "5               ! 1: CTEQ4F3  2: CTEQ5F3  3: GRV94  4: GRV98 5: CTEQ5F4   6: CTEQ5L 7: ZEUS-PDf 8: ZEUS-PDF up 9: ZEUS-PDfdown" >> $outfile
  echo "500000          ! NUMBER OF VEGAS POINTS FOR LO     500000" >> $outfile
  echo "2               ! NUMBER OF VEGAS ITERATIONS FOR LO" >> $outfile
  echo "80000           ! NUMBER OF VEGAS POINTS FOR NLO    800000" >> $outfile
  echo "4               ! NUMBER OF VEGAS ITERATIONS FOR NLO" >> $outfile
  echo "2               ! 1: CHARM 2: BOTTOM" >> $outfile
  echo "4.75D0          ! QUARK MASS mb=4.75" >> $outfile
  echo "920D0           ! ENERGY OF PROTON" >> $outfile
  echo "27.5D0          ! ENERGY OF INCIDENT ELECTRON" >> $outfile
  echo $q2min"D0         ! Q2 MIN" >> $outfile
  echo $q2max"D0         ! Q2 MAX" >> $outfile
  echo $xmin"D0      ! XBJ MIN" >> $outfile
  echo $xmax"D0      ! XBJ MAX" >> $outfile
   echo $q2min"D0         ! Q2 MIN" > $mailfile
   echo $q2max"D0         ! Q2 MAX" >> $mailfile
   echo $xmin"D0      ! XBJ MIN" >> $mailfile
   echo $xmax"D0      ! XBJ MAX" >> $mailfile
  echo "0.05D0          ! Y MIN" >> $outfile
  echo "0.80D0          ! Y MAX" >> $outfile
  echo "2.5D0           ! |ETA| MAX" >> $outfile
  echo "0.0D0           ! PT MIN" >> $outfile
  echo "1500000D0       ! PT MAX" >> $outfile
  echo "0               ! 0: NO FRAGMENTATION  1: PETERSON FRAGMENTATION <-- should be off" >> $outfile
  echo "1               ! 0: NO SL DECAY  1: SL DECAY (ONLY WITH IFRAG=1)" >> $outfile
  echo "0.0035D0        ! EPSION FOR PETERSON FRAGMENTATION" >> $outfile
  echo "0.2205D0        ! HADRONIZATION FRACTION (ONLY USED WHEN FRAGMENTING) 0.235D0" >> $outfile
  echo "5.278D0         ! MASS OF HEAVY HADRON 5.01" >> $outfile
  echo "1               ! ren scale factor" >> $outfile
  echo "0               ! 0: Peterson 1:Pet (2:Bowler) 3:Kart (4:Lund) 5:SLD 6:F1 7:P8" >> $outfile
  echo "1               ! SL routine 1: Vincenzo 2: Felix  3: Felix dir only 4: charm" >> $outfile
  echo "'f2b_"$nametag".histos'   ! PREF FOR OUTPUT FILES" >> $outfile

run_hvqdis.sh $nametag
grep "Total      sig (pb):" output/ben_$nametag.out >> $mailfile
mail -s "HVQDIS: $nametag completed" ${USER}@mail.desy.de < $mailfile
done
