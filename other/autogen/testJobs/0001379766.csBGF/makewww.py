#
# script to create web page with information about MC samples
# INPUT: WebInfoFile
# OUTPUT: WebPageFileName
# Vladyslav Libov
# libov@mail.desy.de
#

# --------- options section ----------
WebPageFileName='testpage.htm'
OutputPath='/zow/user/libov/WWW/MC'
WebInfoFile='web.info'
#--------------------------------------


#----------------------------------- helper functions section -------------------------------
def	createYearHeader(year, file):
	file.write('<center><h1>RAPGAP MC for inclusive beauty & charm</h1></center>\n')
	file.write('<center><h1>in resolved photon DIS for '+year+' data</h1></center>\n<hr>\n<hr>\n\n\n')

def	createFlavourHeader(flavour, file):
	file.write('<h2>Inclusive '+flavour+' in resolved photon DIS</h2>\n\n\n')

def	createProcessHeader(process, flavour, file):
	 prefix=flavour[0]
	 finalstate=prefix+' '+prefix+prefix+'bar'
	 if process=='C':
	 	file.write('<h3>'+flavour+' excitation ('+prefix+' gluon -> '+prefix+' gluon)</h3>\n\n\n')
	 if process=='AE':
	 	file.write('<h3>Other resolved processes (gluon gluon->'+prefix+' '+finalstate+', Q Qbar->'+finalstate+')</h3>\n\n\n')

def	createTable(file):
	file.write('<table border=1 cellspacing=0 cellpadding=5><tr><td><b>Period</b></td><td><b>Funnel Vers.</b></td><td colspan=2 align=center><b>Trigger Config</td></b><td><b>Kinematic range</b></td><td><b>Cross section, nb</b></td><td><b>Events</b>  </td><td><b>Luminosity, pb<sup>-1</sup></b></td><td><b>MC/Data</b></td><td><b>Generation Info</b></td><td><b>Cards</b></td></tr>\n\n')



# ----------------------------------------- Main part ---------------------------------------

webinfo=open(WebInfoFile,'r')
linesList=[]
# --- first sort the list ---
firstline=True
#bla=0
for line in webinfo:
	#bla+=1
	#if bla==5: break
	lineList=line.split()
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
for line in linesList:
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
			webpage.write('</table>\n\n')
			unclosedTable=False

	if newYear:
		createYearHeader(year, webpage)
		newYear=False


	if newFlavour:
		createFlavourHeader(flavour, webpage)
		newFlavour=False

	if newProcess:
		createProcessHeader(process, flavour, webpage)
		newProcess=False

	if newTable:
		createTable(webpage)
		unclosedTable=True
		newTable=False

	webpage.write('<tr><td>')
	#print line
	#print
	for word in line:
		if word==line[0] or word==line[1]: continue	# we don't need process and year in the file
		if word==line[6]: word='Q&sup2; &gt; '+word+'GeV&sup2'
		if word==line[11]: word='<a href="./'+word+'">Generation Info</a>'
		if word==line[12]: word='<a href="./'+word+'">Cards</a>'
		webpage.write(word+'</td><td>')
	webpage.write('</td></tr>\n\n')

webpage.close()
import commands
commands.getoutput('cp '+WebPageFileName+' '+OutputPath)
print 'File '+WebPageFileName+' copied to '+OutputPath

# --------------- these comparisons are used in sorting, just a reminder... -------------------------
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
