# copies all directories from <sourcepath> (that contain <searchString> string) to <destpath> ( from / to dCache )
# assuming that all matching subdirectories in <sourcepath> contain ONLY files, not directories
# (as it is for MC files)

import os
import os.path
import commands

#------------------- option section -----------------------
#destpath =     '/data/zenith234b/libov/REFUNNEL/0607_p/'
destpath =     '/data/zenith234b/libov/REFUNNEL/06_e/charm/'
#destpath =     '/data/zenith234b/libov/REFUNNEL/05_e/'
#destpath =    '/acs/users/libov/MC/rgap30/'
#sourcepath =  '/data/zenith226a/libov/amadeus/events/rgap30/'
#sourcepath =  '/data/zenith234b/libov/'
#sourcepath =   '/acs/users/shehzadi/mcgen/0607_p/'
sourcepath =   '/acs/users/shehzadi/mcgen/06_e/charm/'
#sourcepath =   '/acs/users/shehzadi/mcgen/05_e'
#searchString = 'rg30'
#searchString = ''
#searchString = 'beauty'
#searchString = 'charm'
searchString = 'Q2G4'
#----------------------------------------------------------

dirListFile='directories.list'
#os.chdir(sourcepath)

if os.path.exists(dirListFile):
	print 'deleting '+dirListFile
	os.remove(dirListFile)

commands.getoutput('ls -1 '+sourcepath+' > '+dirListFile)

fdirlist=open('directories.list','r')

for dirname in fdirlist:
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
