#include <canvas.cxx>
int main()
{


	// -------------------------------------- //
	// DO NOT FORGET TO CHANGE:		  //
	//	1. Angle range			  //
	//	2. Path to files		  //
	//	3. entry1 and entry2 for titles   //
	// -------------------------------------- //

	//----------------  Choose files to compare ----------------//
	//--
	Float_t		low_theta_cut=40.0,
			up_theta_cut=140.0;
	//--
	TString		pathMC;		// path to files
	TString		pathDATA;	// path to files
	//--
	pathDATA="/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/00p_new/res/";
	pathMC="/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/dijetMC9600/res/";
	//--

	char		range[256];
	TString 	name;
	name="rest";
	sprintf(range,"%d_%d",(Int_t)low_theta_cut,(Int_t)up_theta_cut);
	name.Append(range);
	name.Append(".root");
	pathDATA.Append(name);
	pathMC.Append(name);
	cout<<"input files:"<<endl;
	cout<<pathDATA<<endl;
	cout<<pathMC<<endl;

	TFile *f1 =new TFile(pathDATA,"read");
	TFile *f2 =new TFile(pathMC,"read");
	//--
	TString		entry1;
	TString		entry2;
	//--
	entry1="Data 00p (PHP+DIS)";
	entry2="MC dijet PHP 96-00p";
	//--

	Int_t	choice=0;


	cout<<"What do You want to build?"<<endl;
	cout<<"1 = pT (projection)"<<endl;
	cout<<"2 = theta (projection)"<<endl;
	cout<<"3 = pT (slices)"<<endl;
	cout<<"4 = theta (slices)"<<endl;
	cout<<"5 = e-pz"<<endl;
	cout<<"6 = zvtx"<<endl;
	cout<<"7 = y_jb"<<endl;
	cout<<"8 = quit"<<endl;

	cin>>choice;

	CreateCanvas();
	// pT(K0) distribution data/mc comparison
	if (choice==1)
	{
		TH1F *h_pt1= (TH1F*)f1->Get("h_pt");
		TH1F *h_pt2= (TH1F*)f2->Get("h_pt");

		h_pt1->SetStats(0);
		h_pt2->SetStats(0);

		leg = new TLegend(0.55,0.55,0.89,0.89);
    		leg->AddEntry(h_pt1,entry1,"p");
    		leg->AddEntry(h_pt2,entry2,"f");
 		leg->SetHeader("   p_{T}(K^{0}) distribution   ");
		leg->SetFillColor(0);

		h_pt2->Sumw2();
		Double_t integral=h_pt2->Integral();
		h_pt2->Scale((h_pt1->Integral())/integral);


		h_pt1->SetMarkerStyle(20);
		h_pt2->SetFillColor(5);
		h_pt1->SetXTitle("p_{T}");
		h_pt2->Draw("HIST");
		h_pt1->Draw("same E");
		leg->Draw();

		cout<<h_pt1->Integral()<<" K0s in data"<<endl;
		cout<<h_pt2->Integral()<<" K0s in MC"<<endl;
	}


	// theta(K0) distribution data/mc comparison
	if (choice==2)
	{
		TH1F *h_th1= (TH1F*)f1->Get("h_th");
		TH1F *h_th2= (TH1F*)f2->Get("h_th");
		h_th1->SetStats(0);
		h_th2->SetStats(0);

		leg1 = new TLegend(0.55,0.55,0.89,0.89);
    		leg1->AddEntry(h_th1,entry1,"p");
    		leg1->AddEntry(h_th2,entry2,"f");
 		leg1->SetHeader("  #theta(K^{0}) distribution   ");
		leg1->SetFillColor(0);
		h_th1->SetXTitle("#theta");
		h_th1->SetTitle("#theta(K^{0}) distribution");


		h_th2->Sumw2();
		Double_t integral=h_th2->Integral();
		h_th2->Scale((h_th1->Integral())/integral);

		h_th1->SetMarkerStyle(20);
		h_th2->SetFillColor(5);
		h_th2->Draw("HIST");
		h_th1->Draw("same E");
		leg1->Draw();

		cout<<h_th1->Integral()<<" K0s in data"<<endl;
		cout<<h_th2->Integral()<<" K0s in MC"<<endl;
	}

	// pT distributions in theta slices
	if (choice==3)
	{
		c1->Divide(2,2);
		TH1F *h_pt1_1= (TH1F*)f1->Get("h_pt_1");
		TH1F *h_pt1_2= (TH1F*)f1->Get("h_pt_2");
		TH1F *h_pt1_3= (TH1F*)f1->Get("h_pt_3");
		TH1F *h_pt1_4= (TH1F*)f1->Get("h_pt_4");
		h_pt1_1->SetStats(0);
		h_pt1_2->SetStats(0);
		h_pt1_3->SetStats(0);
		h_pt1_4->SetStats(0);
		TH1F *h_pt2_1= (TH1F*)f2->Get("h_pt_1");
		TH1F *h_pt2_2= (TH1F*)f2->Get("h_pt_2");
		TH1F *h_pt2_3= (TH1F*)f2->Get("h_pt_3");
		TH1F *h_pt2_4= (TH1F*)f2->Get("h_pt_4");
		h_pt2_1->SetStats(0);
		h_pt2_2->SetStats(0);
		h_pt2_3->SetStats(0);
		h_pt2_4->SetStats(0);

		c1->cd(1);
		h_pt1_1->SetXTitle("p_{T}");
		h_pt2_1->Sumw2();
		Double_t integral=h_pt2_1->Integral();
		h_pt2_1->Scale((h_pt1_1->Integral())/integral);

		leg1 = new TLegend(0.55,0.55,0.89,0.89);
    		leg1->AddEntry(h_pt1_1,entry1,"p");
    		leg1->AddEntry(h_pt2_1,entry2,"f");
 		leg1->SetFillColor(0);


		h_pt1_1->SetMarkerStyle(20);
		h_pt2_1->SetFillColor(5);
		h_pt2_1->Draw("HIST");
		h_pt1_1->Draw("same E");
		leg1->Draw();

		c1->cd(2);
		h_pt1_2->SetXTitle("p_{T}");
		h_pt2_2->Sumw2();
		Double_t integral=h_pt2_2->Integral();
		h_pt2_2->Scale((h_pt1_2->Integral())/integral);



		h_pt1_2->SetMarkerStyle(20);
		h_pt2_2->SetFillColor(5);
		h_pt2_2->Draw("HIST");
		h_pt1_2->Draw("same E");
		leg1->Draw();

		c1->cd(3);
		h_pt1_3->SetXTitle("p_{T}");

		h_pt1_3->Draw();
		h_pt2_3->Sumw2();
		Double_t integral=h_pt2_3->Integral();
		h_pt2_3->Scale((h_pt1_3->Integral())/integral);

		h_pt1_3->SetMarkerStyle(20);
		h_pt2_3->SetFillColor(5);
		h_pt2_3->Draw("HIST");
		h_pt1_3->Draw("same E");
		leg1->Draw();

		c1->cd(4);
		h_pt1_4->SetXTitle("p_{T}");

		h_pt2_4->Sumw2();
		Double_t integral=h_pt2_4->Integral();
		h_pt2_4->Scale((h_pt1_4->Integral())/integral);

		h_pt1_4->SetMarkerStyle(20);
		h_pt2_4->SetFillColor(5);
		h_pt2_4->Draw("HIST");
		h_pt1_4->Draw("same E");
		leg1->Draw();
	}


	// theta distributions in pt slices
	if (choice==4)
	{
		c1->Divide(2,2);
		TH1F *h_th1_1= (TH1F*)f1->Get("h_th_1");
		TH1F *h_th1_2= (TH1F*)f1->Get("h_th_2");
		TH1F *h_th1_3= (TH1F*)f1->Get("h_th_3");
		TH1F *h_th1_4= (TH1F*)f1->Get("h_th_4");
		h_th1_1->SetStats(0);
		h_th1_2->SetStats(0);
		h_th1_3->SetStats(0);
		h_th1_4->SetStats(0);
		TH1F *h_th2_1= (TH1F*)f2->Get("h_th_1");
		TH1F *h_th2_2= (TH1F*)f2->Get("h_th_2");
		TH1F *h_th2_3= (TH1F*)f2->Get("h_th_3");
		TH1F *h_th2_4= (TH1F*)f2->Get("h_th_4");
		h_th2_1->SetStats(0);
		h_th2_2->SetStats(0);
		h_th2_3->SetStats(0);
		h_th2_4->SetStats(0);

		c1->cd(1);
		h_th1_1->SetXTitle("#theta");

		h_th2_1->Sumw2();
		Double_t integral=h_th2_1->Integral();
		h_th2_1->Scale((h_th1_1->Integral())/integral);
		leg1 = new TLegend(0.55,0.55,0.89,0.89);
    		leg1->AddEntry(h_th1_1,entry1,"p");
    		leg1->AddEntry(h_th2_1,entry2,"f");
 		leg1->SetFillColor(0);
		h_th1_1->SetMarkerStyle(20);
		h_th2_1->SetFillColor(5);
		h_th2_1->Draw("HIST");
		h_th1_1->Draw("same E");
		leg1->Draw();

		c1->cd(2);
		h_th1_2->SetXTitle("#theta");
		h_th2_2->Sumw2();
		Double_t integral=h_th2_2->Integral();
		h_th2_2->Scale((h_th1_2->Integral())/integral);
		leg1 = new TLegend(0.55,0.55,0.89,0.89);
    		leg1->AddEntry(h_th1_2,entry1,"p");
    		leg1->AddEntry(h_th2_2,entry2,"f");
 		leg1->SetFillColor(0);
		h_th1_2->SetMarkerStyle(20);
		h_th2_2->SetFillColor(5);
		h_th2_2->Draw("HIST");
		h_th1_2->Draw("same E");
		leg1->Draw();

		c1->cd(3);
		h_th1_3->SetXTitle("#theta");
		h_th2_3->Sumw2();
		Double_t integral=h_th2_3->Integral();
		h_th2_3->Scale((h_th1_3->Integral())/integral);
		leg1 = new TLegend(0.55,0.55,0.89,0.89);
    		leg1->AddEntry(h_th1_3,entry1,"p");
    		leg1->AddEntry(h_th2_3,entry2,"f");
 		leg1->SetFillColor(0);
		h_th1_3->SetMarkerStyle(20);
		h_th2_3->SetFillColor(5);
		h_th2_3->Draw("HIST");
		h_th1_3->Draw("same E");
		leg1->Draw();

		c1->cd(4);
		h_th1_4->SetXTitle("#theta");
		h_th2_4->Sumw2();
		Double_t integral=h_th2_4->Integral();
		h_th2_4->Scale((h_th1_4->Integral())/integral);
		leg1 = new TLegend(0.55,0.55,0.89,0.89);
    		leg1->AddEntry(h_th1_4,entry1,"p");
    		leg1->AddEntry(h_th2_4,entry2,"f");
 		leg1->SetFillColor(0);
		h_th1_4->SetMarkerStyle(20);
		h_th2_4->SetFillColor(5);
		h_th2_4->Draw("HIST");
		h_th1_4->Draw("same E");
		leg1->Draw();
	}
	if (choice==5)
	{
		TH1F *h_e_pz1= (TH1F*)f1_ev->Get("h_e_pz");
		TH1F *h_e_pz2= (TH1F*)f2_ev->Get("h_e_pz");
		h_e_pz1->SetStats(0);
		h_e_pz2->SetStats(0);

		leg = new TLegend(0.55,0.55,0.89,0.89);
    		leg->AddEntry(h_e_pz1,entry1,"p");
    		leg->AddEntry(h_e_pz2,entry2,"f");
 		leg->SetHeader("   E-p_{z} distribution   ");
		leg->SetFillColor(0);

		h_e_pz2->Sumw2();
		Double_t integral=h_e_pz2->Integral();
		h_e_pz2->Scale((h_e_pz1->Integral())/integral);


		h_e_pz1->SetMarkerStyle(20);
		h_e_pz2->SetFillColor(5);
		h_e_pz1->SetXTitle("E-p_{z}");
		h_e_pz2->Draw("HIST");
		h_e_pz1->Draw("same E");
		leg->Draw();
	}
	if (choice==6)
	{
		TH1F *h_zvtx1= (TH1F*)f1_ev->Get("h_zvtx");
		TH1F *h_zvtx2= (TH1F*)f2_ev->Get("h_zvtx");
		h_zvtx1->SetStats(0);
		h_zvtx2->SetStats(0);

		leg = new TLegend(0.55,0.55,0.89,0.89);
    		leg->AddEntry(h_zvtx1,entry1,"p");
    		leg->AddEntry(h_zvtx2,entry2,"f");
 		leg->SetHeader("   Z_{vtx} distribution   ");
		leg->SetFillColor(0);

		h_zvtx2->Sumw2();
		Double_t integral=h_zvtx2->Integral();
		h_zvtx2->Scale((h_zvtx1->Integral())/integral);


		h_zvtx1->SetMarkerStyle(20);
		h_zvtx2->SetFillColor(5);
		h_zvtx1->SetXTitle("Z_{vtx}");
		h_zvtx2->Draw("HIST");
		h_zvtx1->Draw("same E");
		leg->Draw();
	}

	if (choice==7)
	{
		TH1F *h_yjb1= (TH1F*)f1_ev->Get("h_yjb");
		TH1F *h_yjb2= (TH1F*)f2_ev->Get("h_yjb");
		h_yjb1->SetStats(0);
		h_yjb2->SetStats(0);

		leg = new TLegend(0.55,0.55,0.89,0.89);
    		leg->AddEntry(h_yjb1,entry1,"p");
    		leg->AddEntry(h_yjb2,entry2,"f");
 		leg->SetHeader("   y_{jb} distribution   ");
		leg->SetFillColor(0);

		h_yjb2->Sumw2();
		Double_t integral=h_yjb2->Integral();
		h_yjb2->Scale((h_yjb1->Integral())/integral);


		h_yjb1->SetMarkerStyle(20);
		h_yjb2->SetFillColor(5);
		h_yjb1->SetXTitle("y_{jb}");
		h_yjb2->Draw("HIST");
		h_yjb1->Draw("same E");
		leg->Draw();
	}
	if (choice==8)
	{
		return 0;
	}

}
