#This will submit jobs to zarah. You must be authorized via zarah-auth
#control cards you wish to submit must be in /cmd/mycards/
#and their names must be: xcontrol.cards
#x=0,1,2,3...
print 'This will submit your jobs to zarah'
import commands
import os
import os.path
counter=0
numberOfJobs=0
while os.path.exists('K0s_analysis_part1+true_'+str(counter)+'.cxx'):
	filename='K0s_analysis_part1+true_'+str(counter)+'.cxx'
	exename=str(counter)+'.exe'
	command1='gcc '+filename+' -I. Mother.cxx Daughter.cxx -o '+exename+' `root-config --libs --cflags`'
	print command1
	tempstr=commands.getoutput(command1)
	print tempstr
	command2='zarah-jobsub -q M -s '+exename
	print command2
	tempstr=commands.getoutput(command2)
	print tempstr
	numberOfJobs=numberOfJobs+1
	counter=counter+1
print str(numberOfJobs)+' jobs submitted'
