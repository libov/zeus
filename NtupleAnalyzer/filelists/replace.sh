for file in *06ev06b*; do
	echo processing $file
	mv $file $file.tmp
	sed 's/\/acs/zeus:\/\/acs/g' $file.tmp > $file
	rm $file.tmp
done
