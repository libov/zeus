#include<canvas.cxx>
int main()
{
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijet_basic.root");
	//TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijet_basic_side.root");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_zsplit.root");
//TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_zsplit_SIDE.root");

TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_new.root");
TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_new_side.root");

	TH1F *h2 = (TH1F*)f1->Get("h2");
	TH1F *h2_bg = (TH1F*)f2->Get("h2");
	TH1F *h2_signal=new TH1F("h2_signal","",280,0.8,5);
	h2_signal->Add(h2);
	h2_signal->Add(h2_bg,-1);

	TH1F *h2z_0 = (TH1F*)f1->Get("h2z_0");
	TH1F *h2z_0_bg = (TH1F*)f2->Get("h2z_0");
	TH1F *h2z_0_signal=new TH1F("h2z_0_signal","",280,0.8,5);
	h2z_0_signal->Add(h2z_0);
	h2z_0_signal->Add(h2z_0_bg,-1);

	TH1F *h2z_1 = (TH1F*)f1->Get("h2z_1");
	TH1F *h2z_1_bg = (TH1F*)f2->Get("h2z_1");
	TH1F *h2z_1_signal=new TH1F("h2z_1_signal","",280,0.8,5);
	h2z_1_signal->Add(h2z_1);
	h2z_1_signal->Add(h2z_1_bg,-1);

	TH1F *h2z_2 = (TH1F*)f1->Get("h2z_2");
	TH1F *h2z_2_bg = (TH1F*)f2->Get("h2z_2");
	TH1F *h2z_2_signal=new TH1F("h2z_2_signal","",280,0.8,5);
	h2z_2_signal->Add(h2z_2);
	h2z_2_signal->Add(h2z_2_bg,-1);

	TH1F *h2z_3 = (TH1F*)f1->Get("h2z_3");
	TH1F *h2z_3_bg = (TH1F*)f2->Get("h2z_3");
	TH1F *h2z_3_signal=new TH1F("h2z_3_signal","",280,0.8,5);
	h2z_3_signal->Add(h2z_3);
	h2z_3_signal->Add(h2z_3_bg,-1);


	//TFile *fout =new 	TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijet_basic_substr.root","recreate");

	TFile *fout =new 	TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_new_substr.root","recreate");

	h2_signal->Write();

	h2z_0_signal->Write();
	h2z_1_signal->Write();
	h2z_2_signal->Write();
	h2z_3_signal->Write();

	fout->Close();

	return 0;
}

