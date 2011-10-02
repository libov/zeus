# V. Libov, calculation of combined systematic uncertainty
# libov@mail.desy.de
# 29/03/2010
#---------------------------------------------------------------------------------
import os
from math import sqrt
#---------------------------------------------------------------------------------
FileList = ['fitter.fullv2.b.diff', 'fitter.fullv3.b.diff', 'fitter.fullv4.b.diff','fitter.fullv5.b.diff', 'fitter.fullv6.b.diff', 'fitter.fullv7.b.diff','fitter.fullv8.b.diff','fitter.fullv9.b.diff']
# FileList = ['fitter.fullv10.b.diff', 'fitter.fullv11.b.diff']
#---------------------------------------------------------------------------------
HISTO_PATH=os.environ['HISTO_PATH']
Total_Unc_Positive = [0.] * 62
Total_Unc_Negative = [0.] * 62

def	readFile(FileName, values):
	index = 0
	file = open(HISTO_PATH+'/'+FileName, 'read')
	for line in file:
		lineList = line.split()
		if lineList[0]=="#":
			continue
		values[index]=float (lineList[1])
		index+=1
	file.close()

def	chooseValue(up, down):
	plus = 0
	minus =0
	# if both are positive - take larger and assign to positive variation
	if (up>=0) and (down>=0):
		if up>down:
			plus = up
		else:
			plus = down
	# if both are negative - take larger by modulus and assign to negative variation
	if (up<=0) and (down<=0):
		if up>down:
			minus = down
		else:
			minus = up
	# one positive, the other negative
	if (up>0) and (down<0):
		plus =up
		minus =down
	if (up<0) and (down>0):
		plus =down
		minus =up

	return (plus, minus)

def	writeFile(templatefileName, outputfile):
	index = 0
	templatefile=open(HISTO_PATH+'/'+templatefileName, 'read')
	outputfile.write('beauty uncertainty\n')
	for line in templatefile:
		lineList = line.split()
		# print lineList
		if lineList[0]=="#":
			outputfile.write(line)
			continue
		# outstr = lineList[0] + '{0:3f} % {0:3f}'
		#outstr='{0:3f} % {0:3f}'.format(Total_Unc_Positive[index], Total_Unc_Negative[index])
		#outputfile.write(lineList[0]+' '+str(Total_Unc_Positive[index])[0:5]+' %   '+str(Total_Unc_Negative[index])[0:5]+' %\n')
		#print outstr
		outputfile.write(lineList[0]+' '+str(Total_Unc_Positive[index])[0:4]+' %   '+str(Total_Unc_Negative[index])[0:5]+' %\n')
		index+=1

print 'files will be written to current directory'

#for fileName in FileList:
#	print 'processing', fileName
#	readFile(HISTO_PATH, fileName)
yjb_up  = [0.]*62
yjb_down = [0.]*62

empz_up = [0.]*62
empz_down = [0.]*62

eel_up = [0.]*62
eel_down = [0.]*62

jet_up = [0.]*62
jet_down = [0.]*62


readFile('fitter.fullv2.b.diff', yjb_down)
readFile('fitter.fullv3.b.diff', yjb_up)

readFile('fitter.fullv4.b.diff', eel_up)
readFile('fitter.fullv5.b.diff', eel_down)

readFile('fitter.fullv6.b.diff', empz_down)
readFile('fitter.fullv7.b.diff', empz_up)

readFile('fitter.fullv10.b.diff', jet_up)
readFile('fitter.fullv11.b.diff', jet_down)


for index in range(0, len(Total_Unc_Positive)):
	(plusValue_yjb, minusValue_yjb) = chooseValue(yjb_up[index], yjb_down[index])
	(plusValue_empz, minusValue_empz) = chooseValue(empz_up[index], empz_down[index])
	(plusValue_eel, minusValue_eel) = chooseValue(eel_up[index], eel_down[index])
	Total_Unc_Positive[index]=sqrt(plusValue_yjb*plusValue_yjb+plusValue_empz*plusValue_empz+plusValue_eel*plusValue_eel)
	Total_Unc_Negative[index]=(-1)*sqrt(minusValue_yjb*minusValue_yjb+minusValue_empz*minusValue_empz+minusValue_eel*minusValue_eel)

outfile = open('total_uncertainty_DIS', 'write')
writeFile(FileList[0], outfile)
outfile.close()

for index in range(0, len(Total_Unc_Positive)):
	Total_Unc_Positive[index]=0
	Total_Unc_Negative[index]=0

for index in range(0, len(Total_Unc_Positive)):
	(plusValue_jet, minusValue_jet) = chooseValue(jet_up[index], jet_down[index])
	Total_Unc_Positive[index]=plusValue_jet
	Total_Unc_Negative[index]=minusValue_jet

outfile = open('total_uncertainty_Jets', 'write')
writeFile(FileList[0], outfile)
outfile.close()