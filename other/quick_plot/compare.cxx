int compare() {

    TString bin = "bin6";

    TString variable = "significance";
    //TString variable = "track_theta";

    TString HISTO_PATH = getenv("HISTO_PATH");
    TFile *f1 = new TFile(HISTO_PATH+"/analysis.mc07pv06b.f15643.rgap3.nc.c.q2g4.p.full.forCHARMcutoff.root", "read");
    TFile *f2 = new TFile(HISTO_PATH+"/analysis.mc07pv06b.f15643.rgap3.nc.c.q2g4.p.full.forCHARMno_cutoff.root", "read");

    TH1F * h1_1 = (TH1F*) f1 -> Get(bin+"/"+variable);
    TH1F * h2_1 = (TH1F*) f2 -> Get(bin+"/"+variable);

    h1_1 -> Draw();
    h2_1 -> Draw("same");

    h1_1 -> SetLineColor(kRed);
    h2_1 -> SetLineColor(kBlue);

    cout << h1_1 -> GetEntries() << " " << h2_1 -> GetEntries() << endl;

}