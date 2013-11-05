void marker(Double_t, Double_t, unsigned);

void arrow(Double_t, Double_t, Double_t, Double_t);

void draw_y_ranges();

void line(Double_t x1, Double_t y1, Double_t x2, Double_t y2, int color=1, int width=2) {

    TLine * l = new TLine (TMath::Log10(x1), TMath::Log10(y1), TMath::Log10(x2), TMath::Log10(y2));
    l -> SetLineColor(color);
    l -> SetLineWidth(width);
    l -> Draw();
}

int q2_x_plane_beauty (TString type="inclusive", TString sample = "data", unsigned mode = 4) {

    TCanvas *c = new TCanvas ("c", "", 1600, 1200);

    // style settings
    gStyle -> SetOptStat(0);
    gStyle -> SetMarkerSize(0.8);
    gStyle -> SetLineStyle(7);

    TString HISTO_PATH = getenv("HISTO_PATH");
    TString filename = HISTO_PATH+"/merged.full.forCHARM2.109.1.0405e06e07p.root";
    cout << "Opening " << filename << endl;
    TFile * f = new TFile (filename);

    // get the histo
    TH2F * q2_x = 0;
    if (type == "charm") {
        q2_x = (TH2F*) f -> Get("bin1/q2_x_charm/"+sample);
    } else if (type == "beauty") {
        q2_x = (TH2F*) f -> Get("bin1/q2_x_beauty/"+sample);
    } else if  (type == "inclusive") {
        q2_x = (TH2F*) f -> Get("bin1/q2_x/"+sample);
    } else {
        cout << "ERROR: argument " << type << " is not supported" << endl;
        abort();
    }

    // draw it
    q2_x -> Draw("col");
    q2_x -> SetXTitle("log_{10}x");
    q2_x -> SetYTitle("log_{10}Q^{2}/GeV^{2}");

    // needed for text
    TLatex * text = new TLatex ();
    text -> SetNDC();
    text -> SetTextSize(0.03);

    // histogram range in x
    Double_t low_x = TMath::Power(10, -4.5);
    Double_t up_x = 1;

    // histogram range in Q2
    Double_t low_q2 = TMath::Power(10, 0.5);
    Double_t up_q2 = TMath::Power(10, 3);

    // q2 edges
    line(low_x, 5, 0.003, 5, 1);
    line(low_x, 20, 0.01, 20, 1);
    line(low_x, 60, 0.04, 60, 1);
    line(low_x, 120, 0.06, 120, 1);
    line(low_x, 400, 0.1, 400, 1);
    line(low_x, 1000, 0.1, 1000, 1);

    // x edges
    line(0.00008, 5, 0.00008, 20);
    line(0.0002, 5, 0.0002, 20);
    line(0.0003, 5, 0.0003, 20);
    line(0.0005, 5, 0.0005, 20);
    line(0.003, 5, 0.003, 20);

    line(0.0003, 20, 0.0003, 60);
    line(0.0005, 20, 0.0005, 60);
    line(0.0012, 20, 0.0012, 60);
    line(0.002, 20, 0.002, 60);
    line(0.0035, 20, 0.0035, 60);
    line(0.01, 20, 0.01, 60);

    line(0.0008, 60, 0.0008, 120);
    line(0.0018, 60, 0.0018, 120);
    line(0.003, 60, 0.003, 120);
    line(0.006, 60, 0.006, 120);
    line(0.04, 60, 0.04, 120);

    line(0.0016, 120, 0.0016, 400);
    line(0.005, 120, 0.005, 400);
    line(0.016, 120, 0.016, 400);
    line(0.06, 120, 0.06, 400);

    line(0.005, 400, 0.005, 1000);
    line(0.02, 400, 0.02, 1000);
    line(0.1, 400, 0.1, 1000);

    text -> SetTextColor(kBlack);
    text -> DrawLatex(0.115, 0.175, "Q^{2} = 5 GeV^{2}");
    text -> DrawLatex(0.115, 0.38, "Q^{2} = 20 GeV^{2}");
    text -> DrawLatex(0.115, 0.55, "Q^{2} = 60 GeV^{2}");
    text -> DrawLatex(0.115, 0.65, "Q^{2} = 120 GeV^{2}");
    text -> DrawLatex(0.115, 0.83, "Q^{2} = 400 GeV^{2}");

    // q2-x points where F2 is extracted - vertex measurement
    marker(0.00015, 6.5, 20);
    marker(0.00028, 6.5, 20);
    marker(0.00043, 12, 20);
    marker(0.00065, 12, 20);

    marker(0.00043, 25, 20);
    marker(0.0008, 25, 20);
    marker(0.0016, 30, 20);
    marker(0.0025, 30, 20);
    marker(0.0045, 30, 20);

    marker(0.0016, 80, 20);
    marker(0.0025, 80, 20);
    marker(0.0045, 80, 20);

    marker(0.0035, 160, 20);
    marker(0.008, 160, 20);
    marker(0.02, 160, 20);

    marker(0.013, 600, 20);
    marker(0.035, 600, 20);

    // x values of the common-grid comparison plot
    line(0.00013, low_q2, 0.00013, up_q2, kRed);
    line(0.0002, low_q2, 0.0002, up_q2, kRed);
    line(0.0005, low_q2, 0.0005, up_q2, kRed);
    line(0.0013, low_q2, 0.0013, up_q2, kRed);
    line(0.002, low_q2, 0.002, up_q2, kRed);
    line(0.005, low_q2, 0.005, up_q2, kRed);
    line(0.013, low_q2, 0.013, up_q2, kRed);
    line(0.032, low_q2, 0.032, up_q2, kRed);

    text -> SetTextColor(kRed);
    text -> SetTextSize(0.02);
    text -> DrawLatex(0.15, 0.97, "x = 0.00013");
    text -> DrawLatex(0.23, 0.97, "x = 0.0002");
    text -> DrawLatex(0.31, 0.97, "x = 0.0005");
    text -> DrawLatex(0.38, 0.97, "x = 0.0013");
    text -> DrawLatex(0.45, 0.97, "x = 0.002");
    text -> DrawLatex(0.52, 0.97, "x = 0.005");
    text -> DrawLatex(0.6, 0.97, "x = 0.013");
    text -> DrawLatex(0.68, 0.97, "x = 0.032");

    // vertex points after swimming
    marker(0.00013, 6.5, 26);
    marker(0.0002, 6.5, 26);
    marker(0.0005, 10, 26);
    marker(0.0005, 12, 26);

    marker(0.0005, 22, 26);
    marker(0.0005, 25, 26);
    marker(0.0013, 30, 26);
    marker(0.002, 30, 26);
    marker(0.005, 30, 26);

    marker(0.0013, 80, 26);
    marker(0.002, 80, 26);
    marker(0.005, 80, 26);

    marker(0.005, 160, 26);
    marker(0.013, 160, 26);
    marker(0.032, 160, 26);

    marker(0.013, 600, 26);
    marker(0.032, 600, 26);

    draw_y_ranges();

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    TString title = PLOTS_PATH+"/kin_plane_"+type+"_"+sample + "_";
    title += mode;
    title += "_beauty.eps";
    c -> Print(title);

    return 0;
}

void marker(Double_t x, Double_t y, unsigned type) {

    TMarker * m = new TMarker (TMath::Log10(x), TMath::Log10(y), type);
    m -> Draw();
}

void arrow(Double_t x1, Double_t y1, Double_t x2, Double_t y2) {
    Double_t q2_offset;
    if (y2>y1) q2_offset = -0.03;
    else  q2_offset = 0.03;

    TArrow * a = new TArrow(TMath::Log10(x1), TMath::Log10(y1)-q2_offset, TMath::Log10(x2), TMath::Log10(y2)+q2_offset, 0.005, "|>");
    a -> SetLineStyle(1);
    a -> Draw();
}

void draw_y_ranges() {
    // constants
    Double_t    s = 318. * 318.;
    Double_t    y_min = 0.02;
    Double_t    y_max = 0.7;

    // draw lines of constant y (min and max cut)
    // q2 = s x y =>  log q2 = log s + log x + log y
    // pol1: p0 = log s + log y = log sy, p1 = 1
    TF1 * l_y_min = new TF1 ("l_y_min", "pol1", -4.5, 0);
    l_y_min -> SetParameters(TMath::Log10(s * y_min), 1);

    TF1 * l_y_max = new TF1 ("l_y_max", "pol1", -4.5, 0);
    l_y_max -> SetParameters(TMath::Log10(s * y_max), 1);

    l_y_min -> SetLineWidth(1);
    l_y_max -> SetLineWidth(1);

    l_y_min -> Draw("same");
    l_y_max -> Draw("same");
}