#include "fastjet/ClusterSequence.hh"
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdio.h>
#include <iostream>
#include "inc/GR_MCcharmincl_05e_lowQ2.h"
#include "inc/GR_MCbeautyincl_05e.h"
using namespace fastjet;
using namespace std;

// hadronMode: defines pre-selection at the hadron level
//	0: ~"standard" ZEUS pre-selection silimar to promp-photon analyses (which use part_* block in CN)
//	   selecting entries with isthep%10000 == 1
//	   exclude SIGMA0 (198,199) and eta0 (57) in agreement with the the original FMCKin definition (and include decay products)
//	   still some photons are not filtered out? (isthep = 65100001, 65090001, 1065100001 1065090001)
//	1: Selection the same as in the MCHBMJets- stable particles(isthep%10000) + stable c and b hadrons
//	   Checked to be in perfect agreement for CN v06.
//
// partonMode: defines pre-selection at the parton level
//	0: ?

int fmck_prt[1000],fmck_daug[1000],fmck_daug2[1000],fmck_isthep[1000],fmck_nstor,fmck_id[1000],simrunnr;
float fmck_px[1000],fmck_py[1000],fmck_pz[1000], fmck_m[1000], fmck_e[1000];
float mc_y,mc_q2,mc_x,mc_q2_cr,mc_x_cr,mc_y_cr;

int npart,part_id[1000],part_prt[1000];
float part_p[1000][4];

int nhmjets;
float pxhmjet[100],pyhmjet[100],pzhmjet[100],ehmjet[100];

TLorentzVector tmpJet;

// Definitions of crange and brange were taken from mcjets.fpp from Orange v2013a for CN v08
// and from Sebastian's talk on 24/11/2011 for CN v06
//const int nbrange=10, ncrange=5;
//v08
//                      D       Lambdac   Omegac    Xic       doubly-charmed
//int crange[ncrange][2]={64,69,  208,209,  212,213,  423,426,  427,432};
//                      B       Lambdab   B         Xib0      Xib+-     Omegab    charmed b-baryons ->
//int brange[nbrange][2]={72,75,  214,215,  468,471,  488,489,  492,493,  494,495,  496,497,  500,501,  504,505,  508,509};
//v06
const int nbrange=8, ncrange=4;
//                      D       Lambdac   Omegac    Xic    
int crange[ncrange][2]={64,69,  208,209,  210,211,  466,467};
//                      B       Lambdab   B        b baryons  charmed b-baryons ->
int brange[nbrange][2]={72,75,  214,215,  468,471,  480,495,  496,497,  500,501,  504,505,  508,509};

vector<int> dontake;

bool Is_RAPGAP_inclusive_c_DIS(string type);
bool Is_RAPGAP_inclusive_b_DIS(string type);
bool IsGoodHadron(int j, int mode=0);
bool IsGoodParton(int j, int mode=0);
void AddBranches_True(TChain *ch);

int main (int argc, char* argv[]) {

  int i,j,k, leptonId, isFinalLepton, eInJet;
  float etaJet, eTJet;
  int hadronMode=1;  
  int partonMode=0;
  int iNoMother=2147483647;

  string mcType="c";

  if (argc>=2) {    
    mcType=argv[1];
  }
  TH1F * h_Et_hadr  = new TH1F("h_Et_hadr"  ,"E_{T}^{hadr}",500,0,50);
  //TH1F * h_Et_hadr  = new TH1F("h_Et_hadr"  ,"E_{T}^{hadr}",500,0,50);
  /*TH1F * h_px_hadr  = new TH1F("h_px_hadr"  ,"E_{T}^{hadr}",500,0,50); 
  TH1F * h_py_hadr  = new TH1F("h_py_hadr"  ,"E_{T}^{hadr}",500,0,50);
  TH1F * h_pz_hadr  = new TH1F("h_pz_hadr"  ,"E_{T}^{hadr}",500,0,50);*/

    TH1F * h_Et_hadr_ora  = new TH1F("h_Et_hadr_ora"  ,"E_{T}^{hadr}",500,0,50);

  
  //Define jet algorithm here
  double R = 1.0;
  JetDefinition jet_def(kt_algorithm, R, E_scheme);
  vector<PseudoJet> hadrons;
  vector<PseudoJet> partons;
  vector<PseudoJet> hadr_jets;
  vector<PseudoJet> part_jets;
  // not used for a moment
  //vector<PseudoJet> hadr_constit;
  //vector<PseudoJet> part_constit;

  //Phase space is defined by etaMin < eta(jet) < etaMax, E_T(jet) = p_T(jet)/p(jet)*E(jet) > emin
  float etaMin=-1.6;
  float etaMax=2.2;
  float emin=0.0;  
  int nent=0;
  TChain * data_ch= new TChain("orange");
  if( Is_RAPGAP_inclusive_c_DIS(mcType) ) {    
    emin=4.2;
    
    data_ch->Add("dcap://dcap.desy.de/pnfs/desy.de/usr/zeus/z/ntup/06e/v06b/mc/root/zeusmc.aetre26.f15643.ccbar.rg30.q2g1.5.bgf.0079.root");
//data_ch->Add("dcap://dcap.desy.de/pnfs/desy.de/usr/zeus/z/ntup/04/v02e/mc/root/zeusmc.acpx424.f13695.rgap3.nc.ccdir.p.q2g4.205.root");
    nent=data_ch->GetEntries();
    //nent=3325064;
    //ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_06e_Q1_5::addToZaconChain(data_ch);

    cout<<"Running over CHARM sample"<<endl;
    cout<<"N events = "<<nent<<endl;
  } 
  else if ( Is_RAPGAP_inclusive_b_DIS(mcType) ) {
    emin=5.0;
    
    data_ch->Add("dcap://dcap.desy.de/pnfs/desy.de/usr/zeus/z/ntup/06e/v06b/mc/root/zeusmc.aetre26.f15643.bbbar.rg30.q2g1.bgf.017.root");
    nent=data_ch->GetEntries();
    //nent=839541;
    //ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_06e_Q1::addToZaconChain(data_ch);

    cout<<"Running over BEAUTY sample"<<endl;
    cout<<"N events = "<<nent<<endl;
  }
  else {
    cout<<"Warning! Choose c/charm/b/beauty"<<endl;
    return -1;
  }

  // activate only needed branches
  data_ch->SetBranchStatus("*", 0);
  AddBranches_True(data_ch);

  // Event loop starts here
  for (i=0;i<nent;i++) {

    if( ! data_ch->GetEntry(i)){break;}

    hadrons.clear();
    partons.clear();
    hadr_jets.clear();
    part_jets.clear();    
    //hadr_constit.clear();
    //part_constit.clear();
    dontake.clear();

    //get lepton particle ID from the 0-th element in fcmkin2
    leptonId=fmck_prt[0];
    isFinalLepton=0;

    if(hadronMode==1) {
      // reject particles from c and b decay chains
      for(j=0; j<fmck_nstor; j++) {
        if(fmck_daug[j]!=iNoMother) {
          for(k=0; k<dontake.size(); k++) {
            if(dontake.at(k) == fmck_daug[j])
              dontake.push_back(fmck_id[j]);
          }
        }

        for(k=0; k<nbrange; k++) {
          if(fmck_prt[j]>=brange[k][0] && fmck_prt[j]<=brange[k][1]) {
            dontake.push_back(fmck_id[j]);
          }
        }
        for(k=0; k<ncrange; k++) {
          if(fmck_prt[j]>=crange[k][0] && fmck_prt[j]<=crange[k][1]) {
            dontake.push_back(fmck_id[j]);
          }
        }
      }
    }

    for (j=0; j<fmck_nstor; j++) {

      // reject the scattered electron
      if(fmck_prt[j]==leptonId && fmck_daug[j]==1 && fmck_isthep[j]%10000==1)
        isFinalLepton=1;
      else
        isFinalLepton=0;

      // fill input hadron- and parton-level jet inputs here
      PseudoJet particle(fmck_px[j], fmck_py[j], fmck_pz[j], fmck_e[j]);
      // is not used for a moment. Might be useful for other electron removal procedures
      particle.set_user_index(isFinalLepton);
      //
      //if(good hadron)
      if(IsGoodHadron(j,hadronMode) && !isFinalLepton)
        hadrons.push_back( particle );
      //if(good parton)
      if(IsGoodParton(j,partonMode))
        partons.push_back( particle );
    }

    // run jet clustering
    ClusterSequence hadr_seq(hadrons, jet_def);    
    ClusterSequence part_seq(partons, jet_def);

    // retrieve unordered set of jets (w/o E_T cut)
    hadr_jets = hadr_seq.inclusive_jets();
    part_jets = part_seq.inclusive_jets();

    //fill hadron-level distributions applying e_T and eta cuts
    vector<TLorentzVector> goodJets_ML;
    for(j=0; j<hadr_jets.size(); j++){ 
      /*//electron rejection via constituents
      // not used. May be useful later
      eInJet=0;
      hadr_constit.clear();
      hadr_constit = hadr_jets[j].constituents();
      for(k=0; k<hadr_constit.size(); k++) {
        if(hadr_constit[k].user_index()==1)
          eInJet=1;          
      }*/

      tmpJet.SetPxPyPzE(hadr_jets[j].px(),hadr_jets[j].py(),hadr_jets[j].pz(),hadr_jets[j].E());
      etaJet=tmpJet.Eta();
      eTJet=tmpJet.Et();
      if((etaJet>etaMin) && (etaJet<etaMax) && (eTJet>emin)) {
        // fill hadron-level distributions here
        goodJets_ML.push_back(tmpJet);
        h_Et_hadr->Fill(hadr_jets[j].E(),1.);
        /*h_px_hadr->Fill(hadr_jets[j].px(),1.);
        h_py_hadr->Fill(hadr_jets[j].py(),1.);
        h_pz_hadr->Fill(hadr_jets[j].pz(),1.);*/
      }
    }


    //fill parton-level distributions applying e_T and eta cuts
    for(j=0; j<part_jets.size(); j++){
      tmpJet.SetPxPyPzE(part_jets[j].px(),part_jets[j].py(),part_jets[j].pz(),part_jets[j].E());
      etaJet=tmpJet.Eta();
      eTJet=tmpJet.Et();
      if((etaJet>etaMin) && (etaJet<etaMax) && (eTJet>emin) && (eInJet==0)) {
        //fill some histos
      }
    }


    vector<TLorentzVector> goodJets_CN;
    for(j=0; j<nhmjets; j++){
      tmpJet.SetPxPyPzE(pxhmjet[j],pyhmjet[j],pzhmjet[j],ehmjet[j]);
      etaJet=tmpJet.Eta();
      eTJet=tmpJet.Et();
      if((etaJet>etaMin) && (etaJet<etaMax) && (eTJet>emin)){
        goodJets_CN.push_back(tmpJet);
      }
    }

    for (int orajet=0; orajet<nhmjets; orajet++) {
        TLorentzVector jet(pxhmjet[orajet], pyhmjet[orajet], pzhmjet[orajet], ehmjet[orajet]);
      if((jet.Eta()>etaMin) && (jet.Eta()<etaMax) && (jet.Et()>emin)) {

        h_Et_hadr_ora->Fill(jet.E(),1.);
}
    }

  }

    TCanvas * c_hadr = new TCanvas();
    c_hadr -> Divide(1,2);
    c_hadr -> cd(1);
    h_Et_hadr -> Draw();
    c_hadr -> cd(2);
    h_Et_hadr_ora -> Draw();
    c_hadr -> Print("c_hadr.eps");

  cout<<"Done."<<endl;

} 



bool Is_RAPGAP_inclusive_c_DIS(string type) {

  if( (type.find("c") != string::npos) || (type.find("charm") != string::npos) )
    return 1;
  else
    return 0;
}

bool Is_RAPGAP_inclusive_b_DIS(string type) {

  if( (type.find("b") != string::npos) || (type.find("beauty") != string::npos) )
    return 1;
  else
    return 0;
}

bool IsGoodHadron(int j, int mode) {
  int k,l;
  bool res;
  if(mode==0) {

    res=((fmck_isthep[j]%10000 == 1  &&  fmck_prt[j]!=57 && fmck_prt[j]!=198 && fmck_prt[j]!=199) || (fmck_prt[fmck_daug[j]-1]==57));

  } else if(mode==1) {

    res=(fmck_isthep[j]%10000 == 1);

    for(k=0; k<nbrange; k++) {
      if(fmck_prt[j]>=brange[k][0] && fmck_prt[j]<=brange[k][1]) {
        for(l=0; l<dontake.size(); l++) { 
          if(fmck_daug[j] == dontake.at(l))
            break;
          else
            if (l == dontake.size()-1)
              return true;
        }
      }
    }
    for(k=0; k<ncrange; k++) {
      if(fmck_prt[j]>=crange[k][0] && fmck_prt[j]<=crange[k][1]) {
        for(l=0; l<dontake.size(); l++) {
          if(fmck_daug[j] == dontake.at(l))
            break;
          else
            if (l == dontake.size()-1)
              return true;
        }
      }
    }
    for(l=0; l<dontake.size(); l++) {
      if(fmck_daug[j] == dontake.at(l))
        res=false;
    }

  } else

    res=false;

  return res;
}


bool IsGoodParton(int j, int mode) {
  bool res;

  // placeholder only! To be written!

  return false;
}


void AddBranches_True(TChain *ch) {
     ch->SetBranchStatus ("Fmck_nstor", 1);
     ch->SetBranchAddress("Fmck_nstor",&fmck_nstor);
     ch->SetBranchStatus ("Fmck_prt", 1);
     ch->SetBranchAddress("Fmck_prt", fmck_prt);
     ch->SetBranchStatus ("Fmck_daug",1);
     ch->SetBranchAddress("Fmck_daug", fmck_daug);
     ch->SetBranchStatus ("Fmck_daug2",1);
     ch->SetBranchAddress("Fmck_daug2", fmck_daug2);
     ch->SetBranchStatus ("Fmck_id",1);
     ch->SetBranchAddress("Fmck_id", fmck_id);
     ch->SetBranchStatus ("Fmck_px",1);
     ch->SetBranchAddress("Fmck_px", fmck_px);
     ch->SetBranchStatus ("Fmck_py",1);
     ch->SetBranchAddress("Fmck_py", fmck_py);
     ch->SetBranchStatus ("Fmck_pz",1);
     ch->SetBranchAddress("Fmck_pz", fmck_pz);
     ch->SetBranchStatus ("Fmck_m",1);
     ch->SetBranchAddress("Fmck_m", fmck_m);
     ch->SetBranchStatus ("Fmck_e",1);
     ch->SetBranchAddress("Fmck_e", fmck_e);
     ch->SetBranchStatus ("Fmck_isthep",1);
     ch->SetBranchAddress("Fmck_isthep", fmck_isthep);

     ch->SetBranchStatus ("Mc_q2", 1);
     ch->SetBranchAddress("Mc_q2", &mc_q2);
     ch->SetBranchStatus ("Mc_q2_cr", 1);
     ch->SetBranchAddress("Mc_q2_cr", &mc_q2_cr);
     ch->SetBranchStatus ("Mc_y", 1);
     ch->SetBranchAddress("Mc_y", &mc_y);
     ch->SetBranchStatus ("Mc_x", 1);
     ch->SetBranchAddress("Mc_x", &mc_x);
     ch->SetBranchStatus ("Mc_x_cr", 1);
     ch->SetBranchAddress("Mc_x_cr", &mc_x_cr);

     /*ch->SetBranchStatus ("Npart", 1);
     ch->SetBranchAddress("Npart",&npart);
     ch->SetBranchStatus ("Part_id", 1);
     ch->SetBranchAddress("Part_id",part_id);
     ch->SetBranchStatus ("Part_prt", 1);
     ch->SetBranchAddress("Part_prt",part_prt);
     ch->SetBranchStatus ("Part_p", 1);
     ch->SetBranchAddress("Part_p",part_p);*/

     // Note, that jets with stable c and b hadrons are linked to variables without "b" in the name
     ch->SetBranchStatus ("Nhbmjets", 1);
     ch->SetBranchAddress("Nhbmjets",&nhmjets);
     ch->SetBranchStatus ("Pxhbmjet", 1);
     ch->SetBranchAddress("Pxhbmjet",pxhmjet);
     ch->SetBranchStatus ("Pyhbmjet", 1);
     ch->SetBranchAddress("Pyhbmjet",pyhmjet);
     ch->SetBranchStatus ("Pzhbmjet", 1);
     ch->SetBranchAddress("Pzhbmjet",pzhmjet);
     ch->SetBranchStatus ("Ehbmjet", 1);
     ch->SetBranchAddress("Ehbmjet",ehmjet);
}
