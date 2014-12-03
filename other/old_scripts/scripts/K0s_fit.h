#ifndef __K0SFIT_H__
#define __K0SFIT_H__
#include <TROOT.h>
#include<TH1F.h>
#include<TF1.h>
class K0s_fit
{
	public:
		K0s_fit();
		K0s_fit(TH1F * hinv_init);
		~K0s_fit();

		void		Draw();
		void		Draw_fsum();
		void		Draw_Signal_Bg();
		void 		Print();
		void		Fit();
		Double_t	GetK0cand();
		Double_t	GetUpBand();
		Double_t	GetDownBand();

	private:
		TH1F 		* hinv;
		TF1 		* fsum;
		TF1 		* fpol1;
		TF1 		* fgaus1;
		TF1 		* fgaus2;
		TF1 		* fline;
		TAxis		* xaxis;
		Double_t	bin_width,
				histRangeLow,
				histRangeUp;

		Double_t	parameters[15];
		Double_t	Signal,
				Background,
				K0cand,
				UpBand,
				DownBand,
				fitRangeLow,
				fitRangeUp;
		Int_t		nbins;

};
#endif /*__K0SFIT_H__*/
