def fill(name):
	fin=open(name,'r')
	fout=open('listMCdijetPHP','w')
	while True:
		tempstr=fin.readline(41)  # use readline(41) instead of readline() because the
		                          # latter adds newline character
		if tempstr=='':
			break
		path='myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/'
		fout.write(path+tempstr+'");\n')
		tempstr=fin.readline()		#once again to move to the next row
	fin.close()
	fout.close()