###############################################################################################
#
# Steering script to generate large monte carlo samples for ZEUS
# "Working horse": sample class (implemented in sample.py)
# Usage: 1. create an instance of sample class 2. call its _generate() method
# Current version works for charm/beauty resolved/BGF DIS; in principle
# can be modified for any generator.
#
# Constructor in the current version:
# mySample = sample (flavour, Q2Min, SubProcess, Luminosity, Trigger)
#	flavour="charm" or "beauty"
#  SubProcess= "C" or "AE" - see Rapgap manual & cards.template
#  Config - string describing funnel/trigger/vertex used; see _convert() method of sample class;
#           used as a prefix to filenames
#
#	To generate events:
#     mySample._generate()
#
#  This will
#    * generate test job to calculate cross section
#    * calculate number of events according to desired luminosity
#    * generate events
#    * create special file that containes information to be put to web page of this sample(s).
#      This file is used as an input to makewww.py script
#
#	Pay attention to:
#		* getOutputPathPrefix(confFileSuffix) function - specifies where events are written
#
# author: Vladyslav Libov, DESY
# 10 December 2009
# libov@mail.desy.de
#
# modified 17 January 2010: function convert(trigger) is now a method of the sample class
#
###############################################################################################

from sample import sample
import shutil
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-f", "--webinfofile", dest="webInfoFileName", default="default.web.info", help="specify file name for output webinfo file")
parser.add_option("-p", "--pathwebinfofile", dest="webInfoPath", default="/data/zenith226a/libov/amadeus/events/rgap30/web.info.files/", help="specify path to the output webinfo file")
parser.add_option("-c", "--configfileSuffix", dest="confFileSuffix", default=".test", help="specify suffix of input config file")
(options, args) = parser.parse_args()

# ------------------------------------- options section ------------------------------------
NumberOfEventsCrossSect = 100000
shouldEvaluateCrossSections = False
#csFile=open('csFile.cfg','r')
#csFile=open('csFileBGF.cfg','r')
#--------------------------------------------------------------------------------------------

#----------------------------------- helper functions section -------------------------------

# ----- calculates cross sections according to parameters in csFile.cfg -----
def evaluateCrossSections():
	for tmpline in csFile:
		line=tmpline.split()
		if line==[]: continue
		if line[0]=='STOP': break
		if not (line[0]=='charm' or line[0]=='beauty'):
			continue
		Flavour=line[0]
		Q2Min=line[1]

		x=sample(Flavour, Q2Min, "AE", 0, '')
		x._verbose=False
		x._NumberOfEventsCrossSect=10000
		print Flavour+', Q^2> '+Q2Min+' GeV^2, resAE'
		x._calculateCrossSect()

		y=sample(Flavour, Q2Min, "C", 0, '')
		y._verbose=False
		y._NumberOfEventsCrossSect=10000
		print Flavour+', Q^2> '+Q2Min+' GeV^2, resC'
		y._calculateCrossSect()

		z=sample(Flavour, Q2Min, "BGF", 0, '')
		z._verbose=True
		z._NumberOfEventsCrossSect=10000
		print Flavour+', Q^2> '+Q2Min+' GeV^2, BGF'
		z._calculateCrossSect()

# ----------------------------  where-data-go-table   ------------------------------#
def	getOutputPathPrefix(confFileSuffix):
	if confFileSuffix=='.C.0304p':    return '/data/zenith226a/libov/amadeus/events/rgap30/'
	if confFileSuffix=='.C.06e':      return '/data/zenith226a/libov/amadeus/events/rgap30/'
	if confFileSuffix=='.AE.03p_06e': return '/data/zenith226a/libov/amadeus/events/rgap30/'

	if confFileSuffix=='.C.05e.part1': return '/data/zenith234b/libov/'
	if confFileSuffix=='.C.05e.part1a': return '/data/zenith234b/libov/'
	if confFileSuffix=='.C.05e.part2': return '/data/zenith234b/libov/'

	# default value
	return '/data/zenith226a/libov/amadeus/events/rgap30/'

# ------------- main function - generates events for a given config file -------------
def processConfigFile(confFileSuffix):
	configFile=open('config'+confFileSuffix+'.cfg','r')
	for tmpline in configFile:
		line=tmpline.split()
		if line==[]: continue
		if line[0]=='STOP': break
		if not (line[0]=='charm' or line[0]=='beauty'):				# to enable any comments in config file
			continue
		Flavour=line[0]
		SubProcess=line[1]
		Q2Min=line[2]
		Luminosity=line[3]
		Trigger=line[4]
		print Flavour+', subprocess: '+SubProcess+', Q^2> '+Q2Min+' GeV^2'
		x = sample(Flavour, Q2Min, SubProcess, float(Luminosity), Trigger)
		x._NumberOfEventsCrossSect=NumberOfEventsCrossSect
		x._LetterToAppend='submit.letter'+confFileSuffix		# For each entry in the config file there will be a separate
																				# submission letter file. In addition, content of this submission letter
																				# will be appended to file specified by this variable (will be created
																				# if does not exist). There will be one such file per config file.

		x._OutputPathPrefix=getOutputPathPrefix(confFileSuffix)
		x._generate()
		x._InfoForWeb(webInfoFile)
		#x._InfoForWebAfter(webInfoFile)
# -------------------------------- steering part------------------------------------

print ''
print '............... Large MC samples generator ...............'
print ''

if shouldEvaluateCrossSections:
	evaluateCrossSections()

webInfoFile=open('webinfo','w')

processConfigFile(options.confFileSuffix)
webInfoFile.close()
webInfoFile = open('webinfo','r')
webInfo = webInfoFile.read()
webInfoFile.close()

webInfoFileTotal=open(options.webInfoPath+options.webInfoFileName,'a')
webInfoFileTotal.write(webInfo)
webInfoFileTotal.close()

print ''
print '........................ COMPLETED .........................'
print ''
