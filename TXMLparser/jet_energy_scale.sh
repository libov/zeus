#!/bin/bash
# 1, 13, 21, 30, 37 - inclusive
# 2 - 12 eta
# 14 - 20 Et
# 22 - 29 Phi 
# 31 - 36 xda
# 38 - 45 q2da
# 46 - 63 double differential
rm jet_energy_scale_plots/*
let COUNTER=0
for i in {14..20}
do
    jet_energy_scale $i $COUNTER >> jet_energy_scale_plots/results
    let "COUNTER += 1"
done
# also for inclusive bin
jet_energy_scale 1 999 >> jet_energy_scale_plots/results
