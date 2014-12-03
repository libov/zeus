#include<canvas.cxx>
int main()
{

	CreateCanvas();
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_v2.6.root");
	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/06p_COMMNTUP_v1.root");
	TFile *f3 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/07p_COMMNTUP_v1.root");


	TH1F *hf1 = (TH1F*)f1->Get("hk0k0_5_280");
	TH1F *hf2 = (TH1F*)f2->Get("hk0k0_5_280");
	TH1F *hf3 = (TH1F*)f3->Get("hk0k0_5_280");

	/*TH1F *hf1 = (TH1F*)f1->Get("hk0k0_5");
	TH1F *hf2 = (TH1F*)f2->Get("hk0k0_5");
	TH1F *hf3 = (TH1F*)f3->Get("hk0k0_5");*/




	/*c1->Divide(1,3);
	c1->cd(1);
	hf1->Draw();
	c1->cd(2);
	hf2->Draw();
	c1->cd(3);
	hf3->Draw();*/


	hf1->Sumw2();
	hf2->Sumw2();
	hf3->Sumw2();
	hf1->Add(hf2);
	hf1->Add(hf3);
	hf1->Draw();


	TFile *f4 =new TFile("/data/zenith226a/libov/results/plots/05e06p07p_280.root","recreate");
	hf1->Write();
	f4->Close();


	return 0;
}
