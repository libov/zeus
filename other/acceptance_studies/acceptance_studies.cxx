// note: there is some duplication of code, taken from other files under quick_plot
// TODO: create some standard plotting tools!!!

const TString FILENAME_RESOLVED_CHARM = "analysis.mc05ev02ef15643.ccbar.rg30.q2g4.resc.full.forCHARM2.29.3.root";
const TString FILENAME_DIRECT_CHARM = "analysis.mc05v02e.rgap3.nc.c.q2g4.full.forCHARM2.29.3.root";

const TString FILENAME_DIRECT_BEAUTY = "analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARM2.29.3.root";
const TString FILENAME_RESOLVED_BEAUTY = "analysis.mc05ev02ef15643.bbbar.rg30.q2g1.resc.full.forCHARM2.29.3.root";

//const TString FILENAME = FILENAME_RESOLVED_CHARM;
//const TString FILENAME = FILENAME_DIRECT_CHARM;
const TString FILENAME = FILENAME_DIRECT_BEAUTY;

// helping function to get a histogram
TH1F * getHisto(TString filename, TString relative_path_histo) {

    TString     HISTO_PATH = getenv("HISTO_PATH");
    TFile * file = new TFile(HISTO_PATH+"/"+filename, "read");
    return (TH1F*)file -> Get(relative_path_histo);
}

Float_t acceptance(TString bin) {

    Float_t n_vertices = 0;
    //n_vertices += getHisto(FILENAME, bin+"/significance_massbin1_mirrored") -> Integral(5, 20);
    //n_vertices += getHisto(FILENAME, bin+"/significance_massbin2_mirrored") -> Integral(5, 20);
    n_vertices += getHisto(FILENAME, bin+"/significance_massbin3_mirrored") -> Integral(5, 20);
    
    Float_t     njets = getHisto(FILENAME, bin+"/truejets") -> Integral();

    Float_t     acceptance = n_vertices / njets;

    cout << bin << ": " << acceptance << endl;
    return acceptance;
}

void   acceptance_studies() {

    // so that titles are visible - the opposite is done in the rootlogon script
    gStyle -> SetOptTitle(1);

    // ************ eta ****************
    Float_t x[11] = {-1.6, -1.1, -0.8, -0.5, -0.2, 0.1, 0.4, 0.7, 1.0, 1.3, 1.6};
    Float_t y[11];

    y[0] = acceptance("bin2");
    y[1] = acceptance("bin3");
    y[2] = acceptance("bin4");
    y[3] = acceptance("bin5");
    y[4] = acceptance("bin6");
    y[5] = acceptance("bin7");
    y[6] = acceptance("bin8");
    y[7] = acceptance("bin9");
    y[8] = acceptance("bin10");
    y[9] = acceptance("bin11");
    y[10] = acceptance("bin12");

    TGraph  * acceptance_eta = new TGraph(11, x, y);

    acceptance_eta -> Draw("ap");
    acceptance_eta -> SetMarkerStyle(20);
    acceptance_eta -> SetTitle("acceptance as a fucntion of #eta, Resolved Charm MC");

    // ************ et ****************
    Float_t x_et[7] = {4.2, 8.0, 11.0, 14.0, 17.0, 20.0, 25.0};
    Float_t y_et[7];

    y_et[0] = acceptance("bin14");
    y_et[1] = acceptance("bin15");
    y_et[2] = acceptance("bin16");
    y_et[3] = acceptance("bin17");
    y_et[4] = acceptance("bin18");
    y_et[5] = acceptance("bin19");
    y_et[6] = acceptance("bin20");

    TGraph  * acceptance_et = new TGraph(7, x_et, y_et);

   // acceptance_et -> Draw("ap");
    acceptance_et -> SetMarkerStyle(20);
    //acceptance_et -> SetTitle("acceptance as a fucntion of E_{T}, direct Charm MC");

}
