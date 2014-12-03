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
                tempstr=commands.getoutput('mv '+path+'*.root'+' /data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/')
		print tempstr
		files=files+1
	job=job+1
print str(files)+' ntuples copied'
