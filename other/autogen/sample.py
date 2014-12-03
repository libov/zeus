##################################################################################################
# class to automatize generation of ZEUS Monte Carlo
# current implementation: rapgap resolved dis charm/beauty;
# 22.01.2010: BGF added
# see also comments in steer.py in this directory
#
# author: Vladyslav Libov, DESY
# libov@mail.desy.de
# December 2009
# modified: 17th January 2010
# modified: 22nd January 2010 (BGF option included; template.cards & python scripts modified)
#
##################################################################################################

import sys
import commands
import os
import os.path
import string

class		sample:

	def __init__(self, Flavour, Q2MIN, SubProcess, Luminosity, Trigger):
		# -- common settings
		self._generatorScript='run_rapgap30'
		#self._triggerTableFileName='triggers.cfg'
		#self._triggerTableFileName='triggers.new.cfg'
                self._triggerTableFileName='triggers.Mozart2010.cfg'
		# print '** generator script: '+self._generatorScript
		# choose where files output files should be stored
		self._OutputPathPrefix='/data/zenith226a/libov/amadeus/events/rgap30/'    # effectively - default value;
                                                                                          # can be set in outer world of course
		self._DefaultNumberOfEvents=20000
		self._NumberOfEventsCrossSect=100000			# default number of events to be generated for
								        # cross section calculation
		self._User='f15643'
		# -- control card settings
		# flavour selection
		self._Flavour=Flavour								# at the moment used only in web info stuff
		self._SubProcess=SubProcess						        # at the moment used only in web info stuff
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
			print 'ERROR in sample.__init__(): wrong Process selected. Choose C or AE or BGF'
			sys.exit(1)

		self._TriggerRAW=Trigger
		self._Luminosity=Luminosity	# to be changed to _dataLumi x factor in the future

		self._triggerHighLow='dummy'
		self._Trigger='dummy'
		self._Funnel='dummy'
		self._Period='dummy'
		self._DataLumi='dummy'
		self._ExtractInfo(self._triggerTableFileName)	# in this function, variables marked as 'dummy' (default value) are defined
		self._lumiTimesData=str(float(self._Luminosity)/float(self._DataLumi))


		self._FileName=self._Trigger+'.'+self._User+'.'+Spec
		# added 06 July 2010 to have different name from already existing
		#self._FileName=self._Trigger+'.'+self._User+'.'+Spec+"fix"
		# added 26 July 2010
		#self._FileName=self._Trigger+'.'+self._User+'.'+Spec+"noQED"

		# prepare card
		self._prepareCardPreamble()
		self._FileCounter=0
		self._GeneratorCrossSection=1				# some dummy value
		self._verbose=True							# used in _generateJob()
		self._LetterToAppend='full.letter'		# some default name for letter file to which to append info;
								# is set in steer.py according to selected config file;
								# variable is used in _appendLeter()

	def	_makedir(self):
		commands.getoutput('rm -rf '+self._OutputPath)
		commands.getoutput('mkdir '+self._OutputPath)
		if os.path.exists(self._OutputPath):
			print 'files go to: '+self._OutputPath
		else:
			print 'Error! Output directory does not exist! Files will be lost! Terminating!'
			sys.exit(1)

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
		#cardTemplate=open("/data/zenith226a/libov/amadeus/v2008g/run/rapgap/autogen/cards/cards.template.no_QED_EW",'r')
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
		card=open('current.cards','w')						# local (zarah spool if run there) - to avoid problems
											# if run in parallel
		card.write(self._cardPreambleSTR)
		card.write('C-- Number of events\n')
		card.write('ZRLIMIT-NEVT '+str(NumberOfEvents)+'\nSTOP\n')
		card.close()
		commands.getoutput('rm -f heracles.dat')		# to avoid 'kinematical incosistency', see also log.txt 22.01.2010
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
		self._FileCounter=self._FileCounter+1	# analog to i++ in python  ??
		# now additional job
		self._generateJob(NEventsRest)
		self._moveFiles(NEventsRest)

		self._InfoFile=open(self._OutputPath+self._FileName+'.info','w')
		self._createInfoFile()
		self._InfoFile.close()
		self._LetterFile.close()
		self._appendLeter()

	def _calculateCrossSect(self):
		print 'calculating cross-section for selected process & kinematic range (# of events: '+str(self._NumberOfEventsCrossSect)+' )'
		print 'start cross section job'
		self._generateJob(self._NumberOfEventsCrossSect)
		print 'cross section job finished'
		log=open('current.log','r')
		logstr=log.read()
		# the whole stuff of finding sigma here is error-prone; there are other sigmas there (sigma mesons)
		# perhaps we were lucky and search is case-sensitive. that's why we had no problems
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
		fullLetter.write('\n\n')
		fullLetter.write(self._LetterFile.read())
		self._LetterFile.close()
		fullLetter.close()

	def _IsElectron(self):
		if self._Period.find('e-')!=-1:
			return True
		if self._Period.find('e+')!=-1:
			return False
		else:
			print 'ERROR: wrong period (does not contain e-/e+). Terminating.'
			sys.exit(1)

# this can now be called after generation; the next one after it is for calling during generation.
# here we need info file for cross sections (and numevents, lumi, though the latter could be calculated without info file)
	def _InfoForWebAfter(self, webInfoFile):
		line=self._Flavour+' '+self._SubProcess+' '+self._Period+' '+self._Funnel+' '+self._triggerHighLow+' '+self._TriggerRAW+' '+self._Q2MIN
		# now read info file

		# case 1: data disks
		self._OutputPath=self._OutputPathPrefix+self._FileName+'/'
		info=open(self._OutputPath+self._FileName+'.info','r')	# data disks
		#case 2: dCache space
		#print commands.getoutput('dccp /acs/users/libov/MC/rgap30/'+self._FileName+'/'+self._FileName+'.info .')
		#info=open(self._FileName+'.info','r')

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
		line = line+' '+line1[1]	# why I did not simply use self._Luminosity?
											# ah, the cross section could only be read from info file;
											# so I read luminosity from it as well...

		timesData=str(float(line1[1])/float(self._DataLumi))
		line=line+' '+timesData

		line=line+' '+self._FileName+'.info'

		line=line+' '+string.upper(self._FileName)+'.txt\n'

		webInfoFile.write(line)
		#info.close()
		#os.remove(self._FileName+'.info')

        # this is class method to create webpage with info during generation.
        # previous method is not removed in order to stil have a possibility
        # to generate webpage after events were generated
        # here we don't need an info file
	def	_InfoForWeb(self, webInfoFile):
		line=self._Flavour+' '+self._SubProcess+' '+self._Period+' '+self._Funnel+' '+self._triggerHighLow+' '+self._TriggerRAW+' '+self._Q2MIN+' '+str(self._GeneratorCrossSection)+' '+str(self._TotalNumberOfEvents)+' '+str(self._Luminosity)+' '+self._lumiTimesData+' '+self._FileName+'.info'+' '+string.upper(self._FileName)+'.txt\n'
		webInfoFile.write(line)


	def _ExtractInfo(self, triggerConfigFileName):
		triggerConfigFile=open(triggerConfigFileName,'r')
		triggerFound = False
		for line in	triggerConfigFile:
			lineList=line.split()
			if lineList==[]: continue
			if lineList[0]==self._TriggerRAW:
				self._triggerHighLow=lineList[1]
				self._Funnel=lineList[2]
				self._Trigger=lineList[3]
				self._Period=lineList[4]
				self._DataLumi=lineList[5]
				triggerFound = True
				break
		if not triggerFound:
			print 'Error: check trigger in your config file. Terminating.'
			sys.exit(1)
		triggerConfigFile.close()
