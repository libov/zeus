#include <iostream>
#include <fstream>
#include <stdio.h>
#include <canvas.cxx>

Double_t f1(Double_t *x,Double_t *par)
{
	Double_t	pT=x[0];
	Double_t	a=par[0];
	//Double_t	b=par[1];
	Double_t	b=1.00000;


	Double_t	exp=0;
	exp=TMath::Exp((-1)*pT/a);
	return	b*(1-exp);
}

Double_t f2(Double_t *x,Double_t *par)
{
	Double_t	pT=x[0];
	Double_t	a=par[0];
	Double_t	b=par[1];


	return	(1-a*(1/(pT+b)));
}

Double_t f3(Double_t *x,Double_t *par)
{
	Double_t	pT=x[0];
	Double_t	a=par[0];
	Double_t	b=par[1];
	Double_t	c=par[2];
	//Double_t	c=1;

	return	c*(TMath::ATan(pT*a+b));
}


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
	Float_t		low_theta_cut=30.0,
			up_theta_cut=150.0;
	//--
	TString		pathMC;		// path to files
	TString		pathDATA;	// path to files
	//--
	//pathDATA="/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/00p_new/res1/iters/";
	//pathDATA="/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/05ev3/res/iters/";
//pathMC="/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/dijetMC9600/res1/iters/";
	pathDATA="/data/zenith226a/libov/results/K0sK0s_trees/k0eff/MC_MEPS_NCDIS_MASSIMO/res_tght1/iters/";
	pathMC="/data/zenith226a/libov/results/K0sK0s_trees/k0eff/MC_MEPS_NCDIS_MASSIMO/res_ls/iters/";
	//--
	TString		entry1;
	TString		entry2;
	//--
	//entry1="Data 00p (PHP+DIS)";
	//entry2="MC dijet PHP 96-00p";
	entry1="MC NCDIS MEPS 05, tight";
	entry2="MC NCDIS MEPS 05, loose";
	//--

	char		name[256];
	sprintf(name,"%d_%d",(Int_t)low_theta_cut,(Int_t)up_theta_cut);
	pathDATA.Append(name);
	pathMC.Append(name);
	pathDATA.Append("/eff_da__00_xxxxxx.txt8");
	pathMC.Append("/eff_da__00_xxxxxx.txt8");
	// ---------------------------------------------------------//
	ifstream myfile1 (pathDATA);
	ifstream myfile2 (pathMC);
	//----------------------------------------------------------//

	//----------------------  Initialization -------------------//

	CreateCanvas();
	Float_t		eff_ptslow[70];
	Float_t		ptslow[70];
	Float_t		ratio[70];

	Float_t		step_pt_slow=(0.4-0.06)/68;
	Float_t		pt_slow_low,
			pt_slow_up;

	string 		line1;
	char* 		line2;

	Float_t	eff=0;
	Int_t 		n=0;
	Int_t		counter=0;


	TLine *line=new TLine(0.027,1,0.43,1);
	line->SetLineWidth(3);
	line->SetLineStyle(4);
	//----------------------------------------------------------//

	//-----------------------  READING  ------------------------//

	// myfile1
	counter=0;
	if (myfile1.is_open())
  	{
    		while (!myfile1.eof())
		{
      			getline (myfile1,line1);
			line2=line1.data();
			n=sscanf (line2,"%f",&eff);
			eff_ptslow[counter]=eff;
			counter++;

		}
		myfile1.close();
  	}

	cout<<counter<<" points"<<endl;
	for (int k=0;k<counter-1;k++)
	{
		pt_slow_low=0.06+k*step_pt_slow;
		pt_slow_up=0.06+(k+1)*step_pt_slow;
		ptslow[k]=(pt_slow_low+pt_slow_up)/2;
		cout<<k<<" "<<ptslow[k]<<" "<<eff_ptslow[k]<<endl;
	}


	TGraph	*efficiency1=new TGraph(68,ptslow,eff_ptslow);
	efficiency1->SetMarkerStyle(20);
	efficiency1->SetMarkerColor(2);
	efficiency1->SetMarkerSize(1.1);

	//myfile2
	counter=0;
	if (myfile2.is_open())
  	{
    		while (!myfile2.eof())
		{
      			getline (myfile2,line1);
			line2=line1.data();
			n=sscanf (line2,"%f",&eff);
			ratio[counter]=0;
			if (eff>0)
			{
				ratio[counter]=eff_ptslow[counter]/eff;
			}
			eff_ptslow[counter]=eff;
			counter++;

		}
		myfile2.close();
  	}

	cout<<counter<<" points"<<endl;
	for (int k=0;k<counter-1;k++)
	{
		pt_slow_low=0.06+k*step_pt_slow;
		pt_slow_up=0.06+(k+1)*step_pt_slow;
		ptslow[k]=(pt_slow_low+pt_slow_up)/2;
		cout<<k<<" "<<ptslow[k]<<" "<<eff_ptslow[k]<<endl;
	}


	TGraph	*efficiency2=new TGraph(68,ptslow,eff_ptslow);
	efficiency2->SetMarkerStyle(20);
	efficiency2->SetMarkerColor(4);
	efficiency2->SetMarkerSize(1.1);

	TGraph	*ratio_gr=new TGraph(68,ptslow,ratio);
	ratio_gr->SetMarkerStyle(20);
	ratio_gr->SetMarkerColor(6);
	ratio_gr->SetMarkerSize(1.1);


	//------------------------------------------------------------//

	//------------------- DRAWING AND FITTiNG --------------------//

	c1->Divide(2,1);

	c1->cd(1);
	efficiency1->SetTitle("Efficiency");
	efficiency1->GetXaxis()->SetTitle("p_{T}(#pi^{slow})");

	efficiency1->Draw("ap");
	efficiency2->Draw("psame");

	char range[15];
	sprintf(range,"%d<theta<%d",(Int_t)low_theta_cut,(Int_t)up_theta_cut);
	TLegend *l=new TLegend(0.4,0.2,0.89,0.49);
	l->SetHeader(range);
	l->AddEntry(efficiency1, entry1,"p");
	l->AddEntry(efficiency2, entry2,"p");
	l->SetFillColor(0);
	l->Draw("same");

	line->Draw("same");


	c1->cd(2);

	ratio_gr->Draw("ap");
	//ratio_gr->SetTitle("Ratio");
	//ratio_gr->SetTitle("Ratio Data 05e/MC dijet PHP 05e, 40<#theta<140");
	//ratio_gr->SetTitle("Ratio Data 00p/MC dijet PHP 96-00;");

	ratio_gr->SetTitle("Ratio");

	cout<<range<<endl;
	//ratio_gr->SetTitle("Ratio Data 00p/djangoh inclusive 00p, 30<#theta<150");
	ratio_gr->GetXaxis()->SetTitle("p_{T}(#pi^{slow})");
	TLegend *l2=new TLegend(0.4,0.4,0.85,0.7);
	l2->AddEntry(ratio_gr, range,"p");
	//l2->SetFillColor(0);
	l2->Draw("same");

	line->Draw("same");


	TF1 *fitfcn=new TF1("fitfcn",f1,0.1,0.4,1);
	fitfcn->SetParName(0,"a");
	fitfcn->SetParameter(0,1);
	ratio_gr->Fit("fitfcn","R");

	//TLatex latex;
   	//latex.DrawLatex(0.25,0.67,"1-a#frac{1}{p_{T}+b}");
	//latex.DrawLatex(0.25,0.67,"1-e^{- #frac{p_{T}}{a} }");
	//latex.DrawLatex(0.25,0.67,"c atan(a*p_{T}+b)");

	//------------------------------------------------------------//


	return 0;
}


