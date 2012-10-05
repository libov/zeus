int hadr_int_rate() {

    // load Sasha's routine
    gROOT -> ProcessLine(".L TrackAllEfficiency.cc+");

    // total number of points
    const unsigned n_points = 1000;

    // pT
    Double_t pt[n_points];
    Double_t prob_pt[n_points];
    Double_t low_pt = 0.2;
    Double_t high_pt = 10;
    Double_t step_pt = (high_pt - low_pt)/n_points;

    // theta
    Double_t theta[n_points];
    Double_t prob_theta[n_points];
    Double_t low_theta = 20;
    Double_t high_theta = 160;
    Double_t step_theta = (high_theta - low_theta)/n_points;

    // phi
    Double_t phi[n_points];
    Double_t prob_phi[n_points];
    Double_t low_phi = 0;
    Double_t high_phi = 360;
    Double_t step_phi = (high_phi - low_phi)/n_points;

    // these keep efficiency/inefficiency
    Float_t TrEff = -1;
    Float_t TrInt = -1;

    const Float_t   grad_per_rad = 180. / TMath::Pi();

    // reference track parameters
    Float_t phi_ref = 1.5;
    Float_t theta_ref = TMath::Pi()/2;
    Float_t cot_ref = cos(theta_ref)/sin(theta_ref);
    Float_t p_ref = 1;
    Int_t   charge_ref = 1;
    Int_t   id_ref = 1; // 2=kaon, 3=proton, else=pion

    // determine interaction probability for different values of track parameters
    for (int i=0; i<n_points; i++) {

        // pT
        pt[i] = low_pt + step_pt * i;
        Float_t p = pt[i]/sin(theta_ref);
        TrackAllEfficiency (phi_ref, cot_ref, p, charge_ref, id_ref, TrEff, TrInt);
        prob_pt[i] = TrInt;

        // theta
        theta[i] = low_theta + step_theta * i;
        Float_t cot = cos(theta[i]/grad_per_rad)/sin(theta[i]/grad_per_rad);
        Float_t p = pt[i]/sin(theta/grad_per_rad);
        TrackAllEfficiency (phi_ref, cot, p_ref, charge_ref, id_ref, TrEff, TrInt);
        prob_theta[i] = TrInt;

        // phi
        phi[i] = low_phi + step_phi * i;
        Float_t phi_rad = phi[i]/grad_per_rad;
        TrackAllEfficiency (phi_rad, cot_ref, p_ref, charge_ref, id_ref, TrEff, TrInt);
        prob_phi[i] = TrInt;
    }

    TCanvas * c1 = new TCanvas ("c1", "", 1200, 1200);
    TGraph * g_pt = new TGraph(n_points, pt, prob_pt);
    g_pt -> Draw("apl");

    TCanvas * c2 = new TCanvas ("c2", "", 1200, 1200);
    TGraph * g_theta = new TGraph(n_points, theta, prob_theta);
    g_theta -> Draw("apl");

    TCanvas * c3 = new TCanvas ("c3", "", 1200, 1200);
    TGraph * g_phi = new TGraph(n_points, phi, prob_phi);
    g_phi -> Draw("apl");

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c1 -> Print(PLOTS_PATH + "/hadr_int_rate_pt.eps");
    c2 -> Print(PLOTS_PATH + "/hadr_int_rate_theta.eps");
    c3 -> Print(PLOTS_PATH + "/hadr_int_rate_phi.eps");

    return 0;
}