###############################################################################
#
# steering script to generate large monte carlo samples (ZEUS)
# working horse: sample class; see implementation in sample.py
# usage: create an instance of sample class and call its _generate() method
# current version works for charm/beauty resolved DIS, can be modified for any generatora
#
# constructor in the current version:
# mySample=sample(flavour, Q2Min, SubProcess, Luminosity, Config)
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
#
#
# author: Vladyslav Libov, DESY
# 10 December 2009
# libov@mail.desy.de
#
# modified 17 January 2010: function convert(trigger) is now a method of the sample class
#
###############################################################################
from sample import sample


#----------------------------------- helper functions section -------------------------------
# ----- calculates cross sections according to parameters in csFile.cfg -----
def evaluateCrossSections():

	csFile=open('csFile.cfg','r')
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
		print Flavour+', Q^2> '+Q2Min+' GeV^2, resAE'
		x._NumberOfEventsCrossSect=10000
		x._calculateCrossSect()

		y=sample(Flavour, Q2Min, "C", 0, '')
		y._verbose=False
		y._NumberOfEventsCrossSect=10000
		print Flavour+', Q^2> '+Q2Min+' GeV^2, resC'
		y._calculateCrossSect()

# -------------------------  where-data-go-table   ---------------------------#
def	getPathPrefix(confFileSuffix):
	if confFileSuffix=='.C.0304p':    return '/data/zenith226a/libov/amadeus/events/rgap30/'
	if confFileSuffix=='.C.06e':      return '/data/zenith226a/libov/amadeus/events/rgap30/'
	if confFileSuffix=='.AE.03p_06e': return '/data/zenith226a/libov/amadeus/events/rgap30/'

	if confFileSuffix=='.C.05e.part1': return '/data/zenith234b/libov/'
	if confFileSuffix=='.C.05e.part1a': return '/data/zenith234b/libov/'
	if confFileSuffix=='.C.05e.part2': return '/data/zenith234b/libov/'

	# default value
	return '/data/zenith226a/libov/amadeus/events/rgap30/'





# --------- main function - generates events for a given config file ----------
def processConfigFile(confFileSuffix):
	configFile=open('config'+confFileSuffix+'.cfg','r')
	for tmpline in configFile:
		line=tmpline.split()
		if line==[]: continue
		if line[0]=='STOP': break
		if not (line[0]=='charm' or line[0]=='beauty'):				#to enable comments in config file
			continue
		Flavour=line[0]
		SubProcess=line[1]
		Q2Min=line[2]
		Luminosity=line[3]
		Trigger=line[4]
		print Flavour+', subprocess: '+SubProcess+', Q^2> '+Q2Min+' GeV^2'
		x=sample(Flavour, Q2Min, SubProcess, float(Luminosity), Trigger)
		x._NumberOfEventsCrossSect=1
		x._LetterToAppend='submit.letter'+confFileSuffix
		x._OutputPathPrefix=getPathPrefix(confFileSuffix)
		x._generate()
		#x._InfoForWeb(web)

# ------------------------------ steering part---------------------------------
# defines which config file to process and calls processConfigFile(confFileSuffix) function

print ''
print '............... Large MC samples generator ...............'
print ''

#evaluateCrossSections()
#confFileSuffixList=['.C.0304p', '.C.05e.part1', '.C.05e.part1a', '.C.05e.part2', '.C.06e', '.AE.03p_06e']
confFileSuffixList=['.test']


web=open('web.info','w')
for confFileSuffix in confFileSuffixList:
	processConfigFile(confFileSuffix)


print ''
print '........................ COMPLETE .........................'
print ''


