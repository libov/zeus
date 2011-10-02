#!/usr/bin/python
#--------------------------------------------------------------
#
# V.Libov
# look into config file and run analysis.
# This script is largely overlapping with
# submit-createMiniNtuples.py - think how to optimize later
#
#--------------------------------------------------------------
import os
import commands
import sys
from optparse import OptionParser
import os.path
#-------------------GLOBAL VARIABLES---------------------------
year=''
CNversion=''
dataOrMC=''
lumi=''
details=''
SampleName=''
ZARAH_QUEUE = 'S'
binningFileSuffix = ''
histoVersionEnding = ''
#-------------------HELPING FUNCTIONS--------------------------
def	run_zarah():
	"""Creates script that will launch analysis program and submits this script to zarah"""
	os.remove('run_zarah.sh')	# => can't run several submitters in parallel!
	run_script=open('run_zarah.sh', 'w')
	run_script.write("#!/bin/bash\n")
        run_script.write("echo entered $0\n")
	run_script.write("source env.sh\n")
        run_script.write("echo PATH= $PATH\n")
        command = 'tar -zxvf NtupleAnalyzer.tar.gz'
        run_script.write(command+'\n')
        command = 'cd NtupleAnalyzer'
        run_script.write(command+'\n')
	command = 'ln -s ../libxerces-c.so.27.0 libxerces-c.so'
        run_script.write(command+'\n')
        command = 'make clean && make analysis'
        run_script.write(command+'\n')
        command = 'mv analysis ../'
        run_script.write(command+'\n')
        command = 'cd ../'
        run_script.write(command+'\n')
	command = 'ln -s libxerces-c.so.27.0 libxerces-c.so.27'
        run_script.write(command+'\n')
        command = 'rm -rf NtupleAnalyzer'
        run_script.write(command+'\n')
        # old style
	#command = 'analysis '+SampleName+' '+binningFileSuffix + ' '+histoVersionEnding   
        # new style (not finished)
        command = 'analysis '+SampleName+' '+binningFileSuffix + ' '+histoVersionEnding
	run_script.write(command+'\n')
	run_script.close()
	commands.getoutput("chmod a+x run_zarah.sh")
	command='zarah-jobsub -q '+ZARAH_QUEUE+' -s run_zarah.sh -R "defined(sl4)"  ../NtupleAnalyzer.tar.gz '+ANALYSIS+'/env.sh'+' '+SampleName+'.txt ' + '../xerces/lib*'
	print command
	output = commands.getoutput(command)
	print output

# ----------------------  M A I N  P A R T  -------------------

# parse options
parser = OptionParser()
parser.add_option("-c", "--configfile", dest="configFile", default="samples.todo.db", help="Name of the configuration file. Contains list of samples to be processed. Should be under $DATABASE_PATH environmental variable")
parser.add_option("-b", "--binningfile", dest="binningFileSuffix", default="inclusive", help="Suffix of the file containing bins definition.")
parser.add_option("-v", "--histoversion", dest="histoVersionEnding", default="v1", help="Histograms Version")

(options, args) = parser.parse_args()
configFileName=options.configFile
binningFileSuffix=options.binningFileSuffix
histoVersionEnding=options.histoVersionEnding

# print some welcome messages
print "\n\n******************************************************\n";
print "* Welcome to ZEUS Common Ntuple analysis framework   *\n";
print "* Step 2: submission of jobs to analyze mini ntuples *\n";
print "******************************************************\n\n";
print 'config file selected: ', configFileName, '\n'
print 'binning selected: ', binningFileSuffix, '\n'

# get some environment variables
ANALYSIS=os.environ['ANALYSIS']
DATABASE_PATH=os.environ['DATABASE_PATH']

# create a tarball which will be to be sent to ZARAH
print 'creating a tarball'
os.chdir(ANALYSIS)
command='rm -f NtupleAnalyzer.tar.gz'
command='tar -zcvf NtupleAnalyzer.tar.gz NtupleAnalyzer'
output = commands.getoutput(command)
print output
os.chdir(ANALYSIS+'/NtupleAnalyzer')

# full name of the configuration file (one containing info about the samples to be analysed)
configFile=open(DATABASE_PATH+'/'+configFileName, 'r')

# finally, loop over samples in the configuration file
for tmpline in configFile:
        # split the line into words
	line=tmpline.split()
        # skip if empty line
	if line==[]: continue
        # skip if this is a comment line; TODO: this now only works if there's a space after hash symbol! 
	if line[0]=='#': continue
        # now get relevant information
	year=line[0]
	CNversion=line[1]
	dataOrMC=line[2]
	lumi=line[3]
	details=''
	if len(line)>4:	details=line[4]
        # construct name of the sample
	SampleName=dataOrMC+year+CNversion+details
        # check whether a text file containing list of files belonging to this sample exists
        # and generate it in case it doesnt
	if not os.path.exists(SampleName+".txt"):
        	print 'file ' + SampleName+".txt does not exist! generating it!"
	  	print commands.getoutput("sh create-NtupleList.sh "+year+" "+CNversion+" "+dataOrMC+" "+details)
	print 'Currently analyzing sample: '+SampleName+'\n'
        # finally, submit this job
	run_zarah()
# --------------------------------------------------------------
