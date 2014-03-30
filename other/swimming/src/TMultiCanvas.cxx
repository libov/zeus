// system headers
#include <iostream>
#include <fstream>
using namespace std;

// ROOT headers
#include <TROOT.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TFile.h>
#include <TObjString.h>
#include <TObjArray.h>
#include <TPad.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TText.h>
#include <TLegend.h>
#include <TLatex.h>

// custom headers
#include <TMultiCanvas.h>

TMultiCanvas::TMultiCanvas(unsigned npads):
fNPads(npads)
{
    // create a canvas
    fCanvas = new TCanvas("c", "sigma_red", 800, 800);
    fCanvas -> cd();
    gStyle -> SetFrameBorderMode(0);
    gStyle -> SetEndErrorSize(5);
    fCanvas -> SetFillColor(0);

    // set some constants
    fMarginX = 0.13;
    fMarginY = 0.08;
    fPadSizeY = (1.0 - 2 * fMarginY)/3;
    fPadSizeX = (1.0 - fMarginX)/3;
    fXmin = 4e-5;
    fXmax = 2.5e-1;
    fRightMargin = 0.015;

    fYmin = 0;
    fYmaxBeauty = 0.057;
    fYmaxBeautyUpperRow = 0.02;
    fYmaxCharm = 0.7;

    fBeauty = false;

    fYAxisTitle = "#sigma_{red}^{c#bar{c}}";

    // initialize
    create_pads();
    draw_dummy_histos();
    draw_axes();
    draw_labels();

    fLegend = new TLegend(0.55, 0.10, 0.85, 0.27);
    fLegend -> SetFillColor(0);
    fLegend -> SetShadowColor(0);
    fLegend -> SetBorderSize(0);
    fLegend -> Draw();
}

void TMultiCanvas::create_pads() {

    fPads[1] = new TPad ("p1", "", 0*fPadSizeX + fMarginX, 2*fPadSizeY + fMarginY, 1*fPadSizeX + fMarginX, 3*fPadSizeY + fMarginY);
    fPads[2] = new TPad ("p2", "", 1*fPadSizeX + fMarginX, 2*fPadSizeY + fMarginY, 2*fPadSizeX + fMarginX, 3*fPadSizeY + fMarginY);
    fPads[3] = new TPad ("p3", "", 2*fPadSizeX + fMarginX, 2*fPadSizeY + fMarginY, 1, 3*fPadSizeY + fMarginY);

    fPads[4] = new TPad ("p4", "", 0*fPadSizeX + fMarginX, 1*fPadSizeY + fMarginY, 1*fPadSizeX + fMarginX, 2*fPadSizeY + fMarginY);
    fPads[5] = new TPad ("p5", "", 1*fPadSizeX + fMarginX, 1*fPadSizeY + fMarginY, 2*fPadSizeX + fMarginX, 2*fPadSizeY + fMarginY);
    fPads[6] = new TPad ("p6", "", 2*fPadSizeX + fMarginX, 1*fPadSizeY + fMarginY, 1, 2*fPadSizeY + fMarginY);

    fPads[7] = new TPad ("p7", "", 0*fPadSizeX + fMarginX, 0*fPadSizeY + fMarginY, 1*fPadSizeX + fMarginX, 1*fPadSizeY + fMarginY);

    // cosmetics
    for (int i=1; i<=7; i++) {
        fPads[i] -> Draw();
        fPads[i] -> SetFrameFillColor(0);
        fPads[i] -> SetFillColor(0);
        fPads[i] -> SetLogx();
        fPads[i] -> SetTicks(1,1);
/*    }

    for (int i=1; i<=7; i++) {*/
         fPads[i] -> SetTopMargin(0);
         fPads[i] -> SetRightMargin(0);
         fPads[i] -> SetBottomMargin(0);
         fPads[i] -> SetLeftMargin(0);
    }

     fPads[3] -> SetRightMargin(fRightMargin);
     fPads[6] -> SetRightMargin(fRightMargin);
}

void TMultiCanvas::draw_dummy_histos() {

    // dummy histo
    TH1F * h = new TH1F ("", "", 100, fXmin, fXmax);
    h -> SetStats(kFALSE);
    if (fBeauty) h -> SetAxisRange(fYmin, fYmaxBeauty, "Y");
    else h -> SetAxisRange(fYmin, fYmaxCharm, "Y");
    h -> SetNdivisions(504, "Y");
    TH1F * h2 = (TH1F *) h -> Clone();
    h2 -> SetAxisRange(0, fYmaxBeautyUpperRow, "Y");

    TH1F * dummy;
    for (unsigned i=1; i<=fNPads; i++) {
        fPads[i] -> cd();
        if (i<=3 && fBeauty) {
            dummy = h2;
        } else {
            dummy = h;
        }
        dummy -> Draw();
    }
}

void TMultiCanvas::draw_axes() {

    fCanvas -> cd();

    // horizontal axes (for labels and title)
    Float_t label_size_x = 0.027;
    Float_t label_size_y = 0.027;
    Float_t title_offset_x = 0.93;
    Float_t title_size_x = 0.035;
    TString axis_title_x = "x ";
    TGaxis *axis1 = new TGaxis(fMarginX, fMarginY, fMarginX+fPadSizeX, fMarginY, fXmin, fXmax, 510,"G");
    axis1 -> SetLabelSize(label_size_x);
    axis1 -> SetLabelOffset(0.002);
    axis1 -> SetTitleOffset(title_offset_x);
    axis1 -> SetTitle(axis_title_x);
    axis1 -> SetTitleSize(title_size_x);
    axis1 -> Draw();

    TGaxis *axis2 = new TGaxis(fMarginX+fPadSizeX, fMarginY+fPadSizeY, fMarginX+2*fPadSizeX, fMarginY+fPadSizeY, fXmin, fXmax, 510, "G");
    axis2 -> SetLabelSize(label_size_x);
    axis2 -> SetLabelOffset(0.002);
    axis2 -> SetTitleOffset(title_offset_x);
    axis2 -> SetTitle(axis_title_x);
    axis2 -> SetTitleSize(title_size_x);
    axis2 -> Draw();

    TGaxis *axis3 = new TGaxis(fMarginX+2 * fPadSizeX, fMarginY+fPadSizeY, fMarginX+3*fPadSizeX-fRightMargin*fPadSizeX, fMarginY+fPadSizeY, fXmin, fXmax, 510, "G");
    axis3 -> SetLabelSize(label_size_x);
    axis3 -> SetLabelOffset(0.002);
    axis3 -> SetTitleOffset(title_offset_x);
    axis3 -> SetTitle(axis_title_x);
    axis3 -> SetTitleSize(title_size_x);
    axis3 -> Draw();

    // vertical ones
    TGaxis *axis4;
    if (!fBeauty) axis4 = new TGaxis(fMarginX, fMarginY+2*fPadSizeY, fMarginX, fMarginY+3*fPadSizeY, fYmin, fYmaxCharm, 504);
    if (fBeauty) axis4 = new TGaxis(fMarginX, fMarginY+2*fPadSizeY, fMarginX, fMarginY+3*fPadSizeY, fYmin, fYmaxBeautyUpperRow, 504);
    axis4 -> SetLabelSize(label_size_y);
    axis4 -> SetTitleOffset(1.2);
    if (fBeauty) axis4 -> SetTitleOffset(1.4);
    axis4 -> SetTitle(fYAxisTitle);
    axis4 -> Draw();

    TGaxis *axis5;
    if (!fBeauty) axis5 = new TGaxis(fMarginX, fMarginY+1*fPadSizeY, fMarginX, fMarginY+2*fPadSizeY, fYmin, fYmaxCharm, 504);
    if (fBeauty) axis5 = new TGaxis(fMarginX, fMarginY+1*fPadSizeY, fMarginX, fMarginY+2*fPadSizeY, fYmin, fYmaxBeauty, 504);
    axis5 -> SetLabelSize(label_size_y);
    axis5 -> Draw();

    TGaxis *axis6;
    if (!fBeauty) axis6 = new TGaxis(fMarginX, fMarginY, fMarginX, fMarginY+1*fPadSizeY, fYmin, fYmaxCharm, 504);
    if (fBeauty) axis6 = new TGaxis(fMarginX, fMarginY, fMarginX, fMarginY+1*fPadSizeY, fYmin, fYmaxBeauty, 504);
    axis6 -> SetLabelSize(label_size_y);
    axis6 -> Draw();
}

void TMultiCanvas::draw_labels() {

    fCanvas -> cd();

    // finally, print the ZEUS on top
    TText * zeus = new TText (0.49, 0.94, "ZEUS");
    zeus -> SetTextFont(62);
    zeus -> SetTextSize (0.07);
    zeus -> Draw();

    // create Q2 labels
    Float_t y_position;
    if (fBeauty) y_position = 0.87;
    if (!fBeauty) y_position = 0.87;
    TLatex * q2_values[10];
    q2_values[0] = new TLatex(0.24 + 0 * fPadSizeX, y_position, "Q^{2} = 7 GeV^{2}");
    q2_values[1] = new TLatex(0.24 + 1 * fPadSizeX, y_position, "Q^{2} = 12 GeV^{2}");
    q2_values[2] = new TLatex(0.24 + 2 * fPadSizeX, y_position, "Q^{2} = 18 GeV^{2}");
    q2_values[3] = new TLatex(0.24 + 0 * fPadSizeX, y_position - 1 * fPadSizeY, "Q^{2} = 32 GeV^{2}");
    q2_values[4] = new TLatex(0.24 + 1 * fPadSizeX, y_position - 1 * fPadSizeY, "Q^{2} = 60 GeV^{2}");
    q2_values[5] = new TLatex(0.24 + 2 * fPadSizeX, y_position - 1 * fPadSizeY, "Q^{2} = 120 GeV^{2}");
    q2_values[6] = new TLatex(0.24 + 0 * fPadSizeX, y_position- 2 * fPadSizeY, "Q^{2} = 650 GeV^{2}");

    for (int i=0; i<fNPads; i++) {
        q2_values[i] -> Draw();
        q2_values[i] -> SetTextSize(0.025);
    }
}

Int_t TMultiCanvas::get_pad_number(Double_t q2) {

    Double_t plotted_q2[7] = {7, 12, 18, 32, 60, 120, 650};
    bool found = false;
    for (int i=0; i<fNPads; i++) {
        if (plotted_q2[i] == q2) return i;
    }

    return -1;
}

void TMultiCanvas::PlotData(TCharmMeasurement data, Float_t shift, int marker_style, Float_t marker_size, int color, bool draw_total_uncertainty) {

    unsigned npoints = data.get_n_points();

    TGraphAsymmErrors * g;

    for (int i=0; i<npoints; i++) {

        Double_t q2 = data.getQ2(i);
        Double_t x = data.getX(i);
        Double_t value = data.getValue(i);
        Double_t tot_error_up = data.getErrTotalUp(i);
        Double_t tot_error_down = data.getErrTotalDown(i);
        Double_t stat_error = data.getErrStat(i);

        Int_t pad = get_pad_number(q2);
        if (pad<0) continue;
        fPads[pad+1] -> cd();

        Double_t x_array[1];
        Double_t y_array[1];
        Double_t x_err_up_array[1];
        Double_t x_err_down_array[1];
        Double_t y_err_up_array[1];
        Double_t y_err_down_array[1];

        x_array[0] = x * exp(shift);
        y_array[0] = value;
        if (draw_total_uncertainty) {
            y_err_up_array[0] = tot_error_up;
            y_err_down_array[0] = tot_error_down;
        } else {
            y_err_up_array[0] = stat_error;
            y_err_down_array[0] = stat_error;
        }

        g = new TGraphAsymmErrors(1, x_array, y_array, x_err_down_array, x_err_up_array, y_err_down_array, y_err_up_array);
        g -> SetMarkerStyle(marker_style);
        g -> SetMarkerSize(marker_size);
        g -> SetMarkerColor(color);
        g -> SetLineColor(color);

        TString draw_option;
        if (draw_total_uncertainty) {
            draw_option = "pz";
        } else {
            draw_option = "||";
        }

        g -> Draw(draw_option);
    }

    if (draw_total_uncertainty) fLegend -> AddEntry(g, data.getNameForLegend(), "p");
}

void TMultiCanvas::Print(TString filename) {
    TString PLOTS_PATH = getenv("PLOTS_PATH");
    fCanvas -> Print(PLOTS_PATH+"/"+filename);
}
