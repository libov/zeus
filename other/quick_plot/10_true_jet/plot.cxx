#include <TH1F.h>
#include <TFile.h>
#include <TLegend.h>
#include <TPad.h>
#include <TCanvas.h>

#include <iostream>

// const TString FILENAME_DIRECT_CHARM = "analysis.mc05v02e.rgap3.nc.c.q2g4.full.forCHARM2.29.1.root";
// const TString FILENAME_RESOLVED_CHARM = "analysis.mc05ev02ef15643.ccbar.rg30.q2g4.resc.full.forCHARM2.29.1.root";
// const TString FILENAME_DIRECT_BEAUTY = "analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARM2.29.1.root";
// const TString FILENAME_RESOLVED_BEAUTY = "analysis.mc05ev02ef15643.bbbar.rg30.q2g1.resc.full.forCHARM2.29.1.root";

// const TString FILENAME_DIRECT_CHARM = "analysis.mc05v02e.rgap3.nc.c.q2g4.inclusivex_gamma_test.root";
// const TString FILENAME_RESOLVED_CHARM = "analysis.mc05ev02ef15643.ccbar.rg30.q2g4.resc.inclusivex_gamma_test.root";
// const TString FILENAME_DIRECT_BEAUTY = "analysis.mc05v02e.rgap3.nc.b.q2g1.e..inclusivex_gamma_test.root";
// const TString FILENAME_RESOLVED_BEAUTY = "analysis.mc05ev02ef15643.bbbar.rg30.q2g1.resc.inclusivex_gamma_test.root";

// const TString FILENAME_DIRECT_CHARM = "analysis.mc05v02e.rgap3.nc.c.q2g4.full.forCHARMx_gamma_test.root";
// const TString FILENAME_RESOLVED_CHARM = "analysis.mc05ev02ef15643.ccbar.rg30.q2g4.resc.full.forCHARMx_gamma_test.root";
// const TString FILENAME_DIRECT_BEAUTY = "analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARMx_gamma_test.root";
// const TString FILENAME_RESOLVED_BEAUTY = "analysis.mc05ev02ef15643.bbbar.rg30.q2g1.resc.full.forCHARMx_gamma_test.root";

const TString FILENAME_RESOLVED_CHARM = "analysis.mc05ev02ef15643.ccbar.rg30.q2g4.resc.full.forCHARM2.29.3.root";
const TString FILENAME_DIRECT_CHARM = "analysis.mc05v02e.rgap3.nc.c.q2g4.full.forCHARM2.29.3.root";

//bool normalize = false;
bool normalize = true;

// helping
TH1F * getHisto(TString filename, TString relative_path_histo) {

    TString     HISTO_PATH = getenv("HISTO_PATH");
    TFile * file = new TFile(HISTO_PATH+"/"+filename, "read");
    return (TH1F*)file -> Get(relative_path_histo);
}

void draw(TString filename1, TString filename2, TString relative_path_histo) {

    TCanvas * c = new TCanvas();
    c -> cd();

    // histogram 1
    TH1F * h1 = getHisto(filename1, relative_path_histo);
    h1 -> Draw("hist");
    h1 -> SetLineColor(kBlue);

    // histogram 2
    TH1F * h2 = getHisto(filename2, relative_path_histo);
    if (normalize) h2 -> Scale (h1 -> Integral() / h2 -> Integral());
    h2 -> Draw("same hist");

    // legend
    TLegend * leg = new TLegend (0.5,0.7,0.95,0.9);
    leg -> AddEntry(h1, "BGF", "l");
    leg -> AddEntry(h2, "#gamma exc", "l");
    leg -> Draw("same");

    gPad -> SetTickx(1);
    gPad -> SetTicky(1);
    
    cout << "Ratio of Histogram integrals (2nd to 1st): " << h2 -> Integral() / h1 -> Integral() << endl;
    

}

// main
int plot() {

//     // jets, charm
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/truejeteta");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/truejetet");
//     // partons, charm
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/ccbar_eta");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/ccbar_et");

//     // jets, beauty
//     draw(FILENAME_DIRECT_BEAUTY, FILENAME_RESOLVED_BEAUTY, "bin1/truejeteta");
//     draw(FILENAME_DIRECT_BEAUTY, FILENAME_RESOLVED_BEAUTY, "bin1/truejetet");
//     // partons, beauty
//     draw(FILENAME_DIRECT_BEAUTY, FILENAME_RESOLVED_BEAUTY, "bin1/bbbar_eta");
//     draw(FILENAME_DIRECT_BEAUTY, FILENAME_RESOLVED_BEAUTY, "bin1/bbbar_et");

    // x_gamma, beauty
//      draw(FILENAME_DIRECT_BEAUTY, FILENAME_RESOLVED_BEAUTY, "bin19/x_gamma_1");
//      draw(FILENAME_DIRECT_BEAUTY, FILENAME_RESOLVED_BEAUTY, "bin19/x_gamma_1_true");

    // x_gamma, charm
/*    draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_true_partons");
    draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_true_hadrons");*/
// 
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_lab_jets");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_lab_jets_tagged");

   //draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_breit_jets");
     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/truejetet");
        //draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/kt_etjet_b_charm_diff");
      //draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_breit_jets_charm_diff");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_breit_jets_beauty_diff");

// 
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/q2_reco_reso");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/q2da_reso");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/q2el_reso");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/q2jb_reso");
// 
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/Wda_reso");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/W_reso");

//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_1");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_2");
//     draw(FILENAME_DIRECT_CHARM, FILENAME_RESOLVED_CHARM, "bin1/x_gamma_3");



    return 0;
}

