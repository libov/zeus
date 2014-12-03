#
#
#
#
import commands
import os.path
files=0
job=750000
for x in range(100000):
	jobid='0000'+str(job)
	path=jobid+'/'
	if os.path.exists(path):
		print path+' exists'
		#tempstr=commands.getoutput('mv '+path+'*.root'+' ../../../data/MCtemp/')
                tempstr=commands.getoutput('mv '+path+'*.root'+' root/')
		print tempstr
		files=files+1
	job=job+1
print str(files)+' ntuples copied'
