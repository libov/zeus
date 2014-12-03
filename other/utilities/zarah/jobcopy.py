#
#
#
#
import commands
import os.path
files=0
job=1000000
for x in range(100000):
	jobid='000'+str(job)
	path=jobid+'/'
	if os.path.exists(path):
		print path+' exists'
		#tempstr=commands.getoutput('mv '+path+'*.root'+' /data/zenith226a/libov/master/06_data_05e_nocuts_2/')
		tempstr=commands.getoutput('mv '+path+'*.root'+' /data/zenith226a/libov/data/HERAII/')
		print tempstr
		files=files+1
	job=job+1
print str(files)+' jobs copied'
