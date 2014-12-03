int main()
{

	//TF1 *fpol=new TF1("fpol","pol0",0.99,4);
	TF1 *fpol=new TF1("fpol","landau(0)",0.99,10);
	fpol->SetParameters(100,5,1);
	fpol->Draw("pl");
	return 0;
}
