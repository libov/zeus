#----------------------------------------------------------------
# a small script to calculate the luminosity of ZEUS data
# V. Libov, last modified: 21 March 2011
#----------------------------------------------------------------
yearlist=['03','04', '05' ,'06e','06p']
#specifierlist=['', 'mvd_', 'mvdstt_']
#specifierlist=['']
specifierlist=['mvd_']
#specifierlist=['mvdstt_']
configFile='runperiods.cfg'
#----------------------------------------------------------------
prefix='http://www-zeus.desy.de/physics/lumi/'
suffix='validruns.html'
#----------------------------------------------------------------

import urllib

print '\n**** Welcome to ZEUS Luminosity Calculator ****\n'

class	subtrigger:
    def __init__(self, firstRun, lastRun, trigTitle, trigType):
        self._firstRun = int(firstRun)
        self._lastRun = int(lastRun)
        self._trigTitle = trigTitle
        self._lumiPCAL = 0
        self._lumiSPEC = 0
        self._trigType = trigType

def conv(arg):
    return str(arg/1000.)

# list containing objects of subtrigger class
subtriggerList=[]
# configuration file containing info for each subtrigger
runperiods = open (configFile, 'r')

# loop over lines in the configuration file
for tmpline in	runperiods:
    line=tmpline.split()
    if len(line) != 4: continue
    if line[0]=='#': continue
    (tTitle, fRun, lRun, tType)=line
    # create an object of subtrigger class
    instance=subtrigger(fRun, lRun, tTitle, tType)
    # and insert it into the list
    subtriggerList.append(instance)

list=['YEAR', 'TAKE', 'PCAL_TOTAL','SPEC_TOTAL', 'PCAL_LOW','SPEC_LOW', 'PCAL_HIGH','SPEC_HIGH', 'PCAL_UNKN','SPEC_UNKN']
for a in list:
	print a.ljust(10),
print '\n'

for year in yearlist:
	for specifier in specifierlist:
		lumi_pcal_total=0.
		lumi_spec_total=0.
		lumi_pcal_low=0.
		lumi_spec_low=0.
		lumi_pcal_high=0.
		lumi_spec_high=0.
		lumi_pcal_unkn=0.
		lumi_spec_unkn=0.
		#first
		url=prefix+'lumi'+year+'/'+specifier+suffix
		file=urllib.urlopen(url)
		takeline=False
		for tmpline in file:
			line=tmpline.split()
			if line==[]: continue
			if len(line) == 1: continue
			if line[1] == 'run':
				takeline=True
				continue
			if not takeline: continue
			#print line
			run=int(line[1])
			pcal=float(line[3])
			spec=float(line[4])
			trig=line[6]
			low=False
			high=False
			if	trig.find('LOW') != -1: low=True
			if	trig.find('HIGH') != -1: high=True
			#print str(run), low, high
			lumi_pcal_total+=pcal
			lumi_spec_total+=spec
			for	subtrigger in subtriggerList:
				tType=subtrigger._trigType
				if (run>=subtrigger._firstRun) and (run<=subtrigger._lastRun):
					if (low and (tType=='LOW')) or (high and (tType=='HIGH')) or (tType=='none'):
						subtrigger._lumiPCAL+=pcal
						subtrigger._lumiSPEC+=spec
			if low:
				lumi_pcal_low+=pcal
				lumi_spec_low+=spec
			elif high:
				lumi_pcal_high+=pcal
				lumi_spec_high+=spec
			else:
				lumi_pcal_unkn+=pcal
				lumi_spec_unkn+=spec

		list=[year, specifier, conv(lumi_pcal_total), conv(lumi_spec_total), conv(lumi_pcal_low), conv(lumi_spec_low)]
		list.append(conv(lumi_pcal_high))
		list.append(conv(lumi_spec_high))
		list.append(conv(lumi_pcal_unkn))
		list.append(conv(lumi_spec_unkn))
		for a in list:
			print a.ljust(10),
		print ''


# print luminosities trigger by trigger

# print number of triggers that were processed (i.e. the number if triggers in the config file)
length=len(subtriggerList)
print '\n'+str(length)+' subtriggers read from '+configFile+'\n'

# print header
list=['TRIGGER', 'FIRSTRUN', 'LASTRUN', 'TYPE', 'PCAL', 'SPEC']
for a in list:
    print a.ljust(10),
print '\n'

# print actual values
for t in subtriggerList:
    list=[t._trigTitle, str(t._firstRun), str(t._lastRun), str(t._trigType), str(t._lumiPCAL/1000.), str(t._lumiSPEC/1000.)]
    for a in list:
        print a.ljust(10),
    print ''
