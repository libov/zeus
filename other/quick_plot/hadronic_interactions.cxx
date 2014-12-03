TString SAMPLE = "";
TString HISTO_PATH = getenv("HISTO_PATH");
TString PLOTS_PATH = getenv ("PLOTS_PATH");

//TString filename = "analysis.data06ev06a.full.forCHARM2.76.1.root";
TString filename = "analysis.data06ev06a.full.forCHARM2.76.2.root";
TString full_filename = HISTO_PATH+"/"+filename;
TFile * FILE = new TFile(full_filename, "read");
std::cout << " Opened file " << full_filename << std::endl;

void DrawLine() {
    TLine * l = new TLine (0, 1, 180, 1);
    l -> SetLineStyle(2);
    l -> SetLineWidth(1);
    l -> Draw();
}

void SetHistoParameters(TH1F * h) {
    h -> Draw();
    h -> SetAxisRange(0, 0.15, "Y");
    h -> SetXTitle("#theta [degrees]");
    h -> SetYTitle("p^{hadr}");
    h -> SetTitleOffset(1.1, "Y");
    h -> SetMarkerStyle(21);
}

void SetHistoParametersRatio(TH1F * h) {
    h -> Draw();
    h -> SetAxisRange(0, 3, "Y");
    h -> SetXTitle("#theta [degrees]");
    h -> SetYTitle("new correction/old correction");
    h -> SetTitleOffset(1.1, "Y");
    h -> SetMarkerStyle(21);
    gStyle -> SetOptStat(0);
}

void PrintHisto(TString name, bool set_parameters = true) {

    TCanvas * c = new TCanvas();

    TH1F * h = (TH1F*) FILE -> Get("bin1/"+name+SAMPLE);

    if (set_parameters) SetHistoParameters(h);

    c -> Print(PLOTS_PATH + "/" + name + ".eps");

    c -> Close();
}

TH1F* PrintHistoRatio(TString name) {

    TCanvas * c = new TCanvas();

    TH1F * h = (TH1F*) FILE -> Get("bin1/"+name+SAMPLE);

    SetHistoParametersRatio(h);

    DrawLine();

    c -> Print(PLOTS_PATH + "/" + name + ".eps");

    return h;
}

TH1F* FitHistoRatio(TString name) {

    TCanvas * c = new TCanvas();

    TH1F * h = (TH1F*) FILE -> Get("bin1/"+name+SAMPLE);

    SetHistoParametersRatio(h);

    DrawLine();

    h -> Fit("pol0", "", "", 60, 120);

    gStyle -> SetOptFit(1);

    c -> Print(PLOTS_PATH + "/" + name + "_fit.eps");
    return h;
}

void draw_sum_map_variables() {

    TCanvas * c = new TCanvas();
    c -> cd();

    TH1F * hTrEffI = (TH1F*) FILE -> Get("bin1/TrEffI_Sum_theta"+SAMPLE);
    hTrEffI -> SetMarkerColor(kRed);
    hTrEffI -> SetMarkerStyle(21);
    hTrEffI -> Draw();

    TH1F * hTrEff = (TH1F*) FILE -> Get("bin1/TrEff_Sum_theta"+SAMPLE);
    hTrEff -> SetMarkerColor(kBlue);
    hTrEff -> SetMarkerStyle(21);
    hTrEff -> Draw("same");

    TH1F * hTrInt = (TH1F*) FILE -> Get("bin1/TrInt_Sum_theta"+SAMPLE);
    hTrInt -> SetMarkerStyle(21);
    hTrInt -> SetMarkerColor(kGreen);
    hTrInt -> Draw("same");

    TH1F * hTrIntN = (TH1F*) FILE -> Get("bin1/TrIntN_Sum_theta"+SAMPLE);
    hTrIntN -> SetMarkerStyle(21);
    hTrIntN -> SetMarkerColor(kBlack);
    hTrIntN -> Draw("same");

    hTrEffI -> SetAxisRange(0, 1, "Y");

    TLegend * l = new TLegend (0.8, 0.8, 1.0, 1.0);
    l -> AddEntry(hTrEff, "m & n/i");
    l -> AddEntry(hTrEffI, "m & i");
    l -> AddEntry(hTrInt, "n/m & i");
    l -> AddEntry(hTrIntN, "n/m & n/i");
    l -> Draw();

    c -> Print(PLOTS_PATH + "/draw_sum_map_variables.eps");

}

int hadronic_interactions() {

    if (filename.Contains("merged")) SAMPLE += "/charm";

    draw_sum_map_variables();

    PrintHisto("TrInt_All_theta");
    PrintHisto("corr_All_theta");
    PrintHisto("corr_All_lowpt_theta");
    PrintHisto("TrInt_Rec_theta");
    PrintHisto("TrInt_Rec_nonzero_theta");
    PrintHisto("corr_Rec_theta");
    PrintHisto("corr_Rec_lowpt_theta");
    PrintHisto("phadr_Sum_theta");
    PrintHisto("drop_probability_lowpt_theta");
    PrintHisto("drop_probability_theta");
    PrintHisto("corr_Sum_scaled1_theta");
    PrintHisto("corr_Sum_scaled2_theta");
    PrintHisto("corr_Sum_scaled1_lowpt_theta");

    PrintHisto("track_theta", false);

    PrintHistoRatio("corr_Sum_vs_All_theta");
    PrintHistoRatio("corr_Sum_scaled1_vs_Rec_theta");
    PrintHistoRatio("corr_Sum_scaled1_vs_All_theta");

    PrintHistoRatio("corr_Sum_scaled1_vs_Rec_theta");
    FitHistoRatio("corr_Sum_scaled1_vs_Rec_theta");

    PrintHistoRatio("phadr_Sum_vs_Rec_theta");
    FitHistoRatio("phadr_Sum_vs_Rec_theta");

    return 0;
}
