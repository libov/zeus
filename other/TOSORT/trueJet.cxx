int	trueJet()
{
	TString		RefSampleCharm06eBGF="mc06ev02eccbar.rg30.q2g1.5.bgf";
	TString		RefSampleBeauty06eBGF="mc06ev02e.rgap3.nc.bbdir.e.q2g1.";

	TString		RefSampleCharm06eRES="mc06ev02ef15643.ccbar.rg30.q2g1.5.resc";
	TString		RefSampleBeauty06eRES="mc06ev02ef15643.bbbar.rg30.q2g1.resc";

	Double_t		RefSampleCharmLumi06eBGF = 54.51;
	Double_t		RefSampleBeautyLumi06eBGF = 912.499;

	Double_t		RefSampleCharmLumi06eRES = 54.9;
	Double_t		RefSampleBeautyLumi06eRES = 925.26;

	TString 		HISTO_PATH = getenv("HISTO_PATH");
	TString 		HistogramsVersion = "inclusivev4";

	TFile			*fCharm06eBGF = new TFile(HISTO_PATH+"/analysis."+RefSampleCharm06eBGF+"."+HistogramsVersion+".root", "read");
	TFile			*fBeauty06eBGF = new TFile(HISTO_PATH+"/analysis."+RefSampleBeauty06eBGF+"."+HistogramsVersion+".root", "read");

	TFile			*fCharm06eRES = new TFile(HISTO_PATH+"/analysis."+RefSampleCharm06eRES+"."+HistogramsVersion+".root", "read");
	TFile			*fBeauty06eRES = new TFile(HISTO_PATH+"/analysis."+RefSampleBeauty06eRES+"."+HistogramsVersion+".root", "read");
/*
	// -- # of events (after Q2 and y cuts)
	TString			neventsHisto = "bin1/eventsInFiducial";
	Float_t			neventsB06eBGF=((TH1F*)fBeauty06eBGF->Get(neventsHisto))->GetEntries();
	Float_t			neventsB06eRES=((TH1F*)fBeauty06eRES->Get(neventsHisto))->GetEntries();
	Float_t			neventsC06eBGF=((TH1F*)fCharm06eBGF->Get(neventsHisto))->GetEntries();
	Float_t			neventsC06eRES=((TH1F*)fCharm06eRES->Get(neventsHisto))->GetEntries();
	cout<<"eventsInFiducial"<<endl;
	cout<<"beauty"<<endl;
	cout<<"BGF: "<<neventsB06eBGF<<"; RES: "<<neventsB06eRES<<endl;
	cout<<"charm"<<endl;
	cout<<"BGF: "<<neventsC06eBGF<<"; RES: "<<neventsC06eRES<<endl;

	// -- # of events (before Q2 and y cuts)
	TString			neventsInMCHisto = "bin1/eventsInMC";
	Float_t			neventsInMCB06eBGF=((TH1F*)fBeauty06eBGF->Get(neventsInMCHisto))->GetEntries();
	Float_t			neventsInMCB06eRES=((TH1F*)fBeauty06eRES->Get(neventsInMCHisto))->GetEntries();
	Float_t			neventsInMCC06eBGF=((TH1F*)fCharm06eBGF->Get(neventsInMCHisto))->GetEntries();
	Float_t			neventsInMCC06eRES=((TH1F*)fCharm06eRES->Get(neventsInMCHisto))->GetEntries();
	cout<<"eventsInMC"<<endl;
	cout<<"beauty"<<endl;
	cout<<"BGF: "<<neventsInMCB06eBGF<<"; RES: "<<neventsInMCB06eRES<<endl;
	cout<<"charm"<<endl;
	cout<<"BGF: "<<neventsInMCC06eBGF<<"; RES: "<<neventsInMCC06eRES<<endl;

	// -- number of events after jet selection
	TString			truejets = "bin1/truejets";
	Float_t			ntruejetsB06eBGF=((TH1F*)fBeauty06eBGF->Get(truejets))->GetEntries();
	Float_t			ntruejetsB06eRES=((TH1F*)fBeauty06eRES->Get(truejets))->GetEntries();
	Float_t			ntruejetsC06eBGF=((TH1F*)fCharm06eBGF->Get(truejets))->GetEntries();
	Float_t			ntruejetsC06eRES=((TH1F*)fCharm06eRES->Get(truejets))->GetEntries();
	cout<<"truejets"<<endl;
	cout<<"beauty"<<endl;
	cout<<"BGF: "<<ntruejetsB06eBGF<<"; RES: "<<ntruejetsB06eRES<<endl;
	cout<<"charm"<<endl;
	cout<<"BGF: "<<ntruejetsC06eBGF<<"; RES: "<<ntruejetsC06eRES<<endl;
*/


	// ---------- VISUALISING SOME DISTRIBUTIONS -------------//
	// - et and eta distributions ( after cuts)
 	const TString HistoNamejetet="bin1/truejetet1";
	const TString HistoNamejeteta="bin1/truejeteta1";

	// ------- beauty --------
	TH1F *	jetetB06eBGF =fBeauty06eBGF->Get(HistoNamejetet);
	TH1F *	jetetaB06eBGF =fBeauty06eBGF->Get(HistoNamejeteta);

	TH1F *	jetetB06eRES =fBeauty06eRES->Get(HistoNamejetet);
	TH1F *	jetetaB06eRES =fBeauty06eRES->Get(HistoNamejeteta);

	jetetB06eBGF->SetLineColor(kRed);
	jetetaB06eBGF->SetLineColor(kRed);
	jetetB06eRES->SetLineColor(kBlue);
	jetetaB06eRES->SetLineColor(kBlue);

	jetetB06eBGF->SetLineWidth(2);
	jetetaB06eBGF->SetLineWidth(2);
	jetetB06eRES->SetLineWidth(2);
	jetetaB06eRES->SetLineWidth(2);

	jetetaB06eBGF->SetAxisRange(-3, 3, "X");
	jetetaB06eRES->SetAxisRange(-3, 3, "X");

	jetetB06eBGF->SetStats(0);
	jetetaB06eBGF->SetStats(0);
	jetetB06eRES->SetStats(0);
	jetetaB06eRES->SetStats(0);

	jetetB06eBGF->SetXTitle("E_{T}^{jet}");
	jetetaB06eBGF->SetXTitle("#eta^{jet}");
	jetetB06eRES->SetXTitle("E_{T}^{jet}");
	jetetaB06eRES->SetXTitle("#eta^{jet}");

	jetetB06eBGF->SetTitleSize(0.06);
	jetetaB06eBGF->SetTitleSize(0.06);
	jetetB06eRES->SetTitleSize(0.06);
	jetetaB06eRES->SetTitleSize(0.06);

	jetetB06eBGF->SetTitleSize(0.06, "Y");
	jetetaB06eBGF->SetTitleSize(0.06, "Y");
	jetetB06eRES->SetTitleSize(0.06, "Y");
	jetetaB06eRES->SetTitleSize(0.06, "Y");

	jetetB06eBGF->SetTitleOffset(0.69);
	jetetaB06eBGF->SetTitleOffset(0.69);
	jetetB06eRES->SetTitleOffset(0.69);
	jetetaB06eRES->SetTitleOffset(0.69);

	jetetB06eBGF->SetYTitle("Entries");
	jetetaB06eBGF->SetYTitle("Entries");
	jetetB06eRES->SetYTitle("Entries");
	jetetaB06eRES->SetYTitle("Entries");

	jetetaB06eRES->Scale(jetetaB06eBGF->Integral()/jetetaB06eRES->Integral());
	jetetB06eRES->Scale(jetetB06eBGF->Integral()/jetetB06eRES->Integral());


	TCanvas * cB = new TCanvas();
	cB->SetFrameFillColor(0);
	cB->SetFillColor(0);
	cB->ToggleToolBar();
	cB->ToggleEventStatus();
	cB->ToggleEditor();

	cB->Divide(2,1);

	cB->cd(1);
	//jetetB06eBGF->SetTitle("Beauty");
	jetetB06eBGF->Draw("histo");
	jetetB06eRES->Draw("same histo");

	TLegend * l1B= new TLegend(0.5,0.6,0.89,0.89,"Beauty","brNDC");
	l1B -> AddEntry (jetetB06eBGF, "BGF", "L");
	l1B -> AddEntry (jetetB06eRES, "Excitation", "L");
	l1B->SetFillColor(0);
	l1B->Draw("same");
	gPad->SetLogy();

	cB->cd(2);
	//jetetaB06eBGF->SetTitle("Beauty");
	jetetaB06eRES->Draw("histo");
	jetetaB06eBGF->Draw("same histo");

	TLegend * l2B = new TLegend(0.7,0.7,0.9,0.9,"beauty","brNDC");

	l2B -> AddEntry (jetetaB06eBGF, "BGF", "L");
	l2B -> AddEntry (jetetaB06eRES, "Excitation", "L");
	l2B->SetFillColor(0);
	//l2B->Draw("same");

	cout<<"beauty truejetet1/truejeteta1 integrals"<<endl;
	cout<<"et BGF "<<jetetB06eBGF->Integral()<<endl;
	cout<<"et RES "<<jetetB06eRES->Integral()<<endl;
	cout<<"eta BGF "<<jetetaB06eBGF->Integral()<<endl;
	cout<<"eta RES "<<jetetaB06eRES->Integral()<<endl;


	// ------- charm --------
	TH1F *	jetetC06eBGF =fCharm06eBGF->Get(HistoNamejetet);
	TH1F *	jetetaC06eBGF =fCharm06eBGF->Get(HistoNamejeteta);

	TH1F *	jetetC06eRES =fCharm06eRES->Get(HistoNamejetet);
	TH1F *	jetetaC06eRES =fCharm06eRES->Get(HistoNamejeteta);

	jetetC06eBGF->SetLineColor(kRed);
	jetetaC06eBGF->SetLineColor(kRed);
	jetetC06eRES->SetLineColor(kBlue);
	jetetaC06eRES->SetLineColor(kBlue);

	jetetC06eBGF->SetLineWidth(2);
	jetetaC06eBGF->SetLineWidth(2);
	jetetC06eRES->SetLineWidth(2);
	jetetaC06eRES->SetLineWidth(2);

	jetetC06eBGF->SetStats(0);
	jetetaC06eBGF->SetStats(0);
	jetetC06eRES->SetStats(0);
	jetetaC06eRES->SetStats(0);

	jetetC06eBGF->SetXTitle("E_{T}^{jet}");
	jetetaC06eBGF->SetXTitle("#eta^{jet}");
	jetetC06eRES->SetXTitle("E_{T}^{jet}");
	jetetaC06eRES->SetXTitle("#eta^{jet}");

	jetetC06eBGF->SetTitleSize(0.06);
	jetetaC06eBGF->SetTitleSize(0.06);
	jetetC06eRES->SetTitleSize(0.06);
	jetetaC06eRES->SetTitleSize(0.06);

	jetetC06eBGF->SetTitleSize(0.06, "Y");
	jetetaC06eBGF->SetTitleSize(0.06, "Y");
	jetetC06eRES->SetTitleSize(0.06, "Y");
	jetetaC06eRES->SetTitleSize(0.06, "Y");


	jetetC06eBGF->SetTitleOffset(0.69);
	jetetaC06eBGF->SetTitleOffset(0.69);
	jetetC06eRES->SetTitleOffset(0.69);
	jetetaC06eRES->SetTitleOffset(0.69);

	jetetC06eBGF->SetYTitle("Entries");
	jetetaC06eBGF->SetYTitle("Entries");
	jetetC06eRES->SetYTitle("Entries");
	jetetaC06eRES->SetYTitle("Entries");


	jetetaC06eBGF->SetAxisRange(-3, 3, "X");
	jetetaC06eRES->SetAxisRange(-3, 3, "X");

	TCanvas * cC = new TCanvas();
	cC->SetFrameFillColor(0);
	cC->SetFillColor(0);
	cC->ToggleToolBar();
	cC->ToggleEventStatus();
	cC->ToggleEditor();


	cC->Divide(2,1);

	cC->cd(1);
	jetetC06eRES->Draw("histo");
	jetetC06eBGF->Draw("same histo");
	jetetC06eRES->Scale(jetetC06eBGF->Integral()/jetetC06eRES->Integral());

	TLegend * l1C = new TLegend(0.5,0.6,0.89,0.89,"Charm","brNDC");
	l1C -> AddEntry (jetetC06eBGF, "BGF", "L");
	l1C -> AddEntry (jetetC06eRES, "Excitation", "L");
	l1C->SetFillColor(0);
	l1C->Draw("same");

	gPad->SetLogy();

	cC->cd(2);

	jetetaC06eRES->Scale(jetetaC06eBGF->Integral()/jetetaC06eRES->Integral());
	jetetC06eRES->Scale(jetetC06eBGF->Integral()/jetetC06eRES->Integral());
	jetetaC06eRES->Draw("histo");
	jetetaC06eBGF->Draw("same histo");
	TLegend * l2C = new TLegend(0.7,0.7,0.9,0.9,"charm","brNDC");

	l2C -> AddEntry (jetetaC06eBGF, "BGF", "L");
	l2C -> AddEntry (jetetaC06eRES, "Excitation", "L");
	l2C->SetFillColor(0);
	//l2C->Draw("same");
	cout<<"charm truejetet1/truejeteta1 integrals"<<endl;
	cout<<"et BGF "<<jetetC06eBGF->Integral()<<endl;
	cout<<"et RES "<<jetetC06eRES->Integral()<<endl;
	cout<<"eta BGF "<<jetetaC06eBGF->Integral()<<endl;
	cout<<"eta RES "<<jetetaC06eRES->Integral()<<endl;
	cout<<" -1.6<eta<2.2: BGF= "<<jetetaC06eBGF->Integral(10, 40)<<" RES= "<<jetetaC06eRES->Integral(10, 40)<<endl;
	cout<<jetetaC06eBGF->GetBinLowEdge(10)<<" "<<jetetaC06eBGF->GetBinLowEdge(40)<<endl;
/*	// -- parton level distributions
	// -- beauty
	const TString HistoNamebbbaret="bin1/bbbar_et";
	const TString HistoNamebbbareta="bin1/bbbar_eta";

	TH1F *	bbbar_etB06eBGF =fBeauty06eBGF->Get(HistoNamebbbaret);
	TH1F *	bbbar_etaB06eBGF =fBeauty06eBGF->Get(HistoNamebbbareta);

	TH1F *	bbbar_etB06eRES =fBeauty06eRES->Get(HistoNamebbbaret);
	TH1F *	bbbar_etaB06eRES =fBeauty06eRES->Get(HistoNamebbbareta);

	//bbbar_etB06eBGF->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);
	//bbbar_etaB06eBGF->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);

	bbbar_etB06eRES->SetLineColor(kBlue);
	bbbar_etaB06eRES->SetLineColor(kBlue);

	bbbar_etB06eBGF->SetLineColor(kRed);
	bbbar_etaB06eBGF->SetLineColor(kRed);

	bbbar_etB06eRES->Scale(bbbar_etB06eBGF->Integral()/bbbar_etB06eRES->Integral());
	bbbar_etaB06eRES->Scale(bbbar_etaB06eBGF->Integral()/bbbar_etaB06eRES->Integral());

	TCanvas * cpartonB = new TCanvas();
	cpartonB->Divide(2,1);

	cpartonB->cd(1);
	bbbar_etB06eRES->Draw("histo");
	bbbar_etB06eBGF->Draw("same histo");
	TLegend * lparton1B = new TLegend(0.5,0.5,0.9,0.9,"beauty","brNDC");

	lparton1B -> AddEntry (bbbar_etB06eRES, "06e RES", "L");
	lparton1B -> AddEntry (bbbar_etB06eBGF, "06e BGF", "L");
	lparton1B->Draw("same");

	cpartonB->cd(2);
	bbbar_etaB06eRES->Draw("histo");
	bbbar_etaB06eBGF->Draw("same histo");
	TLegend * lparton2B = new TLegend(0.7,0.7,0.9,0.9,"beauty","brNDC");
	lparton2B -> AddEntry (bbbar_etaB06eRES, "06e RES", "L");
	lparton2B -> AddEntry (bbbar_etaB06eBGF, "06e BGF", "L");
	//lparton2B->Draw("same");


	/*cout<<"integrals beauty" <<endl;
	cout<<"et, 0607p: "<<bbbar_etB06e->Integral()<<endl;
	cout<<"et, 06e: "<<bbbar_etB06e->Integral()<<endl;
	cout<<"eta, 0607p: "<<bbbar_etaB06e->Integral()<<endl;
	cout<<"eta, 06e: "<<bbbar_etaB06e->Integral()<<endl;*/

	// charm
/*	const TString HistoNameccbaret="bin1/ccbar_et";
	const TString HistoNameccbareta="bin1/ccbar_eta";

	TH1F *	ccbar_et06eBGF =fCharm06eBGF->Get(HistoNameccbaret);
	TH1F *	ccbar_eta06eBGF =fCharm06eBGF->Get(HistoNameccbareta);

	TH1F *	ccbar_et06eRES =fCharm06eRES->Get(HistoNameccbaret);
	TH1F *	ccbar_eta06eRES =fCharm06eRES->Get(HistoNameccbareta);

	//bbbar_etB06eBGF->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);
	//bbbar_etaB06eBGF->Scale(RefSampleBeautyLumi06e / RefSampleBeautyLumi0607p);

	ccbar_et06eRES->SetLineColor(kBlue);
	ccbar_eta06eRES->SetLineColor(kBlue);

	ccbar_et06eBGF->SetLineColor(kRed);
	ccbar_eta06eBGF->SetLineColor(kRed);

	ccbar_et06eRES->Scale(ccbar_et06eBGF->Integral()/ccbar_et06eRES->Integral());
	ccbar_eta06eRES->Scale(ccbar_eta06eBGF->Integral()/ccbar_eta06eRES->Integral());

	TCanvas * cpartonC = new TCanvas();
	cpartonC->Divide(2,1);

	cpartonC->cd(1);
	ccbar_et06eRES->Draw("histo");
	ccbar_et06eBGF->Draw("same histo");
	TLegend * lparton1C = new TLegend(0.5,0.5,0.9,0.9,"charm","brNDC");

	lparton1C -> AddEntry (ccbar_et06eRES, "06e RES", "L");
	lparton1C -> AddEntry (ccbar_et06eBGF, "06e BGF", "L");
	lparton1C->Draw("same");

	cpartonC->cd(2);
	ccbar_eta06eRES->Draw("histo");
	ccbar_eta06eBGF->Draw("same histo");
	TLegend * lparton2C = new TLegend(0.7,0.7,0.9,0.9,"charm","brNDC");
	lparton2C -> AddEntry (ccbar_eta06eRES, "06e RES", "L");
	lparton2C -> AddEntry (ccbar_eta06eBGF, "06e BGF", "L");
	//lparton2B->Draw("same");
*/

	/*cout<<"integrals charm" <<endl;
	cout<<"et, 0607p: "<<ccbar_et0607p->Integral()<<endl;
	cout<<"et, 06e: "<<ccbar_et06e->Integral()<<endl;
	cout<<"eta, 0607p: "<<ccbar_eta0607p->Integral()<<endl;
	cout<<"eta, 06e: "<<ccbar_eta06e->Integral()<<endl;*/

	// ------- q2, y  ------
/*	const TString HistoNameq2="bin1/q2";
	const TString HistoNamey="bin1/y";

	TH1F *	q206eBGFb =fBeauty06eBGF->Get(HistoNameq2);
	TH1F *	y06eBGFb =fBeauty06eBGF->Get(HistoNamey);

	TH1F *	q206eRESb =fBeauty06eRES->Get(HistoNameq2);
	TH1F *	y06eRESb =fBeauty06eRES->Get(HistoNamey);

	TCanvas * ckinem = new TCanvas();
	ckinem->Divide(2,1);

	ckinem->cd(1);
	q206eBGFb->Draw("histo");
	q206eRESb->Draw("same histo");
	q206eBGFb->SetLineColor(kRed);
	q206eRESb->SetLineColor(kBlue);

	ckinem->cd(2);
	y06eBGFb->Draw("histo");
	y06eRESb->Draw("same histo");
	y06eBGFb->SetLineColor(kRed);
	y06eRESb->SetLineColor(kBlue);
*/

	return 0;
}

