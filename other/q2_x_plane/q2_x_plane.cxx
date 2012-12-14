void marker(Double_t, Double_t, unsigned);

void arrow(Double_t, Double_t, Double_t, Double_t);

void draw_y_ranges();

void line(Double_t x1, Double_t y1, Double_t x2, Double_t y2, int color=1, int width=2) {

    TLine * l = new TLine (TMath::Log10(x1), TMath::Log10(y1), TMath::Log10(x2), TMath::Log10(y2));
    l -> SetLineColor(color);
    l -> SetLineWidth(width);
    l -> Draw();
}

int q2_x_plane (TString type="inclusive", TString sample = "data", unsigned mode = 4) {

    TCanvas *c = new TCanvas ("c", "", 1600, 1200);

    // style settings
    gStyle -> SetOptStat(0);
    gStyle -> SetMarkerSize(0.8);
    gStyle -> SetLineStyle(7);

    TString HISTO_PATH = getenv("HISTO_PATH");
    TString filename = HISTO_PATH+"/merged.full.forCHARM2.70.1.0405e06e07p.root";
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
    marker(0.008, 80, 20);

    marker(0.0035, 160, 20);
    marker(0.008, 160, 20);
    marker(0.02, 160, 20);

    marker(0.013, 600, 20);
    marker(0.035, 600, 20);

    if (mode > 1) {
        // charm combination
        line(low_x, 5, up_x, 5, 2, 1);
        line(low_x, 7, up_x, 7, 2, 1);
        line(low_x, 12, up_x, 12, 2, 1);
        line(low_x, 18, up_x, 18, 2, 1);
        line(low_x, 32, up_x, 32, 2, 1);
        line(low_x, 60, up_x, 60, 2, 1);
        line(low_x, 120, up_x, 120, 2, 1);
        line(low_x, 200, up_x, 200, 2, 1);
        line(low_x, 350, up_x, 350, 2, 1);
        line(low_x, 650, up_x, 650, 2, 1);

        // Draw the columns titles
        text -> SetTextColor(kRed);
        text -> DrawLatex(0.83, 0.182, "Q^{2} = 5 GeV^{2}");
        text -> DrawLatex(0.83, 0.232, "Q^{2} = 7 GeV^{2}");
        text -> DrawLatex(0.83, 0.310, "Q^{2} = 12 GeV^{2}");
        text -> DrawLatex(0.83, 0.370, "Q^{2} = 18 GeV^{2}");
        text -> DrawLatex(0.83, 0.455, "Q^{2} = 32 GeV^{2}");
        text -> DrawLatex(0.83, 0.55, "Q^{2} = 60 GeV^{2}");
        text -> DrawLatex(0.83, 0.645, "Q^{2} = 120 GeV^{2}");
        text -> DrawLatex(0.83, 0.730, "Q^{2} = 200 GeV^{2}");
        text -> DrawLatex(0.83, 0.815, "Q^{2} = 350 GeV^{2}");
        text -> DrawLatex(0.83, 0.895, "Q^{2} = 650 GeV^{2}");

        // charm combination points
        marker(0.00007, 5, 26);
        marker(0.00018, 5, 26);
        marker(0.00035, 5, 26);
        marker(0.001, 5, 26);

        marker(0.00013, 7, 26);
        marker(0.00018, 7, 26);
        marker(0.0003, 7, 26);
        marker(0.0005, 7, 26);
        marker(0.0008, 7, 26);
        marker(0.0016, 7, 26);

        marker(0.00022, 12, 26);
        marker(0.00032, 12, 26);
        marker(0.0005, 12, 26);
        marker(0.0008, 12, 26);
        marker(0.0015, 12, 26);
        marker(0.003, 12, 26);

        marker(0.00035, 18, 26);
        marker(0.0005, 18, 26);
        marker(0.0008, 18, 26);
        marker(0.00135, 18, 26);
        marker(0.0025, 18, 26);
        marker(0.0045, 18, 26);

        marker(0.0006, 32, 26);
        marker(0.0008, 32, 26);
        marker(0.0014, 32, 26);
        marker(0.0024, 32, 26);
        marker(0.0032, 32, 26);
        marker(0.0055, 32, 26);
        marker(0.008, 32, 26);

        marker(0.0014, 60, 26);
        marker(0.002, 60, 26);
        marker(0.0032, 60, 26);
        marker(0.005, 60, 26);
        marker(0.008, 60, 26);
        marker(0.015, 60, 26);

        marker(0.002, 120, 26);
        marker(0.0032, 120, 26);
        marker(0.0055, 120, 26);
        marker(0.01, 120, 26);
        marker(0.025, 120, 26);

        marker(0.005, 200, 26);
        marker(0.013, 200, 26);

        marker(0.01, 350, 26);
        marker(0.025, 350, 26);

        marker(0.013, 650, 26);
        marker(0.032, 650, 26);
    }

    if (mode > 2) {

        arrow(0.00043, 25, 0.00048, 18);
        arrow(0.00043, 25, 0.00053, 32);
        arrow(0.0008, 25, 0.0008, 32);

        arrow(0.0016, 80, 0.00145, 60);
        arrow(0.0025, 80, 0.00215, 60);
        arrow(0.0045, 80, 0.0048, 60);
        arrow(0.008, 80, 0.008, 60);

        arrow(0.0035, 160, 0.0033, 120);
        arrow(0.008, 160, 0.0095, 120);
        arrow(0.02, 160, 0.023, 120);

        arrow(0.0035, 160, 0.0048, 200);
        arrow(0.008, 160, 0.012, 200);
    }

    if (mode>3) draw_y_ranges();

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    TString title = PLOTS_PATH+"/kin_plane_"+type+"_"+sample + "_";
    title += mode;
    title += ".eps";
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