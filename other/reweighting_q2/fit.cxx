void fit() {

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    TString PATH_SCALING_FACTORS = PLOTS_PATH + "/36_07November2011/01_3.31.4/02_scaling_beauty";

    TFile * file = new TFile (PATH_SCALING_FACTORS+"/q2da.root", "read");
    TCanvas * canv = (TCanvas*) file -> Get("CrossSection.q2daresults.full.forCHARM2.31.4.0405e06e07p.v02.true05e06e0607p.xml");
    TPad * subpad = (TPad*) canv -> GetListOfPrimitives() -> At (0);
    TH1F * histo = (TH1F*) subpad -> GetPrimitive("q2da");
    
    TF1 * f = new TF1 ("f", "[0] + [1] * log(x)", 5, 1000);
    cout << "\n ------------  FITTING THE Q2 DISTRIBUTION  ------------" << endl;
    histo -> Fit("f");
    cout << " ------------             DONE              ------------\n" << endl;

    TCanvas * c = new TCanvas ();
    c -> cd();
    subpad -> Draw();
    subpad -> cd();

}
