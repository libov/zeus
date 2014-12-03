#include<canvas.cxx>
int main()
{
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight.root");

	TH1F *hz0 = (TH1F*)f1->Get("hz_0");
	TH1F *hz1 = (TH1F*)f1->Get("hz_1");
	TH1F *hz2 = (TH1F*)f1->Get("hz_2");

	CreateCanvas();
	//hz2->Add(hz1);
	hz0->Draw();
	//h3_signal->Add(h3);
	//h3_signal->Add(h3_bg,-1);


	return 0;
}

