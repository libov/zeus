//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////

#include <inc/TGlobalBin.h>
#include <inc/TMiniNtupleAnalyzer.h>
#include <inc/VariablePhase.h>
#include<iostream>
using namespace std;

TGlobalBin::TGlobalBin(TMiniNtupleAnalyzer* instance):
fList_TBin(new TList()),
fListHistograms(new TList()),
fBinDescription(""),
fAnalyzerInstance(instance),
fNevents(0),
fWeightingFactor( (Double_t)1 )
{
}

void TGlobalBin::AddBin(TBin* bin) {
    fList_TBin->Add(bin);
    fBinDescription=fBinDescription+bin->GetDescription()+" ";
}

Bool_t TGlobalBin::CheckGlobalBin(VariablePhase VarPhase) {
    TBin *currentTBin;
    TIter Iter_TBin(fList_TBin);

    while ( (currentTBin=(TBin *)Iter_TBin.Next()) ) {

        if ( (currentTBin -> GetVarPhase()) != VarPhase) continue;
        Bool_t TBinFired=currentTBin -> CheckBin();
        if ( !TBinFired ) return false;
    }
    fNevents++;
    return true;
}

int     TGlobalBin::FillHistogram(TString HistTitle, Float_t	Value) {

    if (!fListHistograms->FindObject(HistTitle)) {
        cout << "ERROR: " << HistTitle << " histogram not found!" << endl;
        abort();
    }

    TH1F    *currentHistogram;
    currentHistogram = (TH1F*) fListHistograms -> FindObject(HistTitle);
    currentHistogram -> Fill(Value, fWeightingFactor);

    // now fill two histograms separately for S>0 and S<0
    if (!fAnalyzerInstance->fFillMirrored)  return 0;
    TString     HistTitlePos=HistTitle+"_pos";
    TString     HistTitleNeg=HistTitle+"_neg";

    if (fAnalyzerInstance -> fSignificance > 0) {

        if (fListHistograms->FindObject(HistTitlePos)) {
            currentHistogram=(TH1F*)fListHistograms->FindObject(HistTitlePos);
            currentHistogram->Fill(Value, fWeightingFactor);
        }
    }

    if (fAnalyzerInstance -> fSignificance < 0) {

        if (fListHistograms->FindObject(HistTitleNeg)) {
            if (HistTitle.Contains("significance"))	Value=(-1)*Value; // if you work with significance distribution (which is signed) - the negative-significance-part should be also mirrored - that is multiplied by -1; for other distributions (like Q2) this is not true, because the range is the same for S>0 and S<0 obviously

            currentHistogram=(TH1F*) fListHistograms -> FindObject(HistTitleNeg);
            currentHistogram->Fill(Value, fWeightingFactor);
        }
    }

    return 0;
}

void TGlobalBin::MirrorHistograms() {

    for (int hist = 0; hist < fMirroredHistTitle.size(); hist++) {

        TString HistTitle = fMirroredHistTitle[hist];
        TString HistTitlePos = HistTitle+"_pos";
        TString HistTitleNeg = HistTitle+"_neg";
        TString HistTitleSum = HistTitle+"_sum";
        TString HistTitleDiff = HistTitle+"_diff";
        if (!(fListHistograms -> FindObject(HistTitlePos)))
        cout<<"ERROR: No histogram called "<<HistTitlePos<<" found"<<endl;
        if (!(fListHistograms->FindObject(HistTitleNeg)))
        cout<<"ERROR: No histogram called "<<HistTitleNeg<<" found"<<endl;
        if ((!fListHistograms->FindObject(HistTitleNeg)))
        cout<<"ERROR: No histogram called "<<HistTitleSum<<" found"<<endl;
        if ((!fListHistograms->FindObject(HistTitleDiff)))
        cout<<"ERROR: No histogram called "<<HistTitleDiff<<" found"<<endl;

        TH1F* cHistPos=(TH1F*)fListHistograms->FindObject(HistTitlePos);
        TH1F* cHistNeg=(TH1F*)fListHistograms->FindObject(HistTitleNeg);
        TH1F* cHistSum=(TH1F*)fListHistograms->FindObject(HistTitleSum);
        TH1F* cHistDiff=(TH1F*)fListHistograms->FindObject(HistTitleDiff);

        cHistSum->Add(cHistPos,cHistNeg,1,1);
        cHistDiff->Add(cHistPos,cHistNeg,1,-1);
    }
}

void TGlobalBin::Print() {

    TBin *currentTBin;
    TIter Iter_TBin(fList_TBin);

    while ( (currentTBin=(TBin *)Iter_TBin.Next()) ) {
        cout << currentTBin -> GetDescription () << endl;
    }
}
