//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  september 2009                              //
//                                              //
//////////////////////////////////////////////////

// ROOT includes
#include<TFile.h>
#include<TCanvas.h>
#include<TH1F.h>
#include<TMath.h>
#include<TPaveText.h>
using namespace TMath;

// system  includes
#include <iostream>
using namespace std;

#include <inc/TDistribution.h>

TDistribution::TDistribution()
{
}

TDistribution::TDistribution(TString BinName, TString VariableName,TString HistogramsVersion):
fVariableName(VariableName),
fBinName(BinName),
fHistogramVersion(HistogramsVersion),
fHist_data(NULL),
fHist_uds(NULL),
fHist_c(NULL),
fHist_b(NULL)
{
    const TString ari = "light";
    const TString beauty = "beauty";
    const TString charm = "charm";

    TString path=getenv ("HISTO_PATH");
    fHistogramsFile=new TFile(path+"/merged."+HistogramsVersion+".root","read");
    TString HistName=BinName+"/"+fVariableName;

    // get templates
    fHist_data=(TH1F*)fHistogramsFile->Get(HistName+"/data");
    fHist_uds=(TH1F*)fHistogramsFile->Get(HistName+"/"+ari);
    fHist_c=(TH1F*)fHistogramsFile->Get(HistName+"/"+charm);
    fHist_b=(TH1F*)fHistogramsFile->Get(HistName+"/"+beauty);

    // sanity check
    if  ( (fHist_data==NULL) || (fHist_uds==NULL) || (fHist_c==NULL) || (fHist_b==NULL) ) {
        cout<<"ERROR: no "+HistName+"/data "<<"histogram found!"<<endl;
        abort();
    }

    // cosmetics
    fHist_data->SetStats(0);
    fHist_uds->SetStats(0);
    fHist_c->SetStats(0);
    fHist_b->SetStats(0);

    // get number of bins
    fNbins = fHist_data -> GetNbinsX();

    // sanity check
    if (fNbins!=(fHist_uds->GetNbinsX())) {
        cout<<"ERROR: binning is different!!!";
        abort();
    }
    if (fNbins!=(fHist_c->GetNbinsX())) {
        cout<<"ERROR: Binning is different!!!";
        abort();
    }
    if (fNbins!=(fHist_b->GetNbinsX())) {
        cout<<"ERROR: Binning is different!!!";
        abort();
    }

    // now use the template histograms to fill bin content and error arrays
    // which will be used for chi2 calculation during MINUIT minimization
    FillArrays();

    // create a histogram containing total MC before the fit;
    // for plotting purposes only
    fHist_totalMC=(TH1F*)fHist_b->Clone("totMC");
    fHist_totalMC->Add(fHist_c);
    fHist_totalMC->Add(fHist_uds);
    fHist_totalMC->SetFillColor(kYellow);
    fHist_totalMC->SetLineColor(kYellow);

    //  create a canvas
    fCanvas=CreateCanvas();
    fCanvas->Divide(1,2);
    //fCanvas->Divide(2,2);

}

TDistribution::~TDistribution()
{
}

void TDistribution::FillArrays() {
    // loop over all bins in the histogram and fill arrays
    for (int k=1;k<fNbins+1;k++) {
        fN_data[k] = fHist_data->GetBinContent(k);
        fN_uds[k] = fHist_uds->GetBinContent(k);
        fN_c[k] = fHist_c->GetBinContent(k);
        fN_b[k] = fHist_b->GetBinContent(k);

        fSigma_data[k]=fHist_data->GetBinError(k);
        fSigma_uds[k]=fHist_uds->GetBinError(k);
        fSigma_c[k]=fHist_c->GetBinError(k);
        fSigma_b[k]=fHist_b->GetBinError(k);
    }
}

Double_t    TDistribution::CalculateChi2(Double_t p1, Double_t p2, Double_t p3) {
    Bool_t    merge_fine_binning = true;    // this to move from 'fine' to 'coarse'  (1 unit/bin --> 2 units/bin)
    Bool_t    merge_last_bins = true;       // this also to use [14, 17] [17, 20] instead of [14, 16] [16, 18] [18, 20]
                                            // has effect only if merge_fine_binning = true.

    // for signal extraction studies
    bool      start_from_3 = false;
    bool      start_from_5 = false;

    // return variable
    Double_t  chi2=0;

    // loop over the bins, calculate the contribution to chi2 and add it
    int start_bin=5;
    if (start_from_3) start_bin=4;
    if (start_from_5) start_bin=6;
    for (int bin=start_bin; bin<=fNbins; bin++) {

        Float_t data = fN_data[bin];
        Float_t b = fN_b[bin];
        Float_t c = fN_c[bin];
        Float_t uds = fN_uds[bin];

        Float_t data_err = fSigma_data[bin];
        Float_t b_err = fSigma_b[bin];
        Float_t c_err = fSigma_c[bin];
        Float_t uds_err = fSigma_uds[bin];

        // if selected a coarser binning, add also the next bin
        if (merge_fine_binning) {

            data += fN_data[bin+1];
            b += fN_b[bin+1];
            c += fN_c[bin+1];
            uds += fN_uds[bin+1];
            data_err = Sqrt ( Power(fSigma_data[bin],2) + Power(fSigma_data[bin+1],2) );
            b_err = Sqrt( Power(fSigma_b[bin], 2) + Power(fSigma_b[bin+1], 2) );
            c_err = Sqrt( Power(fSigma_c[bin], 2) + Power(fSigma_c[bin+1], 2) );
            uds_err = Sqrt( Power(fSigma_uds[bin], 2) + Power(fSigma_uds[bin+1], 2) );

            bool add_another_bin = (start_from_3 && (bin==4)) || (start_from_5 && (bin==6)) || (merge_last_bins && ((bin == 15) || (bin == 18)));
            if (add_another_bin) {
                data += fN_data[bin+2];
                b += fN_b[bin+2];
                c += fN_c[bin+2];
                uds += fN_uds[bin+2];
                data_err = Sqrt ( Power(fSigma_data[bin],2) + Power(fSigma_data[bin+1],2)+ Power(fSigma_data[bin+2],2) );
                b_err = Sqrt( Power(fSigma_b[bin], 2) + Power(fSigma_b[bin+1], 2) + Power(fSigma_b[bin+2], 2) );
                c_err = Sqrt( Power(fSigma_c[bin], 2) + Power(fSigma_c[bin+1], 2) + Power(fSigma_c[bin+2], 2) );
                uds_err = Sqrt( Power(fSigma_uds[bin], 2) + Power(fSigma_uds[bin+1], 2) + Power(fSigma_uds[bin+2], 2));
                bin++;
            }

            bin++;
        }

        Double_t    deviation=(data-p1*b-p2*c-p3*uds);
        Double_t    error_squared=0;
        Double_t    data_error_squared=Power(data_err,2);
        Double_t    MC_error_squared=0;
        MC_error_squared = Power(p1*b_err,2) + Power(p2*c_err,2) + Power(p3*uds_err,2);

        error_squared=data_error_squared+MC_error_squared;
        if (error_squared==0) {
            cout<<"ERROR: error_squared=0"<<endl;
            abort();
        }
        if (error_squared!=0) chi2=chi2+(Power(deviation,2))/(error_squared);
    }

    return chi2;
}

Double_t	TDistribution::CalculateChi2Norm(Double_t p1, Double_t p2, Double_t p3)
{

	Double_t    chi2Norm=0;

	Double_t    Int_data=fHist_data->Integral();
	Double_t    Int_b=fHist_b->Integral();
	Double_t    Int_c=fHist_c->Integral();
	Double_t    Int_uds=fHist_uds->Integral();

	Double_t	deviation=(Int_data-p1*Int_b-p2*Int_c-p3*Int_uds);

	Double_t    error_squared=0;
	Double_t    data_error_squared=Int_data;
	Double_t    MC_error_squared=0;

	for (int bin=1;bin<fNbins+1;bin++)
	{
MC_error_squared=Power(p1*fSigma_b[bin],2)+Power(p2*fSigma_c[bin],2)+Power(p3*fSigma_uds[bin],2);
//MC_error_squared=(p1**2)*Int_b+(p2**2)*Int_c+(p3**2)*Int_uds;
	}

	error_squared=data_error_squared+MC_error_squared;
	chi2Norm=0;
	if (error_squared!=0)
    chi2Norm=(Power(deviation,2))/(error_squared);

	return chi2Norm;
}


void	TDistribution::Draw(Double_t p1, Double_t p2, Double_t p3, TString TotMCDrawOpt)
{
    this->Scale(p1,p2,p3);
    TString	opt = "";
    Float_t    chi2BEFORE;
    Float_t    chi2AFTER;
    if ( fVariableName.Contains("mirrored") ) {
        chi2BEFORE=this->CalculateChi2(1,1,1);
        chi2AFTER=this->CalculateChi2(p1,p2,p3);
    } else if ( fVariableName == "significance" ) {
        chi2BEFORE=this->CalculateChi2Norm(1,1,1);
        chi2AFTER=this->CalculateChi2Norm(p1,p2,p3);
        opt="hist";
    } else {
        cout << "ERROR from TDistribution::Draw(): not supported variable name" << endl;
        abort();
    }

    fCanvas->cd(1);
/*
    fHist_totalMC->Draw(TotMCDrawOpt);
    fHist_data->Draw("same");
    fHist_b->Draw("same"+opt);
    fHist_c->Draw("same"+opt);
    fHist_uds->Draw("same"+opt);
    this->DrawPave(chi2BEFORE);

    fCanvas->cd(2);
    fHist_totalMC_fitted->Draw(TotMCDrawOpt);
    fHist_data->Draw("same");
    fHist_b_fitted->Draw("same hist");
    fHist_c_fitted->Draw("same hist");
    fHist_uds_fitted->Draw("same hist");
    this->DrawPave(chi2AFTER);

    fCanvas->cd(3);
    gPad->SetLogy();
    fHist_totalMC->Draw(TotMCDrawOpt);
    fHist_data->Draw("same");
    fHist_b->Draw("same"+opt);
    fHist_c->Draw("same"+opt);
    fHist_uds->Draw("same"+opt);


    fCanvas->cd(4);
    gPad->SetLogy();
    fHist_totalMC_fitted->Draw(TotMCDrawOpt);
    fHist_data->Draw("same");
    fHist_b_fitted->Draw("same hist");
    fHist_c_fitted->Draw("same hist");
    fHist_uds_fitted->Draw("same hist");*/

    fCanvas->cd(1);
    fHist_totalMC_fitted->Draw(TotMCDrawOpt);
    if (fVariableName=="significance_massbin1_mirrored") fHist_totalMC_fitted->SetTitle("1 < M_{VTX} < 1.4 GeV");
    if (fVariableName=="significance_massbin2_mirrored") fHist_totalMC_fitted->SetTitle("1.4 < M_{VTX} < 2 GeV");
    if (fVariableName=="significance_massbin3_mirrored") fHist_totalMC_fitted->SetTitle("2 < M_{VTX} < 6 GeV");
    fHist_totalMC_fitted->SetXTitle("S^{+}-S^{-}");
    fHist_totalMC_fitted->SetAxisRange(4, 20, "X");

    fHist_data->Draw("same");
    fHist_b_fitted->Draw("same hist");
    fHist_c_fitted->Draw("same hist");
    fHist_uds_fitted->Draw("same hist");
    this->DrawPave(chi2AFTER);

    fCanvas->cd(2);
    gPad->SetLogy();
    fHist_totalMC_fitted->Draw(TotMCDrawOpt);
    //fHist_totalMC_fitted->SetTitle("");
    fHist_data->Draw("same");
    fHist_b_fitted->Draw("same hist");
    fHist_c_fitted->Draw("same hist");
    fHist_uds_fitted->Draw("same hist");

    //-------------- colors ---------------
    fHist_b_fitted->SetLineColor(kBlue);
    fHist_b->SetLineColor(kBlue);

    fHist_c_fitted->SetLineColor(kGreen);
    fHist_c->SetLineColor(kGreen);

    //--------------width -----------------

    fHist_b_fitted->SetLineWidth(2);
    fHist_c_fitted->SetLineWidth(2);
    fHist_uds_fitted->SetLineWidth(2);
    fHist_data->SetMarkerStyle(20);

    //fCanvas->Print("/data/zenith226a/libov/analysis/"+fBinName+".eps","eps");

}

void TDistribution::Scale(Double_t p1, Double_t p2, Double_t p3) {
    fHist_b_fitted=(TH1F*)fHist_b->Clone("b_after");
    fHist_c_fitted=(TH1F*)fHist_c->Clone("c_after");
    fHist_uds_fitted=(TH1F*)fHist_uds->Clone("uds_after");

    fHist_b_fitted->Scale(p1);
    fHist_c_fitted->Scale(p2);
    fHist_uds_fitted->Scale(p3);

    fHist_totalMC_fitted=(TH1F*)fHist_b_fitted->Clone("totMC_fitted");
    fHist_totalMC_fitted->Add(fHist_c_fitted);
    fHist_totalMC_fitted->Add(fHist_uds_fitted);
    fHist_totalMC_fitted->SetFillColor(kYellow);
    fHist_totalMC_fitted->SetLineColor(kYellow);
}

void TDistribution::ScaleInput(Double_t p1, Double_t p2, Double_t p3) {
    fHist_b -> Scale(p1);
    fHist_c -> Scale(p2);
    fHist_uds -> Scale(p3);
}



void TDistribution::Write(TFile *file) {
    file->cd();
    fCanvas->Write();
    //TString path="/data/zenith226a/libov/F2CC/scripts/Fitter/results/"+fBinName+"_"+fVariableName+".eps";
    //fCanvas->Print(path);
}


void TDistribution::DrawPave(Float_t	chi2) {
    char str1[256];

    TPaveText *pt1 = new TPaveText(0.6644408,0.7790474,0.8845288,0.8850358,"brNDC");
    pt1->SetFillColor(0);
    sprintf(str1,"#chi^{2}=%3.3f",chi2);
    pt1->AddText(str1);
    //pt1->Draw("same");
}

TCanvas* TDistribution::CreateCanvas() {
    //TCanvas *fCanvas = new TCanvas(fCanvName+BinName, "Control Plots",14,31,700,500);
    TCanvas *Canvas = new TCanvas(fBinName+fVariableName, "Control Plots",14,31,700,500);
    //gStyle->SetOptFit(1111);
    Canvas->Range(0.275,-234.806,5.525,2113.26);
    Canvas->SetBorderSize(2);
    Canvas->SetFrameFillColor(0);
    Canvas->SetFillColor(0);
    Canvas->ToggleToolBar();
    Canvas->ToggleEventStatus();
    Canvas->ToggleEditor();
    //fCanvas->Divide(2,2);

    return Canvas;
}


