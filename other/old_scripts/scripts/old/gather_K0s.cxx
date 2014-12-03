int main()
{
	TFile *f1=new TFile("/data/zenith226a/libov/results/recent/last2004.root");
	TFile *f2=new TFile("/data/zenith226a/libov/results/recent/last2007.root");
	TFile *f3=new TFile("/data/zenith226a/libov/results/recent/last2005.root");
	TFile *f4=new TFile("/data/zenith226a/libov/results/recent/last2006.root");



	TH1F *h2_1= (TH1F*)f1->Get("hinv_base");
	TH1F *h2_2= (TH1F*)f2->Get("hinv_base");
	TH1F *h2_3= (TH1F*)f3->Get("hinv_base");
	TH1F *h2_4= (TH1F*)f4->Get("hinv_base");


	Float_t		histRangeLow=450,
			histRangeUp=542,
			histRange=histRangeUp-histRangeLow,
			bin_width=1.5;
	Int_t 		nbins=(Int_t)histRange/bin_width;
	bin_width=(Float_t)histRange/nbins;
	cout<<bin_width<<" "<<nbins<<endl;
	gStyle->SetOptFit(0000);
	TH1F *h=new TH1F("h","sas",nbins,histRangeLow,histRangeUp);
	h->GetXaxis()->SetTitle("Invariant mass, MeV ");
	h->GetYaxis()->SetTitle(" Combinations / 1.5 MeV ");

	for(Int_t i=0;i<150;i++)
	{
		Double_t content=h2_1->GetBinContent(i)+h2_2->GetBinContent(i)+h2_3->GetBinContent(i)+h2_4->GetBinContent(i);
		h->SetBinContent(i,content);
	}

	h->Draw();
	TFile *f=new TFile("/data/zenith226a/libov/results/recent/K0s_full.root","new");
	h->Write();
	f->Close();
	return 0;
}
