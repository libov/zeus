//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

#ifndef __SAMPLE_H__
#define __SAMPLE_H__

// ROOT and system headers
#include <TROOT.h>
#include <TString.h>
#include <TFile.h>
#include <vector>
using namespace std;

// my headers
#include <TSubSet.h>

class    TSample : public TObject
{

    public:
        TSample() {};
        TSample(TSubSet subset, Float_t relative_luminosity, TString HistogramsVersion);
        ~TSample() {};

        Float_t             GetRelativeLuminosity() {return fRelativeLuminosity;};
        TSubSet::Flavour    GetFlavour() {return fSubSet.getFlavourENUM();};

        TFile*              GetInputHistogramsFile() {return fInputHistogramsFile;};

        Int_t               GetNumberOfBins() {return fNumberOfBinsInFile;};
        Int_t               GetNumberOfHistograms() {return fNumberOfHistograms;};
        vector<TString>     GetVectorOfBins() {return	fVectorOfBins;};
        vector<TString>     GetVectorOfHistograms() {return	fVectorOfHistograms;};

        TSubSet             GetSubSet() { return fSubSet; };

    private:
        TFile*              fInputHistogramsFile;
        TString             fHistogramsVersion;

        Float_t             fRelativeLuminosity;        //!< the relative luminosity wrt data, i.e. the weighting factor

        Int_t               fNumberOfBinsInFile;        //!< Each analysis file has several subdirectories (bins)
        Int_t               fNumberOfHistograms;        //!< Each bin has a number of histograms
        vector<TString>     fVectorOfBins;
        vector<TString>     fVectorOfHistograms;

        void                CalculateNumberOfBinsHistos();
        TFile*              OpenInputFile();

        TSubSet             fSubSet;
};
#endif

