#!/usr/bin/python
#
# copies all directories from <sourcepath> (that contain <searchString> string) to <destpath> ( from / to dCache )
# assuming that all matching subdirectories in <sourcepath> contain ONLY files, not directories
# (as it is for MC files)
# V. Libov 25 May 2010
# libov@mail.desy.de

import os
import os.path
import commands
from optparse import OptionParser
import sys

#------------------- option section -----------------------
parser = OptionParser()
parser.add_option("-d", "--destpath", dest="destpath", default="", help="Destination Path")
parser.add_option("-s", "--sourcepath", dest="sourcepath", default="", help="Source Path")
parser.add_option("-p", "--searchString", dest="searchString", default="", help="Pattern to be searched")

(options, args) = parser.parse_args()
destpath=options.destpath
sourcepath=options.sourcepath
searchString=options.searchString

print 'destination path: ', destpath
print 'source path: ', sourcepath
print 'searchString: ', searchString
#sys.exit()
#----------------------------------------------------------

dirListFile='directories.list'
#os.chdir(sourcepath)

if os.path.exists(dirListFile):
	print 'deleting '+dirListFile
	os.remove(dirListFile)

# get list of all directories in <sourcepath>
commands.getoutput('ls -1 '+sourcepath+' > '+dirListFile)

fdirlist=open('directories.list','r')

# loop over all directories in <sourcepath>
for dirname in fdirlist:
	# skip if it does not match pattern specified by <searchString>
	if dirname.find(searchString)==-1:
		continue
	dirname=dirname.rstrip("\n")
	source=sourcepath+dirname+'/'
	filelist=os.listdir(source)
	dest=destpath+dirname
	if not os.path.exists(dest):
		os.mkdir(dest)
	for file in filelist:
		print commands.getoutput('dccp '+source+file+' '+dest)
