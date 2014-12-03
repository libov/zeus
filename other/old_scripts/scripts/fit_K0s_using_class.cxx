#include<canvas.cxx>
#include<K0s_fit.h>
#include<K0s_fit.cxx>
/////////////////////
//  F i t t i n g  //
//       o f	   //
//      K 0 s      //
//    invariant    //
//      mass       //
//  distribution   //
/////////////////////
//
// Vladyslav Libov(KNU)
// (using K0s_fit class)

int main()
{


	CreateCanvas();
	//c1->Divide(2,1);

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/temporary/00p_new.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_find_comp_00p.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_SLcut_05COMNTUP.root","UPDATE");

	//TH1F *h_V0 = (TH1F*)f1->Get("h_V0");
	//TH1F *h_V0_SL = (TH1F*)f1->Get("h_V0_SL");
	//TH1F *h_V0lite = (TH1F*)f1->Get("h_V0lite");
	//TH1F *h_V0lite_SL3 = (TH1F*)f1->Get("h_V0lite_SL3");
	//TH1F *h_V0lite_SL5 = (TH1F*)f1->Get("h_V0lite_SL5");
	//TH1F *h_V0lite_SL7 = (TH1F*)f1->Get("h_V0lite_SL7");
	//TH1F *h_V0psy = (TH1F*)f1->Get("h_V0psy");

	//h_V0->Draw();

	//K0s_fit		V0_fit(h_V0);
	//K0s_fit		V0_SL_fit(h_V0_SL);
	//K0s_fit		V0lite_fit(h_V0lite);
	//K0s_fit		V0lite_SL3_fit(h_V0lite_SL3);
	//K0s_fit		V0lite_SL5_fit(h_V0lite_SL5);
	//K0s_fit		V0lite_SL7_fit(h_V0lite_SL7);
	//K0s_fit		V0psy_fit(h_V0psy);

	//c1->cd(1);
	//V0lite_fit.Fit();
	//c1->cd(2);
	//V0lite_SL3_fit.Fit();
	//V0lite_SL5_fit.Fit();
	//V0lite_SL7_fit.Fit();
	//V0_fit.Fit();

	TH1F *hinv_K0s = (TH1F*)f1->Get("hinv_K0s");
	K0s_fit		V0_fit(hinv_K0s);
	V0_fit.Fit();


	//TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_find_comp_00pOUT.root","recreate");
	//c1->Write();
	//f2->Close();

	//h_V0lite->Write();
	//h_V0lite_SL3->Write();
	//h_V0lite_SL5->Write();
	//h_V0lite_SL7->Write();



	return 0;
}

