int main()
{

	TRandom		*uni=new TRandom();
	TH1F *h=new TH1F("h","Normal distribution",300,-5,5);

	for (int i=0; i<1000;i++)
	{
		h->Fill(uni->Gaus(1,0.5));
	}

	for (int i=0; i<500;i++)
	{
		h->Fill(uni->Gaus(3,0.7));
	}

	TFile *f1 =new TFile("toy_norm.root","recreate");
	h->Write();
	return 0;
}
