int plot(TString type = "data", TString variable = "significance", TString  bin="bin1") {

    TString     HISTO_PATH = getenv("HISTO_PATH");
    
    TFile * f_1 = new TFile (HISTO_PATH+"/merged.full.forCHARM2.34.1.0405e06e07p.root", "read");
    TFile * f_2 = new TFile (HISTO_PATH+"/merged.full.forCHARM2.39.1.0405e06e07p.root", "read");

    TH1F * h_data_mirr3_1 = (TH1F*) f_1 -> Get(bin + "/"+variable+"/"+type);
    TH1F * h_data_mirr3_2 = (TH1F*) f_2 -> Get(bin + "/"+variable+"/"+type);

    h_data_mirr3_1 -> SetMarkerColor(kRed);
    h_data_mirr3_1 -> SetMarkerStyle(21);

    h_data_mirr3_2 -> SetMarkerColor(kBlue);
    h_data_mirr3_2 -> SetMarkerStyle(22);

    h_data_mirr3_1 -> Draw();
    h_data_mirr3_2 -> Draw("same");

    TLegend * leg = new TLegend (0.5,0.7,0.95,0.9);
    leg -> SetHeader(variable+" ("+type+")");
    leg -> AddEntry(h_data_mirr3_1, "2.29.1", "p");
    leg -> AddEntry(h_data_mirr3_2, "2.25.1", "p");
    leg -> Draw("same");

    return 0;
}
