#include <canvas.cxx>
int main()
{

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_v2.6.root");

	TH1F *h1 = (TH1F*)f1->Get("hddlen3_1");
	TH1F *h2 = (TH1F*)f1->Get("hddlen3_2");
	TH1F *h3 = (TH1F*)f1->Get("hddlen3_3");
	TH1F *h4 = (TH1F*)f1->Get("hddlen3_4");




	CreateCanvas();
	c1->Divide(2,2);

	c1->cd(1);
	h1->Draw();

	c1->cd(2);
	h2->Draw();

	c1->cd(3);
	h3->Draw();

	c1->cd(4);
	h4->Draw();


	return 0;
}
