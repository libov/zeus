int main()
{
	TFile *f1 =new TFile("histograms.root/DoubleK0s_eta.root");
	Double_t 	eta[7],
			eta_err[7],
			signal1[7],
			signal2[7],
			signal1_err[7],
			signal2_err[7],
			significance1[7],
			significance2[7];

	for(Int_t cut_loop=0;cut_loop<7;cut_loop++)
	{

		Double_t 	eta_cut=2.5-cut_loop*0.25;

		eta_err[cut_loop]=0;
		eta[cut_loop]=eta_cut;
		cout<<"iterator: "<<cut_loop<<"  ABS(pseudorapidity)< "<<eta_cut<<endl;
		char 	t[30],
			t1[30],
			t3[30];
		sprintf(t,"h_%d",cut_loop);
		sprintf(t1,"h2_%d",cut_loop);
		sprintf(t3,"h3_%d",cut_loop);

		TH1F *htemp2 = (TH1F*)f1->Get(t3);
		//rebinning
		//TH1F *htemp2=new TH1F("htemp2","28.6 Mev/bin",150,0.8,5);
		//for(int j=1;j<150;j++) htemp2->SetBinContent(j,(htemp->GetBinContent(2*j)+htemp->GetBinContent(2*j-1)));
	//	htemp2->Draw();
		gStyle->SetOptFit(1111);
		TF1 *fsum=new TF1("fsum",rel_breit_wigner_exp,1.2,2.3,8);
		fsum->SetParameters(1.525,0.03,1,2000,5,1.650,5,0.03);
		//fsum->SetParameters(1.525,30,1,100,100);
		fsum->SetParNames("Mean1","HWHM1","exp slope","Constant_exp","Constant_bw1","Mean2","Constant_bw2","HWHM2");
		fsum->SetLineColor(2);
		fsum->SetLineWidth(2);
		//fsum->Draw("same");
		htemp2->Fit("fsum","R");
		//fsum->GetParameters(&par[0]);
		//fpol1->SetParameters(&par[5]);
		Double_t par[10];
		fsum->GetParameters(&par[0]);
		TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1.2,2.3,3);
		fbw1->SetParameters(par[0],par[1],par[4]);
	//	fbw1->Draw("same");

		TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,1.2,2.3,3);
		fbw2->SetParameters(par[5],par[7],par[6]);
	//	fbw2->Draw("same");

		TF1 *fexp=new TF1("fexp",exp,1.2,2.3,2);
		fexp->SetParameters(par[2],par[3]);
		fexp->SetLineColor(7);
		fexp->SetLineStyle(7);
	//	fexp->Draw("same");

		Double_t 	area_1525=(fbw1->Integral(1.400,1.626))/0.0286,
				area_1710=(fbw1->Integral(1.500,1.84))/0.0286;
		cout<<area_1525<<" "<<area_1710<<endl;
		signal1[cut_loop]=area_1525;
		signal2[cut_loop]=area_1710;
		signal1_err[cut_loop]=signal1[cut_loop]*(fsum->GetParError(4))/par[4];
		signal2_err[cut_loop]=signal2[cut_loop]*(fsum->GetParError(6))/par[6];
		significance1[cut_loop]=par[4]/(fsum->GetParError(4));
		significance2[cut_loop]=par[6]/(fsum->GetParError(6));
		//cout<<par[4]<<" "<<fsum->GetParError(4)<<endl;
	//	TF1 *fexp1=new TF1("fexp1",exp,1.2,2.3,2);
	//	fexp1->SetParameters(par[2],par[3]);
	//	fexp1->SetLineColor(4);
	//	htemp2->Fit("fexp1","R+");
		//fexp1->SetLineStyle(7);
		//fexp1->Draw("same");
	}
		cout<<"sssssssssssssss"<<endl;
		for(int i=0;i<7;i++)
		cout<<signal1[i]<<" "<<signal2[i]<<" "<<eta[i]<<endl;
		TCanvas *c=new TCanvas("c","ss",1000,1000);
		TGraph *gr1=new TGraphErrors(7,eta,signal1,eta_err,signal1_err);
		TGraph *gr2=new TGraphErrors(7,eta,signal2,eta_err,signal2_err);
		TGraph *gr3=new TGraph(7,eta,significance1);
		TGraph *gr4=new TGraph(7,eta,significance2);
		gr1->SetMarkerStyle(7);
		gr2->SetMarkerStyle(7);
		gr3->SetMarkerStyle(7);
		gr4->SetMarkerStyle(7);
		//gr1->Draw("AP");
		gr2->SetMarkerColor(4);
		gr4->SetMarkerColor(4);
		//gr2->Draw("Psame");
		gr3->Draw("ap");
		gr4->Draw("psame");

		return 0;
}
