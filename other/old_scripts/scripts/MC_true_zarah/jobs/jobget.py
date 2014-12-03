# This script gets completed zarah-jobs automatically
# You must be authorized(zarah-auth)!!!
#
print 'This will get your completed jobs from zarah...'
import commands
tempstr=commands.getoutput('zarah-jobq -c')
print 'COMPLETED JOBS:'
print tempstr
print 'Starting to get jobs...'
counter=0
numberOfJobs=0
while ((tempstr[counter])!='*'):
	tempchar=tempstr[counter:counter+4]
	if tempchar == '0000':
		jobid=tempstr[counter:(counter+10)]
		tempstr2=commands.getoutput('zarah-jobget -j '+jobid+' -y -a ')
		print tempstr2
		numberOfJobs=numberOfJobs+1
	counter=counter+1
	continue
print str(numberOfJobs)+' jobs got'