#ifndef __CINT__
#include <iostream>
#include <TROOT.h>
using namespace std;
#include <TMath.h>
#include <Daughter.h>
#endif
Daughter::Daughter()
{
}
/*Daughter::Daughter(const Daughter& inDaughter)
{
px=inDaughter.GetPx();
py=inDaughter.GetPy();
pz=inDaughter.GetPz();
}*/
Daughter::Daughter(Float_t init_px,Float_t init_py,Float_t init_pz)
{
	px=init_px;
	py=init_py;
	pz=init_pz;
}
Daughter::~Daughter()
{
}
void Daughter::SetPx(Float_t px_arg)
{
	px=px_arg;
}
Float_t Daughter::GetPx()
{
	//cout<<"in daughter get px="<<px<<endl;

	return px;
}
void Daughter::SetPy(Float_t py_arg)
{
	py=py_arg;
}
Float_t Daughter::GetPy()
{
	return py;
}
void Daughter::SetPz(Float_t pz_arg)
{
	pz=pz_arg;
}
Float_t Daughter::GetPz()
{
	return pz;
}
Float_t Daughter::GetPt()
{
	pt=sqrt(px*px+py*py);
	return pt;
}
Float_t Daughter::GetP()
{
	p=sqrt(px*px+py*py+pz*pz);
	//cout<<"Daughter: "<<p<<endl;
	return p;
}

Float_t Daughter::GetEnergy(Int_t assumption)
{
	Float_t const_mass=0;
	switch (assumption)
	{
 		case 1:	const_mass=0.497672; break; // K0s
		case 2:	const_mass=1.115683; break; // Lambda/Lambdabar
		case 3:	const_mass=0.000511; break; // Electron/positron
		case 4: const_mass=0.139570; break; // Charged pions
		case 5: const_mass=0.497672; break; // Neutral kaons  DELETE!!!!!!!!!
		case 6: const_mass=0.938272; break; // Proton/Antiproton
	}
	p=this->GetP();
	energy=sqrt(const_mass*const_mass+p*p);
	return energy;
}
Float_t Daughter::GetEta()
{
	p=this->GetP();
	Float_t theta=acos(pz/p);
	eta=(-1)*log(tan(theta/2));
	return eta;
}
Float_t Daughter::GetPhi()
{
	// returns phi [0,2pi]
	pt=this->GetPt();
	px=this->GetPx();
	py=this->GetPy();
	Double_t	phi=0;
	if (py>0) {phi=acos(px/pt);}
	if (py<0) {phi=2*TMath::Pi()-acos(px/pt);}
	return phi;
}
