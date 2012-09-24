int hadr_int_rate_analysis() {

    TFile * f = new TFile ("/data/zenith226a/libov/data/histo/analysis.mc06ev02eccbar.rg30.q2g1.5.bgf.full.forCHARM2.67.5.root", "read");
    TProfile * phi = (TProfile*) f -> Get("f_hadr_prob_phi");
    TProfile * theta = (TProfile*) f -> Get("f_hadr_prob_theta");

    gStyle -> SetErrorX(0);
    gStyle -> SetPadLeftMargin(0.175);
    gStyle -> SetPadRightMargin(0.04);
    gStyle -> SetPadBottomMargin(0.15);

    gStyle -> SetOptStat(1100);
    Float_t right_margin = gStyle->GetPadRightMargin();
    Float_t top_margin = gStyle->GetPadTopMargin();
    gStyle -> SetStatX( 1 - right_margin );
    gStyle -> SetStatY( 1 - top_margin );

    TCanvas * c1 = new TCanvas ("c1", "", 1200, 1200);
    phi -> SetMarkerStyle(20);
    phi -> SetMarkerSize(1.5);
    phi -> SetAxisRange(0, 0.08, "Y");
    phi -> SetAxisRange(0, 360, "X");
    phi -> SetXTitle("#phi (degrees)");
    phi -> SetYTitle("p_{hadr, MC}");
    phi -> SetTitleOffset(1.4, "Y");
    phi -> SetTitleSize(0.06, "Y");
    phi -> SetLabelSize(0.05, "Y");
    phi -> SetTitleOffset(1.2, "X");
    phi -> SetTitleSize(0.06, "X");
    phi -> SetLabelSize(0.05, "X");
    phi -> Draw();

    TCanvas * c2 = new TCanvas ("c2", "", 1200, 1200);
    theta -> SetMarkerStyle(20);
    theta -> SetMarkerSize(1.5);
    theta -> SetAxisRange(0, 0.08, "Y");
    theta -> SetAxisRange(20, 160, "X");
    theta -> SetXTitle("#theta (degrees)");
    theta -> SetYTitle("p_{hadr, MC}");
    theta -> SetTitleOffset(1.4, "Y");
    theta -> SetTitleSize(0.06, "Y");
    theta -> SetLabelSize(0.05, "Y");
    theta -> SetTitleOffset(1.2, "X");
    theta -> SetTitleSize(0.06, "X");
    theta -> SetLabelSize(0.05, "X");
    theta -> Draw();

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c1 -> Print (PLOTS_PATH + "/hadr_int_rate_phi.eps");

    gStyle -> SetStatX( 1 - right_margin - 0.1 );
    c2 -> Print (PLOTS_PATH + "/hadr_int_rate_theta.eps");

    return 0;
}
