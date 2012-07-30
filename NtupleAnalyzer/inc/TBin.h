//////////////////////////////////////////////////
//                                              //
//  Inclusive secondary vertex analysis         //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
#ifndef TBIN_H
#define TBIN_H
#include <TROOT.h>
#include <inc/VariablePhase.h>
#include <vector>
using namespace std;

/** Simple bin.

    Contains pointer to the relevant variable and upper/lower bound of this variable.
    Several TBins build more complex TGlobalBin
*/
class TBin : public TObject {

    public:

    /** Default constructor.
    */
    TBin();

    /** Overloaded constructor.

        Takes four arguments:
            \param VarDescr
            \param Variable initializes fVariable
            \param LowerEdge Lower cut
            \param UpperEdge Upper cut
            \param VarPhase the so called phase of variable - e.g. event variable or jet variable - should be checked in different places of code
    */
		TBin(TString VarDescr, Float_t* Variable, Float_t LowerEdge, Float_t UpperEdge, VariablePhase VarPhase);

		/**	Default destructor.
		*/
		~TBin() {};

		Bool_t			CheckBin();
		TString			GetDescription();
		VariablePhase		GetVarPhase();

	private:

		/**  Pointer to relevant variable. Should be a valid pointer to member of TMiniNtupleAnalyzer object (inherited or own) and is used to retreive variable value that is cutted in this bin
		*/
		Float_t*				fVariable;

		/**	In case of MC - pointer to the true value of fVariable. Otherwise - NULL pointer.
		*/
	/*	Float_t*				fTrueVariable;				// pointer to the relevant variable*/

		/** Contains variable description; is used in ...
		*/
		TString				fVariableDescription;
		Float_t				fLowerEdge;
		Float_t				fUpperEdge;
		VariablePhase		fVarPhase;

};
#endif
