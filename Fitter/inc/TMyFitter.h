//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  september 2009                              //
//                                              //
//////////////////////////////////////////////////


#include<TROOT.h>
#include<TMinuit.h>
#include <inc/TDistribution.h>

class	TMyFitter : public TObject
{

	public:
		TMyFitter() {};
		TMyFitter(TString VariableName, void (*func)(Int_t&, Double_t*, Double_t&, Double_t*, Int_t), TString HistogramsVersion);
		TMyFitter(TString VariableName, TString HistogramsVersion);
		~TMyFitter() {};

		Double_t	GetChi2(Double_t p1, Double_t p2, Double_t p3);
		Double_t	GetMinChi2(){return fChi2Min;};

		Int_t		Fit();

                void            SetScaleLF(bool set_scale) {fScaleLF = set_scale; };
                void            SetScaleLFSize(Float_t scale_size) {fScaleLFSize = scale_size; };

                // getters
                Float_t         get_k_uds() {return k_uds;};
                Float_t         get_k_c() {return k_c;};
                Float_t         get_k_b() {return k_b;};
                Float_t         get_k_uds_err() {return k_uds_err;};
                Float_t         get_k_c_err() {return k_c_err;};
                Float_t         get_k_b_err() {return k_b_err;};

                void            Initialize();

	private:
		Double_t	fChi2Min;
		Double_t	fChi2init;
		TString		fBinName;
		TString		fHistogramsVersion;

		//  Minuit object
		TMinuit*	fMinuit;

		/** histograms which are used for the fit
		 */
		TDistribution	bin1;
		TDistribution	bin2;
		TDistribution	bin3;
		TDistribution	UnsubstrTOT;

		// scaling factors
		Double_t	k_b;
		Double_t	k_c;
		Double_t	k_uds;

		// scaling factors statistical uncertainties
		Double_t	k_b_err;
		Double_t	k_c_err;
		Double_t	k_uds_err;

                bool            fScaleLF;
                Float_t         fScaleLFSize;

};

