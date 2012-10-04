//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav,                            //
//  DESY,                                       //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

// system headers
#include <iostream>
#include <getopt.h>
using namespace std;

// ROOT headers
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>
#include <TPad.h>
#include <TF1.h>
#include <TStyle.h>

// my headers
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"no_variations", no_argument, 0, 1},
        {"fit_function", required_argument, 0, 2},
        {"eta_reweighting", no_argument, 0, 3},
        {"et_reweighting", no_argument, 0, 4},
    };

    // results of the command line option processing will be stored here
    TString version = "";
    bool no_variations = false;
    TString fit_function = "";
    bool eta_reweighting = false;
    bool et_reweighting = false;

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "v:h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                no_variations = true;
                break;
            case 2:
                fit_function = optarg;
                break;
            case 3:
                eta_reweighting = true;
                break;
            case 4:
                et_reweighting = true;
                break;
            case 'v':
                version = optarg;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "\treweighting -v <histogram version> [-h]\n\n";
                cout << "\t--no_variations\tDon't draw systematic variations\n";
                cout << "\t--fit_function\tSelect a fit function\n";
                cout << "\t--eta_reweighting\tFor eta reweighting\n";
                cout << "\t--et_reweighting\tFor et reweighting\n";
                cout << "\t-h\tPrint this help and exit\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    TString xml_filename = "results.full.forCHARM" + version +".0405e06e07p.v02.true05e06e0607p.xml";
    TCrossSection cCrossSection(xml_filename);

    // arrays to store scaling factors and uncertainties
    const unsigned MAXBINS=50;
    Float_t     x[MAXBINS];
    Float_t     y[MAXBINS];
    Float_t     y_err[MAXBINS];
    Float_t     x_err[MAXBINS];

    unsigned nbins = 0;

    for (unsigned i=2; i<13; i++) {
        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(i);
        y[nbins] = cBin.get_k_c();
        y_err[nbins] = cBin.get_k_c_err();
        x[nbins] = (cBin.getSubBinLowEdge(0) + cBin.getSubBinUpEdge(0))/2;
        x_err[nbins] = 0;
        nbins++;
    }

    // cosmetics
    gStyle -> SetPadBottomMargin(0.16);
    gStyle -> SetPadRightMargin(0.05);
    gStyle -> SetPadTopMargin(0.05);
    gStyle -> SetPadLeftMargin(0.15);
    gStyle -> SetOptTitle(0);

    TCanvas c("c", "", 1200, 1200);
    c.SetFillColor(0);

    TGraphErrors * g = new TGraphErrors(nbins, x,y,x_err,y_err);
    g -> Draw("ap");
    g -> SetMarkerStyle(20);

    // cosmetics
    TH1F * histo = g -> GetHistogram();
    histo -> SetAxisRange(0.9, 2.2, "Y");
    histo -> SetXTitle("#eta(jet)");
    histo -> SetYTitle("scaling factor = #sigma(data) / #sigma(MC)");
    histo -> SetTitleOffset(1.2, "X");
    histo -> SetTitleOffset(1.3, "Y");
    histo -> SetTitleSize(0.05, "X");
    histo -> SetTitleSize(0.05, "Y");
    histo -> SetLabelSize(0.05, "X");
    histo -> SetLabelSize(0.05, "Y");

    // perform a fit
    g -> Fit(fit_function);

    // create functions to show extreme systematic variations
    TF1 * fcn_up = new TF1 ("fcn_up", "pol2(0)", -1.6, 2.2);
    fcn_up -> SetParameters(1.16371, 0.135495, 0.15);
    fcn_up -> SetLineColor(kRed);
    fcn_up -> SetLineStyle(7);

    TF1 * fcn_down = new TF1 ("fcn_down", "pol2(0)", -1.6, 2.2);
    fcn_down -> SetParameters(1.16371, 0.135495, 0.05);
    fcn_down -> SetLineColor(kRed);
    fcn_down -> SetLineStyle(10);

    // draw
    if (!no_variations) {
        fcn_up -> Draw("same");
        fcn_down -> Draw("same");
    }

    // print
    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c.Print(PLOTS_PATH + "/" + "eta_reweighting_" + version + ".eps");

    return 0;
}
