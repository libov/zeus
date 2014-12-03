#
#
#
#
print 'This will submit your crashed jobs to zarah'
import commands
import os
import os.path
import string
counter=0
numberOfJobs=0
job=730000
files=0
for x in range(100000):
	jobid='0000'+str(job)
	path='down/'+jobid+'/'
	if os.path.exists(path):
		print path+' exists'
		f=open(path+'stdout','r')
		stdout=f.read()
		succ_str='Successfully completed.'
		is_compl=0
		is_compl=string.find(stdout,succ_str)
		print is_compl
		if is_compl==(-1):
			print 'Not successful!'
			command2='zarah-jobsub -q M -s '+path+'*.exe'
			c2res=commands.getoutput(command2)
			print command2
			print c2res
			files=files+1
	job=job+1
print str(files)+' jobs resubmitted...'
print commands.getoutput('zarah-jobq')

