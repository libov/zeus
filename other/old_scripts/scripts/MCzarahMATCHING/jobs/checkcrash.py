#
#
#
#
print 'This will check your crashed jobs'
import commands
import os
import os.path
import string
counter=0
numberOfJobs=0
job=760000
files=0
for x in range(100000):
	jobid='0000'+str(job)
	path=jobid+'/'
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
			files=files+1
	job=job+1
print str(files)+' jobs not completed successfully...'


