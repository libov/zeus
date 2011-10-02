void MyAnalyser()
{
  Int_t nevents=0;
  Float_t Cal_py, Cal_px, Cal_pz, Cal_pt;
  char prefix[100];
  char name[150];

  	sprintf(prefix,"zeus://acs/z/ntup/03/v02d/data/root/");
	sprintf(name,"%sdata_03_45929_45957_01.root",prefix);
  	cout<<name<<endl;

  TChain* ntuple=new TChain("orange");
  ntuple->Add(name);

  //TFile* myChain = new TFile(name, "READ");
  //TNtuple* ntuple = (TNtuple*) myChain->Get("orange");

  ntuple->SetBranchAddress("Cal_px",&Cal_px);
  ntuple->SetBranchAddress("Cal_py",&Cal_py);
  ntuple->SetBranchAddress("Cal_pz",&Cal_pz);
  ntuple->SetBranchAddress("Cal_pt",&Cal_pt);

  TH1F *histCal1=new TH1F("Cal_px","x-momentum",300,-15,15);
  TH1F *histCal2=new TH1F("Cal_py","y-momentum",300,-15,15);
  TH1F *histCal3=new TH1F("Cal_pz","z-momentum",200,-100,500);
  TH1F *histCal4=new TH1F("Cal_pt","trasv momentum",300,-5,15);
  nevents=10000;

  for (int k=0;k<nevents;k++)
    {
      ntuple->GetEntry(k);
      histCal1->Fill(Cal_px);
      histCal2->Fill(Cal_py);
      histCal3->Fill(Cal_pz);
      histCal4->Fill(Cal_pt);
    }

  //  ntuple->Draw("Cal_py>>histCal");
	TCanvas* c1 = new TCanvas("c1","c1");
  c1->Divide(2,2);
  c1->cd(1);
  histCal1->Draw();
  c1->cd(2);
  histCal2->Draw();
  c1->cd(3);
  histCal3->Draw();
  c1->cd(4);
  histCal4->Draw();

  //  c1->Update();
}
