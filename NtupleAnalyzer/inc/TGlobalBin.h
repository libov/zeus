//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
#ifndef TGLOBALBIN_H
#define TGLOBALBIN_H
#include<inc/TBin.h>
#include<inc/VariablePhase.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TList.h>

#include <vector>
using namespace std;

class TMiniNtupleAnalyzer;

/*! \brief Class for automatic binning

    Contains a list of TBin objects. NOTE: Probably many members here that should better belong to TMiniNtupleAnalyzer...
*/

class TGlobalBin : public TObject {
	public:

		TGlobalBin();
		TGlobalBin(TMiniNtupleAnalyzer *instance);
		~TGlobalBin();

		void							AddBin(TBin * bin);
		Bool_t						CheckGlobalBin(VariablePhase	VarPhase);
		TString						BinName;
		TString						GetBinDescription();
		void							AddHistogram(TH1F * histogram);
		int							FillHistogram(TString HistTitle, Float_t	Value);
		TList*						GetHistList();
		void							AddMirroredHistTitle(TString title);
		void							MirrorHistograms();
		void							SetWeightingFactor(Double_t		factor);
		Double_t						GetWeightingFactor();
		void							ApplyWeighting(Bool_t		apply);
                void        Print();

	private:

		TList*						fList_TBin;
		TString						fBinDescription;
		TList*						fListHistograms;
		TMiniNtupleAnalyzer		*fAnalyzerInstance;		// pointer to current TMiniNtupleAnalyzer
																		// object; used for access to some variables
																		// e.g. for histogram mirroring
																		// this mechanism could be used also for
																		// checking of bin values actually...
		vector<TString>			fMirroredHistTitle;
		Int_t							fNevents;					// number of events that fall into this bin
																		//
		Double_t						fWeightingFactor;			//!< Weighting factor for histograms filling.
																		//!< Is used to scale charm distribution when adding up
																		//!< samples with different q2-min-cut
		Bool_t						fApplyWeighting;
};
#endif
