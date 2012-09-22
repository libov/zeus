int plot_MC(){

	bool isLF = false;
	bool isBEAUTY = true;

	TFile * f_0;
        TFile * f_50;
	TFile * f_100;
        TFile * f_150;

	if (isBEAUTY) {
            f_0 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARM2.17.0.root", "read");
            f_50 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARM2.17.2.root", "read");
            f_100 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARM2.17.4.root", "read");
            f_150 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARM2.17.6.root", "read");
	} else if (isLF) {
            f_0 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.0405e.q4.ari_.full.forCHARM2.17.0.root", "read");
            f_50 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.0405e.q4.ari_.full.forCHARM2.17.2.root", "read");
            f_100 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.0405e.q4.ari_.full.forCHARM2.17.4.root", "read");
            f_150 = new TFile ("/data/zenith226a/libov/analysis/data/histo/analysis.mc05v02e.0405e.q4.ari_.full.forCHARM2.17.6.root", "read");
	}

	// get the histograms from the files
        TH1F * h_0;
        TH1F * h_50;
        TH1F * h_100;
        TH1F * h_150;
        if (mirrored_all_masses) {
	   h_0 = (TH1F*) f_0 -> Get("bin1/significance_mirrored");
	   h_50 = (TH1F*) f_50 -> Get("bin1/significance_mirrored");
           h_100 = (TH1F*) f_100 -> Get("bin1/significance_mirrored");
           h_150 = (TH1F*) f_150 -> Get("bin1/significance_mirrored");
        }

        h_0 -> Rebin(2);
        h_50 -> Rebin(2);
        h_100 -> Rebin(2);
        h_150 -> Rebin(2);

        h_0 -> Draw("hist");
        h_50 -> Draw("histsame");
        h_100 -> Draw("histsame");
        h_150 -> Draw("histsame");

        h_0 -> SetLineColor(1);
        h_50 -> SetLineColor(2);
        h_100 -> SetLineColor(3);
        h_150 -> SetLineColor(4);
	
	TLegend * leg = new TLegend(0.12, 0.6, 0.4, 0.88);
	leg -> AddEntry(h_0, "smearing 0%", "l");
	leg -> AddEntry(h_50, "smearing 50%", "l");
        leg -> AddEntry(h_100, "smearing 100% (default)", "l");
        leg -> AddEntry(h_150, "smearing 150%", "l");

	leg -> Draw("same");

	return 0;
}

    
    
    