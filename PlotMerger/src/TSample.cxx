//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////
#include <inc/TSample.h>
#include <TFile.h>
#include <TKey.h>
#include <TStopwatch.h>
#include <iostream>
using namespace std;

TSample::TSample(TSubSet subset, Float_t relative_luminosity, TString HistogramsVersion):
fHistogramsVersion(HistogramsVersion),
fRelativeLuminosity(relative_luminosity),
fSubSet(subset)
{
    // open the file
    fInputHistogramsFile = OpenInputFile();

    // sanity check
    if  (fInputHistogramsFile -> IsZombie()) {
        cout << "ERROR(TSample): could not open a file with histograms: " << fInputHistogramsFile -> GetName() << endl;
    }
    // info message
    cout << "INFO(TSample): Added histogram file: " << fInputHistogramsFile -> GetName() << endl;

    // get number if bins and number of histograms in each bin
    CalculateNumberOfBinsHistos();
}

TFile* TSample::OpenInputFile() {
    TFile *myFile;
    TString HistName="/analysis." + fSubSet.getSampleName() + "."+fHistogramsVersion+".root";
    TString HISTO_PATH = getenv("HISTO_PATH");
    TString PathToHistogramsFile = HISTO_PATH + HistName;
    myFile = new TFile(PathToHistogramsFile, "read");
    return myFile;
}

void TSample::CalculateNumberOfBinsHistos() {

    // clear the vector - just to be safe, probably not needed
    fVectorOfHistograms.clear();
    fVectorOfBins.clear();

    // loop over all entities in this file - the .root output of analysis step
    TIter nextBin(fInputHistogramsFile->GetListOfKeys());
    TKey* keyBins;
    Bool_t firstBin=true;
    while( (keyBins=(TKey*)nextBin()) ) {

        // check that this is a TDirectory (there also might be histograms in the top level directory)
        if ( ( (TString) keyBins -> GetClassName() ) != "TDirectoryFile" )    continue;

        // get a name of the directory
        TString SubDirName = keyBins -> GetName();
        fVectorOfBins.push_back(SubDirName);

        // loop over histograms and store it's name; should be done only for the first bin;
        // for the other we do a partial sanity check - that of number of histograms
        TList *ListOfKeys = fInputHistogramsFile -> GetDirectory(SubDirName) -> GetListOfKeys();
        TIter nextHisto(ListOfKeys);
        TKey    *keyHisto;
        if (firstBin) {
            while((keyHisto=(TKey*)nextHisto())) {
                TString HistoName = keyHisto->GetName();
                fVectorOfHistograms.push_back(HistoName);
            }
            // save the number of bins
            fNumberOfHistograms = fVectorOfHistograms.size();
        }

        // sanity check: compare the number histograms to number of keys TODO: more comments
        if (fNumberOfHistograms != (ListOfKeys->GetEntries()) ) {
            if (firstBin) {
                cout<<"ERROR: Vector size is different from number of keys (histos)!! "<<endl;
            } else {
                cout<<"ERROR: Number of histograms in different bins is differrent!"<<endl;
            }
            abort();
        }
        firstBin = false;
    }   // end loop over bins

    // in the above loop, we get all the directories in memory
    // the following command clears this memory
    // otherwise it will be there till the end of the merging step,
    // and for all heraII can occupy up to 400M! (September2011)
    fInputHistogramsFile -> GetList() -> Clear();
    
    // set number of bins
    fNumberOfBinsInFile=fVectorOfBins.size();
}
