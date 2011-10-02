//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

// system headers
#include<iostream>
#include<map>
using namespace std;

// ROOT headers
#include <TFile.h>
#include <TKey.h>

// my headers
#include <inc/TPlotMerger.h>
#include <inc/TSample.h>
#include <inc/normtype.h>
#include <TCrossSection.h>
#include <TSubSet.h>

// temporary
#include <TStopwatch.h>

class SampleGroup {
    public:
        TList       *SampleList;
        TString     GroupID;
        normtype    NormType;
        TH1F        *Histogram;
};

// default constructor and destructors
TPlotMerger::TPlotMerger(){}
TPlotMerger::~TPlotMerger(){}

TPlotMerger::TPlotMerger(TString     HistogramsVersion, TString remark):
fHistogramsVersion(HistogramsVersion),
fFirstSample(true),               // used in AddSample()
fXMLfilename(""),
fScaleFitResults(false)
{
    // a suggestion from ROOTTALK: remove the normal ROOT bookkeeping in oder to reduce
    // closing time of the file; no significant effect however! anyway, keeping it for the timebeing
    // TODO: what does it mean?
    TH1::AddDirectory(kFALSE);
    TString    PathToHistograms=getenv("HISTO_PATH");
    PathToHistograms+="/merged."+fHistogramsVersion+remark+".root";
    fOuptutHistogramsFile = new TFile(PathToHistograms,"recreate");
    if (fOuptutHistogramsFile) {
        cout << "INFO: Writing merged histograms to " << PathToHistograms << endl;
    } else {
        cout << "ERROR: Unable to create an output root file. Terminating!"<<endl;
        abort();
    }
}

void TPlotMerger::Initialize() {
    if (fScaleFitResults) fCrossSection = new TCrossSection(fXMLfilename);
}

void TPlotMerger::AddSampleGroup (TString cGroupID, normtype cNormType) {

    // create a new group of samples
    SampleGroup     cGroup;
    // create a list that will contain samples belonging to this group
    cGroup.SampleList = new TList();
    // get it's normalization type: no normalization, to lumi or to area
    cGroup.NormType = cNormType;
    // an identifier of the group
    cGroup.GroupID = cGroupID;

    // finally, store the group in the array
    fSampleGroupMap.push_back ( cGroup );
}
    
void TPlotMerger::AddSample(TString tGroupID, TSubSet subset, Float_t Luminosity) {

    // helping variable
    Int_t index = -1;

    // try to find a group with a given id
    for (int k=0; k<fSampleGroupMap.size(); k++) {
        if (fSampleGroupMap[k].GroupID == tGroupID) {
            index = k;
            break;
        }
    }

    // could not find such a group
    if (index == -1 ) {
        cout<<" ERROR: Could not find such sample group index. Terminating, sorry."<<endl;
        abort();
    }

    // group was found, get some paramters of it
    SampleGroup   cGroup = fSampleGroupMap[ index ];
    TList         *cList = cGroup.SampleList;
    normtype      cNormType = cGroup.NormType;

    // create an instance of the sample and add it to the list
    TSample *cSample = new TSample(subset, Luminosity, fHistogramsVersion);
    cList -> Add(cSample);

    // get number of bins in the root file (i.e. number of subdirectories in the root file)
    Int_t cNumberOfBins=cSample->GetNumberOfBins();
    if (fFirstSample) {
        fNumberOfBins = cNumberOfBins;
        fVectorOfBins = cSample -> GetVectorOfBins();
        fVectorOfHistograms = cSample -> GetVectorOfHistograms();
    }

    // consistency check: number of bins should be the same in all samples
    if (fNumberOfBins!=cNumberOfBins) {
        cout<<"ERROR: Number of bins in different files (samples) are not the same. Terminating."<<endl;
        abort();
    }

    // get number of histograms for this sample (i.e. in each bin; internally, there is a check in TSample,
    // that it should be the same in all bins)
    Int_t cNumberOfHistograms = cSample -> GetNumberOfHistograms();
    if (fFirstSample) fNumberOfHistograms = cNumberOfHistograms;

    // consistency check: NUmber of histograms should also be the same between all samples
    if (fNumberOfHistograms != cNumberOfHistograms) {
        cout<<"ERROR: Number of histograms in different files (samples) are not the same. Terminating."<<endl;
        abort();
    }

    // not the first sample anymore
    fFirstSample = false;
}

void TPlotMerger::Merge() {

    // here we assume that file structure is exactly the same between different samples.
    // This means that the number of bins is the same among samples and the set
    // of histograms in each bin of each of the files is exactly the same. This should
    // be the case if TMiniNtupleAnalyzer works correctly. To check this few consistency
    // checks are made (namely that number of histograms is the same among bins and number
    // of bins is the same among files). Of course this is not that robust but it can help
    // to find obvious bugs.

    // loop over all bins
    for (int bin=0; bin < fVectorOfBins.size(); bin++) {
    
        //fOuptutHistogramsFile->cd();
        TString cBinName = fVectorOfBins[bin];
        cout<<"INFO: merging histograms from directory: " << cBinName << endl;
        fOuptutHistogramsFile->mkdir(cBinName);
        
        for (int histo=0;histo<fVectorOfHistograms.size(); histo++) {
            //fOuptutHistogramsFile -> cd(cBinName);
            
            TString cHistName = fVectorOfHistograms[histo];
            fOuptutHistogramsFile -> GetDirectory(cBinName) -> mkdir(cHistName);
            //gDirectory->mkdir(cHistName);
            //gDirectory->cd(cHistName);
            BuildPlot(cBinName,cHistName);
        }

        // now clean up further - in particular, when we take histograms from analysis
        // histograms, those directories stay in memory! Hence, even though we don't
        // assign a histo to that directory (because of  TH1::AddDirectory(kFALSE) in the constructor
        // of TPlotMerger), there is still significant memory usage (~350M towards the end of
        // the execution) which is not really needed; note that clearing this here and not in
        // the sample loop in build plot SIGNIFICANTLY improves the performance! (body of the sample loop
        // in build plot executes O(1 000 000)! )
        // the performance due to cleaning it here is not degraded significantly, while
        // memory consumption is reduced a lot!
        TSample                *cSample;
        for( int i = 0; i < fSampleGroupMap.size(); i++) {

            // get a current group
            SampleGroup     cGroup = fSampleGroupMap[i];
            // get it's identifier
            TString         cGroupID = cGroup.GroupID;
            // get a list of samples in this group
            TList           *cList = cGroup.SampleList;

            // now loop over all samples in the current group
            TIter SamplesIter(cList);
            while ( cSample= (TSample *)SamplesIter.Next()) {

                // get a file which belongs to this sample
                TFile *cFile = cSample -> GetInputHistogramsFile();
                // and clean everything from it's memory
                cFile -> GetList() -> Clear();
            }
        }

        // write the output histograms to file!
        fOuptutHistogramsFile -> Write();
        // it is important to realize that even if BuildPlot(..) command above is not called,
        // created directories stay in memory; then, when we are trying to close the file, they
        // first have to be removed from the memory and that takes time
        // of course this effect is negligible comparing to what happens if we call also BuildPlot(..),
        // but anyway interesting and important to realize.
        // of course this also removes the histograms that we write there
        fOuptutHistogramsFile -> GetList() -> Clear();
    }

    cout<<"INFO: Closing file"<<endl;
    fOuptutHistogramsFile -> Close();
    cout<<"INFO: File closed."<<endl;
}

void TPlotMerger::BuildPlot(TString cBinName, TString cHistName) {
    
    // construct relative path to the histogram (bin name + histo name)
    TString               cBinHistName=cBinName+"/"+cHistName;
    //TDirectory*          cDirectory=fOuptutHistogramsFile->GetDirectory(cBinHistName);
    TSample                *cSample;

    // loop over all groups
    for( int i = 0; i < fSampleGroupMap.size(); i++) {

        // get a current group
        SampleGroup     cGroup = fSampleGroupMap[i];
        // get it's identifier
        TString         cGroupID = cGroup.GroupID;
        // get a list of samples in this group
        TList           *cList = cGroup.SampleList;
        // get a normalization type for this group
        normtype        cNormType = cGroup.NormType;
        // set a pointer to group's histogram (the histo does not yet exist!)
        TH1F            *cHistogram=cGroup.Histogram;
        // this flag will be turned to false when we processed 1st sample for this group
        Bool_t          first_histo=true;

        // now loop over all samples in the current group
        TIter SamplesIter(cList);
        while ( cSample= (TSample *)SamplesIter.Next()) {

            // get a file which belongs to this sample
            TFile *cFile = cSample -> GetInputHistogramsFile();

            TH1F     *cHist = NULL;
            cHist = (TH1F*)cFile -> Get(cBinHistName);
            // sanity check
            if (cHist == NULL) {
                cout << "ERROR: could not access the histogram "<< cBinHistName << "! " << endl;
                abort();
            }

            // Normalize according to the group option
            switch (cNormType) {
                case kNone:
                    // noop
                    break;
                case kLumi:
                    // scale by the weighting factor (relative luminosuty - wrt to data luminosity)
                    cHist -> Scale( cSample -> GetRelativeLuminosity() );

                    if (fScaleFitResults) {
                        // get a bin number
                        int bin_id=-1;
                        TString     bin_name_tmp = cBinName;
                        // remove first three letters, namely "bin", what remains is then bin number
                        bin_name_tmp.Remove(0,3);
                        sscanf(bin_name_tmp.Data(), "%d", &bin_id);
                        if (bin_id == -1) { 
                            cout << "ERROR: could not identify bin index. Terminating!" << endl;
                            abort();
                        }

                        // get scaling factors from the fit results for this bin index
                        Float_t     k_c = fCrossSection->getCrossSectionBin(bin_id).get_k_c();
                        Float_t     k_b = fCrossSection->getCrossSectionBin(bin_id).get_k_b();
                        Float_t     k_uds = fCrossSection->getCrossSectionBin(bin_id).get_k_uds();

                        // depending on the type of the sample, scale the histogram
                        if (cSample -> GetFlavour() == TSubSet::kCHARM) cHist -> Scale(k_c);
                        if (cSample -> GetFlavour() == TSubSet::kBEAUTY) cHist -> Scale(k_b);
                        if (cSample -> GetFlavour() == TSubSet::kLIGHT) cHist -> Scale(k_uds);
                    }
                    break;

                case kArea:
                    cout << "scaling to area is not supported at the moment!" << endl;
                    abort();
                    break;
            }

            if (first_histo) {
                cHistogram=(TH1F*)cHist->Clone(cGroupID);
                // a new histogram should be stored in the output file (corresponding bin and histo directories),
                // set it now explicitly; then, it is sufficient to call fOuptutHistogramsFile->Write() to 
                // write it to file
                cHistogram -> SetDirectory (fOuptutHistogramsFile -> GetDirectory(cBinHistName));
                first_histo=false;
            } else {
                cHistogram->Add(cHist);
            }

            delete cHist;

         } // end loop over sample

        // write the histogram (the directory was set already)
//         cHistogram -> Write();
        // and clean up the memory
 //       delete cHistogram;
    } // end loop over groups
}
