#
# script to create web page with information about MC samples
# INPUT: WebInfoFile
# OUTPUT: OutputPath/WebPageFileName
# Vladyslav Libov
# libov@mail.desy.de
#

# ------------------------------------ options section -------------------------------------
WebInfoPath='/data/zenith226a/libov/amadeus/REFUNNEL/refunnel_Mozart2010/0304p/'
WebInfoFile='info.0304p'
WebPageFileName='0304p.html'
OutputPath='/zow/user/libov/WWW/MC/refunnel_Mozart2010/'
dCachePath='/acs/users/libov/MC/rgap30_Mozart2010/'	# for log/generatorfile path on the page
#-------------------------------------------------------------------------------------------


#----------------------------------- helper functions section -------------------------------
def	createYearHeader(year, file):
	#file.write('<center><h1>RAPGAP MC for inclusive beauty & charm</h1></center>\n')
	#file.write('<center><h1>in resolved photon DIS for '+year+' data</h1></center>\n<hr>\n<hr>\n\n\n')
	file.write('<center><h1>RAPGAP MC for inclusive charm in DIS</h1></center>\n')
	file.write('<center><h1>for '+year+' period</h1></center>\n<hr>\n<hr>\n\n\n')

def	createFlavourHeader(flavour, file):
	#file.write('<h2>Inclusive '+flavour+' in resolved photon DIS</h2>\n\n\n')
	file.write('<h2>Inclusive '+flavour+' in DIS</h2>\n\n\n')

def	createProcessHeader(process, flavour, file):
	 prefix=flavour[0]
	 finalstate=prefix+' '+prefix+'bar'
	 if process=='C':
	 	file.write('<h3>'+flavour+' excitation ('+prefix+' gluon -> '+prefix+' gluon)</h3>\n\n\n')
	 if process=='AE':
	 	file.write('<h3>Other resolved processes (gluon gluon-> '+finalstate+', Q Qbar-> '+finalstate+')</h3>\n\n\n')
	 if process=='BGF':
	 	file.write('<h3>Direct Boson-Gluon Fusion (gamma gluon-> '+finalstate+')</h3>\n\n\n')

def	createTableHeader(file):
	file.write('<table border=1 cellspacing=0 cellpadding=5><tr><td><b>Period</b></td><td><b>Funnel Vers.</b></td><td colspan=2 align=center><b>Trigger Config</td></b><td><b>Kinematic range</b></td><td><b>Cross section, nb</b></td><td><b>Events</b>  </td><td><b>Luminosity, pb<sup>-1</sup></b></td><td><b>MC/Data(appr.!)</b></td><td><b>Generation Info</b></td><td><b>Cards</b></td></tr>\n\n')

def	finalizeSection(file, directoryList):
	file.write('</table>\n\n')
	# now paths to generator and log files
	file.write('<br>\nGenerator and log files:\n<br>\n')
	for directory in directoryList:
		file.write('<span  STYLE="color:BLUE">'+dCachePath+'/'+directory+'/'+'</span>\n<br>\n')

# ----------------------------------------- Main part ---------------------------------------

# open the file with web info (i.e. information about each sample that needs to be documented)
webinfo=open(WebInfoPath+WebInfoFile,'r')
# helping variables
linesList=[]
linesList2=[]

# --- first sort the list ---
firstline=True
for line in webinfo:
	lineList=line.split()
	linesList2.append(lineList)
	#print lineList
	if firstline:
		linesList.append(lineList)
		firstline=False
		continue
	year=lineList[2]
	flavour=lineList[0]
	insertPos=-1
	for i in range (len(linesList)-1, -1, -1):
		#print 'i= '+str(i)
		#print linesList[i][2]+''+year
		if linesList[i][2]<=year:
			#print 'debug0'
			if linesList[i][2]!=year:
				insertPos=i+1
				break
			for k in range (i,-1,-1):
				if linesList[k][0]<=flavour:
					insertPos=k+1
					break
			break
	#print
	#print insertPos
	linesList.insert(insertPos,lineList)
#print '*************'

# --- ok, now assume linesList is sorted according to what we want to see in the web page
webpage=open(WebPageFileName,'w')
webpage.write('<html>\n<body>\n\n')
previousFlavour=linesList[0][0]
previousProcess=linesList[0][1]
previousYear=linesList[0][2]
newFlavour=True
newProcess=True
newYear=True
newTable=True
#firstTable=True
#LastTable=False
unclosedTable=False
directoryList=[]
#for line in linesList:
for line in linesList2:
	flavour=line[0]
	process=line[1]
	year=line[2]
	if flavour!=previousFlavour:
		newFlavour=True
		previousFlavour=flavour
	if process!=previousProcess:
		newProcess=True
		previousProcess=process
	if year!=previousYear:
		newYear=True
		previousYear=year

	if newFlavour or newProcess or newYear:
		newTable=True
		if unclosedTable:
			finalizeSection(webpage, directoryList)
			unclosedTable=False
			# reset list with path to logs/generator files
			directoryList=[]

	if newYear:
		createYearHeader(year, webpage)
		newYear=False
		createFlavourHeader(flavour, webpage)
		newFlavour=False
		createProcessHeader(process, flavour, webpage)
		newProcess=False

	if newFlavour:
		createFlavourHeader(flavour, webpage)
		newFlavour=False

	if newProcess:
		createProcessHeader(process, flavour, webpage)
		newProcess=False

	if newTable:
		createTableHeader(webpage)
		unclosedTable=True
		newTable=False

	webpage.write('<tr><td>')

	for word in line:
		if word==line[0] or word==line[1]: continue	# we don't need process and year in the file
		if word==line[6]: word='Q&sup2; &gt; '+word+'GeV&sup2'
		if word==line[10]: word=str(round(float(word)))
		if word==line[11]:
			word='<a href="./'+word+'">Generation Info</a>'
		if word==line[12]: word='<a href="./'+word+'">Cards</a>'
		webpage.write(word+'</td><td>')
	webpage.write('</td></tr>\n\n')
	
	directoryList.append(line[11].strip('.info\n'))

finalizeSection(webpage, directoryList)

webpage.close()

import commands
commands.getoutput('cp '+WebPageFileName+' '+OutputPath)
print 'File '+WebPageFileName+' copied to '+OutputPath

# --------------- this kind of comparisons is used in sorting, here just as a reminder... -------------------------
#bla1='2003/2004e+'
#bla2='2005e-'
#bla3='2006e-'
#print bla1<bla2
#print bla1<bla3
#print bla2<bla3
#print bla1>bla2
#a='charm'
#b='beauty'
#print a>b
#-----------------------------------------------------------------------------------------------------
