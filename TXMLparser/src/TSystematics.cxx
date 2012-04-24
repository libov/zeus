#include <iostream>
using namespace std;

#include <TSystematics.h>
#include <TCrossSection.h>

#include <TAxis.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TF1.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TH1F.h>

TSystematics::TSystematics():
fCNVersion("v02"),
fYears(".0405e06e07p"),
fIsCharm(true),
fPlotxSect(false),
fBin(1),
fOutputFileName("test"),
fBinningFile("full.forCHARM"),
fTrueYears(".true05e06e0607p"),
fDrawOnlyErrors(false),
fYaxisLowLimit(-1),
fYaxisUpLimit(-1)
{
    TString PLOTS_PATH = getenv("PLOTS_PATH");
    fOutputPath = PLOTS_PATH;
    fCNVersion = getenv("CN_VERSION");
}

void TSystematics::Initialize () {

    // by default, set error array to zero
    for (unsigned i=0; i<fNpoints; i++) {
        x_err[i] = 0;
    }
}

void TSystematics::Draw() {

    // buffers
    Float_t     result;
    Float_t     result_err;

    // get the fit results for each value of the scanning variable
    for (unsigned i=0; i<fNpoints; i++ ) {
        // for charm
        fIsCharm = true;
        GetResult(i, result, result_err);
        if (fDrawOnlyErrors) {
            k_c[i] = result_err;
            k_c_err[i] = 0;
        } else {
            k_c[i] = result;
            k_c_err[i] = result_err;
        }
        // for beauty
        fIsCharm = false;
        GetResult(i, result, result_err);
        if (fDrawOnlyErrors) {
            k_b[i] = result_err;
            k_b_err[i] = 0;
        } else {
            k_b[i] = result;
            k_b_err[i] = result_err;
        }
    }

    TCanvas def("","", 1200, 1000);
    def.cd();
    // nice look (no grey background)
    def.SetFillColor(0);
    
    // move upper right corner of statistics box inside a pad
    gStyle->SetStatX(0.8);
    gStyle->SetStatY(0.9);
    // show fit results
    gStyle->SetOptFit(1);
    // don't show histogram title
    gStyle->SetOptTitle(0);

    // create graphs
    fCharmGraph = new TGraphErrors(fNpoints, x, k_c, x_err, k_c_err);
    fBeautyGraph = new TGraphErrors(fNpoints, x, k_b, x_err, k_b_err);

    // cosmetics
    fCharmGraph -> SetMarkerStyle(22);
    fCharmGraph -> SetMarkerColor(kGreen);
    fCharmGraph -> SetMarkerSize(1.5);

    fBeautyGraph -> SetMarkerStyle(22);
    fBeautyGraph -> SetMarkerColor(kBlue);
    fBeautyGraph -> SetMarkerSize(1.5);

    // axes titles and ranges
    TAxis   *ax_charm_y = fCharmGraph -> GetYaxis();
    // change axis range  only if requested
    if (fYaxisUpLimit!=-1) ax_charm_y -> SetRangeUser(fYaxisLowLimit, fYaxisUpLimit);
    if (fPlotxSect) ax_charm_y -> SetTitle ("Cross Section");
    else ax_charm_y -> SetTitle ("Scaling factor");
    TAxis   *ax_charm_x = fCharmGraph -> GetXaxis();
    ax_charm_x -> SetTitle(fXAxisTitle);

    // Draw the graph
    fCharmGraph -> Draw("ap");
    fBeautyGraph -> Draw("psame");

    // fit the graph
    fCharmGraph -> Fit("pol1", "q", "", x[0], x[fNpoints-1]);
    fBeautyGraph -> Fit("pol1", "q", "", x[0], x[fNpoints-1]);
    
    // get the function and paramter errors
    TF1 *pol1_charm = fCharmGraph->GetFunction("pol1");
    TF1 *pol1_beauty = fBeautyGraph->GetFunction("pol1");
    
    Float_t     intercept_charm = pol1_charm -> GetParameter(0);
    Float_t     slope_charm = pol1_charm -> GetParameter(1);
    Float_t     slope_err_charm = pol1_charm -> GetParError(1);

    Float_t     intercept_beauty = pol1_beauty -> GetParameter(0);
    Float_t     slope_beauty = pol1_beauty -> GetParameter(1);
    Float_t     slope_err_beauty = pol1_beauty -> GetParError(1);

    Float_t     central_value_charm = intercept_charm + slope_charm * fDefault;
    Float_t     central_value_beauty = intercept_beauty + slope_beauty * fDefault;

    Float_t     systematic_error_charm = fVariation * slope_charm / central_value_charm;
    Float_t     systematic_error_beauty = fVariation * slope_beauty / central_value_beauty;
    
    fCharmSyst[fBin] = systematic_error_charm;
    fBeautySyst[fBin] = systematic_error_beauty;

    TPaveText   *  syst = new TPaveText(0.44, 0.65, 0.8, 0.73 ,"NDC");
    syst -> SetShadowColor(0);
    syst -> SetTextAlign(12);

    char tmp[256];
    sprintf (tmp, "Rel. syst. unc. charm: %.3f ", systematic_error_charm);
    syst -> AddText(tmp);

    sprintf (tmp, "Rel. syst. unc. beauty: %.3f ", systematic_error_beauty);
    syst -> AddText(tmp);
    
    syst -> Draw();

    TLine   * line_central = new TLine (fDefault, fYaxisLowLimit, fDefault, fYaxisUpLimit);
    line_central->SetLineStyle(2);
    line_central->SetLineWidth(2);

    TLine   * line_u = new TLine (fDefault+fUpVariation, fYaxisLowLimit, fDefault+fUpVariation, fYaxisUpLimit);
    line_u->SetLineStyle(3);
    line_u->SetLineWidth(1);

    TLine   * line_d = new TLine (fDefault-fDownVariation, fYaxisLowLimit, fDefault-fDownVariation, fYaxisUpLimit);
    line_d->SetLineStyle(3);
    line_d->SetLineWidth(1);

    line_central -> Draw();
    line_u -> Draw();
    line_d -> Draw();

    TString filename = fOutputPath+"/"+fOutputFileName+"_bin";
    filename += fBin;
    def.Print(filename+".png");
    def.Print(filename+".root");
}

void    TSystematics::GetResult(unsigned point, Float_t & result, Float_t & result_err) {

    TString XMLfilename;
    XMLfilename = "results."+fBinningFile+fVersionArray[point]+fYears+"."+fCNVersion+fTrueYears+".xml";

    TCrossSection   cCrossSection(XMLfilename);
    cCrossSection.setVerbose(false);

    if (fPlotxSect) {
            if (fIsCharm) {
            result = cCrossSection.getCrossSectionBin(fBin).get_sigma_c();
            result_err = cCrossSection.getCrossSectionBin(fBin).get_sigma_c_err();
        } else {
            result = cCrossSection.getCrossSectionBin(fBin).get_sigma_b();
            result_err = cCrossSection.getCrossSectionBin(fBin).get_sigma_b_err();
        }
    } else {
        if (fIsCharm) {
            result = cCrossSection.getCrossSectionBin(fBin).get_k_c();
            result_err = cCrossSection.getCrossSectionBin(fBin).get_k_c_err();
        } else {
            result = cCrossSection.getCrossSectionBin(fBin).get_k_b();
            result_err = cCrossSection.getCrossSectionBin(fBin).get_k_b_err();
        }
    }
}

void TSystematics::SetXArray(double * x_arr){
    for (unsigned i=0; i<fNpoints; i++) {
        x[i] = x_arr[i];
    }
}

void TSystematics::SetXerrorArray(double * x_err_arr){
    for (unsigned i=0; i<fNpoints; i++) {
        x_err[i] = x_err_arr[i];
    }
}

void TSystematics::SetVersionArray (TString * version_arr) {
    for (unsigned i=0; i<fNpoints; i++) {
        fVersionArray[i] = version_arr[i];
    }
}

// loops over all bins and determines systematic uncertainty for each of them;
// plots the systematics as a function of a bin number
void TSystematics::DrawAll() {

    // loop over all bins in xml file (hardcoded at the moment)
    for (int bin=1; bin<=63; bin++) {
        cout << "INFO: setting bin to " << bin << endl;
        SetBin(bin);
        // determine the systematics and print the plot with the scan
        Draw();
    }

    // draw the systematic uncertainty as a function of a bin number
    DrawVector(fCharmUpSyst, fCharmUpSyst_err, "charm_up");
    DrawVector(fCharmDownSyst, fCharmDownSyst_err, "charm_down");
    DrawVector(fBeautyUpSyst, fBeautyUpSyst_err, "beauty_up");
    DrawVector(fBeautyDownSyst, fBeautyDownSyst_err, "beauty_down");
}

// draws the syst. unc. as a function of a bin number
void TSystematics::DrawVector(map<unsigned, Float_t> syst_map, map<unsigned, Float_t> syst_err_map, TString suffix) {

    // get the number of bins stored to a map
    unsigned nbins = syst_map.size();
    map<unsigned, Float_t>::iterator it;

    // helping arrays
    double  x[100];
    double  x_err[100];
    double  y[100];
    double  y_err[100];
    unsigned counter = 0;

    // loop over the map
    for ( it=syst_map.begin() ; it != syst_map.end(); it++ ) {
        // get the bin number as stored in the map
        x[counter] = (*it).first;
        x_err[counter] = 0;
        // get the systematic uncertainty
        y[counter] = (*it).second;
        // get "uncertainty on uncertainty", i.e. an uncertainty of the slope fit
        y_err[counter] = syst_err_map[(*it).first];
        counter++;
    }

    // create a graph and a canvas
    TGraphErrors * gr = new TGraphErrors(counter, x, y, x_err, y_err);
    TCanvas def("","", 2000, 800);
    def.cd();
    // nice look (no grey background)
    def.SetFillColor(0);
    // dummy histo
    TH1F * h  = new TH1F ("dummy","",65,0,65);
    h->SetStats(0);
    h->Draw();
    h->SetAxisRange(-0.05, 0.25, "Y");

    gr -> SetMarkerStyle(20);
    gr -> SetMarkerSize(1);
    gr -> Draw("p");

    // print the result into a file
    def.Print(fOutputPath+"/"+fOutputFileName+"_"+suffix+"_all_bins.png");
    def.Print(fOutputPath+"/"+fOutputFileName+"_"+suffix+"_all_bins.root");
}
