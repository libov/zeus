#!/bin/bash
#
#	Run HVQDIS with different steering files
#	by PK
#
#echo '*** Running HVQDIS 1.4 ***'
source env.sh
if [ -z $1 ]; then
  echo usage $0 nametag
  exit
else
  tag=$1
fi
output=${tag}.out
time ./hvq.x < hvqdis_${tag}.dat > ${output}
#echo '*** Bye ***'
#
#
#
# 
