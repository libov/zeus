//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
#ifndef TGLOBALBIN_H
#define TGLOBALBIN_H
#include<inc/TBin.h>
#include<inc/VariablePhase.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TList.h>
#include <TProfile2D.h>

#include <vector>
using namespace std;

class TMiniNtupleAnalyzer;

/*! \brief Class for automatic binning

    Contains a list of TBin objects. NOTE: Probably many members here that should better belong to TMiniNtupleAnalyzer...
*/

class TGlobalBin : public TObject {

    public:

        TGlobalBin() {};
        TGlobalBin(TMiniNtupleAnalyzer *instance);
        ~TGlobalBin(){};

        void        AddBin(TBin * bin);
        Bool_t      CheckGlobalBin(VariablePhase VarPhase);
        TString     BinName;
        TString     GetBinDescription() { return fBinDescription; }
        void        AddHistogram(TH1 * histogram) { fListHistograms->Add(histogram); }
        int         FillHistogram(TString HistTitle, Float_t Value);
        int         FillHistogram(TString HistTitle, Float_t Value1, Float_t Value2);
        int         FillProfileHistogram(TString HistTitle, Float_t Value1, Float_t Value2);
        int         FillProfile2DHistogram(TString HistTitle, Float_t x, Float_t y, Float_t value);
        TList*      GetHistList() { return fListHistograms; }
        void        AddMirroredHistTitle(TString title) { fMirroredHistTitle.push_back(title); }
        void        MirrorHistograms();
        void        SetWeightingFactor(Double_t factor) { fWeightingFactor = factor; }
        Double_t    GetWeightingFactor() { return fWeightingFactor; }
        void        Print();

    private:

        TList*      fList_TBin;
        TString     fBinDescription;
        TList*      fListHistograms;
        TMiniNtupleAnalyzer *fAnalyzerInstance; // pointer to current TMiniNtupleAnalyzer
                                                // object; used for access to some variables
                                                // e.g. for histogram mirroring
                                                // this mechanism could be used also for
                                                // checking of bin values actually...
        vector<TString> fMirroredHistTitle;
        Int_t           fNevents;               // number of events that fall into this bin
        Double_t        fWeightingFactor;       //!< Weighting factor for histograms filling.
                                                //!< Is used to scale charm distribution when adding up
                                                //!< samples with different q2-min-cut
};
#endif
