
int find_closest_jet (TLorentzVector c_particle, Int_t Nhbmjets, Float_t * Pxhbmjet, Float_t * Pyhbmjet, Float_t * Pzhbmjet, Float_t * Ehbmjet ) {

    Float_t distance_min = 999999;
    unsigned closest_jet;
    bool jet_found = false;

    for ( unsigned i = 0; i<Nhbmjets; i++) {
        TLorentzVector jet(Pxhbmjet[i], Pyhbmjet[i], Pzhbmjet[i], Ehbmjet[i]);
        Float_t dist = jet.DeltaR(c_particle);

        if (dist < distance_min ) {
            distance_min = dist;
            closest_jet = i;
            jet_found = true;
        }
    }

    assert(jet_found);

    return closest_jet;
}

int jet_algorithm() {

    gStyle -> SetOptTitle(1);
    gStyle -> SetPadTopMargin(0.08);
    gStyle  -> SetPalette(1);

    Float_t ETMIN = 2;

    TChain * c = new TChain ("orange");
    c -> Add("zeus://acs/z/ntup/05/v02e/mc/root/zeusmc.hduwe25.f13695.rgap3.nc.c.q2g1.5.22.root");
    c -> SetBranchStatus("*", 0);
    unsigned nevents = c -> GetEntries();
    cout << "nevents= " << nevents << endl;

    TH1F * h_nhbmjets = new TH1F ("", "all jets multiplicity", 10, 0, 10);
    TH2F * h_eta_et_all_jets = new TH2F ("", "E_{T}-#eta plane, all jets", 100, -3, 3, 100, 0, 15);
    TH1F * h_nhbmjets_etmin = new TH1F ("", "multiplicity of jets with E_{T}>E_{T,min} ", 10, 0, 10);
    TH1F * h_etjets = new TH1F ("", "E_{T} of jets ", 20, 0, 15);
    TH1F * h_massjets = new TH1F ("", "mass of jets", 10, 0, 10);
    TH1F * h_ncb = new TH1F ("", "charmed particle multiplicity (Ncb)", 20, 0, 20);
    TH1F * h_c_mass = new TH1F ("", "charmed particles mass", 100, 0, 4);
    TH1F * h_c_type = new TH1F ("", "charmed particles type", 3000, 0, 3000);
    TH1F * h_n_c_quarks = new TH1F ("", "c quark multiplicity", 20, 0, 20);
    TH1F * h_n_c_antiquarks = new TH1F ("", "c antiquark multiplicity", 20, 0, 20);
    TH2F * h_eta_et_c_quarks = new TH2F ("", "E_{T}-#eta plane, c quarks", 100, -3, 3, 100, 0, 15);
    TH2F * h_eta_p_c_quarks = new TH2F ("", "p-#eta plane, c quarks", 100, -3, 3, 100, 0, 15);
    TH1F * h_c_quark_jet_min_distance = new TH1F ("", "c_quark_jet_min_distance", 100, 0, 10);
    TH2F * h_eta_et_c_quark_jets = new TH2F ("", "E_{T}-#eta plane, jets closest to c quarks", 100, -3, 3, 100, 0, 15);
    TH2F * h_p_c_quark_vs_p_closest_jet = new TH2F ("", "p_c_quark_vs_p_closest_jet", 100, 0, 15, 100, 0, 15);
    TH2F * h_p_c_quark_vs_et_closest_jet = new TH2F ("", "p_c_quark_vs_et_closest_jet", 100, 0, 15, 100, 0, 15);
    TH2F * h_p_c_quark_vs_e_closest_jet = new TH2F ("", "p_c_quark_vs_e_closest_jet", 100, 0, 15, 100, 0, 15);
    TH1F * h_mass_closest_jet = new TH1F ("", "Closest jet mass", 100, 0, 15);

    unsigned const max_nhbmjets = 100;
    unsigned const npart_max = 2000;

    Int_t Nhbmjets;
    c -> SetBranchStatus("Nhbmjets", 1);
    c -> SetBranchAddress("Nhbmjets", &Nhbmjets);

    Float_t Pxhbmjet[max_nhbmjets];
    Float_t Pyhbmjet[max_nhbmjets];
    Float_t Pzhbmjet[max_nhbmjets];
    Float_t Ehbmjet[max_nhbmjets];
    c -> SetBranchStatus("Ehbmjet", 1);
    c -> SetBranchStatus("Pxhbmjet", 1);
    c -> SetBranchStatus("Pyhbmjet", 1);
    c -> SetBranchStatus("Pzhbmjet", 1);
    c -> SetBranchAddress("Ehbmjet", Ehbmjet);
    c -> SetBranchAddress("Pxhbmjet", Pxhbmjet);
    c -> SetBranchAddress("Pyhbmjet", Pyhbmjet);
    c -> SetBranchAddress("Pzhbmjet", Pzhbmjet);

    Int_t   Ncb;
    c -> SetBranchStatus("Ncb", 1);
    c -> SetBranchAddress("Ncb", &Ncb);

    Float_t Cb_p[npart_max][5];
    c -> SetBranchStatus("Cb_p", 1);
    c -> SetBranchAddress("Cb_p", Cb_p);

    Int_t   Cb_prt[npart_max];
    c -> SetBranchStatus("Cb_prt", 1);
    c -> SetBranchAddress("Cb_prt", Cb_prt);

    for ( unsigned i = 0; i < nevents; i++) {

        if ( i % 1000 == 0 )   cout<< " processing event " << i << endl;

        c -> GetEntry(i);

        assert(Nhbmjets <= max_nhbmjets);
        assert(Ncb <= npart_max);

        // number of jets in the block
        h_nhbmjets -> Fill (Nhbmjets);

        // loop over jets
        unsigned njets_etmin = 0;
        for ( unsigned j = 0; j < Nhbmjets; j++) {
            TLorentzVector jet(Pxhbmjet[j], Pyhbmjet[j], Pzhbmjet[j], Ehbmjet[j]);

            h_etjets -> Fill(jet.Et());
            h_massjets -> Fill(jet.M());

            if ( jet.Et() > ETMIN ) njets_etmin++;

            h_eta_et_all_jets -> Fill(jet.Eta(), jet.Et());
        }

        // number of jets above a certain threshold
        h_nhbmjets_etmin -> Fill (njets_etmin);

        h_ncb -> Fill(Ncb);

        unsigned n_c_quarks = 0;
        unsigned n_c_antiquarks = 0;

        for (unsigned p=0; p<Ncb; p++) {

            TLorentzVector c_particle(Cb_p[p][0], Cb_p[p][1], Cb_p[p][2], Cb_p[p][3]);

            h_c_mass -> Fill(c_particle.M());

            h_c_type -> Fill(Cb_prt[p]);

            if (Cb_prt[p] == 7) n_c_quarks++;
            if (Cb_prt[p] == 8) n_c_antiquarks++;

            if ( (Cb_prt[p] == 7) || (Cb_prt[p] == 8) ) {
                h_eta_et_c_quarks -> Fill (c_particle.Eta(), c_particle.Et());
                h_eta_p_c_quarks -> Fill (c_particle.Eta(), c_particle.P());
                if (Nhbmjets != 0) {
                    unsigned closest_jet_id = find_closest_jet( c_particle, Nhbmjets, Pxhbmjet, Pyhbmjet, Pzhbmjet, Ehbmjet );
                    TLorentzVector closest_jet(Pxhbmjet[closest_jet_id], Pyhbmjet[closest_jet_id], Pzhbmjet[closest_jet_id], Ehbmjet[closest_jet_id]);
                    h_c_quark_jet_min_distance -> Fill(closest_jet.DeltaR(c_particle));
                    if ( closest_jet.DeltaR(c_particle) < 0.5 ) {
                        h_eta_et_c_quark_jets -> Fill(closest_jet.Eta(), closest_jet.Et());
                        h_p_c_quark_vs_p_closest_jet -> Fill(c_particle.P(), closest_jet.P());
                        h_p_c_quark_vs_et_closest_jet -> Fill(c_particle.P(), closest_jet.Et());
                        h_p_c_quark_vs_e_closest_jet -> Fill(c_particle.P(), closest_jet.E());
                        h_mass_closest_jet -> Fill(closest_jet.M());
                    }
                }
            }
        }

        h_n_c_quarks -> Fill(n_c_quarks);
        h_n_c_antiquarks -> Fill(n_c_antiquarks);
    }

    TCanvas * c1 = new TCanvas ("c1", "", 1000, 500);
    c1 -> cd();
    h_nhbmjets -> Draw();

    TCanvas * c1a = new TCanvas ("c1a", "", 1000, 500);
    c1a -> cd();
    h_eta_et_all_jets -> Draw("col");

    TCanvas * c2 = new TCanvas ("c2", "", 1000, 500);
    c2 -> cd();
    h_nhbmjets_etmin -> Draw();

    TCanvas * c3 = new TCanvas ("c3", "", 1000, 500);
    c3 -> cd();
    h_etjets -> Draw();

    TCanvas * c4 = new TCanvas ("c4", "", 1000, 500);
    c4 -> cd();
    h_massjets -> Draw();

    TCanvas * c5 = new TCanvas ("c5", "", 1000, 500);
    c5 -> cd();
    h_ncb -> Draw();

    TCanvas * c6 = new TCanvas ("c6", "", 1000, 500);
    c6 -> cd();
    h_c_mass -> Draw();

    TCanvas * c7 = new TCanvas ("c7", "", 1000, 500);
    c7 -> cd();
    h_c_type -> Draw();

    TCanvas * c8 = new TCanvas ("c8", "", 1000, 500);
    c8 -> cd();
    h_n_c_quarks -> Draw();

    TCanvas * c9 = new TCanvas ("c9", "", 1000, 500);
    c9 -> cd();
    h_n_c_antiquarks -> Draw();

    TCanvas * c10 = new TCanvas ("c10", "", 1000, 500);
    c10 -> cd();
    h_eta_et_c_quarks -> Draw("col");

    TCanvas * c11 = new TCanvas ("c11", "", 1000, 500);
    c11 -> cd();
    h_eta_p_c_quarks -> Draw("col");

    TCanvas * c12 = new TCanvas ("c12", "", 1000, 500);
    c12 -> cd();
    h_c_quark_jet_min_distance -> Draw();

    TCanvas * c13 = new TCanvas ("c13", "", 1000, 500);
    c13 -> cd();
    h_eta_et_c_quark_jets -> Draw("col");

    TCanvas * c14 = new TCanvas ("c14", "", 1000, 500);
    c14 -> cd();
    h_p_c_quark_vs_p_closest_jet -> Draw("col");
    TLine * l14 = new TLine (0,0,30,30);
    l14 -> Draw("same");

    TCanvas * c15 = new TCanvas ("c15", "", 1000, 500);
    c15 -> cd();
    h_p_c_quark_vs_et_closest_jet -> Draw("col");

    TCanvas * c16 = new TCanvas ("c16", "", 1000, 500);
    c16 -> cd();
    h_p_c_quark_vs_et_closest_jet -> Draw("col");

    TCanvas * c17 = new TCanvas ("c17", "", 1000, 500);
    c17 -> cd();
    h_p_c_quark_vs_e_closest_jet -> Draw("col");
    TLine * l17 = new TLine (0,1.5,30,30);
    l17 -> Draw("same");

    TCanvas * c18 = new TCanvas ("c18", "", 1000, 500);
    c18 -> cd();
    h_mass_closest_jet -> Draw();

    return 0;
}
