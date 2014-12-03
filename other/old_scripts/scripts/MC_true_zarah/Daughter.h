#ifndef __DAUGHTER_H__
#define __DAUGHTER_H__
#include <TROOT.h>
class Daughter
{
	public:
		Daughter();
		Daughter(Float_t init_px,Float_t init_py,Float_t init_pz);
		~Daughter();
		void	 	SetPx(Float_t px_arg);
		void 		SetPy(Float_t py_arg);
		void 		SetPz(Float_t pz_arg);
		Float_t 	GetPx();
		Float_t 	GetPy();
		Float_t 	GetPz();
		Float_t		GetP();
		Float_t		GetPt();
		Float_t		GetEnergy(Int_t assumption);
		Float_t		GetEta();
		Float_t		GetPhi();



	private:
		Float_t 	px,
				py,
				pz,
				p,
				pt,
				energy,
				eta,
				phi;
};
#endif /*__DAUGHTER_H__*/
