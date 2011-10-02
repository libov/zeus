const unsigned      NPOINTS = 1000000;
const float         SMEARING_PROB = 0.5;
const float         G0_WIDTH = 2;
const float         G2_WIDTH = 0.2;

int smearing_simulation () {
    TH1F * h1 = new TH1F ("", "", 100, -20, 20);
    TH1F * h2 = new TH1F ("", "", 100, -20, 20);
    TH1F * hsum = new TH1F ("", "", 100, -20, 20);
    TH1F * hratio;

    TRandom3    rnd;
    
    for (unsigned i = 0; i < NPOINTS; i++) {

        float   g1 = G0_WIDTH * rnd.Gaus();
        h1 -> Fill(g1);

        float   u = rnd.Rndm();
        if (u < SMEARING_PROB) {
            float g2 = G2_WIDTH * rnd.Gaus();
            h2 -> Fill(g2);
            g1 += g2;
        }

        hsum -> Fill (g1);
    }

    hratio  = (TH1F*)hsum -> Clone("ratio");
    hratio -> Divide(h1);

    // now draw
    TCanvas * c = new TCanvas;
    c->Divide (2,2);
    
    c->cd(1);
    h1 -> Draw("e");

    c->cd(2);
    h2 -> Draw("e");

    c->cd(3);
    hsum -> Draw("e");
    hsum -> Fit ("gaus", "","", -20, 20);
    gPad -> SetLogy();

    c->cd(4);
    hratio -> Draw("e");
}
