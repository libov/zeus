//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//  March 2011                                  //
//////////////////////////////////////////////////

// system includes
#include <iostream>
using namespace std;

// ROOT includes
#include <TGraphErrors.h>
#include <TROOT.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TPaveText.h>

// my includes
#include <TCrossSection.h>
#include <TCrossSectionBin.h>



//TString CN_version_short = "v02";
TString CN_version_short = "v04";
bool        with0304p = true;
bool        et4_2 = true;
unsigned    bin_to_study = 1;
bool        beauty_binning = false;

// global counter
int counter = 0;

// prints results for particular histograms version (e.g. 2.1)
void    print_results_version(TString histo_version);
// prints results for particular year (remark) within a version
void    print_results_version_year(TString year, TString histo_version, float * results);

// main function
int main() {

    print_results_version("2.20.0");
    print_results_version("2.20.1");
    print_results_version("2.20.2");
    print_results_version("2.20.3");
    print_results_version("2.20.4");

//     print_results_version("2.21.1");
//     print_results_version("2.21.2");
//     print_results_version("2.21.3");
//     print_results_version("2.21.4");
//     print_results_version("2.21.5");
//     print_results_version("2.21.6");
//     print_results_version("2.21.7");
//     print_results_version("2.21.8");
//     print_results_version("2.21.9");
//     print_results_version("2.21.10");
//     print_results_version("2.21.11");
//     print_results_version("2.21.12");
//     print_results_version("2.21.13");
//     print_results_version("2.21.14");
//     print_results_version("2.21.15");
//     print_results_version("2.21.16");
//     print_results_version("2.21.17");
//     print_results_version("2.21.18");
//     print_results_version("2.21.19");
//     print_results_version("2.21.20");
//     print_results_version("2.21.21");
//     print_results_version("2.21.22");
//     print_results_version("2.21.23");
//     print_results_version("2.21.24");
//     print_results_version("2.21.25");
//     print_results_version("2.21.26");
//     print_results_version("2.21.27");
//     print_results_version("2.21.28");   
//     print_results_version("2.21.29");

    return 0;
}

void    print_results_version(TString histo_version) {

    // these variables will hold k-factors for different subperiods
    float   x[3], x_err[3], k_c[3], k_c_err[3], k_b[3], k_b_err[3];
    // this is a dummy x-vector and vector of errors
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;
    x_err[0] = 0;
    x_err[1] = 0;
    x_err[2] = 0;


    // create a structure to hold k_b, k_c and their errors
    float * results = new float[4];
    
    cout << "\n//----- " << histo_version << " -------" << endl;
    /*print_results_version_year("05e", histo_version, results);
    k_c[0] = results[0];
    k_c_err[0] = results[1];
    k_b[0] = results[2];
    k_b_err[0] = results[3];
    print_results_version_year("06e", histo_version, results);
    k_c[1] = results[0];
    k_c_err[1] = results[1];
    k_b[1] = results[2];
    k_b_err[1] = results[3];
    print_results_version_year("07p", histo_version, results);
    k_c[2] = results[0];
    k_c_err[2] = results[1];
    k_b[2] = results[2];
    k_b_err[2] = results[3];*/


    if (with0304p) {
        print_results_version_year("0405e06e07p", histo_version, results);
    } else {
        print_results_version_year("05e06e07p", histo_version, results);
    }

    // plot the results for the histogram version
    /*TGraphErrors * graph_charm = new TGraphErrors(3, x, k_c, x_err, k_c_err);
    TGraphErrors * graph_beauty = new TGraphErrors(3, x, k_b, x_err, k_b_err);

    graph_charm -> SetMarkerStyle(22);
    graph_beauty -> SetMarkerStyle(23);

    graph_charm -> SetMarkerColor(kGreen);
    graph_beauty -> SetMarkerColor(kBlue);

    graph_charm -> Draw("ap");
    graph_beauty -> Draw("samep");

    graph_charm -> Fit("pol0", "", 0, 3);
    graph_beauty -> Fit("pol0", "",  0, 3);

    TPaveText pave_text(0, 0, 0.2, 0.2, "NDC");
    pave_text.AddText(histo_version.Data());
    pave_text.Draw();

    graph_charm -> GetYaxis() -> SetRangeUser(1, 2);
    gROOT -> GetListOfCanvases() -> Print(histo_version+".png");*/

    // clean up
    delete[] results;
}

void    print_results_version_year(TString year, TString histo_version, float * results) {

    /*if ( histo_version.Contains("2.2") || histo_version.Contains("2.3") || histo_version.Contains("2.5") || histo_version.Contains("2.7") || histo_version.Contains("2.8") || histo_version.Contains("2.9.0") || histo_version.Contains("2.9.1") || histo_version.Contains("2.11") ) {
        CN_version_short = "v04";
    } else if ( histo_version.Contains("2.1") || histo_version.Contains("2.4") || histo_version.Contains("2.6") || histo_version.Contains("2.9.2") || histo_version.Contains("2.9.3")) {
        CN_version_short = "v02";
    } else {
        cout << " Unknown histogram version: " << histo_version << endl;
        cout << " At the moment 2.1, 2.2, 2.3, 2,4, 2.5, 2.6, 2.7 are supported" << endl;
        cout << " Choose the correct one or implement in "<< __FILE__ << endl;
        cout << " Terminating, sorry" << endl;
        exit(-1);
    }*/

    TString filename;

//     filename = "results.inclusive"+histo_version+"."+year+"."+CN_version_short+".true05e06e0607p.xml";

        if (beauty_binning) {
            filename = "results.full"+histo_version+"."+year+"."+CN_version_short+".true05e06e0607p.xml";
        } else {
            if (et4_2) {
                filename = "results.full.forCHARM"+histo_version+"."+year+"."+CN_version_short+".true05e06e0607p.xml";
            } else {
                filename = "results.full.forCHARM.ET5"+histo_version+"."+year+"."+CN_version_short+".true05e06e0607p.xml";
            }
        }


    TCrossSection   cCrossSection(filename);

    /*cout << "k_c["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_c() << "; ";
    cout << "k_c_err["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_c_err() << ";" << endl;;

    cout << "k_b["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_b() << "; ";
    cout << "k_b_err["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_b_err() << ";" << endl;;

    cout << "k_uds["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_uds() << "; ";
    cout << "k_uds_err["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_uds_err() << ";" << endl;;


    cout << "sigma_c["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_sigma_c() << "; ";
    cout << "sigma_c_err["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_sigma_c_err() << ";" << endl;

    cout << "sigma_b["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_sigma_b() << "; ";
    cout << "sigma_b_err["<<counter<<"]= " << cCrossSection.getCrossSectionBin(bin_to_study).get_sigma_b_err() << ";" << endl;*/

    cout << "k_c= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_c() << ";\n";
    cout << "k_b= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_b() << ";\n";
    cout << "k_uds= " << cCrossSection.getCrossSectionBin(bin_to_study).get_k_uds() << ";\n ";

    counter++;
    
    // store k-factors and errors to an array
    results[0] = cCrossSection.getCrossSectionBin(bin_to_study).get_k_c();
    results[1] = cCrossSection.getCrossSectionBin(bin_to_study).get_k_c_err();
    results[2] = cCrossSection.getCrossSectionBin(bin_to_study).get_k_b();
    results[3] = cCrossSection.getCrossSectionBin(bin_to_study).get_k_b_err();
}
