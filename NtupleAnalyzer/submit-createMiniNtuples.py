#!/usr/bin/python
#
# Vladyslav Libov, libov@mail.desy.de
#
""" @package submit-createMiniNtuples.py
Submits creation jobs to zarah

Loops over lines in config file. For each sample creates ntuple list using create-NtupleList.sh.
Evaluates number of events using -c option of createMiniNtuples executable. Calculates number
of needed jobs so that each contains not more than 25M events and submits them.
"""
DEFAULT_FILE_NAME="samples.mc.db"
#DEFAULT_FILE_NAME="samples.data.db"
#NeventsJob=25000000
NeventsJob=20000000
#--------------------------------------------------------------
import os
import commands
import sys
from optparse import OptionParser
#
#-------------------GLOBAL VARIABLES---------------------------
year=''
CNversion=''
dataOrMC=''
lumi=''
details=''
SampleName=''
#-------------------HELPING FUNCTIONS--------------------------
def	run_zarah(first, last):
	"""Creates script that starts up a createMiniNtuples program on zarah and submits job"""
	os.remove('run_zarah.sh')
	run_script=open('run_zarah.sh', 'w')
	run_script.write("#!/bin/bash\n")
        run_script.write("source .profile\n")
	run_script.write("source env.sh\n")
	command = 'createMiniNtuples '+' -s '+SampleName+' -f '+str(first)+' -l '+str(last)
	run_script.write(command+'\n')
	run_script.close()
	commands.getoutput("chmod a+x run_zarah.sh")
	command="zarah-jobsub -q M -s run_zarah.sh createMiniNtuples create-NtupleList.sh "+ANALYSIS+"/env.sh "+SampleName+".txt /afs/desy.de/user/l/libov/.profile"
	#print command
	output = commands.getoutput(command)
	print output, '\n'

# -------------------------  main part  -----------------------
# --- handle options ----
parser = OptionParser()
parser.add_option("-c", "--configfile", dest="configFile", default=DEFAULT_FILE_NAME, help="Name of the configuration file. Contains list of samples to be processed. Should be under $DATABASE_PATH environmental variable")

(options, args) = parser.parse_args()
configFileName=options.configFile
print "\n\n******************************************************\n";
print "* Welcome to ZEUS Common Ntuple analysis framework   *\n";
print "* Step 0: submission of jobs to create mini ntuples  *\n";
print "******************************************************\n\n";
print 'config file selected: '+configFileName

#-- loop over lines in the config File
ANALYSIS=os.environ['ANALYSIS']
print ANALYSIS
DATABASE_PATH=os.environ['DATABASE_PATH']
configFile=open(DATABASE_PATH+'/'+configFileName, 'r')

for tmpline in configFile:
	line=tmpline.split()
	if line==[]: continue
	if line[0]=='#': continue
	year=line[0]
	CNversion=line[1]
	dataOrMC=line[2]
	lumi=line[3]
	if len(line)>4:	details=line[4]
	SampleName=dataOrMC+year+CNversion+details
	print 'Currently analyzing sample: '+SampleName+'\n'
	# -- calculate number of events --
	print commands.getoutput("sh create-NtupleList.sh "+year+" "+CNversion+" "+dataOrMC+" "+details)
	command = 'createMiniNtuples -s '+SampleName+' -c'
	print command
	output=commands.getoutput(command)
	print output
	tmp=open('tmp/'+SampleName+'.tmp', 'w')
	tmp.write(output)
	tmp.close()
	tmp=open('tmp/'+SampleName+'.tmp', 'r')
	for line in tmp:
		line_list=line.split()
		Nevents=-1
		if ( len(line_list) != 2): continue
		if line_list[0]=='Nevents=':
			Nevents=int(line_list[1])
			#print str(Nevents)+ ' events here'
			break
	if (Nevents == -1):
		print 'Not able to determine number of events in the chain'
		sys.exit(1)
	# -- prepare directories
	commands.getoutput("sh prepare-dir.sh "+SampleName)
	# --- spread sample analysis over several jobs and submit ---
	NumberOfBigJobs, RemainingEvents=divmod(Nevents, NeventsJob)
	print '\nGoing to generate '+str(NumberOfBigJobs)+' jobs with '+str(NeventsJob)+' events and 1 job with '+str(RemainingEvents)+' events\n'
	# submit jobs with max number of events
	for job in range(NumberOfBigJobs):
		#print job
		first=job*NeventsJob
		last=(job+1)*NeventsJob
		run_zarah(first, last)
	# and one remaining job
	first=NumberOfBigJobs*NeventsJob
	last=first+RemainingEvents
	run_zarah(first, last)


