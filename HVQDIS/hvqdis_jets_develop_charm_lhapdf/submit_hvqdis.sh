if [ -z $1 ]; then
echo "useage: $0 folder_to_submit"
else
 if [ -z $2 ]; then
  queue="M"
 else
  queue=$2
 fi
 folder=$1
 zarah-jobsub -q $queue -s $folder/run_farm.sh exe/hvq.x $folder/run_hvqdis.sh $ANALYSIS/env.sh
fi
