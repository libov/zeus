//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

// ROOT includes
#include <TString.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TROOT.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TStyle.h>

// my includes
#include <TResultPlotter.h>
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

// system includes
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

TResultPlotter::TResultPlotter():
fNpads_x(1),
fNpads_y(1),
isCharm(true),
fConfig("")
{
}

void TResultPlotter::Initialize() {

    // set ticks on the right and on the top
    gStyle->SetPadTickY(1);
    gStyle->SetPadTickX(1);

    // read settings from the config file
    if (fConfig=="") {
        cout << "ERROR: config file not set!" << endl;
        abort();
    }

    // open config file
    TString config_path = "config/"+fConfig;
    ifstream f(config_path);
    if (!f.is_open()) {
        cout << "ERROR: Unable to open file " << config_path; 
        abort();
    }

    // read settings and store to maps
    string line;
    while ( f.good() ) {

        // read each line
        getline (f,line);

        // skip if empty line
        if (line=="") continue;

        // tokenize
        TString line_str = line;
        TObjArray * tokens = line_str.Tokenize("\t");
        TString id = ((TObjString*)tokens->At(0)) -> GetString();
        TString xtitle = ((TObjString*)tokens->At(1)) -> GetString();
        TString ytitle = ((TObjString*)tokens->At(2)) -> GetString();
        Float_t yaxis_low_limit = (((TObjString*)tokens->At(3)) -> GetString()).Atof();
        Float_t yaxis_up_limit = (((TObjString*)tokens->At(4)) -> GetString()).Atof();

        // set the values that were read
        fXtitle[id] = xtitle;
        fYtitle[id] = ytitle;
        fYaxis_low_limit[id] = yaxis_low_limit;
        fYaxis_up_limit[id] = yaxis_up_limit;
    }
}

void    TResultPlotter::AddXMLFile(TString file_name){

    // get data from the XML file
    TCrossSection cCrossSection(file_name);

    // safety
    fBinGroupMap[file_name].clear();

    // get a map of the bin ids for each bin group (i.e. for each diff. xsection) from TCrossSection
    map<TString, vector<unsigned> > BinIDsMap = cCrossSection.getBinIDsMap();
    map<TString, vector<unsigned> >::iterator iter;

    // loop over the map, for each group of bins get a vector of bin-IDs belonging to that group
    for ( iter=BinIDsMap.begin() ; iter != BinIDsMap.end(); iter++ ) {

        // create a BinGroup structure for each <bin_group>. that represents one plot
        // (i.e. a differential cross-section)
        BinGroup cBinGroup;
        cBinGroup.ID = (*iter).first;

        // arrays to store binning, cross-sections and uncertainties
        const unsigned MAXBINS=50;
        Float_t     bin_center[MAXBINS];        // gives x-values for graphs
        Float_t     bin_edge[MAXBINS];          // used for histograms
        Float_t     y[MAXBINS];                 // gives y-values for graphs/bin contents for histograms
        Float_t     y_err_stat[MAXBINS];
        Float_t     y_err_tot_up[MAXBINS];
        Float_t     y_err_tot_down[MAXBINS];
        Float_t     x_err[MAXBINS];             // represents half-width of a bin, used as an x-error for graphs (for theory only, in order to have a boxed-band)

        // get a vector of bin IDs and loop over them to build a BinGroup structure
        vector <unsigned> binIDList = (*iter).second;
        unsigned nbins = binIDList.size();
        for (int i=0; i<nbins; i++) {

            unsigned id = binIDList[i];
            TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(id);

            // this is to distinguish between
            // single and double differential cross-section
            // single: take 1st subbin variable as binning in the plot
            // double: take 2nd variable (x)
            Float_t         bin_low_edge;
            Float_t         bin_up_edge;
            if (cBin.getNSubBins() == 1 ) {
                bin_low_edge = cBin.getSubBinLowEdge(0);
                bin_up_edge = cBin.getSubBinUpEdge(0);
            } else if (cBin.getNSubBins() == 2) { // for double differential  cross-sections we take the 2nd variable, that is x (not Q2)
                bin_low_edge = cBin.getSubBinLowEdge(1);
                bin_up_edge = cBin.getSubBinUpEdge(1);
            } else {
                cout << "ERROR: more than two subbins found! " << endl;
                cout << "Terminating!" << endl;
                abort();
            }

            // now we know bin edges for this bin
            // sanity check: upper edge for previous bin should be equal 
            // to lower edge bin of the current one (not for the very first bin of course, hence this check for i==0 )
            if ( (i > 0) && (bin_edge[i] != bin_low_edge) ) {
                cout << "ERROR: bins not continuous. Terminating!" << endl;
                abort();
            } else if ( i == 0 ) {   // if this is a first bin, just assign a low edge value
                bin_edge[i]=bin_low_edge;
            }
            // assign upper edge of the bin
            bin_edge[i+1] = bin_up_edge;
            // calculate center and half-width
            bin_center[i] = (bin_low_edge + bin_up_edge)/2;
            if (fStyleMap[file_name].draw_marker) {
                x_err[i] = 0;
            } else {
                x_err[i] = (bin_up_edge - bin_low_edge)/2;
            }

            // assign values and errors
            if (isCharm && fPlotScalingFactors) {

                y[i] = cBin.get_k_c();
                y_err_stat[i] = cBin.get_k_c_err();
                y_err_tot_up[i] = cBin.get_k_c_err();
                y_err_tot_down[i] = cBin.get_k_c_err();

            } else if (isCharm && !fPlotScalingFactors) {

                y[i] = cBin.get_sigma_c();
                y_err_stat[i] = cBin.get_sigma_c_err();
                y_err_tot_up[i] = sqrt(pow(cBin.get_sigma_c_err(), 2) + pow(cBin.get_sigma_c_err_syst_up(), 2));
                y_err_tot_down[i] = sqrt(pow(cBin.get_sigma_c_err(), 2) + pow(cBin.get_sigma_c_err_syst_down(), 2));

            } else if (!isCharm && fPlotScalingFactors) {

                y[i] = cBin.get_k_b();
                y_err_stat[i] = cBin.get_k_b_err();
                y_err_tot_up[i] = cBin.get_k_b_err();
                y_err_tot_down[i] = cBin.get_k_b_err();

            } else if (!isCharm && !fPlotScalingFactors) {

                y[i] = cBin.get_sigma_b();
                y_err_stat[i] = cBin.get_sigma_b_err();
                y_err_tot_up[i] = sqrt(pow(cBin.get_sigma_b_err(), 2) + pow(cBin.get_sigma_b_err_syst_up(), 2));
                y_err_tot_down[i] = sqrt(pow(cBin.get_sigma_b_err(), 2) + pow(cBin.get_sigma_b_err_syst_down(), 2));
            }
        }

        // create a (dummy) histogram
        cBinGroup.histo_dummy = new TH1F (cBinGroup.ID.Data(), "", nbins, bin_edge);

        // create graphs
        cBinGroup.graph_stat = new TGraphErrors(nbins, bin_center, y, x_err, y_err_stat);   // note that there is no use for this if it's predictions
        cBinGroup.graph_tot = new TGraphAsymmErrors(nbins, bin_center, y, x_err, x_err, y_err_tot_down, y_err_tot_up);

        // put the BinGroup into the map
        fBinGroupMap[file_name].push_back(cBinGroup);

        // initialize pointer to canvas for this distribution to NULL to be used as a flag that a canvas doesn't exist and has to be created
        fCanvasMap[cBinGroup.ID] = NULL;
    }
}

// main drawing routine
void TResultPlotter::DrawPlots(TString file_name, unsigned pad_number, bool same) {

        // get a vector of BinGroup objects belonging to this XML file
        vector<BinGroup> cBinGroupList = fBinGroupMap[file_name];

        // loop over all BinGroup objects belonging to this XML file
        for (int i=0; i<cBinGroupList.size(); i++) {

            // get a BinGroup object
            BinGroup cBinGroup = cBinGroupList[i];
            TString id = cBinGroup.ID;

            // set axes names according to settings from the config file
            cBinGroup.histo_dummy -> SetXTitle(fXtitle[id]);
            cBinGroup.histo_dummy -> SetYTitle(fYtitle[id]);

            // set axes range according to settings from the config file
            cBinGroup.histo_dummy -> SetAxisRange(fYaxis_low_limit[id], fYaxis_up_limit[id], "Y");

            // settings for labels, TODO: add sth controllable from above
            cBinGroup.histo_dummy -> SetTitleSize(0.06, "Y");;
            cBinGroup.histo_dummy -> SetTitleOffset(1.25, "Y");
            cBinGroup.histo_dummy -> SetTitleSize(0.07, "X");;
            cBinGroup.histo_dummy -> SetTitleOffset(0.85, "X");

            // remove statistics box
            cBinGroup.histo_dummy -> SetStats(0);

            // get a pointer to a relevant TCanvas (or create it if doesn't exist yet)
            TCanvas   * cCanvas;
            if (fCanvasMap[cBinGroup.ID] == NULL) { // create case
                // create a canvas
                cCanvas = new TCanvas ("CrossSection."+cBinGroup.ID + file_name, "", 0, 0, 700, 860);
                cCanvas -> SetFillColor(0);

                // divide the canvas according to the settings
                cCanvas -> Divide(fNpads_x, fNpads_y);

                // special case of two pads one below the other: make the lower one smaller for the ratio plot
                if ( (fNpads_x==1) && (fNpads_y==2) ) {
                    cCanvas -> cd (1);
                    gPad -> SetPad (0, 0.25, 1, 1);
                    cCanvas -> cd (2);
                    gPad -> SetPad (0, 0, 1, 0.25);
                }

                // add to the map
                fCanvasMap[cBinGroup.ID] = cCanvas;

            } else { // get a pointer case
                cCanvas = fCanvasMap[cBinGroup.ID];
            }

            // select respective subpad
            cCanvas -> cd(pad_number);

            // still some hardcodes... (TODO)
            if ( cBinGroup.ID.Contains("q2") || cBinGroup.ID.Contains("x") ) gPad -> SetLogx();
            if ( (cBinGroup.ID != "phijet") && (cBinGroup.ID != "etajet") ) gPad -> SetLogy();

            gPad->SetLeftMargin(0.15);
            gPad->SetBottomMargin(0.13);

            // draw the histogram
            if ( !same ) cBinGroup.histo_dummy -> Draw();

            // predictions and data are treated separately;
            // predictions: a band + a histogram as for central values,
            // points with stat. and tot. unceratainties

            if (fStyleMap[file_name].draw_band) {

                cBinGroup.graph_tot -> Draw("2");
                cBinGroup.graph_tot -> SetFillColor(fStyleMap[file_name].band_color);
            }

            if (fStyleMap[file_name].draw_line) {

                TH1F * h = (TH1F *) cBinGroup.histo_dummy -> Clone();
                unsigned nbins = h -> GetNbinsX();
                for (int j=1; j<=nbins; j++) {
                    Double_t    x,y;
                    // get the central value from the graph and set to histo
                    cBinGroup.graph_tot -> GetPoint(j-1, x, y);
                    h -> SetBinContent(j, y);
                }
                h -> SetLineColor(fStyleMap[file_name].line_color);
                h -> SetLineWidth(fStyleMap[file_name].line_width);
                h -> SetLineStyle(fStyleMap[file_name].line_style);
                h -> Draw("same");
            }

            if ( fStyleMap[file_name].draw_marker ) {

                cBinGroup.graph_stat -> Draw("epsame");
                cBinGroup.graph_tot -> Draw("epzsame");
                cBinGroup.graph_tot -> SetMarkerColor(fStyleMap[file_name].marker_color);
                cBinGroup.graph_tot -> SetMarkerStyle(fStyleMap[file_name].marker_style);
                cBinGroup.graph_tot -> SetMarkerSize(fStyleMap[file_name].marker_size);
            }

            // redraw axes so that no ticks are hidden by anything
            gPad -> RedrawAxis();
        }
}

void TResultPlotter::DrawRatio(TString file_name1, TString file_name2, unsigned pad_number, bool same) {

    // get vectors of bins for both files
    vector<BinGroup> cBinGroupList1 = fBinGroupMap[file_name1];
    vector<BinGroup> cBinGroupList2 = fBinGroupMap[file_name2];

    // sanity check: sizes of both arrays should be the same
    if ( cBinGroupList1.size() != cBinGroupList2.size() ) {
        cout << "ERROR: incompatible datasets selected: number of <bin_group> elements is different" << endl;
        cout << "Terminating, sorry." << endl;
        abort();
    }

    // loop over contents of the vectors
    for (int i=0; i<cBinGroupList1.size(); i++) {

        BinGroup cBinGroup1 = cBinGroupList1[i];
        BinGroup cBinGroup2 = cBinGroupList2[i];

        // create two graphs for representing statistical and systematic uncertainty in the ratio plot
        TGraphErrors * graph_ratio_stat = (TGraphErrors *) cBinGroup1.graph_stat -> Clone();
        TGraphAsymmErrors * graph_ratio_tot = (TGraphAsymmErrors *) cBinGroup1.graph_tot -> Clone();

        // set values and uncertainties of the ratio graphs
        for (int j=0; j < graph_ratio_stat->GetN(); j++) {

            Double_t x1, y1, y1_err_stat, y1_err_tot_up, y1_err_tot_down, x1_err;   // uncertainties are taken only from the 1st graph
            Double_t x2, y2;

            // get central values from the both graphs; since .graph_tot is used, it's valid both for theory and data
            cBinGroup1.graph_tot -> GetPoint(j, x1, y1);
            cBinGroup2.graph_tot -> GetPoint(j, x2, y2);
            // sanity check
            if (x1 != x2) {
                cout << "ERROR: x values don't match" << endl;
                abort();
            }

            // set the central value of the point - 1st divided by 2nd according to the convention (see output of -h option of plot_results app)
            graph_ratio_stat -> SetPoint(j, x1, y1/y2);
            graph_ratio_tot -> SetPoint(j, x1, y1/y2);

            // get uncertainty; note that it is taken from the 1st graph, which is data in data-to-theory comparisons;
            // for data-to-data comparisons this uncertainty in the ratio doesn't make much sense (correlations)
            y1_err_stat = cBinGroup1.graph_stat -> GetErrorYhigh(j);
            y1_err_tot_up = cBinGroup1.graph_tot -> GetErrorYhigh(j);
            y1_err_tot_down = cBinGroup1.graph_tot -> GetErrorYlow(j);
            if (fStyleMap[file_name1].draw_marker) x1_err = 0;
            else x1_err = cBinGroup1.graph_tot -> GetErrorXhigh(j);

            // set the uncertainties to ratio graphs
            graph_ratio_stat -> SetPointError(j, x1_err, y1_err_stat/y2);
            graph_ratio_tot -> SetPointError(j, x1_err, x1_err, y1_err_tot_down/y2, y1_err_tot_up/y2);
        }

        // create a canvas or get a pointer to it
        TCanvas   * cCanvas;
        if (fCanvasMap[cBinGroup1.ID] == NULL) {
            cCanvas = new TCanvas ("CrossSection."+cBinGroup1.ID + file_name1, "", 0, 0, 1050, 860);
            cCanvas -> SetFillColor(0);
            cCanvas -> Divide(fNpads_x, fNpads_y);

            fCanvasMap[cBinGroup1.ID] = cCanvas;
        } else {
            cCanvas = fCanvasMap[cBinGroup1.ID];
        }

        // select respective subpad
        cCanvas -> cd(pad_number);

        // pad settings
        if ( cBinGroup1.ID.Contains("q2") || cBinGroup1.ID.Contains("x") ) gPad -> SetLogx();
        gPad->SetLeftMargin(0.15);
        gPad->SetBottomMargin(0.13);

        // clone the dummy histogram so that no interference with other pads
        TH1F * histo_dummy = (TH1F*)cBinGroup1.histo_dummy -> Clone();
        histo_dummy -> SetAxisRange(0.4, 2.0, "Y");
        //histo_dummy -> SetAxisRange(0.3, 1.7, "Y");
        histo_dummy -> SetNdivisions(504, "Y");
        histo_dummy -> SetLabelSize(0.15,"Y");
        histo_dummy -> SetYTitle("data / HVQDIS");
        histo_dummy -> SetTitleSize(0.15, "Y");
        histo_dummy -> SetTitleOffset(0.35, "Y");
        histo_dummy -> SetLabelSize(0.15,"X");
        histo_dummy -> SetXTitle("");

        // draw the dummy histogram to set axes
        if ( !same ) histo_dummy -> Draw();

        // draw the ratio
        if (fStyleMap[file_name1].draw_band) {
            graph_ratio_tot -> SetFillColor(fStyleMap[file_name1].band_color);
            graph_ratio_tot -> Draw("2");
        }

        if (fStyleMap[file_name1].draw_line) {

            TH1F * h = (TH1F *) cBinGroup1.histo_dummy -> Clone();
            unsigned nbins = h -> GetNbinsX();

            for (int j=1; j<=nbins; j++) {
                Double_t    x,y;
                // get the central value from the graph and set to histo
                graph_ratio_tot -> GetPoint(j-1, x, y);
                h -> SetBinContent(j, y);

            }
            // otherwise, if the initial histo values were large, this can cause problems in plotting (the histo doesn'n appear for xda)
            h->SetAxisRange(0,2,"Y");

            h -> SetLineColor(fStyleMap[file_name1].line_color);
            h -> SetLineWidth(fStyleMap[file_name1].line_width);
            h -> SetLineStyle(fStyleMap[file_name1].line_style);
            h -> Draw("same");
        }

        if (fStyleMap[file_name1].draw_marker) {
            graph_ratio_stat -> Draw("p");
            graph_ratio_tot -> Draw("zp");
            graph_ratio_tot -> SetMarkerColor(fStyleMap[file_name1].marker_color);
            graph_ratio_tot -> SetMarkerStyle(fStyleMap[file_name1].marker_style);
            graph_ratio_tot -> SetMarkerSize(fStyleMap[file_name1].marker_size);
        }

        // draw the unity line
        Float_t lowx = histo_dummy -> GetBinLowEdge(1);
        Float_t highx = histo_dummy -> GetBinLowEdge(histo_dummy->GetNbinsX()+1);
        TLine *line = new TLine(lowx, 1, highx, 1);
        line->Draw();
        line -> SetLineWidth(2);
        line -> SetLineStyle(2);

        // redraw axes so that no ticks are hidden by anything
        gPad -> RedrawAxis();
    }
}

void    TResultPlotter::PrintCanvases() {

        // create an iterator
        map<TString, TCanvas *>::iterator iter;

        // loop over canvases
        for ( iter=fCanvasMap.begin(); iter != fCanvasMap.end(); iter++ ) {
                (*iter).second -> Print((TString)getenv("PLOTS_PATH")+"/"+(*iter).first+".png");
                (*iter).second -> Print((TString)getenv("PLOTS_PATH")+"/"+(*iter).first+".root");
        }
}

void    TResultPlotter::Divide(unsigned npads_x, unsigned npads_y) {
        fNpads_x = npads_x;
        fNpads_y = npads_y;
}

void    TResultPlotter::SetFileStyleSettings(TString file, bool draw_marker, int marker_color, int marker_style, int marker_size, bool draw_line, int line_color, int line_style, int line_width, bool draw_band, int band_color) {

    //  create a Style structure and save to map
    Style style;

    style.draw_marker = draw_marker;
    style.marker_color = marker_color;
    style.marker_style = marker_style;
    style.marker_size = marker_size;
    style.draw_line = draw_line;
    style.line_color = line_color;
    style.line_style = line_style;
    style.line_width = line_width;
    style.draw_band = draw_band;
    style.band_color = band_color;

    fStyleMap[file] = style;
}
