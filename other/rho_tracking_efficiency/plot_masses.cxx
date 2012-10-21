enum type_t {kData, kMC};
enum class_t {kClassI, kClassII};

int plot_mass(type_t type, class_t cl, TString id) {

    // for merger
    TString var_type;
    // for the text box
    TString var_type_txt;
    if ( type  == kData ) {
        var_type = "data";
        var_type_txt = "data";
    } else if ( type  == kMC ) {
        var_type = "rho";
        var_type_txt = "MC";
    }

    // for merger
    TString variable;
    // for text
    TString cl_txt;
    if ( cl == kClassI) {
        variable = "rho_mass_classI";
        cl_txt = "class I";
    } else if ( cl == kClassII) {
        variable = "rho_mass_classII";
        cl_txt = "class II";
    }

    gStyle -> SetErrorX(0);
    gStyle -> SetPadLeftMargin(0.15);
    gStyle -> SetPadBottomMargin(0.1);
    gStyle -> SetStatColor(0);
    gStyle -> SetOptStat(1110); // mean, rms, entries but no histogram title
    Float_t right_margin = gStyle->GetPadRightMargin();
    Float_t top_margin = gStyle->GetPadTopMargin();
    gStyle -> SetStatX( 1 - right_margin );
    gStyle -> SetStatY( 1 - top_margin );

    TFile * file = new TFile ("/data/zenith226a/libov/data/histo/merged.inclusiverho.v136.0405e06e07p.root", "read");
    TH1F * h = (TH1F*) file -> Get("bin1/"+variable+"/"+var_type);

    TCanvas * c = new TCanvas ("c1", "Exclusive rho production", 600, 600);

    h -> Draw();
    h -> SetMarkerSize(1.2);
    h -> SetMarkerStyle(20);
    h -> SetXTitle("M_{#pi^{+}#pi^{-}} (GeV)");
    h -> SetYTitle("Entries");
    h -> SetTitleSize(0.05, "X");
    h -> SetTitleSize(0.05, "Y");
    h -> SetTitleOffset(0.95, "X");
    h -> SetTitleOffset(1.55, "Y");
    h -> SetLabelSize(0.05, "X");
    h -> SetLabelSize(0.05, "Y");

    if ( ( type  == kMC ) && ( cl == kClassII ) ) h -> SetAxisRange(0, 310, "Y");

    TLatex t;
    t.SetTextSize(0.06);
    t.SetNDC();

    TString text = cl_txt + ", " + var_type_txt;

    t.DrawLatex(0.6, 0.6, text);

    t.DrawLatex(0.2, 0.85, id);

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c -> Print(PLOTS_PATH + "/" + variable + "_" + var_type_txt+".eps");

    return 0;
}

plot_masses() {
    plot_mass(kData, kClassI, "(a)");
    plot_mass(kData, kClassII, "(b)");
    plot_mass(kMC, kClassI, "(c)");
    plot_mass(kMC, kClassII, "(d)");
}