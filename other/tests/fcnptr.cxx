int fcnptr()
{
	TMinuit *bla=new TMinuit(3);
	bla->SetFCN(fcn);
	return 0;
}

void fcn(Int_t& npar, Double_t* grad, Double_t& f, Double_t par[], Int_t iflag)
{
	f=0.2;
}