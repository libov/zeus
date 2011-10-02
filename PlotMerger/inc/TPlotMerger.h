//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////
#ifndef __TPlotMerger_H__
#define __TPlotMerger_H__

#include <vector>
using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h>
#include <TList.h>
#include <TFile.h>
#include <TObjArray.h>

#include <inc/normtype.h>
#include <../NtupleAnalyzer/inc/periods.h>

#include <TCrossSection.h>
#include <TSubSet.h>

class SampleGroup;

class TPlotMerger: public TObject
{
    public:

        TPlotMerger();
        TPlotMerger(TString HistogramsVersion, TString remark);
        ~TPlotMerger();

        void    Initialize();
        void    SetXMLFileName(TString filename) {fXMLfilename = filename;};
        void    SetScaleFitResults(bool scale) {fScaleFitResults=scale;};
        void    AddSampleGroup(TString	cGroupID, normtype cNormType);
        void    AddSample(TString GroupID, TSubSet subset, Float_t Luminosity);
        void    Merge();

    private:

        void                    BuildPlot(TString DirNamee, TString var_name);

        TString                 fHistogramsVersion;
        TFile*                  fOuptutHistogramsFile;

        vector <SampleGroup>    fSampleGroupMap;

        Int_t                   fNumberOfBins;
        vector <TString>        fVectorOfBins;
        
        Int_t                   fNumberOfHistograms;
        vector <TString>        fVectorOfHistograms;

        Bool_t                  fFirstSample;

        TString                 fXMLfilename;
        TCrossSection           *fCrossSection;
        bool                    fScaleFitResults;
};
#endif
