int true_xSect_test()
{
	TString		RefSampleCharm0607p="mc07pv02e.rgap3.nc.c.";
	TString		RefSampleBeauty0607p="mc07pv02e.rgap3.nc.b.q2g1.p";

	TString		RefSampleCharm06e="mc06ev02e.rgap3.nc.ccdir.e.q2g4";
	TString		RefSampleBeauty06e="mc06ev02e.rgap3.nc.bbdir.e.q2g1.";

	Double_t		RefSampleCharmLumi0607p = 498.034;
	Double_t		RefSampleBeautyLumi0607p = 2577.978;

	Double_t		RefSampleCharmLumi06e = 166.303;
	Double_t		RefSampleBeautyLumi06e = 912.499;

	TString HISTO_PATH = getenv("HISTO_PATH");

	//TString HistogramsVersion = "inclusive.v1.1";
	//TString HistogramsVersion = "inclusive.v1.2"

	TString HistogramsVersion = "inclusive.v1.5";
	//TString HistogramsVersion = "all.v1.1";

	//TFile			*fCharm0607p = new TFile(HISTO_PATH+"/analysis."+RefSampleCharm0607p+"."+HistogramsVersion+".root", "read");
	TFile			*fBeauty0607p = new TFile(HISTO_PATH+"/analysis."+RefSampleBeauty0607p+"."+HistogramsVersion+".root", "read");

	//TFile			*fCharm06e = new TFile(HISTO_PATH+"/analysis."+RefSampleCharm06e+"."+HistogramsVersion+".root", "read");
	TFile			*fBeauty06e = new TFile(HISTO_PATH+"/analysis."+RefSampleBeauty06e+"."+HistogramsVersion+".root", "read");


	//----------- TRUE CROSS SECTION CALCULATION -------------//





	// -- jets after cuts
	const TString HistoNameTrueJets="bin1/truejets";
	//-- charm
	/*Float_t		jets_c0607p = (Float_t)(((TH1F*)fCharm0607p->Get(HistoNameTrueJets))->GetEntries()) / RefSampleCharmLumi0607p;
	Float_t		jets_c06e = (Float_t)(((TH1F*)fCharm06e->Get(HistoNameTrueJets))->GetEntries()) / RefSampleCharmLumi06e;
	cout<<"charm"<<endl;
	cout<<"sigma {Jet(Et>5, |eta|<2.5)} = "<<jets_c06e<<" (06e) "<<jets_c0607p<<" (0607p) "<<endl;
	cout<<" relative difference: "<<100*(jets_c06e - jets_c0607p)/jets_c06e<<endl;*/
	//-- beauty
	Float_t		jets_b0607p = (Float_t)(((TH1F*)fBeauty0607p->Get(HistoNameTrueJets))->GetEntries()) / RefSampleBeautyLumi0607p;
	Float_t		jets_b06e = (Float_t)(((TH1F*)fBeauty06e->Get(HistoNameTrueJets))->GetEntries()) / RefSampleBeautyLumi06e;
	cout<<"beauty"<<endl;
	cout<<"sigma {Jet(Et>5, |eta|<2.5)} = "<<jets_b06e<<" (06e), "<<jets_b0607p<<" (0607p) "<<endl;
	cout<<" relative difference: "<<100*(jets_b06e - jets_b0607p)/jets_b06e<<endl;

	// -- # of jets before et/eta cuts
	const TString HistoNameTrueJetsALL="bin1/truejetsALL";
	//-- charm
	/*Float_t		jetsALL_c0607p = (Float_t)(((TH1F*)fCharm0607p->Get(HistoNameTrueJetsALL))->GetEntries()) / RefSampleCharmLumi0607p;
	Float_t		jetsALL_c06e = (Float_t)(((TH1F*)fCharm06e->Get(HistoNameTrueJetsALL))->GetEntries()) / RefSampleCharmLumi06e;
	cout<<"charm"<<endl;
	cout<<"sigma {Jet(no cuts)} = "<<jetsALL_c06e<<" (06e) "<<jetsALL_c0607p<<" (0607p) "<<endl;
	cout<<" relative difference: "<<100*(jetsALL_c06e - jetsALL_c0607p)/jetsALL_c06e<<endl;*/


	Float_t		jetsALL_b0607p = (Float_t)(((TH1F*)fBeauty0607p->Get(HistoNameTrueJetsALL))->GetEntries()) / RefSampleBeautyLumi0607p;
	Float_t		jetsALL_b06e = (Float_t)(((TH1F*)fBeauty06e->Get(HistoNameTrueJetsALL))->GetEntries()) / RefSampleBeautyLumi06e;
	cout<<"beauty"<<endl;
	cout<<"sigma {Jet(no cuts)} = "<<jetsALL_b06e<<" (06e) "<<jetsALL_b0607p<<" (0607p) "<<endl;
	cout<<" relative difference: "<<100*(jetsALL_b06e - jetsALL_b0607p)/jetsALL_b06e<<endl;

	//	-- # of events satisfying 5<Q2<1000, 0.02<y<0.7
	const TString HistoNameTrueEvents="bin1/eventsInFiducial";
	// -- charm
	/*Float_t		events_c0607p = (Float_t)(((TH1F*)fCharm0607p->Get(HistoNameTrueEvents))->GetEntries()) / RefSampleCharmLumi0607p;
	Float_t		events_c06e = (Float_t)(((TH1F*)fCharm06e->Get(HistoNameTrueEvents))->GetEntries()) / RefSampleCharmLumi06e;
	cout<<"charm"<<endl;
	cout<<"sigma {Jet(no cuts)} = "<<events_c06e<<" (06e) "<<events_c0607p<<" (0607p) "<<endl;
	cout<<" relative difference: "<<100*(events_c06e - events_c0607p)/events_c06e<<endl;*/

	Float_t		events_b0607p = (Float_t)(((TH1F*)fBeauty0607p->Get(HistoNameTrueEvents))->GetEntries()) / RefSampleBeautyLumi0607p;
	Float_t		events_b06e = (Float_t)(((TH1F*)fBeauty06e->Get(HistoNameTrueEvents))->GetEntries()) / RefSampleBeautyLumi06e;
	cout<<"beauty"<<endl;
	cout<<"sigma (5<Q2<1000, 0.02<y<0.7) = "<<events_b06e<<" (06e) "<<events_b0607p<<" (0607p) "<<endl;
	cout<<" relative difference: "<<100*(events_b06e - events_b0607p)/events_b06e<<endl;

	// ---------- VISUALISING SOME DISTRIBUTIONS -------------//
	// - et and eta distributions
 	const TString HistoNamejetet="bin1/truejetet1";
	const TString HistoNamejeteta="bin1/truejeteta1";

	// ------- beauty --------
	TH1F *	jetetB0607p =fBeauty0607p->Get(HistoNamejetet);
	TH1F *	jetetaB0607p =fBeauty0607p->Get(HistoNamejeteta);

	TH1F *	jetetB06e =fBeauty06e->Get(HistoNamejetet);
	TH1F *	jetetaB06e =fBeauty06e->Get(HistoNamejeteta);

	jetetB0607p->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);
	jetetaB0607p->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);

	jetetB0607p->SetLineColor(kBlue);
	jetetaB0607p->SetLineColor(kBlue);

	jetetB06e->SetLineColor(kGreen);
	jetetaB06e->SetLineColor(kGreen);

	TCanvas * cB = new TCanvas();
	cB->Divide(2,1);

	cB->cd(1);
	jetetB0607p->Draw("histo");
	jetetB06e->Draw("same histo");
	TLegend * l1B = new TLegend(0.7,0.7,0.9,0.9,"beauty","brNDC");

	l1B -> AddEntry (jetetB0607p, "0607p", "L");
	l1B -> AddEntry (jetetB06e, "06e", "L");
	l1B->Draw("same");

	cB->cd(2);
	jetetaB0607p->Draw("histo");
	jetetaB06e->Draw("same histo");
	TLegend * l2B = new TLegend(0.7,0.7,0.9,0.9,"beauty","brNDC");
	l2B -> AddEntry (jetetaB0607p, "0607p", "L");
	l2B -> AddEntry (jetetaB06e, "06e", "L");
	l2B->Draw("same");

	// ------- charm --------
/*
	cout<<"charm again"<<endl;

	TH1F *	jetetC0607p =(TH1F*)fCharm0607p->Get(HistoNamejetet);
	TH1F *	jetetaC0607p =(TH1F*)fCharm0607p->Get(HistoNamejeteta);

	TH1F *	jetetC06e =(TH1F*)fCharm06e->Get(HistoNamejetet);
	TH1F *	jetetaC06e =(TH1F*)fCharm06e->Get(HistoNamejeteta);

	cout<<"before scaling"<<endl;
	cout<<"06e "<<jetetC06e->Integral()<<" "<<jetetC06e->GetEntries()<<endl;
	cout<<"0607p "<<jetetC0607p->Integral()<<" "<<jetetC0607p->GetEntries()<<endl;

	jetetC0607p->Scale(RefSampleCharmLumi06e / RefSampleCharmLumi0607p);
	jetetaC0607p->Scale(RefSampleCharmLumi06e / RefSampleCharmLumi0607p);

	cout<<"after scaling"<<endl;
	cout<<"06e "<<jetetC06e->Integral()<<" "<<jetetC06e->GetEntries()<<endl;
	cout<<"0607p "<<jetetC0607p->Integral()<<" "<<jetetC0607p->GetEntries()<<endl;

	jetetC0607p->SetLineColor(kBlue);
	jetetaC0607p->SetLineColor(kBlue);

	jetetC06e->SetLineColor(kGreen);
	jetetaC06e->SetLineColor(kGreen);

	TCanvas * cC = new TCanvas();
	cC->Divide(2,1);

	cC->cd(1);
	jetetC0607p->Draw("histo");
	jetetC06e->Draw("same histo");
	TLegend * l1C = new TLegend(0.7,0.7,0.9,0.9, "charm", "brNDC");
	l1C -> AddEntry (jetetC0607p, "0607p", "L");
	l1C -> AddEntry (jetetC06e, "06e", "L");
	l1C->Draw("same");

	cC->cd(2);
	jetetaC0607p->Draw("histo");
	jetetaC06e->Draw("same histo");
	TLegend * l2C = new TLegend(0.7,0.7,0.9,0.9, "charm", "brNDC");
	l2C -> AddEntry (jetetaC0607p, "0607p", "L");
	l2C -> AddEntry (jetetaC06e, "06e", "L");
	l2C->Draw("same");

*/
	// -- parton level distributions
	// -- beauty
	const TString HistoNameqqbaret="bin1/bbbar_et";
	const TString HistoNameqqbareta="bin1/bbbar_eta";
	TH1F *	bbbar_etB0607p =(TH1F*)fBeauty0607p->Get(HistoNameqqbaret);
	TH1F *	bbbar_etaB0607p =(TH1F*)fBeauty0607p->Get(HistoNameqqbareta);

	TH1F *	bbbar_etB06e =fBeauty06e->Get(HistoNameqqbaret);
	TH1F *	bbbar_etaB06e =fBeauty06e->Get(HistoNameqqbareta);

	bbbar_etB0607p->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);
	bbbar_etaB0607p->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);

	bbbar_etB0607p->SetLineColor(kBlue);
	bbbar_etaB0607p->SetLineColor(kBlue);

	bbbar_etB06e->SetLineColor(kGreen);
	bbbar_etaB06e->SetLineColor(kGreen);

	TCanvas * cpartonB = new TCanvas();
	cpartonB->Divide(2,1);

	cpartonB->cd(1);
	bbbar_etB0607p->Draw("histo");
	bbbar_etB06e->Draw("same histo");
	TLegend * lparton1B = new TLegend(0.5,0.5,0.9,0.9,"beauty","brNDC");

	lparton1B -> AddEntry (bbbar_etB0607p, "0607p (RAPGAP-PT2CUT 14 0.)", "L");
	lparton1B -> AddEntry (bbbar_etB06e, "06e (RAPGAP-PT2CUT 14 2)", "L");
	lparton1B->Draw("same");

	cpartonB->cd(2);
	bbbar_etaB0607p->Draw("histo");
	bbbar_etaB06e->Draw("same histo");
	TLegend * lparton2B = new TLegend(0.7,0.7,0.9,0.9,"beauty","brNDC");
	lparton2B -> AddEntry (bbbar_etB0607p, "0607p (RAPGAP-PT2CUT 14 0)", "L");
	lparton2B -> AddEntry (bbbar_etaB06e, "06e (RAPGAP-PT2CUT 14 2)", "L");
	//lparton2B->Draw("same");


	cout<<"integrals" <<endl;
	cout<<"et, 0607p: "<<bbbar_etB0607p->Integral()<<endl;
	cout<<"et, 06e: "<<bbbar_etB06e->Integral()<<endl;
	cout<<"eta, 0607p: "<<bbbar_etaB0607p->Integral()<<endl;
	cout<<"eta, 06e: "<<bbbar_etaB06e->Integral()<<endl;


	return 0;
}