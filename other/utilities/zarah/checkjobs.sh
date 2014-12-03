echo `zarah-jobq c | grep RUNNING | wc -l` jobs running
echo `zarah-jobq c | grep COMPLETED | wc -l` jobs completed
echo `zarah-jobq c | grep PENDING | wc -l` jobs pending

