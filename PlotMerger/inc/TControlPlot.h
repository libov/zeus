//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                             //
//  libov@mail.desy.de                          //
//  July 2009                                   //
//                                              //
//////////////////////////////////////////////////
#ifndef __TControlPlot_H__
#define __TControlPlot_H__

#include <TROOT.h>
#include <TFile.h>

#include <inc/TPlotType.h>

#include <vector>
using namespace std;

class TControlPlot : public TObject {
    public:

        TControlPlot() {};
        TControlPlot(TString    HistogramsVersion);
        ~TControlPlot() {};

        void AddPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Float_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth);
        void AddAdvCanvas(Int_t initNPads_X,Int_t initNPads_Y,TString initSetName, TString initVariables,Int_t initLogs[6]);
        void Draw();

    private:

        TFile*                  fInputFile;
        TFile*                  fOutputFile;
        TString                 fHistogramsVersion;
        vector <TPlotType*>     fPlotTypes;
        TList*                  fList_AdvCanvas;
        TString                 GetTitle(TString variable);
        void                    SetAxisRange(TString, TH1F * );
};
#endif
