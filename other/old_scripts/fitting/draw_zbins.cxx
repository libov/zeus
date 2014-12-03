#include<canvas.cxx>
int draw_zbins()
{
		TFile *f_data =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_zsplit.root","read");
		//TFile *f_data =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/15_HERAII_basic_substr.root","read");

		//TFile *f_data =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_zsplit.root","read");

		CreateCanvas("z_bins_et");
		TCanvas *c1=gROOT->FindObject("z_bins_et");
		c1->Divide(2,2);

		/*TH1F *h_data_h2z_0= (TH1F*)f_data->Get("h2z_0_signal");
		TH1F *h_data_h2z_1= (TH1F*)f_data->Get("h2z_1_signal");
		TH1F *h_data_h2z_2= (TH1F*)f_data->Get("h2z_2_signal");
		TH1F *h_data_h2z_3= (TH1F*)f_data->Get("h2z_3_signal");*/

		TH1F *h_data_h2z_0= (TH1F*)f_data->Get("h2z_0");
		TH1F *h_data_h2z_1= (TH1F*)f_data->Get("h2z_1");
		TH1F *h_data_h2z_2= (TH1F*)f_data->Get("h2z_2");
		TH1F *h_data_h2z_3= (TH1F*)f_data->Get("h2z_3");

		h_data_h2z_0->Sumw2();
		h_data_h2z_1->Sumw2();
		h_data_h2z_2->Sumw2();
		h_data_h2z_3->Sumw2();

		h_data_h2z_0->GetXaxis()->SetRangeUser(0.8,3);
		h_data_h2z_1->GetXaxis()->SetRangeUser(0.8,3);
		h_data_h2z_2->GetXaxis()->SetRangeUser(0.8,3);
		h_data_h2z_3 ->GetXaxis()->SetRangeUser(0.8,3);

		h_data_h2z_0->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
		h_data_h2z_1->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
		h_data_h2z_2->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
		h_data_h2z_3->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");




		c1->cd(1);
		h_data_h2z_0->Draw();
		c1->cd(2);
		h_data_h2z_1->Draw();
		c1->cd(3);
		h_data_h2z_2->Draw();
		c1->cd(4);
		h_data_h2z_3->Draw();

		//CreateCanvas("z_bins_et1");
		//TCanvas *c2=gROOT->FindObject("z_bins_et1");
		//c2->cd();
		//TH1F *h_data_h2z_01= (TH1F*)f_data->Get("h2z_0");
		//h_data_h2z_0->Add(h_data_h2z_1);
		//h_data_h2z_01->Draw();*/




		return 0;
}
