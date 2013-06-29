int significance_data_to_mc(TString version = "2.52.2", TString bin = "bin1") {

    gStyle -> SetOptStat(0);

    TFile * f = new TFile ("/data/zenith226a/libov/data/histo/merged.full.forCHARM" + version + ".0405e06e07p.scaled.root", "read");

    TH1F * h1 = (TH1F*) f -> Get (bin+"/significance/data");
    TH1F * h2 = (TH1F*) f -> Get (bin+"/significance/mc");

    TH1F * ratio = h1 -> Clone("ratio");
    ratio -> Divide(h2);

    TCanvas * c = new TCanvas("c","", 1200, 1200 );
    ratio -> SetMarkerStyle(20);
    ratio -> SetMarkerSize(1.1);
    ratio -> SetYTitle("data / MC");
    ratio -> SetXTitle("S = L_{XY}/#sigma(L_{XY})");
    ratio -> SetTitleSize(0.05, "X");
    ratio -> SetTitleSize(0.05, "Y");
    ratio -> SetTitleOffset(1.05, "X");
    ratio -> SetTitleOffset(1.2, "Y");
    ratio -> SetAxisRange(0.8, 1.3, "Y");
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    ratio -> Draw();

    TLine * l = new TLine(-20, 1, 20, 1);
    l -> Draw();

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c -> Print (PLOTS_PATH + "/significance_"+version+"_"+bin+".eps");
}
