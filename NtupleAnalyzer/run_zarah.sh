#!/bin/bash
echo entered $0
source ROOT.sh
source env.sh
echo PATH= $PATH
tar -zxvf NtupleAnalyzer.tar.gz
cd NtupleAnalyzer
ln -s ../libxerces-c.so.27.0 libxerces-c.so
make clean && make analysis && make createMiniNtuples
mv analysis createMiniNtuples ../
mv reweightingFunction/weightTables/* ../
cd ../
rm NtupleAnalyzer.tar.gz
tar -zcvf NtupleAnalyzer.tar.gz NtupleAnalyzer
rm -rf NtupleAnalyzer
ln -s libxerces-c.so.27.0 libxerces-c.so.27
echo content of the job spool:
ls -l
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
analysis  -t2 -f2 -p8 -q2 -o2 -g0 -bfull.forCHARM -v2.29.3