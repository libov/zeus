#!/bin/bash

# v04
echo '*****     Luminosities for CN version v04  ***********'

echo "05e"
./lumi_CN.py -f 0001712326 -y 05

echo "06e"
./lumi_CN.py -f 0001712327 -y 06e

echo "06p"
./lumi_CN.py -f 0001712328 -y 06p

echo "07p"
./lumi_CN.py -f 0001712329 -y 06p

# v02
echo '*****     Luminosities for CN version v02  ***********'

echo "05e"
./lumi_CN.py -f 0001712282 -y 05

echo "06e"
./lumi_CN.py -f 0001712283 -y 06e

echo "06p"
./lumi_CN.py -f 0001712284 -y 06p

echo "07p"
./lumi_CN.py -f 0001712285 -y 06p
