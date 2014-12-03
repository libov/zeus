#!/bin/bash
#----------------------------------------------------------
# utility for recursive copying with dccp
# 
# note: could be further improved (can work even if argument is a file)
# 
#----------------------------------------------------------

#----------------------------------------------------------
# recursive copy function definition
#----------------------------------------------------------
function copy_directory {
 CURRENT_DIR=$1
 mkdir $OUTPUTDIR/$CURRENT_DIR
 for object in $CURRENT_DIR/*; do
  if [ -d $object ]; then
    copy_directory $object
  elif [ -f $object ]; then
    dccp -d4 $object $OUTPUTDIR/$CURRENT_DIR # && rm -f $object
  fi
 done
 CURRENT_DIR=$1	# needs to be set again, it's overriden in deeper recursions!
if ! [ "$(ls -A $CURRENT_DIR)" ]; then
  rm -r $CURRENT_DIR
fi
}
#----------------------------------------------------------
# end recursive function definition
#----------------------------------------------------------

#----------------------------------------------------------
# main program
#----------------------------------------------------------
# arguments handling; help user if usage is wrong
if [ $# -ne 2 ]; then
 echo
 echo Not enough arguments or too many arguments.
 echo Correct usage of the script:
 echo $0 "<"INPUT directory">" "<"OUTPUT directory">"
 echo Exiting...
 echo
 exit
fi
INPUTDIR=$1
OUTPUTDIR=$2

# make sure the argument is the name of the existing directory
if ! [ -d $INPUTDIR ]; then
 echo Directory $INPUTDIR does not exists. Please make sure you provide correct name. Exiting...
 exit
fi
# copy the directory
copy_directory $INPUTDIR
# end main program
#----------------------------------------------------------
