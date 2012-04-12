if [ -z $1 ]; then
echo "usage: $0 folder_to_submit iterator_for_2nd_loop"
else
 if [ -z $2 ]; then
  iterator=0
 else
  iterator=$2
 fi
 folder=$1
 rm -f $folder/iterator
 echo $iterator > $folder/iterator
 zarah-jobsub -q M -s $folder/run_farm.sh $folder/iterator exe/hvq.x $folder/run_hvqdis.sh $ANALYSIS/env.sh
 rm $folder/iterator
fi
