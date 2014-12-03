#include<4bw_interference_NONREL.cxx>
int main()
{

	TF1 *fsum=new TF1("fsum",bw_interference,0.9,2.7,7);
	Double_t	par[20];

	par[0]=1.275;//par[3]=1.268;
	par[1]=0.185;//par[4]=0.176;
	par[2]=1.318;//par[5]=1.257;
	par[3]=0.107;//par[6]=0.114;
	par[4]=1.525;//par[7]=1.512;
	par[5]=0.073;//par[8]=0.083;

	par[6]=1;

	fsum->SetParameters(&par[0]);
	fsum->Draw("al");

	TF1 *f1=new TF1("f1",bw,0.9,2.7,3);
	f1->SetParameters(par[0],par[1],25);

	TF1 *f2=new TF1("f2",bw,0.9,2.7,3);
	f2->SetParameters(par[2],par[3],9);

	TF1 *f3=new TF1("f3",bw,0.9,2.7,3);
	f3->SetParameters(par[4],par[5],4);

	f1->SetLineColor(4);
	f2->SetLineColor(4);
	f3->SetLineColor(4);

	f1->SetLineWidth(1);
	f2->SetLineWidth(1);
	f3->SetLineWidth(1);

	f1->Draw("same");
	f2->Draw("same");
	f3->Draw("same");


	return 0;
}
