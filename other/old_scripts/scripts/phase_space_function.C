Double_t		mK0=0.497672;
int phase_space_function()
{
	TF1 *ps_1=new TF1("ps_1",ps,0.9,5,1);
	ps_1->SetParameter(0,0);
	ps_1->Draw("al");
	ps_1->SetLineColor(2);
	TF1 *ps_2=new TF1("ps_2",ps,0.9,5,1);
	ps_2->SetParameter(0,-0.5);
	ps_2->Draw("same");

	TF1 *ps_3=new TF1("ps_3",ps,0.9,5,1);
	ps_3->SetParameter(0,-1);
	ps_3->Draw("same");

	return 0;
}

Double_t	ps(Double_t *x, Double_t *par)
{
	// A->BB
	Double_t		m_A=x[0];
	Double_t		m_B=mK0;
	Double_t		diff_B=(m_A/2)**2-m_B**2;
	Double_t		diff_massless=(m_A/2)**2;
	if (diff_B<0)	return 0;
	cout<<par[0]<<endl;
	Double_t		ps=(TMath::Power(diff_massless,par[0]))*sqrt((m_A/2)**2-m_B**2);

	return 		ps;
}
