#--------------------------------------------------------------------------------------------------------------------
# input: orablock.cfg, dbase/orablocks/*
# output: BaseClass.h, BaseClass.C
#--------------------------------------------------------------------------------------------------------------------
# author: Vladyslav Libov, DESY
# 01 December 2009
# modified: 24 August 2011
#--------------------------------------------------------------------------------------------------------------------

# import system modules
import fileinput
import os
import os.path
import sys

#--------------------------------------------------------------------------------------------------------------------
# User settings:
# filename with orange variables configuration
OrablocksConfigFile='config/orablocks.cfg'
# path to files with orange block variable definition
OrablocksPath='dbase/orablocks/'
# list of blocks that are only for Monte Carlo
MCBlocks=['Fmckin','Fmckin1','Cbtrue', 'MCHBMJ', 'Mckine', 'Mckinecr', 'Simrun']
#--------------------------------------------------------------------------------------------------------------------

# open file with variables to be included into BaseClass
print '\nINFO: Reading '+OrablocksConfigFile
forablocks=open(OrablocksConfigFile,'r')

# read contents of this file
for line in forablocks:
        # split the line into words
	words=line.split()
        # the first word is expected to be a card name, so read it...
	CardName=words[0]
        # ... and remove from the list
	words[0:1]=[]
        # check the name of the card and fill respective list
	if CardName=='BLOCKON':
		Blocks=words
	elif CardName=='VARIABLEON':
		VariablesON=words
	elif CardName=='VARIABLEOFF':
		VariablesOFF=words
	else:
		print 'ERROR: Please check orablocks.cfg Only BLOCKON, VARIABLEON and VARIABLEOFF cards are allowed. Terminating...'
		sys.exit(-1)

# print information about what was read from the configuration file
if len(Blocks)==0:
	print 'INFO: No Blocks selected'
else:
	print 'INFO: The following blocks are selected: '
	print Blocks
if len(VariablesON)!=0:
	print 'Following variables are selected additionally: '
	print VariablesON
if len(VariablesOFF)!=0:
	print 'Following variables are turned off: '
	print VariablesOFF

# check whether there is a file for each block selected; otherwise terminate
for block in Blocks:
	if not os.path.exists(OrablocksPath+block):
		print 'ERROR: no file provided for block: '+block
		sys.exit(-1)

# create temporary file with list of ALL variables needed for the BaseClass
allvarDATA=open('tmp/allvarDATA.txt','w')
allvarMC=open('tmp/allvarMC.txt','w')
allvar=open('tmp/allvar.txt','w')

# loop over all block files to get a map of all the variables available from the files
os.chdir(OrablocksPath)
filelist=os.listdir('./')
VariableLineMap={}
VariableBlockMap={}
for cLine in fileinput.input(filelist):
	cFile=fileinput.filename()
	cLineList=cLine.split()
	cVarName=cLineList[1]
        VariableLineMap[cVarName] = cLine
        VariableBlockMap[cVarName] = cFile

# start creating lists of the variable needed for the BaseClass;
# add blocks in the order they appear in the config file (order is very important)
for block in Blocks:
	# open respective file
	block_file = open(block, 'r')
	for line in block_file:
		cVarName = line.split()[1]
		if (cVarName in VariablesOFF): continue
		if block in MCBlocks:
			allvarMC.write(line)
		else:
			allvarDATA.write(line)

# now add separate variables, also in the order they appear
for variable in VariablesON:
	# check whether this variable was not already added
	block = VariableBlockMap[variable]
	if block in Blocks: continue
	# take a line corresponding to this variable from the map
	line = VariableLineMap[variable]
	if block in MCBlocks:
		allvarMC.write(line)
	else:
		allvarDATA.write(line)

#exit(-1)

os.chdir('../../')
allvarDATA.close()
allvarMC.close()
allvarDATA=open('tmp/allvarDATA.txt','r')
allvarMC=open('tmp/allvarMC.txt','r')
line1=allvarDATA.read()
line2=allvarMC.read()
allvar.write(line1+line2)
allvar.close()
allvarDATA.close()
allvarMC.close()
# create C++ code for BaseClass
# this is not yet optimal, e.g. I loop over variables two times- I'm trying
# to separate all steps (some kind of modularity)
#------- BaseClass.h -----------
print 'Creating BaseClass.h'

allvar=open('tmp/allvar.txt','r')
BaseClassH=open('inc/BaseClass.h','w')
line='#ifndef __BASECLASS_H__\n#define __BASECLASS_H__\n'
line=line+'#include <TROOT.h>\n#include <TChain.h>\n#include <TTree.h>\n'
line+='/** \\brief Base class for TNtupleAnalyzer*/\n'
line+='class BaseClass\n{\n\tpublic:\n\t\tTChain\t*fChain;\n\t\tTTree\t*fCurrentTree;\n\t\tBool_t\tfIsMC;\n\n'
BaseClassH.write(line)
for line in allvar:
	line=line.rstrip('\n')
	variable=line.split()
	vartype=variable[0]
	varname=variable[1]
	array = False
	vardim=''
	if len(variable)>2:
		array=True
	if array:
		vardim=variable[2]
	BaseClassH.write('\t\t'+vartype+'\t'+varname+vardim+';\n')
line='\n\t\tvoid\tSetBranchAddresses();\n'
BaseClassH.write(line)
line='\t\tvoid\tAddTreeBranches();\n};\n\n#endif\n'
BaseClassH.write(line)
BaseClassH.close()
allvar.close()
#------- BaseClass.cxx -----------
print 'Creating BaseClass.cxx\n'
allvarDATA=open('tmp/allvarDATA.txt','r')
allvarMC=open('tmp/allvarMC.txt','r')
BaseClassCXX=open('src/BaseClass.cxx','w')
# -- SetBranshAddress function
BaseClassCXX.write('#include<iostream>\nusing namespace std;\n')
line='#include <BaseClass.h>\nvoid\tBaseClass::SetBranchAddresses()\n{\n'
BaseClassCXX.write(line)
line='\tfChain->SetBranchStatus("*", 0);\n'
BaseClassCXX.write(line)
for line in allvarDATA:
	line=line.rstrip('\n')
	variable=line.split()
	vartype=variable[0]
	varname=variable[1]
	array = False
	if len(variable)>2:
		array=True
	prefix=''
	if not array:
		prefix='&'
	BaseClassCXX.write('\tfChain->SetBranchStatus("'+varname+'", 1);\n')
	BaseClassCXX.write('\tfChain->SetBranchAddress("'+varname+'",'+prefix+varname+');\n')
BaseClassCXX.write('\tif (fIsMC)\n\t{\n')
for line in allvarMC:
	line=line.rstrip('\n')
	variable=line.split()
	vartype=variable[0]
	varname=variable[1]
	array = False
	if len(variable)>2:
		array=True
	prefix=''
	if not array:
		prefix='&'
	BaseClassCXX.write('\t\tfChain->SetBranchStatus("'+varname+'", 1);\n')
	BaseClassCXX.write('\t\tfChain->SetBranchAddress("'+varname+'",'+prefix+varname+');\n')
BaseClassCXX.write('\t}\n}\n\n')
# -- AddTreeBranches function
# have to close data files and then reopen them - otherwise cannot read (eof) --> more elegant way to deal?
allvarDATA.close()
allvarMC.close()
allvarDATA=open('tmp/allvarDATA.txt','r')
allvarMC=open('tmp/allvarMC.txt','r')
line='void\tBaseClass::AddTreeBranches()\n{\n'
BaseClassCXX.write(line)
for line in allvarDATA:
	line=line.rstrip('\n')
	variable=line.split()
	# ---- variable type-------
	vartype=variable[0]
	vartype_short=''
	if vartype=='Int_t':
		vartype_short='I'
	if vartype=='Float_t':
		vartype_short='F'
	# --------------------------
	varname=variable[1]
	vardim=''
	array = False
	if len(variable)>2:
		array=True
		vardim=variable[2]
	if len(variable)>3:
		vardim=variable[3]
	prefix=''
	if not array:
		prefix='&'
	BaseClassCXX.write('\tfCurrentTree->Branch("'+varname+'",'+prefix+varname+', "'+varname+vardim+'/'+vartype_short+'");\n')
BaseClassCXX.write('\tif (fIsMC)\n\t{\n')
for line in allvarMC:
	line=line.rstrip('\n')
	variable=line.split()
	# ---- variable type-------
	vartype=variable[0]
	vartype_short=''
	if vartype=='Int_t':
		vartype_short='I'
	if vartype=='Float_t':
		vartype_short='F'
	# --------------------------
	varname=variable[1]
	vardim=''
	array = False
	if len(variable)>2:
		array=True
		vardim=variable[2]
	if len(variable)>3:
		vardim=variable[3]
	prefix=''
	if not array:
		prefix='&'
	BaseClassCXX.write('\t\tfCurrentTree->Branch("'+varname+'",'+prefix+varname+', "'+varname+vardim+'/'+vartype_short+'");\n')
BaseClassCXX.write('\t}\n')
line='}\n'
# -- finalize
BaseClassCXX.write(line)
BaseClassCXX.close()
allvarDATA.close()
# -- end of the story
