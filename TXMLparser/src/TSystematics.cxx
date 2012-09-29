#include <iostream>
#include <fstream>
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

ofstream output;

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
fYaxisUpLimit(-1),
fOnlyInclusive(true),
fBothFlavours(false)
{
    TString PLOTS_PATH = getenv("PLOTS_PATH");
    fOutputPath = PLOTS_PATH;
    fCNVersion = getenv("CN_VERSION");

}

void TSystematics::Initialize () {

    // guess which flavour
    if ( fBinningFile.Contains("full.forCHARM") && !fBinningFile.Contains("ET5") ) {
        fFlavour = kCharm;
        cout << "c" << endl;
    } else {
        fFlavour = kBeauty;
        cout << "b" << endl;
    }

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

    Float_t     intercept_charm, slope_charm, slope_err_charm;
    Float_t     intercept_beauty, slope_beauty, slope_err_beauty;

    // create a canvas
    TCanvas def("","", 1200, 1000);
    def.cd();
    def.SetFillColor(0);

    // move upper right corner of statistics box inside a pad
    gStyle->SetStatX(0.8);
    gStyle->SetStatY(0.9);
    // show fit results
    gStyle->SetOptFit(1);
    // don't show histogram title
    gStyle->SetOptTitle(0);

    // axes for cosmetic settings
    TAxis   *x_axis, *y_axis;

    if (fFlavour == kCharm || fBothFlavours) {

        // create a graph
        fCharmGraph = new TGraphErrors(fNpoints, x, k_c, x_err, k_c_err);
        // cosmetics
        fCharmGraph -> SetMarkerStyle(22);
        fCharmGraph -> SetMarkerColor(kGreen);
        fCharmGraph -> SetMarkerSize(1.5);
        // Draw the graph
        fCharmGraph -> Draw("ap");
        // fit the graph
        fCharmGraph -> Fit("pol1", "q", "", x[0], x[fNpoints-1]);
        // get the function and paramter errors
        TF1 *pol1_charm = fCharmGraph->GetFunction("pol1");
        intercept_charm = pol1_charm -> GetParameter(0);
        slope_charm = pol1_charm -> GetParameter(1);
        slope_err_charm = pol1_charm -> GetParError(1);
        // get axes
        x_axis = fCharmGraph -> GetXaxis();
        y_axis = fCharmGraph -> GetYaxis();

    } else if (fFlavour == kBeauty || fBothFlavours) {

        // create a graph
        fBeautyGraph = new TGraphErrors(fNpoints, x, k_b, x_err, k_b_err);
        // cosmetics
        fBeautyGraph -> SetMarkerStyle(22);
        fBeautyGraph -> SetMarkerColor(kBlue);
        fBeautyGraph -> SetMarkerSize(1.5);
        // Draw the graph
        fBeautyGraph -> Draw("ap");
        // fit the graph
        fBeautyGraph -> Fit("pol1", "q", "", x[0], x[fNpoints-1]);
        // get the function and paramter errors
        TF1 *pol1_beauty = fBeautyGraph->GetFunction("pol1");
        intercept_beauty = pol1_beauty -> GetParameter(0);
        slope_beauty = pol1_beauty -> GetParameter(1);
        slope_err_beauty = pol1_beauty -> GetParError(1);
        // get axes
        x_axis = fBeautyGraph -> GetXaxis();
        y_axis = fBeautyGraph -> GetYaxis();
    }

    // axes titles and ranges
    // change axis range  only if requested
    if (fYaxisUpLimit!=-1) y_axis -> SetRangeUser(fYaxisLowLimit, fYaxisUpLimit);
    if (fPlotxSect) {
        y_axis -> SetTitle ("Cross Section");
    } else {
        y_axis -> SetTitle ("Scaling factor");
    }
    x_axis -> SetTitle(fXAxisTitle);

    Float_t     central_value_charm = intercept_charm + slope_charm * fDefault;
    Float_t     central_value_beauty = intercept_beauty + slope_beauty * fDefault;

    Float_t     systematic_error_charm_up = TMath::Abs(fUpVariation * slope_charm / central_value_charm);
    Float_t     systematic_error_charm_down = TMath::Abs(fDownVariation * slope_charm / central_value_charm);
    Float_t     systematic_error_beauty_up = TMath::Abs(fUpVariation * slope_beauty / central_value_beauty);
    Float_t     systematic_error_beauty_down = TMath::Abs(fDownVariation * slope_beauty / central_value_beauty);

    TPaveText   *  syst = new TPaveText(0.44, 0.55, 0.8, 0.73 ,"NDC");
    syst -> SetShadowColor(0);
    syst -> SetTextAlign(12);

    // depending on the sign of the slope, up-variation of the scan variable can enter +systematics or -systematics;
    // similarly for down-variation
    if (fFlavour == kCharm || fBothFlavours) {
        char tmp[256];
        if (slope_charm>0) {
            sprintf (tmp, "Systematic uncertainty: ^{+%.3f}_{-%.3f}", systematic_error_charm_up, systematic_error_charm_down);
            fCharmUpSyst[fBin] = systematic_error_charm_up;
            fCharmDownSyst[fBin] = systematic_error_charm_down;
            fCharmUpSyst_err[fBin] = systematic_error_charm_up * TMath::Abs(slope_err_charm/slope_charm);
            fCharmDownSyst_err[fBin] = systematic_error_charm_down * TMath::Abs(slope_err_charm/slope_charm);

        } else {
            sprintf (tmp, "Systematic uncertainty: ^{+%.3f}_{-%.3f}", systematic_error_charm_down, systematic_error_charm_up);
            fCharmDownSyst[fBin] = systematic_error_charm_up;
            fCharmUpSyst[fBin] = systematic_error_charm_down;
            fCharmDownSyst_err[fBin] = systematic_error_charm_up * TMath::Abs(slope_err_charm/slope_charm);
            fCharmUpSyst_err[fBin] = systematic_error_charm_down * TMath::Abs(slope_err_charm/slope_charm);
        }
        syst -> AddText(tmp);
    } else if (fFlavour == kBeauty) {
        char tmp[256];
        if (slope_beauty>0) {
            sprintf (tmp, "Systematic uncertainty: ^{+%.3f}_{-%.3f}", systematic_error_beauty_up, systematic_error_beauty_down);
            fBeautyUpSyst[fBin] = systematic_error_beauty_up;
            fBeautyDownSyst[fBin] = systematic_error_beauty_down;
            fBeautyUpSyst_err[fBin] = systematic_error_beauty_up * TMath::Abs(slope_err_beauty/slope_beauty);
            fBeautyDownSyst_err[fBin] = systematic_error_beauty_down * TMath::Abs(slope_err_beauty/slope_beauty);
        } else {
            sprintf (tmp, "Systematic uncertainty: ^{+%.3f}_{-%.3f}", systematic_error_beauty_down, systematic_error_beauty_up);
            fBeautyDownSyst[fBin] = systematic_error_beauty_up;
            fBeautyUpSyst[fBin] = systematic_error_beauty_down;
            fBeautyDownSyst_err[fBin] = systematic_error_beauty_up * TMath::Abs(slope_err_beauty/slope_beauty);
            fBeautyUpSyst_err[fBin] = systematic_error_beauty_down * TMath::Abs(slope_err_beauty/slope_beauty);
        }
        syst -> AddText(tmp);

    } else {
        cout << "ERROR: no such flavour " << fFlavour << endl;
        abort();
    }

    // draw the systematics bos
    syst -> Draw();

    // draw the vertical lines representing default value of the scan variable and variations
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
    def.Print(filename+".eps");
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
    unsigned nbins = 63;
    if (fBinningFile == "full") nbins = 62;
    for (int bin=1; bin<=nbins; bin++) {
        cout << "INFO: setting bin to " << bin << endl;
        SetBin(bin);
        // determine the systematics and print the plot with the scan
        Draw();
        // stop if requested to print only the inclusive bin
        if (fOnlyInclusive) break;
    }

    // draw the systematic uncertainty as a function of a bin number
    DrawVector(fCharmUpSyst, fCharmUpSyst_err, "charm_up");
    DrawVector(fCharmDownSyst, fCharmDownSyst_err, "charm_down");
    DrawVector(fBeautyUpSyst, fBeautyUpSyst_err, "beauty_up");
    DrawVector(fBeautyDownSyst, fBeautyDownSyst_err, "beauty_down");

    // print the results into a text file
    PrintAll();
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

// print systematics for all differential bins
void TSystematics::PrintAll() {

    // open the text file to store the results
    TString PLOTS_PATH=getenv("PLOTS_PATH");
    output.open(PLOTS_PATH + "/" + fOutputFileName);

    output << " Systematic uncertainties for " << fOutputFileName << endl;

    // not using fFlavour variable since for beauty one has to distinguish between full and full.forCHARM.ET5 due to different binning
    if ( fBinningFile.Contains("full.forCHARM") ) {

        if ( fBinningFile.Contains("ET5") ) {

            output << "\nBeauty systematics, total cross-section:" << endl;
            output << "+" << fBeautyUpSyst[1] << " -" << fBeautyDownSyst[1] << endl;

            PrintDifferential(2, 12, kBeauty, "Eta");
            PrintDifferential(14, 20, kBeauty, "Et");
            PrintDifferential(31, 36, kBeauty, "xda");
            PrintDifferential(38, 45, kBeauty, "q2da");
            PrintDifferential(46, 49, kBeauty, "x_q2bin1");
            PrintDifferential(50, 54, kBeauty, "x_q2bin2");
            PrintDifferential(55, 58, kBeauty, "x_q2bin3");
            PrintDifferential(59, 61, kBeauty, "x_q2bin4");
            PrintDifferential(62, 63, kBeauty, "x_q2bin5");

        } else {

            output << "\nCharm systematics, total cross-section:" << endl;
            output << "+" << fCharmUpSyst[1] << " -" << fCharmDownSyst[1] << endl;

            PrintDifferential(2, 12, kCharm, "Eta");
            PrintDifferential(14, 20, kCharm, "Et");
            PrintDifferential(31, 36, kCharm, "xda");
            PrintDifferential(38, 45, kCharm, "q2da");
            PrintDifferential(46, 49, kCharm, "x_q2bin1");
            PrintDifferential(50, 54, kCharm, "x_q2bin2");
            PrintDifferential(55, 58, kCharm, "x_q2bin3");
            PrintDifferential(59, 61, kCharm, "x_q2bin4");
            PrintDifferential(62, 63, kCharm, "x_q2bin5");

        }

    } else {

        output << "\nBeauty systematics, total cross-section:" << endl;
        output << "+" << fBeautyUpSyst[1] << " -" << fBeautyDownSyst[1] << endl;

        PrintDifferential(2, 11, kBeauty, "Eta");
        PrintDifferential(13, 19, kBeauty, "Et");
        PrintDifferential(30, 35, kBeauty, "xda");
        PrintDifferential(37, 44, kBeauty, "q2da");
        PrintDifferential(45, 48, kBeauty, "x_q2bin1");
        PrintDifferential(49, 53, kBeauty, "x_q2bin2");
        PrintDifferential(54, 57, kBeauty, "x_q2bin3");
        PrintDifferential(58, 60, kBeauty, "x_q2bin4");
        PrintDifferential(61, 62, kBeauty, "x_q2bin5");

    }

}

// print systematics for differential distribution
void TSystematics::PrintDifferential(unsigned bin1, unsigned bin2, flavour f, TString variable) {

    TString flavour;
    if (f==kCharm) flavour = "Charm";
    if (f==kBeauty) flavour = "Beauty";

    output << "\n" << flavour << " systematics in differential cross sections d sigma / dY in bins of " << variable << endl;

    unsigned counter = 1;

    for (int i=bin1; i<=bin2; i++) {
        if (f==kCharm) {
            output << "Bin " << counter << ": +" << fCharmUpSyst[i] << " -" << fCharmDownSyst[i] << endl;
        } else if (f==kBeauty) {
            output << "Bin " << counter << ": +" << fBeautyUpSyst[i] << " -" << fBeautyDownSyst[i] << endl;
        }
        counter++;
    }
}

// if an uncertainty is one-sided, it can be used to correct central values of the cross-sections!
void TSystematics::CorrectCrossSections(TString XMLfile) {

    // open the cross-section file
    TCrossSection cCrossSection(XMLfile);
    unsigned nbins = cCrossSection.getNBins();
    for (unsigned i = 1; i<=nbins; i++) {
        // get a bin
        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(i);

        // get values of cross-sections
        Float_t sigma_c = cBin.get_sigma_c();
        Float_t sigma_c_err = cBin.get_sigma_c_err();

        Float_t sigma_b = cBin.get_sigma_b();
        Float_t sigma_b_err = cBin.get_sigma_b_err();

        // get value of the correction; supposed to be one-sided! hence determine if it is indeed one-sided first!
        Float_t correction_charm;
        if (fCharmUpSyst[i]==0) {
            correction_charm = 1 - fCharmDownSyst[i];
        } else if (fCharmDownSyst[i]==0) {
            correction_charm = 1 + fCharmUpSyst[i];
        } else {
            cout << "ERROR: not one-sided uncertainty! Cannot determine a correction!!" << endl;
            abort();
        }

        Float_t correction_beauty;
        if (fBeautyUpSyst[i]==0) {
            correction_beauty = 1 - fBeautyDownSyst[i];
        } else if (fBeautyDownSyst[i]==0) {
            correction_beauty = 1 + fBeautyUpSyst[i];
        } else {
            cout << "ERROR: not one-sided uncertainty! Cannot determine a correction!!" << endl;
            abort();
        }

        sigma_c *= correction_charm;
        sigma_c_err *= correction_charm;
        sigma_b *= correction_beauty;
        sigma_b_err *= correction_beauty;

        cBin.set_sigma_c(sigma_c);
        cBin.set_sigma_c_err(sigma_c_err);
        cBin.set_sigma_b(sigma_b);
        cBin.set_sigma_b_err(sigma_b_err);

        cCrossSection.modifyCrossSectionBin(i, cBin);
    }

    XMLfile += "corrected."+fOutputFileName;
    cCrossSection.WriteXMLfile(XMLfile);
}
