#!/usr/bin/python
# this scripts adds up all the systematic uncertainties in quadrature
# and produces an output file with the results

import os, math
from optparse import OptionParser

# options parsing
parser = OptionParser()
parser.add_option("-b", "--beauty", action="store_true", dest="BEAUTY", default=False, help="run for beauty systematics")
parser.set_defaults(BEAUTY=False)
(options, args) = parser.parse_args()

# check whether charm or beauty and print info
BEAUTY=options.BEAUTY
if not BEAUTY:
    print 'INFO: charm mode'
else:
    print  'INFO: beauty mode'

# a directory with input files
INPUT='/zow/user/libov/WWW/F2cb_vtx_paper_May2012'

if BEAUTY:
    SYST_SOURCES=['BRSystematics_beauty', 'FragmFractionSystematics_beauty', 'tracking_map_beauty_2.49', 'charm_fragmentation_5.0', 'beauty_fragmentation_5.0', 'jet_energy_scale_beauty', 'smearing_core_beauty', 'smearing_tail_beauty', 'lf_asymmetry_beauty', 'et_reweighting_beauty', 'signal_extraction_beauty', 'DIS_y_beauty', 'DIS_Ee_beauty', 'DIS_empz_beauty']
else:
    SYST_SOURCES=['BRSystematics_charm', 'FragmFractionSystematics_charm', 'tracking_map_charm_2.48', 'charm_fragmentation_4.2', 'beauty_fragmentation_4.2', 'jet_energy_scale_charm', 'smearing_core_charm', 'smearing_tail_charm', 'lf_asymmetry_charm', 'eta_reweighting_charm', 'et_reweighting_charm', 'signal_extraction_charm', 'DIS_y_charm', 'DIS_Ee_charm', 'DIS_empz_charm']

# a directory with input files
OUTPUT=os.getenv('PLOTS_PATH')

# new differential cross-section specifier
if BEAUTY:
    new_xsect_prefix='Beauty systematics in differential cross sections d sigma / dY in bins of'
else:
    new_xsect_prefix='Charm systematics in differential cross sections d sigma / dY in bins of'



# print some info
print '\nINFO: taking files with systematic uncertainties from ', INPUT
print 'INFO: writing results to ', OUTPUT, '\n'

# declare a map
uncertainty_pos={}
uncertainty_neg={}

# a flag to say whether this is the first file we study (in this case, the map elements are created)
first_file = True

# loop over all elements of SYST_SOURCES array, i.e. all input files which have to be processed
for source in SYST_SOURCES:
    # get the filename and open it
    filename=INPUT+'/'+source
    print 'INFO: opening ', filename
    file=open(filename,'r')
    # loop over lines in the files, i.e. read uncertainties for this source
    for line in file:
        line=line.strip()
        pos=line.find(new_xsect_prefix)
        if not pos<0:
            # a new differential cross-section is encountered
            # check which one
            variable=line.lstrip(new_xsect_prefix)

            # if a first file, create a new element of map, which is itself a map
            if first_file:
                uncertainty_pos[variable]={}
                uncertainty_neg[variable]={}
            continue
        line_list=line.split()
        if line_list==[]: continue
        if line_list[0]!='Bin': continue
        index=int(line_list[1].rstrip(':'))
        syst_pos=float(line_list[2])
        syst_neg=float(line_list[3])
        # create a zero element if the first file
        if first_file:
            uncertainty_pos[variable][index]=0
            uncertainty_neg[variable][index]=0
        # divide by 100 for Sasha's files
        if source=="BRSystematics_charm" or source=="BRSystematics_beauty" or source=="BRSystematics_charm" or source=="FragmFractionSystematics_charm" or source=="FragmFractionSystematics_beauty":
            syst_pos=syst_pos/100
            syst_neg=syst_neg/100
        # add systematics in quadrature
        uncertainty_pos[variable][index]+=syst_pos**2
        uncertainty_neg[variable][index]+=syst_neg**2
    first_file = False

# print the results to a file
if BEAUTY:
    filename=OUTPUT+'/total_systematics_beauty'
else:
    filename=OUTPUT+'/total_systematics_charm'
file=open(filename, 'w')

print '\nINFO: printing results to ', filename

file.write('Total systematic uncertainty')

def printme( file, nbins, variable ):
    string='\n\n'+new_xsect_prefix+variable
    file.write(string)
    for i in range(1,nbins+1):
        string='\nBin '
        string+=str(i)
        string+=': +'
        string+=str(math.sqrt(uncertainty_pos[variable][i]))
        string+=' -'
        string+=str(math.sqrt(uncertainty_neg[variable][i]))
        file.write(string)
    return


printme(file, 11, 'Eta')
printme(file, 4, 'Et')
printme(file, 6, 'xda')
printme(file, 8, 'q2da')
printme(file, 4, 'x_q2bin1')
printme(file, 5, 'x_q2bin2')
printme(file, 4, 'x_q2bin3')
printme(file, 3, 'x_q2bin4')
printme(file, 2, 'x_q2bin5')