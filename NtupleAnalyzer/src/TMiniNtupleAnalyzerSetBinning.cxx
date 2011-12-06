/**	\author Libov Vladyslav, libov@mail.desy.de
*/

#include <inc/TMiniNtupleAnalyzer.h>
#include <inc/TGlobalBin.h>
#include <inc/VariablePhase.h>
#include<TCollection.h>
#include<TMath.h>
#include<TFile.h>
#include<iostream>
#include<fstream>
#include <map>
using namespace std;
/**\todo Move this elsewhere!
*/

class Var {
	public:
		Var(){}
		Var (TString VarID, Float_t * RecoVar, VariablePhase RecoVarPhase, Float_t * TrueVar, VariablePhase TrueVarPhase){
			fVarID=VarID;
			fRecoVar=RecoVar;
			fRecoVarPhase=RecoVarPhase;
			fTrueVar=TrueVar;
			fTrueVarPhase=TrueVarPhase;
		}
		TString				fVarID;
		Float_t				*fRecoVar, *fTrueVar;
		VariablePhase		fRecoVarPhase, fTrueVarPhase;
};
/**	Sets binning for analysis. Each bin is processed in the same way.
*/
void TMiniNtupleAnalyzer::SetBinning() {
    // choose your binning here, use:
    // TGlobalBin::AddBin(pointer to TBin)
    // TBin::TBin(descripiton of the variable, ptr to it,lowerLimit, upperLimit)
    // don't forget to add them to fList_TGlobalBin at the end of this method
    // Last argument (VariablePhase) DETERMINES POINT (Phase) where this variable is checked;
    // Depends on your desing, be careful!!!

    // Define mapping: variable ID (TString) --> pointer to the relevant variable. Found no better way than doing it like this.
    vector <Var> Variables;
    Variables.push_back( Var("Q2el", &Siq2el[0], kEventVar, &Mc_q2_cr, kTrueVarEvent) );
    Variables.push_back( Var("Q2da", &Siq2da[0], kEventVar, &Mc_q2_cr, kTrueVarEvent) );
    Variables.push_back(Var("xel", &Sixel[0], kEventVar, &Mc_x_cr, kTrueVarEvent  ));
    Variables.push_back(Var("xda", &Sixda[0], kEventVar, &Mc_x_cr, kTrueVarEvent  ));
    Variables.push_back(Var("yel", &Siyel[0], kEventVar, &fTrue_y, kTrueVarEvent  ));
    Variables.push_back(Var("etajet", &fRecoJetEta, kVertexVar, &fTrueJetEta, kTrueVarJet ));
    Variables.push_back(Var("etjet", &fRecoJetEt, kVertexVar , &fTrueJetEt, kTrueVarJet));
    Variables.push_back(Var("phijet", &fRecoJetPhi, kVertexVar, &fTrueJetPhi, kTrueVarJet ));
    Variables.push_back(Var("pitheta", &fPionThetaReco, kRhoVar, &fPionThetaTrue, kRhoTrueVar ));

    map < TString, Var > VarMap;

    for (int k=0; k< Variables.size(); k++) {
        VarMap.insert( make_pair( (TString)Variables[k].fVarID, Variables[k]) );
    }

    // Read config file with binning definition
    ifstream bindef;
    TString arg=(TString)getenv("NTUPLEANALYZER")+(TString) "/config/"+fBinningFileName;
    bindef.open (arg);
    if (bindef.is_open()) {
        cout << "INFO: Binning is taken from " << arg << endl;
        TGlobalBin * GlobalBin = NULL;
        while ( !bindef.eof() ) {
            char varID[256];
            Float_t LowerBound, UpperBound;

            string line;
            getline (bindef, line);
            TString first_char=line[0];
            if ( first_char == "#" ) {
                GlobalBin = new TGlobalBin (this);
                fList_TGlobalBin->Add(GlobalBin);
                continue;
            }
            sscanf ( line.c_str(), "%s %f %f ", varID, &LowerBound, &UpperBound);

            Var cVar=VarMap[(TString)varID];
            GlobalBin->AddBin(new TBin( (TString)varID, cVar.fRecoVar, LowerBound, UpperBound, cVar.fRecoVarPhase) );
            if (fIsMC) {
                GlobalBin->AddBin(new TBin( (TString)varID, cVar.fTrueVar, LowerBound, UpperBound, cVar.fTrueVarPhase) );
            }
        }
    } else {
        cout << " Cannot read file with binning definition. Terminating... " <<endl;
        abort();
    }
    bindef.close();
}
