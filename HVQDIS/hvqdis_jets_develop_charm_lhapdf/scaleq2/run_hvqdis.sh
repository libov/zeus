
#!/usr/bin/bash
#
#	Run HVQDIS with different steering files
#	by PK
#
#echo '*** Running HVQDIS 1.4 ***'
if [ -z $1 ]; then
  echo usage $0 nametag
  exit
else
  tag=$1
fi
output=ben_${tag}.out
time ./hvqben.x < hvqdis_${tag}.dat > ${output}
mv ${output} ./output/
histoname=`grep histos hvqdis_${tag}.dat | awk -F \' '{print $2}'`
mv $histoname ./Histograms/
#echo '*** Bye ***'
#
#
#
# 
