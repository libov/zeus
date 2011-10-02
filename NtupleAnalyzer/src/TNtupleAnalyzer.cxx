//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////

// system includes
#include<fstream>
#include<iostream>
using namespace std;

// ROOT includes
#include <TSystem.h>

// my includes
#include <inc/TNtupleAnalyzer.h>
#include <TSubSet.h>

TNtupleAnalyzer::TNtupleAnalyzer():
fTestNumberOfEvents(10000),
fFileList("NOTSELECTED"),
fPathToMiniNtuples(getenv ("MINI_NTUPLES_PATH")),
fMiniNtuplesOn_dCache(true)
{
    // done here (rather than in BaseClass) in order to keep BaseClass as simple as possible
    fChain = new TChain("orange");
}

void TNtupleAnalyzer::Init() {

    // print welcome message
    cout << "INFO: Initialization of TNtupleAnalyzer object..." << endl;

    // add special ZEUS-dCache libraries
    gSystem->Load("libzio.so");
    gSystem->Load("libdcap.so");

    // initializes fDataset and fSubSet members
    getSubSet();

    // constructs name of the sample and sets it
    getSampleName();

    // print some info messages; TODO: possibly add Print() method so that all the information 
    // will be printed once and not spread everywhere
    cout << "INFO: Sample name: " << fSampleName << endl;

    // check whether this is MC or DATA and set fIsMC flag accordingly
    // this flag is used in several places, e.g. in SetBranchAddress() method
    CheckIfMC();

    // Get the path to minintuples and set fPathToMiniNtuples to it
    fPathToMiniNtuples += "/" + fSampleName;

    // print properties of the sample
    fSubSet.Print();

    cout << "INFO: Initialization of TNtupleAnalyzer object done!" << endl;
}


void TNtupleAnalyzer::CalculateNumberOfEvents() {
    cout<<"\nCalculating number of Events"<<endl;
    fNevents=fChain -> GetEntries();
    cout<<fNevents<<"  events in this chain"<<endl;
}

Int_t TNtupleAnalyzer::GetNumberOfEvents() {
    return	fNevents;
}

void TNtupleAnalyzer::SetTestMode(Bool_t mode) {
    fTestMode=mode;
}

void TNtupleAnalyzer::SetTestNumberOfEvents (Int_t	TestNumberOfEvents) {
    fTestNumberOfEvents=TestNumberOfEvents;
}

void TNtupleAnalyzer::getSubSet() {

    // first, open the XML file containing information about the samples
    // NOTE: macro are used again here, think if this is not just an additional complication
    // one could introduce another variable to see whcih CN version this is and which file to open!
    // THE FILENAMES ARE HARDCODED!
    TString   XMLfilename;
    #ifdef CN_VERSION_V02
        XMLfilename = "samples.v02.xml";
    #elif CN_VERSION_V04
        XMLfilename = "samples.v04.xml";
    #elif CN_VERSION_V06
        XMLfilename = "samples.v06.xml";
    #else
        cout << " Common Ntuple version is not set or not supported." << endl;
        cout << " Please define -DCN_VERSION_V02 or -DCN_VERSION_V04 or -DCN_VERSION_V06 in the Makefile depending on CN version.\n";
        cout << " Terminating, sorry." << endl;
        abort();
    #endif

    // open the XML file and create TDataset structure from it
    fDataset = TDataset(XMLfilename);
    // now get a TSubSet object using sample properties set before (to fSubSet variable)
    if (fSubSet.getTypeENUM() == TSubSet::kMC) {
        fSubSet = fDataset.getSubSet(fSubSet.getTypeENUM(), fSubSet.getPeriodENUM(), fSubSet.getFlavourENUM(), fSubSet.getQ2ENUM(), fSubSet.getProcessENUM(), fSubSet.getTriggerPeriod());
    } else if (fSubSet.getTypeENUM() == TSubSet::kDATA) {
        fSubSet = fDataset.getSubSet(fSubSet.getTypeENUM(), fSubSet.getPeriodENUM());
    }
}

void TNtupleAnalyzer::getSampleName() {
    
    // get properties of the sample
    TString     year = fSubSet.getYear();
    TString     type = fSubSet.getType();
    TString     CN_version = fSubSet.getCNversion();
    TString     name_pattern = fSubSet.getNamePattern();
    
    // construct sample name according to our convention
    fSampleName = type + year + CN_version + name_pattern;
}

void TNtupleAnalyzer::CheckIfMC () {

    if (fSubSet.getTypeENUM() == TSubSet::kDATA) {
        fIsMC = false;
    } else if (fSubSet.getTypeENUM() == TSubSet::kMC) {
        fIsMC = true;
    } else {    // sanity check
        cout << "unknown type of the sample. terminating" << endl;
        abort();
    }
}

void TNtupleAnalyzer::AddFilesToChain() {

    // construct file name containing list of ROOT files to be added to this chain
    // in case it was not explicitely set
    if (fFileList=="NOTSELECTED") fFileList=fSampleName+".txt";
    // if "filelists" directory is present, read filelist from it, otherwise from the current path
    struct stat st;
    if(stat("filelists",&st) == 0) fFileList = "filelists/"+fFileList;

    // open the text file
    ifstream NtupleListFile;
    NtupleListFile.open (fFileList);

    // loop over lines of the text file
    string line;
    Int_t   FilesNumber=0;
    if (NtupleListFile.is_open()) {
        while (! NtupleListFile.eof() ) {
            getline (NtupleListFile, line);
            // add a ROOT file to chain
            if (!line.empty()) {
                fChain -> Add(line.c_str());
                FilesNumber++;
                cout << "INFO: added " << line << endl;
            }
        }
        NtupleListFile.close();
        cout<<FilesNumber<<" files added to chain"<<endl;
    } else { // complain
        cout<<"Unable to open file with ntuple list ("<<fFileList<<"). The program will terminate, sorry."<<endl;
        exit(-1);
    }
}
