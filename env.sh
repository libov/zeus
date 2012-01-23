#! /bin/bash

export ANALYSIS=/data/zenith226a/libov/analysis

export DATABASE_PATH=$ANALYSIS/db

export MINI_NTUPLES_PATH_v02=/acs/users/libov/analysis/data/Minintuples/v02
export MINI_NTUPLES_PATH_v06=/acs/users/libov/analysis/data/Minintuples/v06
export MINI_NTUPLES_PATH_v06_tracking=/acs/users/libov/analysis/data/Minintuples/v06_tracking
export MINI_NTUPLES_PATH_tmp=/data/zenith234b/libov/data/Minintuples_tmp

export HISTO_PATH=/data/zenith226a/libov/data/histo
export PLOTS_PATH=/data/zenith226a/libov/data/plots

export NTUPLEANALYZER=$ANALYSIS/NtupleAnalyzer
export FITTER=$ANALYSIS/Fitter
export PLOTMERGER=$ANALYSIS/PlotMerger
export JOBS=/data/zenith226a/libov/data/zarahJobs

export TLITE=$ANALYSIS/tlite
export CLHEPINCDIR=/opt/products/CLHEP/2.0.3.1/include
export CLHEPLIBDIR=/opt/products/CLHEP/2.0.3.1/lib

export LD_LIBRARY_PATH=$CLHEPLIBDIR:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$ANALYSIS/TXMLparser:$LD_LIBRARY_PATH
