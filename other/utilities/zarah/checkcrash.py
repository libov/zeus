################################################################################
## Libov Vladyslav                                                             #
## National University of Kiev                                                 #
################################################################################
import commands, os, string
# print info
print 'This will check your crashed jobs'
# declare job counters and initialize with zeros
crashedJobs=0
goodJobs=0
numberOfJobs=0
# get the directory contents
joblistfilename='joblist.tmp'
if os.path.exists(joblistfilename):
    os.remove(joblistfilename)
commands.getoutput('ls -1 > '+joblistfilename)
joblistfile=open(joblistfilename,'r')
# loop over directory contents
for job in joblistfile:
    job=job.lstrip()
    job=job.rstrip()
    # check whether it's a directory
    if not os.path.isdir(job): continue
    # increase job counter
    numberOfJobs += 1
    # read the stdout file
    f=open(job+'/stdout','r')
    stdout=f.read()
    # search for successfull completion, crash and warning patterns
    success = string.find(stdout, 'Successfully completed.')
    crash = string.find(stdout, 'Exited')
    warning = string.find(stdout, 'WARNING')
    # increment respective job counters
    if success != (-1):
        goodJobs += 1
    if crash != (-1):
        crashedJobs += 1
        print 'job '+job+' crashed'
#    if warning != -1:
#        commands.getoutput(string[waringn]'')
# print out the results
print 'Total jobs: '+str(numberOfJobs)+' jobs'
print 'Crashed jobs: '+str(crashedJobs)+' jobs'
print 'Successfull jobs: '+str(goodJobs)+' jobs'
# sanity check
if (crashedJobs+goodJobs)!=numberOfJobs:
    print 'ERROR: sum of good and crashed jobs does not equal to the total number of jobs!'
# clean up
os.remove(joblistfilename)


