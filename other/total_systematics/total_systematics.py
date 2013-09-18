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
INPUT='/zow/user/libov/WWW/ZEUS_ONLY/F2cb_vtx_paper_May2012/systematics'

if BEAUTY:
    SYST_SOURCES=['BRSystematics_beauty', 'FragmFractionSystematics_beauty', 'tracking_map_beauty_systematics_2.78', 'charm_fragmentation_5.0', 'beauty_fragmentation_5.0', 'jet_energy_scale_beauty', 'smearing_core_beauty', 'smearing_tail_beauty', 'lf_asymmetry_beauty', 'eta_reweighting_beauty_v2_2.60', 'et_reweighting_beauty', 'etabeauty_reweighting_beauty', 'etbeauty_reweighting_beauty', 'signal_extraction_beauty', 'DIS_y_beauty', 'DIS_Ee_beauty', 'DIS_empz_beauty', 'q2_reweighting_beauty', 'flt_efficiency_beauty', 'EMscale_beauty']
else:
    SYST_SOURCES=['BRSystematics_charm', 'FragmFractionSystematics_charm', 'tracking_map_charm_systematics_2.77', 'charm_fragmentation_4.2', 'beauty_fragmentation_4.2', 'jet_energy_scale_charm', 'smearing_core_charm', 'smearing_tail_charm', 'lf_asymmetry_charm', 'eta_reweighting_charm', 'et_reweighting_charm', 'etabeauty_reweighting_charm', 'etbeauty_reweighting_charm', 'signal_extraction_charm', 'DIS_y_charm', 'DIS_Ee_charm', 'DIS_empz_charm', 'q2_reweighting_charm', 'flt_efficiency_charm', 'EMscale_charm']

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
uncertainty_first={}
uncertainty_second={}

# loop over all elements of SYST_SOURCES array, i.e. all input files which have to be processed
for source in SYST_SOURCES:
    # get the filename and open it
    filename=INPUT+'/'+source
    print 'INFO: opening ', filename
    file=open(filename,'r')
    # create maps for this source
    uncertainty_first[source]={}
    uncertainty_second[source]={}
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
            uncertainty_first[source][variable]={}
            uncertainty_second[source][variable]={}
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
        uncertainty_first[source][variable][index] = syst_first
        uncertainty_second[source][variable][index] = syst_second

# print the results to a file
if BEAUTY:
    filename=OUTPUT+'/total_systematics_beauty'
else:
    filename=OUTPUT+'/total_systematics_charm'
file=open(filename, 'w')

print '\nINFO: printing results to ', filename

file.write('Total systematic uncertainty')

def printme( file, variable ):
    string='\n\n'+new_xsect_prefix+' '+variable
    file.write(string)
    for i in range(1,NBINS[variable]+1):
        # sum up in quadrature systematics from different sources
        pos = 0
        neg = 0
        for source in SYST_SOURCES:
            if uncertainty_first[source][variable][i] > 0:
                pos = pos+uncertainty_first[source][variable][i]**2
            else:
                neg = neg+uncertainty_first[source][variable][i]**2

            if uncertainty_second[source][variable][i] > 0:
                pos = pos+uncertainty_second[source][variable][i]**2
            else:
                neg = neg+uncertainty_second[source][variable][i]**2
        pos = math.sqrt(pos)
        neg = math.sqrt(neg)
        string='\nBin '
        string+=str(i)
        string+=': +'
        string+=str(pos)
        string+=' -'
        string+=str(neg)
        file.write(string)
    return

# Print total systematics for every variable to the file
for variable in VARIABLES:
    printme(file, variable)

##########################################################################
################## PRINT SYSTEMATICS FROM EVERY SOURCE ##################
##########################################################################

# fist merge certain elements, in particular three DIS variations as one, smearing, and BR/fractions
def merge(sources_to_merge, new_source):
    uncertainty_first[new_source]={}
    uncertainty_second[new_source]={}
    for variable in VARIABLES:
        uncertainty_first[new_source][variable]={}
        uncertainty_second[new_source][variable]={}
        for bin in range (1, NBINS[variable]+1):
            pos=0
            neg=0
            for source in sources_to_merge:
                
                if uncertainty_first[source][variable][bin] > 0:
                    pos += uncertainty_first[source][variable][bin]**2
                if uncertainty_second[source][variable][bin] > 0:
                    pos += uncertainty_second[source][variable][bin]**2

                if uncertainty_first[source][variable][bin] < 0:
                    neg += uncertainty_first[source][variable][bin]**2
                if uncertainty_second[source][variable][bin] < 0:
                    neg += uncertainty_second[source][variable][bin]**2
                
            uncertainty_first[new_source][variable][bin] = math.sqrt(pos)
            uncertainty_second[new_source][variable][bin] = -math.sqrt(neg)
    return

if BEAUTY:
    merge(['BRSystematics_beauty', 'FragmFractionSystematics_beauty'], 'BR_frag_frac_beauty')
    merge(['DIS_y_beauty', 'DIS_Ee_beauty', 'DIS_empz_beauty'], 'DIS_beauty')
else:
    merge(['BRSystematics_charm', 'FragmFractionSystematics_charm'], 'BR_frag_frac_charm')
    merge(['DIS_y_charm', 'DIS_Ee_charm', 'DIS_empz_charm'], 'DIS_charm')

# take into account these changes and also change the order so that it matches that of the Table 1 in the paper

if BEAUTY:
    SYST_SOURCES_DDIFF=['DIS_beauty', 'flt_efficiency_beauty', 'tracking_map_beauty_systematics_2.78', 'smearing_core_beauty', 'smearing_tail_beauty', 'signal_extraction_beauty', 'jet_energy_scale_beauty',
                        'EMscale_beauty', 'q2_reweighting_beauty', 'et_reweighting_beauty', 'eta_reweighting_beauty', 'lf_asymmetry_beauty', 'charm_fragmentation_5.0',
                        'beauty_fragmentation_5.0', 'BR_frag_frac_beauty']
else:
    SYST_SOURCES_DDIFF=['DIS_charm', 'flt_efficiency_charm', 'tracking_map_charm_systematics_2.77', 'smearing_core_charm', 'smearing_tail_charm', 'signal_extraction_charm', 'jet_energy_scale_charm',
                        'EMscale_charm', 'q2_reweighting_charm', 'et_reweighting_charm', 'eta_reweighting_charm', 'lf_asymmetry_charm', 'charm_fragmentation_4.2',
                        'beauty_fragmentation_4.2', 'BR_frag_frac_charm']

BIN_RANGE_Q2_X={}
for variable in DDIFF_VARIABLES:
    BIN_RANGE_Q2_X[variable]={}

BIN_RANGE_Q2_X['x_q2bin1'][1]= '5 	& 20 	& 8e-05  & 0.0002'
BIN_RANGE_Q2_X['x_q2bin1'][2]= '5 	& 20 	& 0.0002 & 0.0003'
BIN_RANGE_Q2_X['x_q2bin1'][3]= '5 	& 20 	& 0.0003 & 0.0005'
BIN_RANGE_Q2_X['x_q2bin1'][4]= '5 	& 20 	& 0.0005 & 0.003'

BIN_RANGE_Q2_X['x_q2bin2'][1]= '20 	& 60 	& 0.0003 & 0.0005'
BIN_RANGE_Q2_X['x_q2bin2'][2]= '20 	& 60 	& 0.0005 & 0.0012'
BIN_RANGE_Q2_X['x_q2bin2'][3]= '20 	& 60 	& 0.0012 & 0.002'
BIN_RANGE_Q2_X['x_q2bin2'][4]= '20 	& 60 	& 0.002  & 0.0035'
BIN_RANGE_Q2_X['x_q2bin2'][5]= '20 	& 60 	& 0.0035 & 0.01'

BIN_RANGE_Q2_X['x_q2bin3'][1]= '60 	& 120 	& 0.0008 & 0.0018'
BIN_RANGE_Q2_X['x_q2bin3'][2]= '60 	& 120 	& 0.0018 & 0.003'
BIN_RANGE_Q2_X['x_q2bin3'][3]= '60 	& 120 	& 0.003  & 0.006'
BIN_RANGE_Q2_X['x_q2bin3'][4]= '60 	& 120 	& 0.006  & 0.04'

BIN_RANGE_Q2_X['x_q2bin4'][1]= '120 	& 400 	& 0.0016 & 0.005'
BIN_RANGE_Q2_X['x_q2bin4'][2]= '120 	& 400 	& 0.005  & 0.016'
BIN_RANGE_Q2_X['x_q2bin4'][3]= '120 	& 400 	& 0.016  & 0.06'

BIN_RANGE_Q2_X['x_q2bin5'][1]= '400 	& 1000 	& 0.005  & 0.02'
BIN_RANGE_Q2_X['x_q2bin5'][2]= '400 	& 1000 	& 0.02   & 0.1'

def print_ddiff( file, variable ):
    string='\n\n% '+new_xsect_prefix+' '+variable + '\n'
    file.write(string)
    for i in range(1, NBINS[variable]+1):

        # skip the 4th x bin in the 3rd q2 bin
        if BEAUTY and variable == 'x_q2bin3' and i == 4: continue

        file.write(BIN_RANGE_Q2_X[variable][i])
        for source in SYST_SOURCES_DDIFF:
            # at the moment there is no file for eta reweighting syst. for beauty, therefore skip it 
            if BEAUTY and source == 'eta_reweighting_beauty':
                continue 

            first = uncertainty_first[source][variable][i]
            second = uncertainty_second[source][variable][i]
            sfirst = str(100 * first)
            ssecond = str(100 * second)

            suffix1 = ''
            suffix2 = ''
            if first>0: suffix1='+'
            if second>0: suffix2='+'
            if first==0: sfirst=''
            if second==0: ssecond=''
            if first!=0 and second!=0:
                file_double_diff.write(' & \\numpmerr{' + suffix1 + sfirst + '}{' + suffix2 + ssecond + '}{2}')
            elif first!=0 or second!=0:
                file_double_diff.write(' & \\footnotesize \\num[round-precision=2,round-mode=places]{' + suffix1 + sfirst + suffix2 + ssecond+'}')
            else:
                file_double_diff.write(' & \\footnotesize +0.00')
        file_double_diff.write(' \\\\\n')
    return

if BEAUTY:
    filename_double_diff=OUTPUT+'/double_diff_systematics_beauty'
else:
    filename_double_diff=OUTPUT+'/double_diff_systematics_charm'
file_double_diff=open(filename_double_diff, 'w')

file_double_diff.write('\multicolumn{2}{c|}{\Qsq} & \multicolumn{2}{c|}{$x$}') 
for i in range(1,len(SYST_SOURCES_DDIFF)+1):
    # for the timebeing we skip delta_10 for beauty
    if BEAUTY and i == 11: continue
    if i<4:
        file_double_diff.write(' & $\delta_{'+str(i)+'}$')
    elif i==4:
        file_double_diff.write(' & $\delta_{4}^{core}$')
    elif i==5:
        file_double_diff.write(' & $\delta_{4}^{tail}$')
    else:
        file_double_diff.write(' & $\delta_{'+str(i-1)+'}$')

file_double_diff.write(' \\\\\n')

file_double_diff.write('\multicolumn{2}{c|}{(\gev$^{2}$)} & \multicolumn{2}{c|}{}')
for i in range(1,len(SYST_SOURCES_DDIFF)+1):
    # for the timebeing we skip delta_10 for beauty
    if BEAUTY and i == 11: continue
    file_double_diff.write(' & {(\\%)}')
file_double_diff.write(' \\\\ \hline \n')

# Finally, print the results
for variable in DDIFF_VARIABLES:
    print_ddiff(file_double_diff, variable)
