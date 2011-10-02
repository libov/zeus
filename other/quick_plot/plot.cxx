const   unsigned        Samples_number = 10;

TString         samples_v02[Samples_number] = {

                        "analysis.mc06ev02e.06e.q4.ari_.full.forCHARM2.1.root",
                        "analysis.mc06ev02e.rgap3.nc.bbdir.e.q2g1..full.forCHARM2.1.root",
                        "analysis.mc06ev02eccbar.rg30.q2g1.5.bgf.full.forCHARM2.1.root",
                        "analysis.mc06ev02e.rgap3.nc.ccdir.e.q2g4.full.forCHARM2.1.root",
                        "analysis.data06ev02d.full.forCHARM2.1.root",

                        "analysis.mc07pv02e.0607p.q4.ari_.full.forCHARM2.1.root",
                        "analysis.mc07pv02e.rgap3.nc.b.q2g1.p.full.forCHARM2.1.root",
                        "analysis.mc07pv02eccbar.rg30.q2g1.5.bgf.full.forCHARM2.1.root",
                        "analysis.mc07pv02e.rgap3.nc.c..full.forCHARM2.1.root",
                        "analysis.data07pv02d.full.forCHARM2.1.root"
                }

TString         samples_v04[Samples_number] = {
                        "analysis.mc06ev04bh13622.06e.q4.ari_.full.forCHARM2.2.root",
                        "analysis.mc06ev04b.f15643.bbbar.rg30.q2g1.bgf..full.forCHARM2.2.root",
                        "analysis.mc06ev04b.f15643.ccbar.rg30.q2g1.5.bgf..full.forCHARM2.2.root",
                        "analysis.mc06ev04b.f15643.rgap3.nc.ccdir.e.q2g4..full.forCHARM2.2.root",
                        "analysis.data06ev04b.full.forCHARM2.2.root",

                        "analysis.mc07pv04bh13622.0607p.q4.ari_.full.forCHARM2.2.root",
                        "analysis.mc07pv04b.f15643.rgap3.nc.b.q2g1.p..full.forCHARM2.2.root",
                        "analysis.mc07pv04b.f15643.ccbar.rg30.q2g1.5.bgf..full.forCHARM2.2.root",
                        "analysis.mc07pv04b.f15643.rgap3.nc.c.q2g4.p..full.forCHARM2.2.root",
                        "analysis.data07pv04b.full.forCHARM2.2.root"
                }

TString         sample_Titles[Samples_number] = {
                        "06eLF",
                        "06eb",
                        "06ecQ1.5",
                        "06ecQ4",
                        "06edata",
                        
                        "07pLF",
                        "07pb",
                        "07pcQ1.5",
                        "07pcQ4",
                        "07pdata"
                }

//----------- declaration of global variables that are used in both functions -----------
int             plot_number;
TFile           *f1;
TFile           *f2;
TLegend         *leg;
int             sample_counter;

int plot_histo(TCanvas * c, TString histo_name) {
        cout <<  histo_name << ": ";
        // get histograms
	TH1F * h1 = (TH1F*) f1 -> Get(histo_name);
	TH1F * h2 = (TH1F*) f2 -> Get(histo_name);

	// set colors to distinguish them
	h1 -> SetLineColor(kRed);
	h2 -> SetLineColor(kBlue);
        // draw histograms
        c -> cd(plot_number);
	h1 -> Draw();
	h2 -> Draw("same");
        
        Float_t integral1 = h1->Integral();
        Float_t integral2 = h2->Integral();
        Float_t deviation = 100 * (integral1 -integral2) / integral1;
        cout << integral1 << " <---> " << integral2 << " (" <<deviation << " %)" << endl;

        // create and draw a legend
        if ( plot_number==1 ) {
	       leg = new TLegend(0.1,0.7,0.44,0.9);
               TString title1 = sample_Titles[sample_counter]+"v02e";
               TString title2 = sample_Titles[sample_counter]+"v04b";
	       leg -> AddEntry(h1, title1, "l");
	       leg -> AddEntry(h2, title2, "l");
	       leg -> Draw();
        }

        // now a ratio plot
        TH1F *h3 = (TH1F*)h1->Clone("h3");
        h3 -> Divide(h2);
        c -> cd (plot_number+4);
        h3 -> SetMarkerColor(kBlack);
        h3 -> SetMarkerStyle(20);
        h3 -> Draw();

        TLine *line = new TLine(h3 -> GetBinLowEdge(1), 1, h3 -> GetBinLowEdge(h1->GetNbinsX()), 1);
        line -> Draw("same");

        
        // save the plot to a file
	//c -> Print("temp_plot.png");
        //increment the counter
	plot_number++;
        // good bye
	return 0;
}

int plot_year (TString file1, TString file2) {
        // get files
        cout << sample_Titles[sample_counter] << endl;
        TString		HISTO=getenv("HISTO_PATH");
	f1 = new TFile (HISTO+"/"+file1);
	f2 = new TFile (HISTO+"/"+file2);

        plot_number = 1;
        TCanvas *c = new TCanvas();
        c -> Divide(4,2);

        plot_histo(c, "bin1/significance");
        plot_histo(c, "bin1/significance_massbin1_mirrored");
        plot_histo(c, "bin1/significance_massbin2_mirrored");
        plot_histo(c, "bin1/significance_massbin3_mirrored");

        return 0;
}

int plot() {
        for (sample_counter = 0; sample_counter < Samples_number; sample_counter++) {
                plot_year(samples_v02[sample_counter], samples_v04[sample_counter]);
        }
        
}
        