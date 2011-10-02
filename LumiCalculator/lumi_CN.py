#!/usr/bin/python

# import some modules
import urllib
import ROOT
from optparse import OptionParser

# define options
parser = OptionParser()
parser.add_option("-f", "--filename", dest="filename", help="name of the directory containing zarahoutput file from ntupleanalyzer execution; note that the path is hardcoded in this script, please check")
parser.add_option("-y", "--year", dest="year", help="period of the studied sample; appears as a suffix in the URL.")

# get option values
(options, args) = parser.parse_args()
filename = options.filename
year = options.year

# open the file
#filenamepreffix = '/data/zenith226a/libov/analysis/data/zarahJobs/analysis/full.forCHARM_2.5.LUMI_2.6.LUMI/'
filenamepreffix = '/data/zenith226a/libov/analysis/data/zarahJobs/analysis/inclusive_2.27/'
filenamesuffix = '/stdout'
file = open(filenamepreffix+filename+filenamesuffix, 'r')

# open the URL
prefix='http://www-zeus.desy.de/physics/lumi/'
suffix='validruns.html'
specifier=''
urlfile = urllib.urlopen(prefix+'lumi'+year+'/'+specifier+suffix)

# define structure that will hold data for a single Run ("Run"-structure)
class   Run:
    def __init__(self, events):
        # number of events in this entity
        self._Nevents = events
        # luminosity given by PCAL for this number of events
        self._lumiPCAL = -1.0
        # luminosity given by SPEC
        self._lumiSPEC = -1.0

# create maps containing "Run"- structures (simply Run in the following)
# there are two maps for input from CN (with/without EVTAKE&MVDTAKE)
# and one map for input from URL
runlist_CN_ALL={}
runlist_CN_EVTAKE_MVDTAKE={}
runlist_URL={}

# loop over output file from Ntupleanalyzer that was launched with SetOnlyCalculateEventsPerRun (true);
for tmpline in file:

    # check that line contains the necessary information about the run
    line = tmpline.split()
    if len(line) == 0: continue
    if line[0] != "Run:": continue

    # get the necessry information: the run number and number of events with/without EVTAKE&MVDTAKE requierement
    run = int(line[1])
    nevents_ALL = float(line[3])
    nevents_EVTAKE_MVDTAKE = float(line[5])

    # create a Run-object for events without EVTAKE&MVDTAKE reqierement and store to a map
    Run_CN_ALL = Run(nevents_ALL)
    runlist_CN_ALL[run] = Run_CN_ALL

    # create a Run-object for events with EVTAKE&MVDTAKE reqierement and store to a map
    Run_CN_EVTAKE_MVDTAKE = Run(nevents_EVTAKE_MVDTAKE)
    runlist_CN_EVTAKE_MVDTAKE[run] = Run_CN_EVTAKE_MVDTAKE

# open the URL, loop and fill similar map

# help variable
takeline=False
# actual loop
for tmpline in urlfile:
    # check it's the line we need (a little bit tricky)
    line=tmpline.split()
    if line==[]: continue
    if len(line) == 1: continue
    if line[1] == 'run':
        takeline=True
        continue
    if not takeline: continue

    # pick the needed information (run number, number of events, PCAL and SPEC luminosity, trigger string)
    run=int(line[1])
    nevents = float(line[2])
    lumiPCAL=float(line[3])
    lumiSPEC=float(line[4])
    trig=line[6]

    # define whether this run was with high or low trigger
    low=False
    high=False
    if  trig.find('LOW') != -1: low=True
    if  trig.find('HIGH') != -1: high=True
#    if (low or high):
        #lumi_pcal_total_URL += lumi_pcal
        #lumi_spec_total_URL += lumi_spec
    # create a Run
    Run_URL = Run(nevents)
    Run_URL._lumiPCAL = lumiPCAL
    Run_URL._lumiSPEC = lumiSPEC
    # store it to a map
    runlist_URL[run] = Run_URL

# now loop over runs from URL

lumi_pcal_total_URL = 0
lumi_spec_total_URL = 0
lumi_pcal_total_CN_ALL = 0
lumi_spec_total_CN_ALL = 0
lumi_pcal_total_CN_EVTAKE_MVDTAKE = 0
lumi_spec_total_CN_EVTAKE_MVDTAKE = 0

for RUN in runlist_CN_ALL:
    # get Run objects for each case from the map for this run
    Run_CN_ALL = runlist_CN_ALL[RUN]
    Run_CN_EVTAKE_MVDTAKE = runlist_CN_EVTAKE_MVDTAKE[RUN]
    Run_URL = runlist_URL[RUN]
    
    ratio_nevents_CN_vs_URL = Run_CN_ALL._Nevents/Run_URL._Nevents
#    if (ratio_nevents_CN_vs_URL > 1): 
#        print 'CN:', Run_CN_ALL._Nevents, 'URL:', Run_URL._Nevents, '(printed if there are more events in CN than in URL)'

    # get luminosity for this run for all events
    Run_CN_ALL._lumiPCAL = ratio_nevents_CN_vs_URL * Run_URL._lumiPCAL
    Run_CN_ALL._lumiSPEC = ratio_nevents_CN_vs_URL * Run_URL._lumiSPEC

    # get luminosity for this run for events with EVTAKE/MVDTAKE events
    ratio_nevents_CN_vs_URL = Run_CN_EVTAKE_MVDTAKE._Nevents/Run_URL._Nevents
    Run_CN_EVTAKE_MVDTAKE._lumiPCAL = ratio_nevents_CN_vs_URL * Run_URL._lumiPCAL
    Run_CN_EVTAKE_MVDTAKE._lumiSPEC = ratio_nevents_CN_vs_URL * Run_URL._lumiSPEC

    lumi_pcal_total_CN_ALL += Run_CN_ALL._lumiPCAL
    lumi_spec_total_CN_ALL += Run_CN_ALL._lumiSPEC
    lumi_pcal_total_CN_EVTAKE_MVDTAKE += Run_CN_EVTAKE_MVDTAKE._lumiPCAL
    lumi_spec_total_CN_EVTAKE_MVDTAKE += Run_CN_EVTAKE_MVDTAKE._lumiSPEC
    lumi_pcal_total_URL += Run_URL._lumiPCAL
    lumi_spec_total_URL += Run_URL._lumiSPEC

# finally print the results
#print "\n\nThe following luminosities have been evaluated (PCAL/SPEC)"
print "".ljust(20), "PCAL".ljust(20), "SPEC".ljust(20)
print "URL:".ljust(20), str(lumi_pcal_total_URL).ljust(20), str(lumi_spec_total_URL).ljust(20)
print "CN ALL:".ljust(20), str(lumi_pcal_total_CN_ALL).ljust(20), str(lumi_spec_total_CN_ALL).ljust(20)
print "CN EVTAKE/MVDTAKE:".ljust(20), str(lumi_pcal_total_CN_EVTAKE_MVDTAKE).ljust(20), str(lumi_spec_total_CN_EVTAKE_MVDTAKE).ljust(20)

# print a good-bye message
# print "Finished successfully"
print "\n"