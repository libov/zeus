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
#include <TList.h>

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

        void Initialize();

        void AddPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Float_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth);
        void AddAdvCanvas(Int_t initNPads_X,Int_t initNPads_Y,TString initSetName, TString initVariables, unsigned * initLogs, Int_t, Int_t, Float_t top_margin);
        void Draw();
        void SetPrintPNG(bool print) {fPrintPNG = print;};
        void SetPrintEPS(bool print) {fPrintEPS = print;};
        void SetPrintGIF(bool print) {fPrintGIF = print;};
        void SetPrintROOT(bool print) {fPrintROOT = print;};
        void SetConfigFile(TString file) {fConfigFile = file;};
        void SetNoIndices(bool no_indices) {fNoIndices = no_indices;};
        void ReadSettings();

    private:

        TH1F* Rebin(TH1F*);

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

        bool                    fNoIndices;

        TString                 fConfigFile;

        Float_t                 fXaxisTitleSize;
        Float_t                 fXaxisTitleOffset;
        Float_t                 fXaxisLabelSize;
        Float_t                 fXaxisLabelOffset;

        Float_t                 fYaxisTitleSize;
        Float_t                 fYaxisTitleOffset;
        Float_t                 fYaxisLabelSize;
        Float_t                 fYaxisLabelOffset;

        bool                    fDrawLegend;
        Float_t                 fLegend_x1;
        Float_t                 fLegend_y1;
        Float_t                 fLegend_x2;
        Float_t                 fLegend_y2;

        bool                    fDrawZEUSLogo;
        Float_t                 fZEUSLogo_x;
        Float_t                 fZEUSLogo_y;
        Float_t                 fZEUSLogo_size;

        bool                    fAdditionalText;
        vector<TString>         fText;
        vector<Float_t>         fText_x;
        vector<Float_t>         fText_y;
        vector<Float_t>         fText_size;

        Int_t                   fCanvas_size_x;
        Int_t                   fCanvas_size_y;

        Float_t                 fPadTopMargin;
        Float_t                 fPadBottomMargin;
        Float_t                 fPadLeftMargin;
        Float_t                 fPadRightMargin;

        unsigned                fAxisMaxDigits;
};
#endif
