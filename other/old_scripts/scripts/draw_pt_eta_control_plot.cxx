#include<canvas.cxx>
int draw_pt_eta_control_plot()
{
	gStyle->SetTitleSize(0.06,"x");
	gStyle->SetTitleSize(0.06,"y");
	gStyle->SetTitleOffset(0.8,"x");
	gStyle->SetTitleOffset(0.8,"y");

	CreateCanvas("coll_cuts");
	TCanvas *c1=gROOT->FindObject("coll_cuts");
	c1->Divide(2,1);

	TFile *f_data =new TFile("data_zfiles.root");
	TFile *f_MC =new TFile("MC_data_zfiles.root");

	TH1F *h_pt_data = (TH1F*)f_data->Get("h_pt");
	h_pt_data->SetMarkerStyle(20);
	TH1F *h_pt_MC = (TH1F*)f_MC->Get("h_pt");
	h_pt_MC->SetFillColor(5);


	TH1F *h_eta_data = (TH1F*)f_data->Get("h_eta");
	h_eta_data->SetMarkerStyle(20);
	TH1F *h_eta_MC = (TH1F*)f_MC->Get("h_eta");
	h_eta_MC->SetFillColor(5);

	c1->cd(1);
	h_pt_data->Draw();
	h_pt_MC->Draw("same");
	leg1 = new TLegend(0.55,0.55,0.89,0.89);
	leg1->AddEntry(h_pt_data,"Data","p");
	leg1->AddEntry(h_pt_MC,"Monte Carlo","l");
	leg1->SetFillColor(0);
	leg1->Draw("same");

	c1->cd(2);
	h_eta_data->Draw();
	h_eta_MC->Draw("same");
	leg2 = new TLegend(0.55,0.55,0.89,0.89);
	leg2->AddEntry(h_eta_data,"Data","p");
	leg2->AddEntry(h_eta_MC,"Monte Carlo","l");
	leg2->SetFillColor(0);
	leg2->Draw("same");





	return 0;
}