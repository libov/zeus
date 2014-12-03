#include <canvas.cxx>
int main()
{

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/ptVStheta/05_pt01.root");
	TH1F *htemp1 = (TH1F*)f1->Get("hsig");
	htemp1->SetTitle("Background Substracted K0: Data 05");
	htemp1->SetXTitle("");
	htemp1->SetYTitle("p_{T}");

TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/ptVStheta/comb_ari_meps.root");
	TH1F *htemp2 = (TH1F*)f2->Get("hsig");
	htemp2->SetTitle("Background Substracted K0: MC Meps+Ariadne 05");
	htemp2->SetXTitle("");
	htemp2->SetYTitle("p_{T}");



	CreateCanvas();
	//c1->Divide(2,1);
	//c1->cd(1);

	htemp1->Draw("box");
	//c1->cd(2);
	htemp2->Draw("samebox");
	return 0;
}