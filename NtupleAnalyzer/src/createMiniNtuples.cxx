//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                            //
//  libov@mail.desy.de                          //
//  September 2009                              //
//  February 2010                               //
//////////////////////////////////////////////////
/*! \file createMiniNtuples.cxx
    \brief Main program that creates mini ntuples.

    Creates instance of TMiniNtupleCreator class and runs creation process
*/
#include <TChain.h>
#include <TMath.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TSystem.h>
#include <iostream>
using namespace std;

// my includes
#include<inc/TMiniNtupleCreator.h>
#include <TDataset.h>
#include <TSubSet.h>

int main(int argc, char **argv) {

    TString    programName = argv[0];

    Int_t            firstEvent=-1;
    Int_t            lastEvent=-1;

    Bool_t    calculateNevents = false;

    // declare some variables to store command line arguments. they include:
    // properties of the sample
    TSubSet::Type       type;
    TSubSet::Flavour    flavour;
    TSubSet::Period     period;
    TSubSet::Q2         q2;
    TSubSet::Process    process;
    unsigned            trigger_period;

    // helping boolean variables to make sure all the arguments were passed correctly 
    bool                type_set = false;
    bool                flavour_set = false;
    bool                period_set = false;
    bool                q2_set = false;
    bool                trigger_period_set = false;
    bool                process_set = false;

    //----------------------------  OPTIONS HANDLING  -------------------------------//

    opterr = 0;
    int c;
    while ((c = getopt (argc, argv, "t:f:p:q:g:chr:l:o:")) != -1) {
        switch (c) {
            case 't':
                type = (TSubSet::Type) atoi(optarg);
                type_set = true;
                break;
            case 'f':
                flavour = (TSubSet::Flavour) atoi(optarg);
                flavour_set = true;
                break;
            case 'p':
                period = (TSubSet::Period) atoi(optarg);
                period_set = true;
                break;
            case 'q':
                q2 = (TSubSet::Q2) atoi(optarg);
                q2_set = true;
                break;
            case 'g':
                trigger_period = (unsigned) atoi(optarg);
                trigger_period_set = true;
                break;
            case 'o':
                process = (TSubSet::Process) atoi(optarg);
                process_set = true;
                break;
            case 'r':
                firstEvent=atoi(optarg);
                break;
            case 'l':
                lastEvent=atoi(optarg);
                break;
            case 'c':
                calculateNevents=true;
                break;
            case 'h':
                cout<<programName+" usage:"<<endl;

                cout<<"\t-r <1st event>\t\tFIRST EVENT TO PROCESS"<<endl;
                cout<<"\t-l <last event>\t\tLAST EVENT TO PROCESS"<<endl;
                cout<<"\t-c \t\t\tCALCULATE NUMBER OF EVENTS ONLY"<<endl;
                cout<<"\t-h \t\t\tPRINT THIS HELP"<<endl;
                return 0;
            case '?':
                if (optopt == 's')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort ();
        }
    }
    for (int index = optind; index < argc; index++)
        printf ("WARNING: Non-option argument %s\n", argv[index]);

    // helping variable to flag whether there were enough arguments or not
    bool    not_enough_arguments = false;
    
    // these arguments should be specified both for data and mc
    if ( ! (type_set && period_set) ) {
        not_enough_arguments=true;
    }
    
    // for MC there are also additional requirements
    if ( (type_set) && (type == TSubSet::kMC)) {
        if  ( !(flavour_set && q2_set && trigger_period_set) ) not_enough_arguments = true;
    }
    
    // if not enough arguments, inform user and wuit
    if (not_enough_arguments) {
        cout << "\nNot enough aruments to run " << argv[0] << endl;
        cout << "For more info please try:\n\n";
        cout << argv[0] << " -h" << endl;
        cout << "\nThe program will terminate, sorry." << endl;
        exit(-1);
    }

    cout<<"\n\n******************************************************\n";
    cout<<"* Welcome to ZEUS Common Ntuple analysis framework   *\n";
    cout<<"* Step 1: creation of 'private' mini ntuples         *\n";
    cout<<"* Input: root common ntuples                         *\n";
    cout<<"* Output: root mini ntuples                          *\n";
    cout<<"******************************************************\n\n";

    TMiniNtupleCreator * instance = new TMiniNtupleCreator();

    // set properties of the sample as given from the command line
    instance -> setType(type);
    instance -> setPeriod(period);
    if (type == TSubSet::kMC) {
        instance -> setFlavour(flavour);
        instance -> setQ2(q2);
        instance -> setProcess(process);
    }
    instance -> setTriggerPeriod(trigger_period);

    //---------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------//

    // set paths to minintuples
    TString     MINI_NTUPLES_PATH = getenv("MINI_NTUPLES_PATH");
    instance -> SetPathToMiniNtuples(MINI_NTUPLES_PATH);
    // if want to store mini ntuples to the dCache - first write them locally;
    // this specifies that path
    instance -> SetStore_dCache(true);
    TString MINI_NTUPLES_PATH_tmp = getenv("MINI_NTUPLES_PATH_tmp");
    instance -> SetPathToMiniNtuplesTEMP(MINI_NTUPLES_PATH_tmp);

    //---------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------//

    // now initialize the class
    instance -> Initialize();

    // get number of entries (this just returns the value that 
    // was already calculated during the initialization)
    Int_t        Nevents=instance->GetNumberOfEvents();

    // ultimately, one wants first to calculate number of entries and terminate,
    // in order to determine in how many batches this sample should be splitted
    if (calculateNevents) {
        cout << "Nevents= " << Nevents << endl;
        return 0;
    }

    if ((firstEvent < 0) || (lastEvent <= 0) || ( firstEvent >= lastEvent) || (lastEvent>Nevents) )    {
        firstEvent=0;
        lastEvent=Nevents;
        cout<<"INFO: Running full sample:"<<endl;
    } else {
        cout<<"INFO: Running specified event range:"<<endl;
    }

    // print info
    cout << "\tfirstEvent= " << firstEvent << endl;
    cout << "\tlastEvent= " << lastEvent << endl;

    // create mini ntuples
    instance -> CreateMiniNtuples(firstEvent, lastEvent);

    return 0;
}
