#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyClass::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MyClass.C
//      Root > MyClass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

    Float_t fJetEtCut = 4.2;
    TH1F * fDebugSVTX = new TH1F ("h1", "", 20, 0, 20);

    fChain->SetBranchStatus("*",0);  // disable all branches
    fChain->SetBranchStatus("Siq2da",1);  // activate branchname

    // create a histogram - for graphical visualization
    TH1F * histo_q2da = new TH1F ("h1", "Q^{2} distribution (double-angle method)", 100, 0, 1000);
    histo_q2da -> SetXTitle ("Q^{2}_{da}, GeV");

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // selection of the secondary vertices
       for (int vertex=0; vertex < Kt_njet_a; vertex++) {

            fDebugSVTX->Fill(0);

            // try to match one this jet (from block A) to one of the jets in block B
            // helping variables
            Bool_t      jetAinB=false;
            Int_t       correspjetB=-1;
            // loop over jets in block B
            for (int jetB=0; jetB<Kt_njet_b; jetB++) {
                // check whether Eta, Et and Phi are the same for both jets
                Float_t     deltaEta=Kt_etajet_a[vertex]-Kt_etajet_b[jetB];
                Float_t     deltaPhi=Kt_phijet_a[vertex]-Kt_phijet_b[jetB];
                Float_t     deltaEt=Kt_etjet_a[vertex]-Kt_etjet_b[jetB];
                if ( (deltaEta==0) && (deltaPhi==0) &&  (deltaEt==0) ) {
                    // found a match!
                    jetAinB=true;
                    correspjetB=jetB;
                }
            }

            // skip this block-A-jet if couldn't find a corresponding block-B-jet.
            if ( !jetAinB ) continue;
            fDebugSVTX->Fill(1);

            // JET ET CUT
            if ( Kt_etjet_b[correspjetB] < fJetEtCut) continue;
            fDebugSVTX->Fill(2);

            // JET ETA CUT
            if ( ( Kt_etajet_b[correspjetB] > 2.2 ) || ( Kt_etajet_b[correspjetB] < -1.6 ) ) continue;
            fDebugSVTX->Fill(3);

            // calculate significance of the vertex
            Float_t Significance = CalculateSignificance(vertex);

            // check whether it was successful
            if (Significance==(-999)) continue;
            fDebugSVTX->Fill(4);
            if (Significance==(-998)) continue;
            fDebugSVTX->Fill(5);

            // calculate also projected decay length
            //Float_t     ProjDecayLength = CalculateProjDecayLength(vertex);

            // calculate chi2 over NDOF (in the ntuples we have only chi2)
            Float_t     chi2ndf=Vtxsec_chi2[vertex]/Vtxsec_ndf[vertex];
            // chi2/NDOF cut
            if (chi2ndf>6.) continue;
            fDebugSVTX->Fill(6);

            // create a vertex object to be stored for later processing
    
            // ok, a good vertex was found, store it to array and raise the good-vtx-found flag
            //fSecondaryVertexFound=true;
        }

      // if (Cut(ientry) < 0) continue;
      histo_q2da -> Fill(Siq2da[0]);
   }

    // now draw the histogram
    histo_q2da -> Draw();
}
