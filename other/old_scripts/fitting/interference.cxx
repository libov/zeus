#include<4bw_interference_twomes.cxx>
#include<canvas.cxx>
int main()
{
	gROOT->SetStyle("Plain");
	CreateCanvas("bla");
	TCanvas *c1=gROOT->FindObject("bla");
	c1->Divide(4,2);

	char str1[256];
	Int_t		n;


	Double_t	par[20];
	par[0]=1.2751;		//par[3]=1.268;
	par[1]=0.185;		//par[4]=0.176;

	par[2]=1.3183;		//par[5]=1.257;
	par[3]=0.107;		//par[6]=0.114;

	par[4]=1.525;		//par[7]=1.512;
	par[5]=0.073;		//par[8]=0.083;

	par[2]=1.300;		//par[5]=1.257;
	par[3]=0.107;		//par[6]=0.114;

	par[6]=1;


//---------------
	for (int k=0;k<4;k++)
	{
		par[2]=1.250+k*0.05;

		c1->cd(k+1);
		TString name="fsum_pos_";
		TString name2="f2_pos_";
		TString name3="f3_pos_";
		name+=k;
		name2+=k;
		name3+=k;
		par[7]=1;

		TF1 *fsum_p=new TF1(name,bw_interference,0.9,1.8,8);
		fsum_p->SetParameters(&par[0]);
		fsum_p->SetLineColor(4);
		fsum_p->SetNpx(1000);
		fsum_p->Draw("l");

		TF1 *f2_p=new TF1(name2,bw,0.9,1.8,3);
		f2_p->SetParameters(par[2],par[3],1);
		TF1 *f3_p=new TF1(name3,bw,0.9,1.8,3);
		f3_p->SetParameters(par[4],par[5],1);
		f2_p->SetNpx(1000);
		f3_p->SetNpx(1000);
		f2_p->Draw("same");
		f3_p->Draw("same");

		TPaveText *pt = new TPaveText(0.004256336,0.6876931,0.4537571,0.9966927,"brNDC");
		pt->SetFillColor(0);
		text = pt->AddText("|BW_{1}+BW_{2}|^{2}");
		n=sprintf(str1,"M_{1}= %1.3f, #Gamma_{1}= %1.3f",par[2], par[3]);
		text = pt->AddText(str1);
		n=sprintf(str1,"M_{2}= %1.3f, #Gamma_{2}= %1.3f",par[4], par[5]);
		text = pt->AddText(str1);
		pt->Draw("same");

		c1->cd(k+1+4);
		name="fsum_neg_";
		name2="f2_neg_";
		name3="f3_neg_";
		name+=k;
		name2+=k;
		name3+=k;
		par[7]=-1;

		TF1 *fsum_n=new TF1(name,bw_interference,0.9,1.8,8);
		fsum_n->SetParameters(&par[0]);
		fsum_n->SetLineColor(4);
		fsum_n->SetNpx(1000);
		fsum_n->Draw("l");

		TF1 *f2_n=new TF1(name2,bw,0.9,1.8,3);
		f2_n->SetParameters(par[2],par[3],1);
		TF1 *f3_n=new TF1(name3,bw,0.9,1.8,3);
		f3_n->SetParameters(par[4],par[5],1);
		f2_n->SetNpx(1000);
		f3_n->SetNpx(1000);
		f2_n->Draw("same");
		f3_n->Draw("same");

		TPaveText *pt = new TPaveText(0.004256336,0.6876931,0.4537571,0.9966927,"brNDC");
		pt->SetFillColor(0);
		text = pt->AddText("|BW_{1}-BW_{2}|^{2}");
		n=sprintf(str1,"M_{1}= %1.3f, #Gamma_{1}= %1.3f",par[2], par[3]);
		text = pt->AddText(str1);
		n=sprintf(str1,"M_{2}= %1.3f, #Gamma_{2}= %1.3f",par[4], par[5]);
		text = pt->AddText(str1);
		pt->Draw("same");
	}




	/*TF1 *f1=new TF1("f1",bw,0.9,2,3);
	f1->SetParameters(par[0],par[1],25);
	TF1 *f2=new TF1("f2",bw,0.9,2,3);
	f2->SetParameters(par[2],par[3],1);
	TF1 *f3=new TF1("f3",bw,0.9,2,3);
	f3->SetParameters(par[4],par[5],1);*/



//-----------------------------

/*	TH1F *h_L3=new TH1F ("h_L3","",60,1.005,2.805);
	h_L3->SetBinContent(1,1);
	h_L3->SetBinContent(2,5);
	h_L3->SetBinContent(3,3);
	h_L3->SetBinContent(4,3);
	h_L3->SetBinContent(5,10);
	h_L3->SetBinContent(6,14);
	h_L3->SetBinContent(7,17);
	h_L3->SetBinContent(8,30);
	h_L3->SetBinContent(9,33);
	h_L3->SetBinContent(10,15);
	h_L3->SetBinContent(11,12);
	h_L3->SetBinContent(12,8);
	h_L3->SetBinContent(13,11);
	h_L3->SetBinContent(14,10);
	h_L3->SetBinContent(15,20);
	h_L3->SetBinContent(16,39);
	h_L3->SetBinContent(17,67);
	h_L3->SetBinContent(18,60);
	h_L3->SetBinContent(19,43);
	h_L3->SetBinContent(20,44);
	h_L3->SetBinContent(21,25);
	h_L3->SetBinContent(22,21);
	h_L3->SetBinContent(23,21);
	h_L3->SetBinContent(24,20);
	h_L3->SetBinContent(25,27);
	h_L3->SetBinContent(26,35);
	h_L3->SetBinContent(27,28);
	h_L3->SetBinContent(28,16);
	h_L3->SetBinContent(29,12);
	h_L3->SetBinContent(30,14);
	h_L3->SetBinContent(31,11);
	h_L3->SetBinContent(32,7);
	h_L3->SetBinContent(33,9);
	h_L3->SetBinContent(34,12);
	h_L3->SetBinContent(35,8);
	h_L3->SetBinContent(36,6);
	h_L3->SetBinContent(37,7);
	h_L3->SetBinContent(38,7);

	h_L3->SetBinContent(39,5);
	h_L3->SetBinContent(40,7);
	h_L3->SetBinContent(41,3);
	h_L3->SetBinContent(42,6);
	h_L3->SetBinContent(43,6);
	h_L3->SetBinContent(44,2);
	h_L3->SetBinContent(45,3);
	h_L3->SetBinContent(46,8);
	h_L3->SetBinContent(47,2);
	h_L3->SetBinContent(48,2);
	h_L3->SetBinContent(49,5);
	h_L3->SetBinContent(50,3);
	h_L3->SetBinContent(51,2);
	h_L3->SetBinContent(52,1);
	h_L3->Draw();

	fsum->Draw("samel");
	TFile *file_out =new TFile("L3_data.root","recreate");
	h_L3->Write();
	file_out->Close();

*/
	return 0;
}
