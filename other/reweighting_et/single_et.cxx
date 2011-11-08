Float_t     ET_REF;
Float_t     K_CONST;

void single_et() {

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    TString PATH_SCALING_FACTORS = PLOTS_PATH + "/27_19October2011/06a_2.29.16_scaling_factors_charm";

    TFile * file = new TFile (PATH_SCALING_FACTORS+"/etjet.root", "read");
    TCanvas * canv = (TCanvas*) file -> Get("CrossSection.etjetresults.ETQ2.v22.29.16.0405e06e07p.v02.true05e06e0607p.xml");
    TPad * subpad = (TPad*) canv -> GetListOfPrimitives() -> At (0);
    TH1F * histo = (TH1F*) subpad -> GetPrimitive("etjet");
    
    TF1 * f = new TF1 ("f", "[0] + [1] * sqrt(x)", 0, 35);
    cout << "\n ------------  FITTING THE ET DISTRIBUTION  ------------" << endl;
    histo -> Fit("f");
    cout << " ------------             DONE              ------------\n" << endl;

    Float_t p0_central = f -> GetParameter(0);
    Float_t p1_central = f -> GetParameter(1);
    // choose 8 GeV as a point of intersection of all the curves
    ET_REF = 8;
    K_CONST = p0_central + p1_central * sqrt(ET_REF);
    // now all the coefficients are subject to the constraint:
    // p0 = k_const - p1 * sqrt(et_ref)
    // p0           7.53431e-01   1.44609e-01   1.67237e-05   3.86700e-09
    // p1           1.89124e-01   4.75481e-02   5.49882e-06   1.09532e-08

    TCanvas * c = new TCanvas ();
    c -> cd();
    subpad -> Draw();
    subpad -> cd();

    cout << "\n ------------       FUNCTION PARAMETERS      ------------" << endl;
    draw_function(0.0135, 4, 2, 1);
    draw_function(0.07, 2, 7, 2);   // DOWN VARIATION
    draw_function(0.1265, 4, 2, 1);
    draw_function(0.2315, 4, 2, 1);
    draw_function(0.28, 2, 7, 2);   // UP VARIATION
    draw_function(0.3285, 4, 2, 1);
    cout << " --------------------------------------------------------" << endl;

}

void draw_function (Float_t p1, Int_t line_color, Int_t line_style, Int_t line_width) {
    TF1 * f = new TF1 ("f", "[0] + [1] * sqrt(x)", 0, 35);
    f -> SetParameters(K_CONST - p1 * sqrt(ET_REF), p1);
    f -> SetLineColor(line_color);
    f -> SetLineStyle(line_style);
    f -> SetLineWidth(line_width);
    f -> Draw("same");
    cout << f -> GetParameter(0) << ", " << f -> GetParameter(1) << endl;
}
