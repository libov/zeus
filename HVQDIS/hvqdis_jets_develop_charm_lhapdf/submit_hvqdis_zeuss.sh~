if [ -z $1 ]; then
echo "useage: $0 folder_to_submit"
else
 if [ -z $2 ]; then
  queue="M"
 else
  queue=$2
 fi
 folder=$1
 jobsub -h zenithsub -q $queue $folder/run_farm.sh -f $folder/hvqben.x $folder/run_hvqdis.sh $folder/cteq5f4.tbl  $folder/cteq5f3.tbl 
fi
