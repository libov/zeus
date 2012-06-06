//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
#ifndef __TAdvCanvas_H__
#define __TAdvCanvas_H__
#include <TROOT.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>

class TAdvCanvas : public TObject {

    public:
        TAdvCanvas();
        TAdvCanvas(Int_t NPads_X,Int_t NPads_Y,TString CanvName, TString colonVariables, unsigned * LogPads, Int_t width, Int_t height);
        ~TAdvCanvas();
        Int_t           GetNPads();
        Int_t           GetNumberOfVariables();
        TString         GetVariable(Int_t VarNum);
        Bool_t          LogPad(Int_t Pad);
        TCanvas*        CreateCanvas(/*TString BinName*/);
        TString         GetName();
        Int_t           GetWidth() {return fWidth;};
        Int_t           GetHeight() {return fHeight;};

    private:
        TString         fCanvName;
        TString         fcolonVariables;
        TString         fArrayOfVariables[25];
        Int_t           fNumberOfVariables;
        Int_t           fNPads_X;
        Int_t           fNPads_Y;
        Int_t           fWidth;
        Int_t           fHeight;
        unsigned        *fLogPads;
        void            SeparateVariables();
};
#endif
