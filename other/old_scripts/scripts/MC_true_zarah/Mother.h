#ifndef __MOTHER_H__
#define __MOTHER_H__
#include "Daughter.h"
#include <TROOT.h>
class Mother
{
	public:
		Mother();
		//Mother(const Mother&);
		Mother(Daughter init_daughter1,Daughter init_daughter2);
		~Mother();
		Float_t 	GetPx_m();
		Float_t 	GetPy_m();
		Float_t 	GetPz_m();
		Float_t		GetPt_m();
		Float_t		GetP_m();
		Float_t		GetMass_m(Int_t daughter1,Int_t daughter2);
		Float_t		GetEta_m();
		Float_t		GetTheta_m();
		Float_t		Get_AP_alpha_m();
		Float_t		Get_AP_pt_m();
		Float_t		GetEt_m();
		Float_t		GetPhi_m();



	private:
		Daughter 	daughter1,daughter2;
		Float_t 	px_m,
				py_m,
				pz_m,
				p_m,
				pt_m,
				energy_m,
				mass_m,
				eta_m,
				theta_m;
};
#endif /*__MOTHER_H__*/
