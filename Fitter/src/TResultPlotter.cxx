//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

// ROOT includes
#include <TString.h>
#include <TCanvas.h>
#include <TROOT.h> //?
#include <TLine.h>

// my includes
#include <TResultPlotter.h>
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

// system includes
#include <iostream>
//#include <map>
using namespace std;

TResultPlotter::TResultPlotter():
fNpads_x(1),
fNpads_y(1),
isCharm(true)
{
}

void    TResultPlotter::AddXMLFile(TString file_name){

        // get data from an XML file
        TCrossSection   cCrossSection(file_name);
        fCrossSectionList.push_back(cCrossSection);

        fBinGroupMap[file_name].clear();

        // get info about the plots
        // get a map from TCrossSection
        map<TString, vector<unsigned> >   BinIDsMap = cCrossSection.getBinIDsMap();
        map<TString, vector<unsigned> >::iterator   iter;        

        // loop over the map, for each group of bins get a vector of bin-IDs belonging to that group
        for ( iter=BinIDsMap.begin() ; iter != BinIDsMap.end(); iter++ ) {

                // create a BinGroup structure for each <bin_group>. that represents one plot
                // (e.g. a differential cross-section)
                BinGroup cBinGroup;
                cBinGroup.binGroupID = (*iter).first;
                
                // get a vector of bin IDs and loop over them to build a BinGroup structure
                vector <unsigned> binIDList = (*iter).second;
                for (int i=0; i<binIDList.size(); i++) {

                        unsigned        id = binIDList[i];
                        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(id);

                        // a temporary hack to distinguish between
                        // single and double differential cross-section
                        // single: take 1st subbin variable as binning in the plot
                        // double: take 2nd variable (as a function of x)
                        // TODO: change to something selectable and controllable
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
                        // to lower edge bin of the current one (not for the very first bin of course,
                        // hence this check for i==0 )
                        if ( (i > 0) && (cBinGroup.binning[i] != bin_low_edge) ) {
                                cout << "ERROR: bins not continuous. Terminating!" << endl;
                                abort();
                        } else if ( i ==0 ) {   // if this is a first bin, just assign a low edge value
                                cBinGroup.binning.push_back(bin_low_edge);
                        }
                        // for every bin: assign upper edge
                        cBinGroup.binning.push_back(bin_up_edge);

                        // assign also values and errors
                        if (isCharm) {
                            if (fPlotScalingFactors) {
                                cBinGroup.y_value.push_back(cBin.get_k_c());
                                cBinGroup.y_error.push_back(cBin.get_k_c_err());
                            } else {
                                cBinGroup.y_value.push_back(cBin.get_sigma_c());
                                cBinGroup.y_error.push_back(cBin.get_sigma_c_err());
                            }
                        } else {
                            if (fPlotScalingFactors) {
                                cBinGroup.y_value.push_back(cBin.get_k_b());
                                cBinGroup.y_error.push_back(cBin.get_k_b_err());
                            } else {
                                cBinGroup.y_value.push_back(cBin.get_sigma_b());
                                cBinGroup.y_error.push_back(cBin.get_sigma_b_err());
                            }
                        }
                }

                // now ready to build a histogram

                // convert the vector to an array so that it can be used in a constructor of TH1F
                const   unsigned array_size = cBinGroup.binning.size();
                const unsigned points_number = array_size - 1;
                Float_t         histo_binning[points_number];
                for (int i = 0; i<array_size; i++) {
                        histo_binning[i] = cBinGroup.binning[i];
                }

                // create a histogram
                cBinGroup.histo = new TH1F (cBinGroup.binGroupID.Data(), "", points_number, histo_binning);
                for (int i = 0; i<points_number; i++) {
                        cBinGroup.histo -> SetBinContent(i+1, cBinGroup.y_value[i]);
                        cBinGroup.histo -> SetBinError(i+1, cBinGroup.y_error[i]);
                }


                // finally, put the BinGroup into the map
                fBinGroupMap[file_name].push_back(cBinGroup);
        }
};

// main drawing routine
void TResultPlotter::DrawPlots(TString file_name, bool recreate, unsigned pad_number, bool same, unsigned color) {

        vector<BinGroup> cBinGroupList = fBinGroupMap[file_name];
        for (int i=0; i<cBinGroupList.size(); i++) {
                
                BinGroup cBinGroup = cBinGroupList[i];
                // ----------- now do some settings for the histogram
                cBinGroup.histo -> SetMarkerStyle(20);
                if (file_name.Contains("Philipp")) { 
                        cBinGroup.histo -> SetMarkerStyle(25);
                        cBinGroup.histo -> SetMarkerColor(kRed);
                }

                if (file_name.Contains("2.7")) { 
                        cBinGroup.histo -> SetMarkerStyle(25);
                        cBinGroup.histo -> SetMarkerColor(6);
                }
                cBinGroup.histo -> SetMarkerColor(color);

                // get axes names depending on the variable;
                // now this is automatic/hardcoded here; TODO: one could add also a public method to this class
                // to be able control this from above
                TString Xtitle;
                TString Ytitle;

                if (cBinGroup.binGroupID == "phijet") {
                  Xtitle = "#phi^{jet}, rad";
                  Ytitle = "d#sigma/d#phi^{jet}, pb/rad";
                  if (isCharm) cBinGroup.histo -> SetAxisRange(1500, 4000, "Y");
                  if (!isCharm) cBinGroup.histo -> SetAxisRange(60, 250, "Y");
                }
                if (cBinGroup.binGroupID == "etajet") {
                  Xtitle = "#eta^{jet}";
                  Ytitle = "d#sigma/d#eta^{jet}, pb";
                  //if (isCharm) cBinGroup.histo -> SetAxisRange(1000, 7000, "Y");
                  if (!isCharm) cBinGroup.histo -> SetAxisRange(50, 450, "Y");
                }
                if (cBinGroup.binGroupID == "etjet") {
                    Xtitle = "E_{T}^{jet}, GeV";
                    Ytitle = "d#sigma/dE_{T}^{jet}, pb/GeV";
                }
                if (cBinGroup.binGroupID == "q2da") {
                    Xtitle = "Q^{2}_{da}, GeV^{2}";
                    Ytitle = "d#sigma/dQ^{2}_{da}, pb/GeV^{2}";
                    //if (isCharm) cBinGroup.histo -> SetAxisRange(0.1, 1100, "Y");
                }
                if (cBinGroup.binGroupID.Contains("x")) {
                    Xtitle = "x_{da}";
                    Ytitle = "d#sigma/dx_{da}, pb";
                }
                if (cBinGroup.binGroupID.Contains("xda_bin3")) {
                    if (!isCharm) cBinGroup.histo -> SetAxisRange(50, 42000, "Y");
                }




                // set thos axes names
                cBinGroup.histo -> SetXTitle(Xtitle);
                cBinGroup.histo -> SetYTitle(Ytitle);
                
                // settings for labels, TODO: add sth controllable from above
                cBinGroup.histo -> SetTitleSize(0.06, "Y");;
                cBinGroup.histo -> SetTitleOffset(1.25, "Y");
                cBinGroup.histo -> SetTitleSize(0.07, "X");;
                cBinGroup.histo -> SetTitleOffset(0.85, "X");

                // remove statistics box
                cBinGroup.histo -> SetStats(0);

                // now draw the hidtogram
                // first, get a pointer to a relevant TCanvas (create it if user wishes so, or get from the map)
                // TODO: add some automatic check, so that "recreate" switch is eliminated
                TCanvas   * cCanvas;
                if (recreate) {
                        cCanvas = new TCanvas ("CrossSection."+cBinGroup.binGroupID + file_name, "", 0, 0, 1050, 860);
                        cCanvas -> SetFillColor(0);
                        cCanvas -> Divide(fNpads_x, fNpads_y);

                        fCanvasMap[cBinGroup.binGroupID] = cCanvas;
                } else {
                        cCanvas = fCanvasMap[cBinGroup.binGroupID];
                }

                // select respective subpad
                cCanvas -> cd(pad_number);
                // apply some options as given by DrawOption structure for each subpad
                if (fMap_padID_Option[pad_number].isLog) gPad->SetLogy();

                // settings specific to the plots, not to the subpads
                if ( cBinGroup.binGroupID.Contains("q2") || cBinGroup.binGroupID.Contains("x") ) gPad -> SetLogx();
                gPad->SetLeftMargin(0.15);
                gPad->SetBottomMargin(0.13);

                // draw the histogram
                if ( !same ) {
                        cBinGroup.histo -> Draw("E");
                } else {
                        cBinGroup.histo -> Draw("esame");
                }
        }
}

// main drawing routine - overloaded version - to plot ratio of two sets of data (not possible
// with the procedure above. TODO: revisit, think how both can be unified without any code duplication)
void TResultPlotter::DrawPlots(TString file_name1, TString file_name2, bool recreate, unsigned pad_number, bool same) {

        vector<BinGroup> cBinGroupList1 = fBinGroupMap[file_name1];
        vector<BinGroup> cBinGroupList2 = fBinGroupMap[file_name2];

        // sanity check: sizes of both arrays should be the same
        if ( cBinGroupList1.size() != cBinGroupList2.size() ) {
            cout << "ERROR: incompatible datasets selected: number of <bin_group> elements is different" << endl;
            cout << "Terminating, sorry." << endl;
            abort();
        }

        for (int i=0; i<cBinGroupList1.size(); i++) {
                
                BinGroup cBinGroup = cBinGroupList1[i];
                BinGroup cBinGroup2 = cBinGroupList2[i];

                //  now do some settings for the histogram
                cBinGroup.histo -> SetMarkerStyle(20);

                // get axes names depending on the variable;
                // now this is automatic/hardcoded here; TODO: one could add also a public method to this class
                // to be able control this from above
                TString Xtitle;
                TString Ytitle;

                if (cBinGroup.binGroupID == "phijet") {
                  Xtitle = "#phi^{jet}, rad";
                  Ytitle = "d#sigma/d#phi^{jet}, pb/rad";
                }
                if (cBinGroup.binGroupID == "etajet") {
                  Xtitle = "#eta^{jet}";
                  Ytitle = "d#sigma/d#eta^{jet}, pb";
                }
                if (cBinGroup.binGroupID == "etjet") {
                    Xtitle = "E_{T}^{jet}, GeV";
                    Ytitle = "d#sigma/dE_{T}^{jet}, pb/GeV";
                }
                if (cBinGroup.binGroupID == "q2da") {
                    Xtitle = "Q^{2}_{da}, GeV^{2}";
                    Ytitle = "d#sigma/dQ^{2}_{da}, pb/GeV^{2}";
                }
                if (cBinGroup.binGroupID.Contains("x")) {
                    Xtitle = "x_{da}";
                    Ytitle = "d#sigma/dx_{da}, pb";
                }

                // set thos axes names
                cBinGroup.histo -> SetXTitle(Xtitle);
                cBinGroup.histo -> SetYTitle(Ytitle);
                
                // settings for labels, TODO: add sth controllable from above
                cBinGroup.histo -> SetTitleSize(0.06, "Y");;
                cBinGroup.histo -> SetTitleOffset(1.25, "Y");
                cBinGroup.histo -> SetTitleSize(0.07, "X");;
                cBinGroup.histo -> SetTitleOffset(0.85, "X");

                // remove statistics box
                cBinGroup.histo -> SetStats(0);

                // create another histogram - clone from the 1st one
                TH1F * histo_ratio = (TH1F*)cBinGroup.histo -> Clone();

                // divide it by the 2nd one
                histo_ratio -> Divide(cBinGroup2.histo);

                // further settings
                histo_ratio -> SetMarkerStyle(26);
                histo_ratio -> SetMarkerSize(1);
                histo_ratio -> SetMarkerColor(kBlue);

                // now draw the histogram
                // first, get a pointer to a relevant TCanvas (create it if user wishes so, or get from the map)
                // TODO: add some automatic check, so that "recreate" switch is eliminated
                TCanvas   * cCanvas;
                if (recreate) {
                        cCanvas = new TCanvas ("CrossSection."+cBinGroup.binGroupID + file_name1, "", 0, 0, 1050, 860);
                        cCanvas -> SetFillColor(0);
                        cCanvas -> Divide(fNpads_x, fNpads_y);

                        fCanvasMap[cBinGroup.binGroupID] = cCanvas;
                } else {
                        cCanvas = fCanvasMap[cBinGroup.binGroupID];
                }

                // select respective subpad
                cCanvas -> cd(pad_number);
                // apply some options as given by DrawOption structure for each subpad
                if (fMap_padID_Option[pad_number].isLog) gPad->SetLogy();

                // settings specific to the plots, not to the subpads
                if ( cBinGroup.binGroupID.Contains("q2") || cBinGroup.binGroupID.Contains("x") ) gPad -> SetLogx();
                gPad->SetLeftMargin(0.15);
                gPad->SetBottomMargin(0.13);

                histo_ratio -> SetAxisRange(0.3, 1.7, "Y");

                // draw the histogram
                if ( !same ) {
                        histo_ratio -> Draw("E");
                        // TODO: make the line below readable!!
                        TLine *line = new TLine(cBinGroup.binning[0], 1, cBinGroup.binning[cBinGroup.binning.size()-1], 1);
                        line->Draw("same");
                        line -> SetLineWidth(2);
                        line -> SetLineStyle(2);
                } else {
                        histo_ratio -> Draw("esame");
                }
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
        for (unsigned i = 1; i <= fNpads_x * fNpads_x; i++ ) {
            fMap_padID_Option[i].isLog = false;
            fMap_padID_Option[i].padID = i; // this is not needed in principle
        }
}

void    TResultPlotter::SetLogY(unsigned pad_id) {
        fMap_padID_Option[pad_id].isLog = true;
}
