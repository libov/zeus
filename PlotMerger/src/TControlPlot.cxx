//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

// ROOT headers
#include <TFile.h>
#include <TList.h>
#include <TKey.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TStyle.h>

// system headers
#include<iostream>
#include <vector>
using namespace std;

// custom headers
#include <inc/TControlPlot.h>
#include <inc/TAdvCanvas.h>
#include <inc/TPlotType.h>

TControlPlot::TControlPlot(TString    HistogramsVersion):
fList_AdvCanvas(new TList()),
fHistogramsVersion(HistogramsVersion),
fPrintPNG(false),
fPrintEPS(false),
fPrintGIF(false),
fPrintROOT(false),
fRasterCorrection(1)
{
    // get a path to histograms folder
    TString HISTO_PATH = getenv("HISTO_PATH");
    // get a root file after merger
    fInputFile=new TFile(HISTO_PATH+"/merged."+HistogramsVersion+".root");
    cout << "INFO: Opened " << fInputFile -> GetName() << endl;
    // create a root file to store the plots
    fOutputFile=new TFile(HISTO_PATH+"/plotter."+fHistogramsVersion+".root","recreate");
    cout << "INFO: Plots go to " << fOutputFile -> GetName() << endl;
    gStyle->SetPadTickY(1);
    gStyle->SetPadTickX(1);
    gStyle->SetErrorX(0);
}


void TControlPlot::AddPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Float_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth) {
    fPlotTypes.push_back(new TPlotType(Name, DrawHisto, MarkerStyle, MarkerSize, FillColor, LineColor, LineWidth));
}

void TControlPlot::AddAdvCanvas(Int_t NPads_X, Int_t NPads_Y,TString SetName, TString Variables, Int_t Logs[6]) {
    fList_AdvCanvas->Add(new TAdvCanvas(NPads_X,NPads_Y, SetName,Variables,Logs));
}

void TControlPlot::AddAdvCanvas(Int_t NPads_X, Int_t NPads_Y,TString SetName, TString Variables, Int_t Logs[6], Int_t width, Int_t height){
    fList_AdvCanvas->Add(new TAdvCanvas(NPads_X, NPads_Y, SetName, Variables, Logs, width, height));
}

void TControlPlot::Draw() {

    // loop over bins
    fInputFile -> cd();
    TIter nextBin(gDirectory->GetListOfKeys());
    TKey* keyBins;
    while( (keyBins=(TKey*)nextBin()) ) {
        // get a name of the directory
        TString SubDirName = keyBins->GetName();
        // create a directory in the output file
        fOutputFile->mkdir(SubDirName);
        fOutputFile->cd(SubDirName);
        
        // loop over canvases that user added to the list
        TIter        Iter_AdvCanvas(fList_AdvCanvas);
        TAdvCanvas   *cAdvCanvas;
        while((cAdvCanvas=(TAdvCanvas*)Iter_AdvCanvas.Next())) {

            // get number of variables and pads for this canvas
            Int_t        NumberOfVariables = cAdvCanvas->GetNumberOfVariables();
            Int_t        NPads=cAdvCanvas->GetNPads();

            // sanity check
            if (NumberOfVariables > NPads) {
                cout<<"ERROR: Number of Variables exceed number of Pads"<<endl;
                abort();
            }

            // create a canvas, loop over variables,
            // and draw variable from each sample
            Int_t        cPad=1;
            TCanvas *cCanvas=cAdvCanvas->CreateCanvas();
            for (int cVariableNumber=0; cVariableNumber<NumberOfVariables; cVariableNumber++) {
                
                // sanity check
                if (cPad > NPads) {
                    cout<<"ERROR. Filling stopped."<<endl;
                    abort();
                }
                TString        cVar=cAdvCanvas->GetVariable(cVariableNumber);
                cCanvas->cd(cPad);
                if (cAdvCanvas->LogPad(cPad))    gPad->SetLogy();
                // Loop over the data types, see class TPlotType

                char            buffer[2];        // this is to take into account that same variables
                                                    // might be drawn on same Canvas
                                                    // the digit attached to histo name is just number
                                                    // of current Pad
                sprintf(buffer,"%i",cPad);
                Bool_t    first_histo=true;        // with or without "same"
                TLegend * leg = new TLegend (0.65,0.65,0.88, 0.85, "", "brNDC");

                for (int type=0;type<fPlotTypes.size();type++) {
                    TPlotType     *cType=fPlotTypes[type];
                    TString        cDataType=cType->GetName();
                    TString        NewHistName=cDataType+cVar+buffer;
                    if (!fInputFile->Get(SubDirName+"/"+cVar+"/"+cDataType)) {
                        cout<<"ERROR: no "<<SubDirName+"/"+cVar+"/"+cDataType<<" histogram found"<<endl;
                        abort();
                    }

                    // get a histogram
                    TH1F*    cHist=(TH1F*)fInputFile->Get(SubDirName+"/"+cVar+"/"+cDataType)->Clone(NewHistName);

                    // --------------------------------- //
                    // ----------- cosmetics ----------- //
                    // --------------------------------- //
                    cHist->SetMarkerStyle(cType->GetMarkerStyle());
                    cHist->SetMarkerSize(cType->GetMarkerSize());
                    cHist->SetFillColor(cType->GetFillColor());
                    cHist->SetLineColor(cType->GetLineColor());
                    cHist->SetLineWidth(cType->GetLineWidth());

                    cHist->SetTitle("");
                    cHist->SetStats(0);
                    cHist -> SetFillStyle(3003);

                    TString Xtitle = GetTitle(cVar);
                    cHist->SetXTitle(Xtitle);

                    cHist->SetYTitle("Entries");

                    SetAxisRange(cVar, cHist);

                    cHist->SetTitleSize(0.05, "X");
                    cHist->SetTitleOffset(0.85, "X");

                    cHist->SetTitleSize(0.06, "Y");
                    cHist->SetTitleOffset(0.82, "Y");

                    TString opt="";
                    if    (cType->IsDrawHisto()) opt.Append("HIST");
                    if ( ! first_histo) opt.Append("same");
                    first_histo=false;
                    //cHist->DrawClone(opt);

                    cHist->Draw(opt);
                    TString LegEntry=cDataType;
                    TString option="L";
                    if (cDataType=="data"){
                        LegEntry = "HERAII";
                        option = "P";
                    }
                    if (cDataType=="mc"){
                        LegEntry = "Sum MC ";
                        option = "F";
                    }
                    leg->AddEntry(cHist, LegEntry, option);
                    leg->SetFillColor(0);
                }

                //if (cPad==1) leg->Draw("same");
                cPad++;
            }

            // print the canvas to file
            if (SubDirName=="bin1") {
              cCanvas->Print((TString)getenv("PLOTS_PATH")+"/controlplot."+cAdvCanvas->GetName()+"."+fHistogramsVersion+"."+SubDirName+".png");
            }
            cCanvas->Write();
            cCanvas->Close();
            delete cCanvas;

        }
    }

    fOutputFile->Close();
}

TString TControlPlot::GetTitle(TString cVar) {

    TString Xtitle = "";

    if (cVar.Contains("zvtx"))  Xtitle = "Z_{PRM VTX}, cm";
    if (cVar.Contains("empz"))  Xtitle = "E-p_{Z}, GeV";
    if (cVar.Contains("yel"))   Xtitle = "y_{el}";
    if (cVar.Contains("yjb"))   Xtitle = "y_{jb}";
    if (cVar.Contains("xel"))   Xtitle = "x_{el}";
    if (cVar.Contains("xjb"))   Xtitle = "x_{jb}";
    if (cVar.Contains("xda"))   Xtitle = "x_{da}";
    if (cVar.Contains("q2da"))  Xtitle = "Q^{2}_{da}, GeV^2";
    if (cVar == "siecorr")      Xtitle = "E'_{e}, GeV";
    if (cVar == "thetael")      Xtitle = "#theta_{e}, rad";
    if (cVar == "phiel")        Xtitle = "#phi_{e}, rad";
    if (cVar.Contains("kt_etjet_b"))    Xtitle = "E_{T}^{jet}, GeV";
    if (cVar.Contains("kt_etajet_b"))   Xtitle = "#eta^{jet}";
    if (cVar == "kt_phijet_b")          Xtitle = "#phi^{jet}";
    if (cVar.Contains("vtxsec_mass"))   Xtitle = "MASS (Sec. Vtx.), GeV";
    if (cVar.Contains("vtxsec_multi"))  Xtitle = "MULTIPLICITY (Sec. Vtx.)";
    if (cVar.Contains("vtxsec_chi2ndf")) Xtitle = "#chi^{2}/n.d.o.f. (Sec. Vtx.)";
    if (cVar.Contains("significance") && (!cVar.Contains("mirrored"))) Xtitle = "L_{XY}/#sigma(L_{XY})";

    return Xtitle;
}

void TControlPlot::SetAxisRange(TString cVar, TH1F * cHist){
    if (cVar == "thetael") {
        cHist->SetAxisRange(1.5, 3.14, "X");
        cHist->SetAxisRange(0, 2300000, "Y");
    }
    if (cVar == "phiel") cHist->SetAxisRange(0, 275000, "Y");
    if (cVar == "kt_phijet_b") cHist->SetAxisRange(0, 150000, "Y");
    if (cVar.Contains("vtxsec_mass")) cHist->SetAxisRange(0, 6, "X");
    if (cVar.Contains("vtxsec_multi")) cHist->SetAxisRange(0, 14, "X");
}

/*
                    if ((SubDirName=="bin13")&&cVar.Contains("significance_massbin3") && cVar.Contains("_mirrored")) {
                        //Double_t        newbins[100] = {4, 6, 8, 10, 12, 14, 17, 20};
                        //cHist->Rebin (7, NewHistName+"_rebinned", newbins);
                        //delete cHist;
                        //cHist = (TH1F*) gDirectory -> Get(NewHistName+"_rebinned");
                        Float_t        hjkh [100] = {4, 6, 8, 10, 12, 14, 17, 20};
                        TH1F        * bla = new TH1F(NewHistName+"_rebinned", "", 7,  hjkh);
                        bla->SetBinContent(1, cHist->GetBinContent(5)+cHist->GetBinContent(6));
                        bla->SetBinContent(2, cHist->GetBinContent(7)+cHist->GetBinContent(8));
                        bla->SetBinContent(3, cHist->GetBinContent(9)+cHist->GetBinContent(10));
                        bla->SetBinContent(4, cHist->GetBinContent(11)+cHist->GetBinContent(12));
                        bla->SetBinContent(5, cHist->GetBinContent(13)+cHist->GetBinContent(14));
                        bla->SetBinContent(6, cHist->GetBinContent(15)+cHist->GetBinContent(16)+cHist->GetBinContent(17));
                        bla->SetBinContent(7, cHist->GetBinContent(18)+cHist->GetBinContent(19)+cHist->GetBinContent(20));

                        bla -> Sumw2(); // just for drawing - points
                        delete cHist;
                        cHist= bla;
                        cHist->SetMarkerStyle(cType->GetMarkerStyle());
                        cHist->SetMarkerSize(cType->GetMarkerSize());
                        cHist->SetFillColor(cType->GetFillColor());
                        cHist->SetLineColor(cType->GetLineColor());
                        cHist->SetLineWidth(cType->GetLineWidth());
                        cHist->SetStats(0);
                    }
*/
