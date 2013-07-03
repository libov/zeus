//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  september 2009                              //
//                                              //
//////////////////////////////////////////////////
#ifndef __TDISTRIBUTION_H__
#define __TDISTRIBUTION_H__

// ROOT includes
#include<TROOT.h>
#include<TH1F.h>
#include<TMinuit.h>
#include<TCanvas.h>

class	TDistribution : public TObject
{
    public:
        TDistribution();
        TDistribution(TString BinName,TString VariableName, TString HistogramsVersion);
        ~TDistribution() {};

        void        Draw(Double_t p1, Double_t p2, Double_t p3, TString TotMCDrawOpt);
        Double_t    CalculateChi2(Double_t p1, Double_t p2, Double_t p3);
        Double_t    CalculateChi2Norm(Double_t p1, Double_t p2, Double_t p3);

        void        Scale (Double_t	p1,Double_t	p2,Double_t	p3);
        void        ScaleInput (Double_t	p1,Double_t	p2,Double_t	p3);

        void        Write(TFile *file);
        void        DrawPave(Float_t	chi2);

        Float_t     GetChi2() {return fChi2;};

        void        FillArrays();

    private:
        TFile       *fHistogramsFile;
        TString     fVariableName;
        TString     fBinName;
        TString     fHistogramVersion;

        // before the fit
        TH1F        *fHist_data;
        TH1F        *fHist_b;
        TH1F        *fHist_c;
        TH1F        *fHist_uds;
        TH1F        *fHist_totalMC;

        // after the fit
        TH1F        *fHist_b_fitted;
        TH1F        *fHist_c_fitted;
        TH1F        *fHist_uds_fitted;
        TH1F        *fHist_totalMC_fitted;

        Int_t       fNbins;

        Float_t     fN_data[100];
        Float_t     fN_uds[100];
        Float_t     fN_c[100];
        Float_t     fN_b[100];

        Float_t     fSigma_data[100];
        Float_t     fSigma_uds[100];
        Float_t     fSigma_c[100];
        Float_t     fSigma_b[100];

        TCanvas     *fCanvas;

        TCanvas*    CreateCanvas();

        Float_t     fChi2;
};
#endif
