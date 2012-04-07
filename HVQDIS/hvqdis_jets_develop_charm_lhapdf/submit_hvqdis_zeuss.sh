if [ -z $1 ]; then
echo "useage: $0 folder_to_submit"
else
 if [ -z $2 ]; then
  queue="M"
 else
  queue=$2
 fi
 folder=$1
 jobsub -h zenithsub -q $queue $folder/extract.sh -f $folder/run_farm.sh $folder/hvqben.x $folder/run_hvqdis.sh $folder/ZS_MASSIMO-FFN-3000_MC1.50MB4.75.tar.gz 
fi
