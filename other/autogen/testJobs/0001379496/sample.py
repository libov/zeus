#
# class to automatise generation of ZEUS Monte Carlo
# current implementation: rapgap resolved dis charm/beauty;
# 22.01.2010: BGF added
# see also comments in steer.py in this directory
#
# author: Vladyslav Libov, DESY
# libov@mail.desy.de
# December 2009
# modified: 17th January 2010
# modified: 22nd January 2010
#
# 22.01.2010 ---> modification of script to include BGF is needed
# 1. for resolved - needs to be tested before big generation
# 2. for bgf -

import sys
import commands
import os
import os.path
import string

class		sample:

	def __init__(self, Flavour, Q2MIN, SubProcess, Luminosity, Trigger):
		# -- common settings
		self._generatorScript='run_rapgap30'
		# print '** generator script: '+self._generatorScript
		# choose where files output files should be stored
		self._OutputPathPrefix='/data/zenith226a/libov/amadeus/events/rgap30/' 	# effectively - default value;
																										# can be set in outer world
		self._DefaultNumberOfEvents=20000
		self._NumberOfEventsCrossSect=100000			# default number of events to be generated for
																	# cross section calculation
		self._User='f15643'									# change unless you are Mr. Libov :)
		# -- control card settings
		# flavour selection
		self._Flavour=Flavour								# at the moment used only in web info stuff
		self._SubProcess=SubProcess						# at the moment used only in web info stuff
		self._IsCharm=False
		self._IsBeauty=False
		if Flavour=="charm":
			self._IsCharm=True
			Spec='cc'
		elif Flavour=="beauty":
			self._IsBeauty=True
			Spec='bb'
		else:
			print 'ERROR in sample.__init__(): wrong Flavour selected. Choose charm or beauty'
			sys.exit(1)
		self._Q2MIN=Q2MIN
		Spec=Spec+'bar.rg30.Q2g'+self._Q2MIN
		# subprocess selection
		self._IsSubProcessC=False
		self._IsSubProcessAE=False
		self._IsSubProcessBGF=False
		if	SubProcess=="C":
			self._IsSubProcessC=True
			Spec=Spec+'.resC'
		elif SubProcess=="AE":
			self._IsSubProcessAE=True
			Spec=Spec+'.resAE'
		elif SubProcess=="BGF":
			self._IsSubProcessBGF=True
			Spec=Spec+'.BGF'
		else:
			print 'ERROR in sample.__init__(): wrong Process selected. Choose C or AE'
			sys.exit(1)

		self._Luminosity=Luminosity
		self._TriggerRAW=Trigger
		self._Trigger=self._convert(Trigger)
		self._FileName=self._Trigger+'.'+self._User+'.'+Spec
		# prepare card
		self._prepareCardPreamble()
		self._FileCounter=0
		self._GeneratorCrossSection=1				# some default value
		self._verbose=True							# used in _generateJob()
		self._LetterToAppend='full.letter'		# default name for letter file to which to append info;
															# this variable is used _appendLeter()

	def	_makedir(self):
		commands.getoutput('rm -rf '+self._OutputPath)
		commands.getoutput('mkdir '+self._OutputPath)
		if os.path.exists(self._OutputPath):
			print 'files go to: '+self._OutputPath
		else:
			print 'Error! Output directory does not exist! Files will be lost!'

	def	_makeLetterFile(self):
		self._LetterFile=open(self._OutputPathPrefix+'submit.letters/'+self._FileName+'.letter','w')
		self._LetterFile.write('INFO: '+self._OutputPath+self._FileName+'.info\n\n')

	def _prepareSteerSpec(self):
		# process
		self._cardPreamble.write('C-- Subprocess type\n')
		self._cardPreamble.write('C\t18 - resolved photon processes\n')
		self._cardPreamble.write("C\t1200 - use HERACLES for eq -> e'q'\n")
		self._cardPreamble.write("C\t1400 - use HERACLES for HQ production via BGF : eg -> e'QQ-bar\n")
		if self._IsSubProcessBGF:
			self._cardPreamble.write('RAPGAP-IPRO 1400\n')
		if self._IsSubProcessC or self._IsSubProcessAE:
			self._cardPreamble.write('RAPGAP-IPRO 18\n')

		if self._IsCharm:
			IHFLA=4
			if self._IsSubProcessC:
				comment='C-- Generate cg -> cg'
				NFLQCDC=4
				PT2CUT='1.0'
			if self._IsSubProcessAE:
				comment='C-- Generate qqbar->ccbar and gg->ccbar'
				NFLQCDC=3
				PT2CUT='0.0'
		if self._IsBeauty:
			IHFLA=5
			if self._IsSubProcessC:
				comment='C-- Generate bg -> bg'
				NFLQCDC=5		# not sure if this is different from '4'
				PT2CUT='1.0'
			if self._IsSubProcessAE:
				comment='C-- Generate qqbar->bbbar and gg->bbbar'
				NFLQCDC=3
				PT2CUT='0.0'
		if self._IsSubProcessC or self._IsSubProcessAE:
			self._cardPreamble.write(comment+'\n')
		self._cardPreamble.write('C  IHFLA = 4 - charm\n')
		self._cardPreamble.write('C          5 - beauty\n')
		self._cardPreamble.write('RAPGAP-IHFLA '+str(IHFLA)+'\n')
		if self._IsSubProcessC or self._IsSubProcessAE:
			self._cardPreamble.write('RAPGAP-NFLQCDC '+str(NFLQCDC)+'\n')
			self._cardPreamble.write('C-- Pt^2_hat cut for light quark matrix elements\n')
			self._cardPreamble.write('RAPGAP-PT2CUT 18 '+PT2CUT+'\n')
			self._cardPreamble.write('C-- Photon structure function\n')
			self._cardPreamble.write('RAPGAP-MSTP 56 3005003\n')
		if self._IsSubProcessC:
			self._cardPreamble.write('RAPGAP-IRPA 0\nRAPGAP-IRPE 0\n')
		if self._IsSubProcessAE:
			self._cardPreamble.write('RAPGAP-IRPA 1\nRAPGAP-IRPC 1\nRAPGAP-IRPE 1\n')
		# -- Q2 cut
		self._cardPreamble.write('C-- Minimum Q2\n')
		self._cardPreamble.write('RAPGAP-QMI '+self._Q2MIN+'\n')
		# -- choose positrons or electrons
		self._cardPreamble.write('C-- Incoming lepton: 11=e-, -11=e+\n')
		if self._IsElectron():
			self._cardPreamble.write('RAPGAP-LEPIN    11\n')
		else:
			 self._cardPreamble.write('RAPGAP-LEPIN    -11\n')

	def _prepareCardPreamble(self):
		cardTemplate=open("/data/zenith226a/libov/amadeus/v2008g/run/rapgap/autogen/cards/cards.template",'r')
		cardTemplateSTR=cardTemplate.read()
		#self._cardPreamble=open("/data/zenith226a/libov/amadeus/v2008g/run/rapgap/autogen/tmp",'w')
		self._cardPreamble=open("tmp",'w')		# local (zarah)
		self._cardPreamble.write(cardTemplateSTR)
		self._prepareSteerSpec()
		self._cardPreamble.close()
		#self._cardPreamble=open("/data/zenith226a/libov/amadeus/v2008g/run/rapgap/autogen/tmp",'r')
		self._cardPreamble=open("tmp",'r')	# local
		self._cardPreambleSTR=self._cardPreamble.read()

	def _generateJob(self, NumberOfEvents):
		#rgapdir='/data/zenith226a/libov/amadeus/v2008g/run/rapgap/'		# not used
		#os.chdir('/data/zenith226a/libov/amadeus/v2008g/run/rapgap/')		# now comment out so that running locally, see also
																								# the following comment
		card=open('current.cards','w')												# local (zarah spool if run there) - to avoid problems
																								# if run in parallel
		card.write(self._cardPreambleSTR)
		card.write('C-- Number of events\n')
		card.write('ZRLIMIT-NEVT '+str(NumberOfEvents)+'\nSTOP\n')
		card.close()
		if self._verbose:
			print '\n...generating job #'+str(self._FileCounter)
			print commands.getoutput(self._generatorScript+' '+'current')
			print 'job #'+str(self._FileCounter)+': generation complete'
		else:
			commands.getoutput(self._generatorScript+' '+'current')

	def _moveFiles(self, Nevents):
		# Nevents argument only for submission letter
		OutputFileName=self._FileName+'.'+str(self._FileCounter)+'.gz'
		OutputLogFileName=self._FileName+'.'+str(self._FileCounter)+'.zdi'
		commands.getoutput('gzip output')
		commands.getoutput('mv output.gz '+OutputFileName)
		commands.getoutput('mv current.log'+' '+OutputLogFileName)
		print OutputFileName+' exists: '+str(os.path.exists(OutputFileName))
		print OutputLogFileName+' exists: '+str(os.path.exists(OutputLogFileName))
		commands.getoutput('mv '+OutputFileName+' '+self._OutputPath)
		commands.getoutput('mv '+OutputLogFileName+' '+self._OutputPath)
		self._LetterFile.write('REQ: '+str(Nevents)+' '+self._OutputPath+OutputFileName+'\n')
		self._LetterFile.write('\t'+self._OutputPath+OutputLogFileName+'\n')

	def _generate(self):
		self._OutputPath=self._OutputPathPrefix+self._FileName+'/' # this is here and not in the constructor
																					  # because one wants to change _OutputPathPrefix
																					  # variable after object creation (although not
																					  # really necessary, could be in principle implemented
																					  # as an argument to the constructor)

		self._makedir()
		self._makeLetterFile()
		print str(self._DefaultNumberOfEvents)+' events/job'
		print str(self._Luminosity)+' pb^-1 to be generated'
		self._calculateCrossSect()
		self._TotalNumberOfEvents=int(self._Luminosity*self._GeneratorCrossSection*1000) # assumes sigma in nb and lumi in pb^-1
		print 'Total number Of events to be generated: '+str(self._TotalNumberOfEvents)
		N=divmod (self._TotalNumberOfEvents, self._DefaultNumberOfEvents)
		NJobs=N[0]
		NEventsRest=N[1]
		print 'Number of jobs with '+str(self._DefaultNumberOfEvents)+' events/job: '+str(NJobs)
		print 'Number of events in additional job: '+str(NEventsRest)
		for self._FileCounter in range(NJobs):
			print self._FileCounter
			self._generateJob(self._DefaultNumberOfEvents)
			self._moveFiles(self._DefaultNumberOfEvents)
		self._FileCounter=self._FileCounter+1	# analog to i++  ??
		# now additional job
		self._generateJob(NEventsRest)
		self._moveFiles(NEventsRest)

		self._InfoFile=open(self._OutputPath+self._FileName+'.info','w')
		self._createInfoFile()
		self._InfoFile.close()
		self._LetterFile.close()
		self._appendLeter()

	def _calculateCrossSect(self):
		#print 'calculating cross-section for selected process & kinematic range (# of events: '+str(self._NumberOfEventsCrossSect)+' )'
		print 'start cross section job'
		self._generateJob(self._NumberOfEventsCrossSect)
		print 'cross section job finished'
		log=open('current.log','r')
		logstr=log.read()
		num=logstr.find('sigma')
		log.seek(num)
		line=log.readline().split()
		if not line[0]=="sigma":
			print 'crazy ERROR'
		else:
			self._GeneratorCrossSection=float(line[2])
			print 'Cross Section Given by Generator= '+str(self._GeneratorCrossSection)

	def _createInfoFile(self):
		content=''
		if self._IsCharm:
			content+='* Inclusive charm DIS (ep->ccbarX)\n'
			if self._IsSubProcessC:
				content+='Resolved photon process: charm excitation (cg->cg)\n'
			if self._IsSubProcessAE:
				content+='* Resolved photon process: gg->ccbar and qqbar->ccbar\n'
		if self._IsBeauty:
			content+='* Inclusive beauty DIS (ep->bbbarX)\n'
			if self._IsSubProcessC:
				content+='Resolved photon process: beauty excitation (bg->bg)\n'
			if self._IsSubProcessAE:
				content+='* Resolved photon process: gg->bbbar and qqbar->bbbar\n'
		content+='* Q^2 > '+self._Q2MIN+' GeV^2\n'
		content+='* Cross section given by generator: sigma= '+str(self._GeneratorCrossSection)+' nb\n\n\n'
		content+='* Amadeus: v2008g\n* Generator: Rapgap 3.0\n* Proton structure function: CTEQ5L\n* Photon structure function: GRV-G LO\n* Used filters: no\n* Other parameters:\n\tm_b=4.75 GeV\n\tm_c=1.5 GeV\n\n\n'
		if	self._IsSubProcessAE:
			content+='* Main Rapgap switches to select the process:\n\tIPRO=18 (resolved photon)\n\tIRPA=1\n\tIRPE=1\n\tIRPC=1\n\tNFLQCDC=3\n\n\n'
		if self._IsSubProcessC:
			content+='* Main Rapgap switches to select the process:\n\tIPRO=18 (resolved photon)\n\tIRPA=0\n\tIRPE=0\n\tIRPC=1\n\tNFLQCDC=4 (for charm) NFLQCDC=5 (for beauty, although seems not to be neccessary, 4 works as well)\n\n\n'
		content+='* Number of events generated: Nevents='+str(self._TotalNumberOfEvents)+'\n'
		content+='* Luminosity= '+str(self._Luminosity)+' pb^-1\n'
		self._InfoFile.write(content)
		self._InfoFile.close()

	def _appendLeter(self):
		self._LetterFile=open(self._OutputPathPrefix+'submit.letters/'+self._FileName+'.letter','r')
		LetterFileName=self._OutputPathPrefix+'submit.letters/'+self._LetterToAppend
		if os.path.exists(LetterFileName):
			fullLetter=open(LetterFileName,'a')
		else:
			fullLetter=open(LetterFileName,'w')
		fullLetter.write('\n')
		fullLetter.write('\n')
		fullLetter.write(self._LetterFile.read())
		self._LetterFile.close()
		fullLetter.close()

	def _IsElectron(self):
		if self._Trigger=="cpz324": return False
		if self._Trigger=="cpz424": return False
		if self._Trigger=="cpu424": return False
		if self._Trigger=="cpr424": return False
		if self._Trigger=="cpx424": return False

		if self._Trigger=="duze25": return True
		if self._Trigger=="duye25": return True
		if self._Trigger=="duxe25": return True
		if self._Trigger=="duwe25": return True

		if self._Trigger=="evue26": return True
		if self._Trigger=="evse26": return True

# this can now be called after generation; 2DO: create another method that creates web info
# during files generation
	def _InfoForWeb(self, webinfo):
		self._OutputPath=self._OutputPathPrefix+self._FileName+'/'
		#webinfo=open('web.info','w')

		line=self._Flavour+' '+self._SubProcess+' '+self._whichYearFunnel()+' '+self._triggerHighLow()+' '+self._TriggerRAW+' '+self._Q2MIN
		# now read info file
		info=open(self._OutputPath+self._FileName+'.info','r')
		infostr=info.read()

		num=infostr.find('sigma=')
		info.seek(num)
		line1=info.readline().split()
		line = line+' '+line1[1]

		num=infostr.find('Nevents=')
		info.seek(num)
		line1=info.readline().split()
		line2=line1[0]
		line2=line2.lstrip('Nevents=')
		line = line+' '+line2

		num=infostr.find('Luminosity=')
		info.seek(num)
		line1=info.readline().split()
		line = line+' '+line1[1]

		line=line+' X'

		line=line+' '+self._FileName+'.info'

		line=line+' '+string.upper(self._FileName)+'.txt\n'

		webinfo.write(line)


	def _whichYearFunnel(self):
		# error-prone: 06e+ and 06e- both contain 06, this is not taken into account here!
		# ro be changed for bgf generating
		if (self._TriggerRAW.find("03")!=-1) or (self._TriggerRAW.find("04")!=-1): return "2003/04e+ num03t5.1"
		if (self._TriggerRAW.find("05")!=-1): return "2005e- num05t2.0"
		if (self._TriggerRAW.find("06")!=-1): return "2006e- num06t3.0"

	# configuration table; taken from http://www-zeus.desy.de/~shehzadi/06_07MC/MC.html
	# checked once with painless funnel name maker
	# http://www-zeus.desy.de/components/funnel/cgi-bin/formmaker.cgi
	# (see log.txt for deatils)
	def _convert(self, trigger):
		# 03/04 p
		if trigger=='pfno03': return 'cpz324'
		if trigger=='pfap04': return 'cpz424'
		if trigger=='pfhj04': return 'cpu424'
		if trigger=='pfau04': return 'cpr424'
		if trigger=='pfha04': return 'cpx424'
		# 05 e
		if trigger=='efap05': return 'duze25'
		if trigger=='efha05': return 'duye25'
		if trigger=='efoc05': return 'duxe25'
		if trigger=='efho05': return 'duwe25'
		#06e
		if trigger=='efma06': return 'evue26'
		if trigger=='efhm06': return 'evse26'

		return	'dummy'

	def _triggerHighLow(self):
		# 03/04 p
		if self._TriggerRAW=='pfno03': return 'Low'
		if self._TriggerRAW=='pfap04': return 'Low'
		if self._TriggerRAW=='pfhj04': return 'High'
		if self._TriggerRAW=='pfau04': return 'Low'
		if self._TriggerRAW=='pfha04': return 'High'
		# 05 e
		if self._TriggerRAW=='efap05': return 'Low'
		if self._TriggerRAW=='efha05': return 'High'
		if self._TriggerRAW=='efoc05': return 'Low'
		if self._TriggerRAW=='efho05': return 'High'
		#06e
		if self._TriggerRAW=='efma06': return 'Low'
		if self._TriggerRAW=='efhm06': return 'High'
