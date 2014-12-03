#include<canvas.cxx>
int main()
{
	CreateCanvas();

	c1->Divide(2,1);
	TFile *f1=new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_TRACKING.root","read");
	TH2F *hsec1 = (TH2F*)f1->Get("hsec1");
	TH2F *hsec2 = (TH2F*)f1->Get("hsec2");
	hsec1->GetXaxis()->SetTitle("X, cm");
	hsec1->GetYaxis()->SetTitle("Y, cm");
	hsec2->GetXaxis()->SetTitle("X, cm");
	hsec2->GetYaxis()->SetTitle("Y, cm");
	hsec1->GetXaxis()->SetRangeUser(-10,10);
	hsec1->GetYaxis()->SetRangeUser(-10,10);
	hsec2->GetXaxis()->SetRangeUser(-10,10);
	hsec2->GetYaxis()->SetRangeUser(-10,10);

	c1->cd(1);
	hsec1->Draw();
	c1->cd(2);
	hsec2->Draw();


	/*c1->Divide(3,2);
	TFile *f1=new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_TRUE.root","read");
	TH1F *h_comp_prim_x = (TH1F*)f1->Get("h_comp_prim_x");
	TH1F *h_comp_prim_y = (TH1F*)f1->Get("h_comp_prim_y");
	TH1F *h_comp_prim_z = (TH1F*)f1->Get("h_comp_prim_z");
	TH1F *h_comp_sec_x = (TH1F*)f1->Get("h_comp_sec_x");
	TH1F *h_comp_sec_y = (TH1F*)f1->Get("h_comp_sec_y");
	TH1F *h_comp_sec_z = (TH1F*)f1->Get("h_comp_sec_z");
	c1->cd(1);
	h_comp_prim_x->Draw();
	c1->cd(2);
	h_comp_prim_y->Draw();
	c1->cd(3);
	h_comp_prim_z->Draw();
	c1->cd(4);
	h_comp_sec_x->Draw();
	c1->cd(5);
	h_comp_sec_y->Draw();
	c1->cd(6);
	h_comp_sec_z->Draw();*/

	/*c1->Divide(2,1);
	TFile *f1=new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_TRUE.root","read");
	TH1F *hinv_K0s_true = (TH1F*)f1->Get("hinv_K0s_true");
	TH1F *hinv_K0s_reco = (TH1F*)f1->Get("hinv_K0s_reco");
	c1->cd(1);
	hinv_K0s_true->Draw();
	c1->cd(2);
	hinv_K0s_reco->Draw();*/
	/*c1->Divide(2,1);
	TFile *f1=new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_TRUE.root","read");
	TH1F *hcoll3 = (TH1F*)f1->Get("hcoll3");
	TH1F *hcoll3_mat = (TH1F*)f1->Get("hcoll3_mat");
	c1->cd(1);
	hcoll3->Draw();
	c1->cd(2);
	hcoll3_mat->Draw();*/


	return 0;
}
