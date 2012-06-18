
Float_t integral(TH1F *h) {

    Float_t xsect = 0;

    unsigned nbins = h->GetNbinsX();
    for (unsigned i=1; i<=nbins; i++) xsect += h->GetBinContent(i) * h -> GetBinWidth(i);

    return xsect;
}

int check(TString path) {

    TFile * f = new TFile(path+"/histograms.root","read");

    TH1F * et = (TH1F*)f->Get("HISB/h30101");
    TH1F * eta = (TH1F*)f->Get("HISB/h30102");
    TH1F * q2 = (TH1F*)f->Get("HISB/h30103");
    TH1F * x = (TH1F*)f->Get("HISB/h30104");

    Float_t et_xsect = integral(et);
    Float_t eta_xsect = integral(eta);
    Float_t q2_xsect = integral(q2);
    Float_t x_xsect = integral(x);

    cout << "et= " << et_xsect << endl;
    cout << "eta= " << eta_xsect << endl;
    cout << "q2= " << q2_xsect << endl;
    cout << "x= " << x_xsect << endl;

    return 0;
}
