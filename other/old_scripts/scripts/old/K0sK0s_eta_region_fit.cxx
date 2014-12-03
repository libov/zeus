Double_t rel_breit_wigner_exp(Double_t *x,Double_t *par)
{
	// 1st Breit-Wigner
	// par[0]=peak position f(1525) meson
	// par[1]=HWHM
	// par[4]=Constant
	// 2st Breit-Wigner
	// par[5]=peak position 1750 meson
	// par[7]=HWHM
	//par[6]=constant

	// exponential C*exp(-Ax)
	//par[2]=A
	//par[3]=C
	Double_t exp=par[3]*TMath::Exp((-1)*par[2]*x[0]);
	Double_t bw1=x[0]*x[0]*par[4]/((x[0]*x[0]-par[0]*par[0])*(x[0]*x[0]-par[0]*par[0])+par[1]*par[1]*x[0]*x[0]);
	Double_t bw2=x[0]*x[0]*par[6]/((x[0]*x[0]-par[5]*par[5])*(x[0]*x[0]-par[5]*par[5])+par[7]*par[7]*x[0]*x[0]);

	return exp+bw1+bw2;

}

Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=HWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=x2*par[2]/((x2-m2)*(x2-m2)+x2*g2);
	return bw;
}

Double_t exp(Double_t *x,Double_t *par)
{
	// par[0]=slope
	// par[1]=constant
	return par[1]*TMath::Exp((-1)*par[0]*x[0]);
}
int main()
{
	TFile *f1 =new TFile("histograms.root/K0sK0s_eta_region.root");
	Double_t 	eta[7],
			eta_err[7],
			signal1[7],
			signal2[7],
			signal1_err[7],
			signal2_err[7],
			significance1[7],
			significance2[7];

	Double_t aa[3];
	for(Int_t cut_loop=0;cut_loop<3;cut_loop++)
	{

		Double_t 	eta_cut=2.5-cut_loop*0.25;

		eta_err[cut_loop]=0;
		eta[cut_loop]=eta_cut;
		cout<<"iterator: "<<cut_loop<<"  ABS(pseudorapidity)< "<<eta_cut<<endl;
		char 	t1[30],
			t2[30],
			t3[30];
		sprintf(t1,"h1_%d",cut_loop);
		sprintf(t2,"h2_%d",cut_loop);
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
		aa[cut_loop]=signal1[cut_loop];
	}
		aa[2]=0;
		aa[0]=aa[0]-aa[1];
		aa[1]=aa[1]-aa[2];
		Double_t bb[3];
		bb[0]=-1.75;
		bb[1]=0;
		bb[2]=1.75;
		Double_t aa_norm[3];
		aa_norm[0]=aa[0]/2.5;
		aa_norm[1]=aa[1]/1.0;
		aa_norm[2]=aa[2]/2.5;

		cout<<"sssssssssssssss"<<endl;
		for(int i=0;i<7;i++)
		cout<<signal1[i]<<" "<<signal2[i]<<" "<<eta[i]<<endl;
		TCanvas *c=new TCanvas("c","ss",1000,1000);
		TGraph *gr3=new TGraph(3,bb,aa);
		TGraph *gr5=new TGraph(3,bb,aa_norm);
		TGraph *gr4=new TGraph(7,eta,significance2);
		//gr1->SetMarkerStyle(7);
		//gr2->SetMarkerStyle(7);
		gr3->SetMarkerStyle(7);
		gr5->SetMarkerStyle(7);
		//gr2->SetMarkerColor(4);
		gr5->SetMarkerColor(4);

		//gr1->Draw("AP");
		//gr2->Draw("Psame");
		gr5->GetXaxis()->SetRangeUser(-10.0,10.0);
		gr5->Draw("ap");
		//gr3->Draw("ap");

		return 0;
}
