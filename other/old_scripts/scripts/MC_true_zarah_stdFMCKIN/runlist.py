#
#
#
#
#
#
#
#""" create .cxx files with different inputs from dCache """
temp=0
flist=open('listMCdijetPHP','r')
counter=0
while True:
	# first create file which contains paths to 10 input file on dcache
	ftemp=open('templist','w')
	for x in range(20):
		line=flist.readline()
		print 'reading:'+line
		if line=='':
			break
		ftemp.write(line)
	ftemp.close()
	# then make string with name of output file
	#part1='Int_t temp=sprintf(name,"/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/batch'
	part1='Int_t temp=sprintf(name,"batch'
	part2=str(counter)
	part3='.root");'
	outname=part1+part2+part3
	print outname
	#now start creation of new .cxx file
	tempstr1='true_'+str(counter)+'.cxx'
	fout=open(tempstr1,'w')
	fexamp=open('EXAMPLE.cxx','r')
	#copying of content of fexamp file to fout
	while True:
		tempstr2=fexamp.readline()
		#print tempstr2
		if tempstr2=='//input\n':
			ftemp=open('templist','r')
			while True:
				tempstr=ftemp.readline()
				print tempstr
				if tempstr=='':
					ftemp.close()
					break
				fout.write(tempstr)
				print 'writing: '+tempstr
		if tempstr2=='//output\n':
			print 'here3'
			fout.write(outname)
		if tempstr2=='//STOP\n':
			print 'here4'
			break
		if tempstr2=='':
			break
		fout.write(tempstr2)
	fexamp.close()
	fout.close()
	counter=counter+1
	if line=='':
		break
print str(counter)+' files created'
flist.close()
