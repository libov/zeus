# This script gets completed zarah-jobs automatically
# You must be authorized(zarah-auth)!!!
#
print 'This will get your completed jobs from zarah...'
import commands
import os
import os.path
joblistfilename='joblist.tmp'
if os.path.exists(joblistfilename):
	os.remove(joblistfilename)
tempstr=commands.getoutput('zarah-jobq -c')
commands.getoutput('zarah-jobq -c > '+joblistfilename)
print 'COMPLETED JOBS:'
print tempstr
print 'Starting to get jobs...'
counter=0
numberOfJobs=0
joblistfile=open(joblistfilename,'r')
for line in joblistfile:
	counter+=1
        lineList=line.split()
	if counter<=2 or len(lineList)<5 or lineList[0].find('*')!=-1: continue
	jobid=lineList[0]
	tempstr2=commands.getoutput('zarah-jobget -j '+jobid+' -y -a ')
	print tempstr2
	numberOfJobs=numberOfJobs+1
print str(numberOfJobs)+' jobs got'
os.remove(joblistfilename)
