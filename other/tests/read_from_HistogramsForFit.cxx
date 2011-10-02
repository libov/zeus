int read_from_HistogramsForFit()
{
/*		TFile *f=new TFile("/data/zenith226a/libov/F2CC/scripts/Fitter/HistogramsForFit.root","read");

		f->ls();

		TH1F *h=(TH1F*)(f->Get("bin1/h_significance_mirrored_massbin1Data06p1"));

		h->Draw();

		f->Close();
*/
cout<<"bla"<<endl;
TFile *f=new TFile("/data/zenith226a/libov/F2CC/ntuples/data/Data06p/DIScplots4.root", "read");
//cout<<f->cd("bin1")<<endl;
//f->ls();
//TH1F	*currentHist=(TH1F*)f->Get("h_vtxsec_chi2ndf")->Clone("aaa");
//TH1F	*currentHist=(TH1F*)f->Get("h_vtxsec_chi2ndf");
TH1F	*currentHist1=(TH1F*)f->Get("bin1/h_vtxsec_chi2ndf");
TH1F	*currentHist2=(TH1F*)f->Get("bin2/h_vtxsec_chi2ndf");

TFile *ff=new TFile("shit.root", "recreate");
ff->cd();
currentHist1->Write();
currentHist2->Write();
ff->Close();
//currentHist->Draw();
		return 0;
}