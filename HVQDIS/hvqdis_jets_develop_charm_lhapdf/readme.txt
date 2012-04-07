how to run hvqdis on the farm:

go to 
~/zeus/hvqdis
first edit the script 
./hvqdis_farm/run_farm.sh
change the loops for mass variation and q2 x ranges and set the number of items in the loop to about 2 by editing the 
for i in 1 2 3 4 5 6 ...
e.g. to
for i in 3 4

execute 
./submit_hvqdis.sh hvqdis_farm
to send the job

edit the loop to run over the next 2 items
for i in 5 6

execute the submitscript again ...
