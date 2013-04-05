#!/usr/bin/python
# This script adds up all the systematic uncertainties in quadrature
# and produces an output file with the results.
# It also prints systematic uncertainties for double differential cross from every source
# in a format suitable for inserting directly in the F2bc paper

##########################################################################
############################## PREPARATIONS ##############################
##########################################################################

# import modules
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
INPUT='/zow/user/libov/WWW/ZEUS_ONLY/F2cb_vtx_paper_May2012'

if BEAUTY:
    SYST_SOURCES=['BRSystematics_beauty', 'FragmFractionSystematics_beauty', 'tracking_map_beauty_systematics_2.78', 'charm_fragmentation_5.0', 'beauty_fragmentation_5.0', 'jet_energy_scale_beauty', 'smearing_core_beauty', 'smearing_tail_beauty', 'lf_asymmetry_beauty', 'et_reweighting_beauty', 'signal_extraction_beauty', 'DIS_y_beauty', 'DIS_Ee_beauty', 'DIS_empz_beauty', 'q2_reweighting_beauty', 'flt_efficiency_beauty', 'EMscale_beauty']
else:
    SYST_SOURCES=['BRSystematics_charm', 'FragmFractionSystematics_charm', 'tracking_map_charm_systematics_2.77', 'charm_fragmentation_4.2', 'beauty_fragmentation_4.2', 'jet_energy_scale_charm', 'smearing_core_charm', 'smearing_tail_charm', 'lf_asymmetry_charm', 'eta_reweighting_charm', 'et_reweighting_charm', 'signal_extraction_charm', 'DIS_y_charm', 'DIS_Ee_charm', 'DIS_empz_charm', 'q2_reweighting_charm', 'flt_efficiency_charm', 'EMscale_charm']

# a directory with input files
OUTPUT=os.getenv('PLOTS_PATH')

# new differential cross-section specifier
if BEAUTY:
    new_xsect_prefix='Beauty systematics in differential cross sections d sigma / dY in bins of'
else:
    new_xsect_prefix='Charm systematics in differential cross sections d sigma / dY in bins of'

# a list to store all variables we have
VARIABLES = ['Eta', 'Et', 'xda', 'q2da', 'x_q2bin1', 'x_q2bin2', 'x_q2bin3', 'x_q2bin4', 'x_q2bin5']
# and another to store only double differential variables
DDIFF_VARIABLES = ['x_q2bin1', 'x_q2bin2', 'x_q2bin3', 'x_q2bin4', 'x_q2bin5']
# and a map to specify number of points (bins) for each variable
NBINS={}

if BEAUTY:
    NBINS['Eta']=10
else:
    NBINS['Eta']=11

NBINS['Et'] = 7
NBINS['xda'] = 6
NBINS['q2da'] = 8
NBINS['x_q2bin1'] = 4
NBINS['x_q2bin2'] = 5
NBINS['x_q2bin3'] = 4
NBINS['x_q2bin4'] = 3
NBINS['x_q2bin5'] = 2

##########################################################################
################# CALCULATE AND PRINT TOTAL SYSTEMATICS ##################
##########################################################################

# print some info
print '\nINFO: taking files with systematic uncertainties from ', INPUT
print 'INFO: writing results to ', OUTPUT, '\n'

# declare a map
uncertainty_pos={}
uncertainty_neg={}

# loop over all elements of SYST_SOURCES array, i.e. all input files which have to be processed
for source in SYST_SOURCES:
    # get the filename and open it
    filename=INPUT+'/'+source
    print 'INFO: opening ', filename
    file=open(filename,'r')
    # create maps for this source
    uncertainty_pos[source]={}
    uncertainty_neg[source]={}
    # loop over lines in the files, i.e. read uncertainties for this source
    for line in file:
        # read the line
        line=line.strip()
        # try to find whether this is a beginning of a new cross section (new variable)
        pos=line.find(new_xsect_prefix)
        if not pos<0:
            # a new differential cross-section is encountered
            # check which one
            variable=line.lstrip(new_xsect_prefix)

            # create maps for this variable
            uncertainty_pos[source][variable]={}
            uncertainty_neg[source][variable]={}
            # stop processing of this line, go to the next one
            continue
        # check whether it's a valid line
        line_list=line.split()
        if line_list==[]: continue
        if line_list[0]!='Bin': continue
        # this must be a line containing systematics for a given source for a given bin in a given variable
        # get the bin number
        index=int(line_list[1].rstrip(':'))
        # and the systematics itself
        syst_first=float(line_list[2])
        syst_second=float(line_list[3])
        # divide by 100 for Sasha's and Philipp's files
        if source=="BRSystematics_charm" or source=="BRSystematics_beauty" or source=="BRSystematics_charm" or source=="FragmFractionSystematics_charm" or source=="FragmFractionSystematics_beauty" or source=="q2_reweighting_beauty" or source=="q2_reweighting_charm" or source=="flt_efficiency_beauty" or source=="flt_efficiency_charm":
            syst_first=syst_first/100
            syst_second=syst_second/100
        # store the values to the maps, depending on the sign
        uncertainty_pos[source][variable][index] = 0
        uncertainty_neg[source][variable][index] = 0
        if (syst_first>0):
            uncertainty_pos[source][variable][index]=syst_first
        else:
            uncertainty_neg[source][variable][index]=syst_first
        if (syst_second>0):
            uncertainty_pos[source][variable][index]=syst_second
        else:
            uncertainty_neg[source][variable][index]=syst_second

# print the results to a file
if BEAUTY:
    filename=OUTPUT+'/total_systematics_beauty'
else:
    filename=OUTPUT+'/total_systematics_charm'
file=open(filename, 'w')

print '\nINFO: printing results to ', filename

file.write('Total systematic uncertainty')

def printme( file, nbins, variable ):
    string='\n\n'+new_xsect_prefix+' '+variable
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

if BEAUTY:
    printme(file, 10, 'Eta')
else:
    printme(file, 11, 'Eta')

printme(file, 7, 'Et')
printme(file, 6, 'xda')
printme(file, 8, 'q2da')
printme(file, 4, 'x_q2bin1')
printme(file, 5, 'x_q2bin2')
printme(file, 4, 'x_q2bin3')
printme(file, 3, 'x_q2bin4')
printme(file, 2, 'x_q2bin5')