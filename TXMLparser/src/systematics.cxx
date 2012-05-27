//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav,                            //
//  DESY,                                       //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

// system headers
#include <iostream>
#include <fstream>
#include <getopt.h>
using namespace std;

// custom headers
#include <TSystematics.h>

// main function
int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"file", required_argument, 0, 1},
        {"scaling_factors", no_argument, 0, 2},
        {"correct_cross_sections", no_argument, 0, 3},
        {"cross_sections_XMLfile", required_argument, 0, 4}
    };

    // results of the command line option processing will be stored here
    TString file;
    bool scaling_factors = false;
    bool correct_cross_sections = false;
    TString cross_sections_XMLfile;

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                file = optarg;
                break;
            case 2:
                scaling_factors = true;
                break;
            case 3:
                correct_cross_sections = true;
                break;
            case 4:
                cross_sections_XMLfile = optarg;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "./systematics --file <config file> [Options] [-h]\n\n";
                cout << " AVAILABLE CONFIGURATION FILES:\n";
                system("ls config | grep -v README");
                cout << "\nOptions:\n";
                cout << "--scaling_factors - determine the systematics based on the scaling factor (default: based on the xsect)\n\n";
                cout << "--correct_cross_sections - correct cross-sections by \"systematic uncertainty\"\n\n";
                cout << "--cross_sections_XMLfile - XML filename to be corrected\n\n";
                cout << "-h - Show this help\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // open the config file with settings
    TString path = "config/"+file;
    ifstream f(path);
    if (!f.is_open()) {
        cout << "ERROR: could not open configuration file " << path << endl;    
        abort();
    }
    cout << "INFO: opened " << path << " for reading" << endl;

    // a string to store a line we read from the configuration file
    string line;

    // read the  number of points
    getline(f, line);
    const unsigned NPOINTS = atoi(line.c_str());
    cout << "\nINFO: number of scan points:\t\t\t" << NPOINTS << endl;

    // get the values of a scan variable
    getline(f, line);
    double  x[NPOINTS];
    unsigned array_counter = 0;
    // split the line into tokens
    char * pch;
    char * str=(char*)line.c_str();
    pch = strtok (str ," ");
    while (pch != NULL) {
        x[array_counter] = atof(pch);
        array_counter++;
        pch = strtok (NULL," ");
    }

    // sanity check
    if ( array_counter != NPOINTS ) {
        cout << "ERROR: the number of scan points does not match the length of the array" << endl;
        abort();
    }

    cout << "INFO: values of scan variables:\t\t\t";
    for (int i=0; i<NPOINTS; i++) cout << x[i] << ", ";
    cout << endl;

    // get the corresponding analysis version
    getline(f, line);
    TString version[NPOINTS];
    array_counter = 0;
    // split the line into tokens
    str=(char*)line.c_str();
    pch = strtok (str ," ");
    while (pch != NULL) {
        version[array_counter] = pch;
        array_counter++;
        pch = strtok (NULL," ");
    }

    // sanity check
    if ( array_counter != NPOINTS ) {
        cout << "ERROR: the number of scan points does not match the length of the array" << endl;
        abort();
    }

    cout << "INFO: values of analysis versions:\t\t";
    for (int i=0; i<NPOINTS; i++) cout << version[i] << ", ";
    cout << endl;

    // get the default value of the scan variable
    getline(f, line);
    Double_t scan_default_value = atof(line.c_str());
    cout << "INFO: Default value of the scan variable:\t" << scan_default_value << endl;

    // get the variations
    getline(f, line);
    // split the line into tokens
    str=(char*)line.c_str();
    pch = strtok (str ," ");
    Double_t up_variation = atof(pch);

    // by default, down variation is equal to up variation, i.e. symmetric uncertainty
    Double_t down_variation = up_variation;
    // try to get the second token which corresponds to down_variation
    pch = strtok (NULL ," ");
    if (pch != NULL) down_variation = atof(pch);
    
    cout << "INFO: Up-variation of the scan variable:\t" << up_variation << endl;
    cout << "INFO: Down-variation of the scan variable:\t" << down_variation << endl;

    // get the default value of the scan variable
    getline(f, line);
    TString x_axis_title = line;
    cout << "INFO: Scan variable description:\t\t" << x_axis_title << endl;

    // get the binning
    getline(f, line);
    TString binning = line;
    cout << "INFO: binning:\t\t\t\t\t" << binning << endl;

    // get the years
    getline(f, line);
    TString years = line;
    cout << "INFO: periods:\t\t\t\t\t" << years << endl << endl;

    // create an instance of TSystematics object
    TSystematics instance;

    // set number of points in the scan
    instance.SetNpoints(NPOINTS);

    // set necessary information
    instance.SetXArray(x);
    instance.SetVersionArray(version);

    instance.SetDefault(scan_default_value);
    instance.SetUpVariation(up_variation);
    instance.SetDownVariation(down_variation);
    
    instance.SetYaxisLowLimit(0);
    if (scaling_factors) {
        instance.SetDrawCrossSections(false);
        instance.SetYaxisUpLimit(2);
    } else {
        instance.SetDrawCrossSections(true);
    }

    instance.SetXAxisTitle(x_axis_title);
    instance.SetBinningFile(binning);
    instance.SetYears(years);
    instance.SetOutputFileName(file);

    // initialize the object
    instance.Initialize();

    // draw for all bins
    instance.DrawAll();

    // correct cross-sections if selected
    if (correct_cross_sections) {
        instance.CorrectCrossSections(cross_sections_XMLfile);
    }
 
    return  0;
}
