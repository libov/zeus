#
#
#
#
def kill(start_job):
	print 'This will kill your running jobs from zarah...'
	print 'The first killed job is '+str(start_job)
	import commands
	import os.path
	tempstr=commands.getoutput('zarah-jobq')
	print 'COMPLETED JOBS:'
	print tempstr
	print 'Starting to kill jobs...'
	counter=0
	numberOfJobs=0
	while ((tempstr[counter])!='*'):
		tempchar=tempstr[counter:counter+4]
		if tempchar == '0000':
			jobid=tempstr[counter:(counter+10)]
			jobid_signif=jobid[4:10]
			jobnumber=int(jobid_signif)
			if (jobnumber>=start_job):
				tempstr2=commands.getoutput('zarah-jobkill -j '+jobid+' -y')
 				print tempstr2
 				numberOfJobs=numberOfJobs+1
		counter=counter+1
	#print str(numberOfJobs)+' jobs purged'
