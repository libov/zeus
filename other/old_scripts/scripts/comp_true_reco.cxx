int main()
{
	TChain *myChain=new TChain("resonance");
	//myChain->Add("/data/zenith226a/libov/myOrange/job003/run/*.root");
	myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_MCpsy_eff_v0lite.root");

	Int_t 		Nv0lite=0,
			Nk0s_ctd=0;

	myChain->SetBranchAddress("Nv0lite",&Nv0lite);
	myChain->SetBranchAddress("Nk0s_ctd",&Nk0s_ctd);
	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;
	TH1F *htrue=new TH1F("htrue","",20,0,20);
	TH1F *hreco=new TH1F("hreco","",20,0,20);
	for (int i=0;i<nevents;i++)
	{
		myChain->GetEntry(i);
		hreco->Fill(Nv0lite);
		htrue->Fill(Nk0s_ctd);
	}

	hreco->SetMarkerColor(5);
	hreco->SetStats(0);
	hreco->Sumw2();


	htrue->SetStats(0);

	htrue->SetMarkerColor(2);

	leg1 = new TLegend(0.55,0.55,0.89,0.89);
    	leg1->AddEntry(hreco,"Reconstructed, V0lite","p");
    	leg1->AddEntry(htrue,"true level K0s(both pions within CTD geometric acceptance)","p");
 	leg1->SetFillColor(0);


	htrue->Sumw2();
	htrue->Draw();
	hreco->Draw("same");
	leg1->Draw();

	return 0;
}