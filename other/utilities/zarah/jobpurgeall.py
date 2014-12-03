# This script will purge your completed zarah-jobs automatically
# Make sure they are downloaded!!!
# You must be authorized(zarah-auth)!!!
#
print 'This will purge your completed jobs from zarah...'
print '!!! ALL jobs will be purged !!!'
import commands
import os.path
tempstr=commands.getoutput('zarah-jobq -c')
print 'COMPLETED JOBS:'
print tempstr
print 'Starting to purge jobs...'
counter=0
numberOfJobs=0
while ((tempstr[counter])!='*'):
	tempchar=tempstr[counter:counter+3]
	if tempchar == '000':
		jobid=tempstr[counter:(counter+11)]
		path=jobid+'/'
		tempstr2=commands.getoutput('zarah-jobpurge -j '+jobid+' -y')
		print tempstr2
		numberOfJobs=numberOfJobs+1
####
	counter=counter+1
	continue
print str(numberOfJobs)+' jobs purged'
