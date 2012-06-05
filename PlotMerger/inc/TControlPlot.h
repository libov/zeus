//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  July 2009                                   //
//                                              //
//////////////////////////////////////////////////
#ifndef __TControlPlot_H__
#define __TControlPlot_H__

// ROOT headers
#include <TROOT.h>
#include <TFile.h>

// custom headers
#include <inc/TPlotType.h>

// system headers
#include <vector>
using namespace std;

class TControlPlot : public TObject {
    public:

        TControlPlot() {};
        TControlPlot(TString    HistogramsVersion);
        ~TControlPlot() {};

        void AddPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Float_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth);
        void AddAdvCanvas(Int_t initNPads_X,Int_t initNPads_Y,TString initSetName, TString initVariables,Int_t initLogs[6]);
        void AddAdvCanvas(Int_t initNPads_X,Int_t initNPads_Y,TString initSetName, TString initVariables,Int_t initLogs[6], Int_t, Int_t);
        void Draw();
        void SetPrintPNG(bool print) {fPrintPNG = print;};
        void SetPrintEPS(bool print) {fPrintEPS = print;};
        void SetPrintGIF(bool print) {fPrintGIF = print;};
        void SetPrintROOT(bool print) {fPrintROOT = print;};
        void SetRasterCorrection(unsigned corr) {fRasterCorrection = corr;};

    private:

        TFile*                  fInputFile;
        TFile*                  fOutputFile;
        TString                 fHistogramsVersion;
        vector <TPlotType*>     fPlotTypes;
        TList*                  fList_AdvCanvas;
        TString                 GetTitle(TString variable);
        void                    SetAxisRange(TString, TH1F * );
        bool                    fPrintPNG;
        bool                    fPrintEPS;
        bool                    fPrintGIF;
        bool                    fPrintROOT;
        Int_t                   fRasterCorrection;
};
#endif
