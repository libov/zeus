#include <canvas.cxx>
int main()
{
	CreateCanvas();
	//c1->Divide(2,2);

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_v2.2.root","read");

	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_MC_test.root","read");


 	//c1->cd(1);
	//TH1F *hk0k0_data= (TH1F*)f1->Get("h3");
	//TH1F *hk0k0_MC= (TH1F*)f2->Get("h3");

	TH1F *hk0k0_data= (TH1F*)f1->Get("hk0k0_4");
	TH1F *hk0k0_MC= (TH1F*)f2->Get("hk0k0_4");

	leg1 = new TLegend(0.55,0.55,0.89,0.89);
    	leg1->AddEntry(hk0k0_data,"Data 05e- PHP+DIS","p");
    	leg1->AddEntry(hk0k0_MC,"Dijet MC PHP 05e-","f");
 	leg1->SetFillColor(0);

	hk0k0_MC->Sumw2();
	Double_t integral=hk0k0_MC->Integral();
	hk0k0_MC->Scale((hk0k0_data->Integral())/integral);
	hk0k0_data->SetMarkerStyle(20);
	hk0k0_MC->SetFillColor(5);
	hk0k0_MC->Draw("HIST");
	hk0k0_data->Draw("same E");
	leg1->Draw();


	return 0;
}