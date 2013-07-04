#!/usr/bin/python
from optparse import OptionParser
import array, os, math

# option parser
parser = OptionParser()
parser.add_option("-b", "--beauty", action="store_true", dest="BEAUTY", default=False, help="run for beauty")
parser.set_defaults(BEAUTY=False)
(options, args) = parser.parse_args()

# check whether charm or beauty and print info
BEAUTY=options.BEAUTY
if not BEAUTY:
    print 'INFO: charm mode'
else:
    print  'INFO: beauty mode'

# suffix to distinguish charm and beauty files
FLAVOUR_SUFFIX='c'
if BEAUTY: FLAVOUR_SUFFIX='b'

# expected number of entries in each file - as a cross check
NLINES = 25921

# available file suffices
files_actual=['EuvDUbar', 'EuvDuv', 'fs23', 'fs38', 'mb43', 'mb50', 'mc135', 'mc165', 'q2015', 'q2025', 'q2cut25', 'q2cut5', 'tot']

# since in the 'tot' file there are also experimental uncertainties, need another list
files=[]

# map of arrays
arrays = {}

# construct filenames for variation, create arrays
for file in files_actual:

    filename='f2'+FLAVOUR_SUFFIX+'/'+'f2'+FLAVOUR_SUFFIX+'_herapdf_'+file+'.dat'

    if file != 'tot':
        files.append(file)
        arrays[file] = array.array('d')
    else:
        files.append('central')
        files.append('exp_up')
        files.append('exp_down')
        arrays['central'] = array.array('d')
        arrays['exp_up'] = array.array('d')
        arrays['exp_down'] = array.array('d')

    file_obj = open(filename, 'r')
    for line in file_obj:
        line=line.strip()
        line_list=line.split()
        first = float(line_list[0])
        second = float(line_list[1])
        third = float(line_list[2])
        if file != 'tot':
            arrays[file].append(first)
            if (first != second) or (first != third):
                sys.exit('ERROR: numbers are different')
        else:
            arrays['central'].append(first)
            arrays['exp_up'].append(second)
            arrays['exp_down'].append(third)

    file_obj.close()


# now forget about original files, work with arrays only
# first check if length of all arrays is correct
for file in files:
    if NLINES != len(arrays[file]):
        os.abort()

# calculate total uncertainty
uncertainty_plus = array.array('d')
uncertainty_minus = array.array('d')
for i in range (0,NLINES):
    uncertainty_plus.append(0)
    uncertainty_minus.append(0)

# sum up the uncertainties
for file in files:
    for i in range (0,NLINES):
        difference = arrays[file][i]-arrays['central'][i]
        if difference > 0: uncertainty_plus[i] += difference**2
        if difference < 0: uncertainty_minus[i] += difference**2

# finally, take the square root and print to file
output = 'f2'+FLAVOUR_SUFFIX+'/'+'f2'+FLAVOUR_SUFFIX+'_herapdf_TOTAL_UNCERTAINTY.dat'
output_file = open(output, 'w')
for i in range (0,NLINES):
    uncertainty_plus[i] = math.sqrt(uncertainty_plus[i])
    uncertainty_minus[i] = math.sqrt(uncertainty_minus[i])
    line = ''
    if i != 0: line = '\n'
    line += str(arrays['central'][i]) + '  ' + str(arrays['central'][i]+uncertainty_plus[i]) + '  ' + str(arrays['central'][i]-uncertainty_minus[i])
    output_file.write(line)
output_file.close()