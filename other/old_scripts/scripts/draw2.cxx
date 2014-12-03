#include<canvas.cxx>
int main()
{
	bool				DrawSubstracted=false;
	TString			Hist="/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root";
	TString			SubstrHist="/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight_substr.root";

	//---------------------------------------------------//

	CreateCanvas("def_canv");
	TCanvas *canv=gROOT->FindObject("def_canv");

	TFile *f1 =new TFile(Hist);

	canv->Divide(2,2);

	canv->cd(1);
	TH1F *h2= (TH1F*)f1->Get("h2");
	h2->Draw();
	h2->SetMarkerStyle(20);
	h2->Sumw2();
	h2->GetXaxis()->SetRangeUser(0.8,3);

	canv->cd(2);
	TH1F *h2z_0= (TH1F*)f1->Get("h2z_0");
	h2z_0->Draw();
	h2z_0->SetMarkerStyle(20);
	h2z_0->Sumw2();
	h2z_0->GetXaxis()->SetRangeUser(0.8,3);

	canv->cd(3);
	TH1F *h2z_1= (TH1F*)f1->Get("h2z_1");
	h2z_1->Draw();
	h2z_1->SetMarkerStyle(20);
	h2z_1->Sumw2();
	h2z_1->GetXaxis()->SetRangeUser(0.8,3);


	canv->cd(4);
	TH1F *h2z_2= (TH1F*)f1->Get("h2z_2");
	h2z_2->Draw();
	h2z_2->SetMarkerStyle(20);
	h2z_2->Sumw2();
	h2z_2->GetXaxis()->SetRangeUser(0.8,3);

	if (DrawSubstracted)
	{
		TFile *f2 =new TFile(SubstrHist);
		canv->cd(1);
	TH1F *h2_signal= (TH1F*)f2->Get("h2_signal");
	h2_signal->Draw("same");
	h2_signal->SetMarkerStyle(20);
	h2_signal->SetMarkerSize(0.5);
	h2_signal->SetMarkerColor(2);
	h2_signal->Sumw2();
	h2_signal->GetXaxis()->SetRangeUser(0.8,3);

	canv->cd(2);
	TH1F *h2z_0_signal= (TH1F*)f2->Get("h2z_0_signal");
	h2z_0_signal->Draw("same");
	h2z_0_signal->SetMarkerStyle(20);
	h2z_0_signal->SetMarkerSize(0.5);
	h2z_0_signal->SetMarkerColor(2);
	h2z_0_signal->Sumw2();
	h2z_0_signal->GetXaxis()->SetRangeUser(0.8,3);

	canv->cd(3);
	TH1F *h2z_1_signal= (TH1F*)f2->Get("h2z_1_signal");
	h2z_1_signal->Draw("same");
	h2z_1_signal->SetMarkerStyle(20);
	h2z_1_signal->SetMarkerSize(0.5);
	h2z_1_signal->SetMarkerColor(2);
	h2z_1_signal->Sumw2();
	h2z_1_signal->GetXaxis()->SetRangeUser(0.8,3);


	canv->cd(4);
	TH1F *h2z_2_signal= (TH1F*)f2->Get("h2z_2_signal");
	h2z_2_signal->Draw("same");
	h2z_2_signal->SetMarkerStyle(20);
	h2z_2_signal->SetMarkerSize(0.5);
	h2z_2_signal->SetMarkerColor(2);
	h2z_2_signal->Sumw2();
	h2z_2_signal->GetXaxis()->SetRangeUser(0.8,3);
	}

return 0;
}
