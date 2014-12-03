#ifndef __CINT__
#include <iostream>
using namespace std;
#include <Mother.h>
#include <TMath.h>//
//#include <Daughter.h>
//#include <Daughter.cxx>
#endif
Mother::Mother()
{
}
/*Mother::Mother(const Mother& initMother)
{
}
*/
Mother::Mother(Daughter init_daughter1,Daughter init_daughter2)
{
	//cout<<"in mother constructor:"<<endl;
	daughter1=init_daughter1;
	daughter2=init_daughter2;
	//cout<<"Check: "<<daughter1.GetPx()<<endl;
}
Mother::~Mother()
{
}
Float_t Mother::GetPx_m()
{
	px_m=daughter1.GetPx()+daughter2.GetPx();
	return px_m;
}
Float_t Mother::GetPy_m()
{
	py_m=daughter1.GetPy()+daughter2.GetPy();
	return py_m;
}
Float_t Mother::GetPz_m()
{
	pz_m=daughter1.GetPz()+daughter2.GetPz();
	return pz_m;
}
Float_t Mother::GetPt_m()
{
	px_m=this->GetPx_m();
	py_m=this->GetPy_m();
	return sqrt(px_m*px_m+py_m*py_m);
}
Float_t Mother::GetP_m()
{
	px_m=this->GetPx_m();
	py_m=this->GetPy_m();
	pz_m=this->GetPz_m();
	p_m=sqrt(px_m*px_m+py_m*py_m+pz_m*pz_m);
	return p_m;
}
Float_t Mother::GetMass_m(Int_t daughter1_assumption,Int_t daughter2_assumption)
{
	Float_t 	m1=0,
			m2=0;
	switch (daughter1_assumption)
	{
 		case 1:	m1=0.497672; break; // K0s
		case 2:	m1=1.115683; break; // Lambda/Lambdabar
		case 3:	m1=0.000511; break; // Electron/positron
		case 4: m1=0.139570; break; // Charged pions
		case 5: m1=0.497672; break; // Neutral kaons  DELETE!!!!!!!!!
		case 6: m1=0.938272; break; // Proton/Antiproton
	}
	switch (daughter2_assumption)
	{
 		case 1:	m2=0.497672; break; // K0s
		case 2:	m2=1.115683; break; // Lambda/Lambdabar
		case 3:	m2=0.000511; break; // Electron/positron
		case 4: m2=0.139570; break; // Charged pions
		case 5: m2=0.497672; break; // Neutral kaons  DELETE!!!!!!!!!
		case 6: m2=0.938272; break; // Proton/Antiproton
	}

	//cout<<"Mother, Get_Pm() "<<daughter1_assumption<<" "<<daughter1.GetPx()<<endl;

	Float_t 	E1=daughter1.GetEnergy(daughter1_assumption);
	Float_t 	E2=daughter2.GetEnergy(daughter2_assumption);
	energy_m=E1+E2;
	Float_t 	px1=daughter1.GetPx();
	Float_t 	py1=daughter1.GetPy();
	Float_t 	pz1=daughter1.GetPz();
	Float_t 	px2=daughter2.GetPx();
	Float_t 	py2=daughter2.GetPy();
	Float_t 	pz2=daughter2.GetPz();
	Float_t 	scalar_comp=px1*px2+py1*py2+pz1*pz2;//cout<<" sc_comp "<<scalar_comp<<endl;
	//cout<<scalar_comp<<endl;
	mass_m=sqrt(m1*m1+m2*m2+2*E1*E2-2*scalar_comp);
	return mass_m;
}
Float_t Mother::GetEta_m()
{
	Float_t theta=acos((this->GetPz_m())/(this->GetP_m()));
	eta_m=(-1)*log(tan(theta/2));
	return eta_m;
}
Float_t Mother::GetTheta_m()
{
	theta_m=57.2957*acos((this->GetPz_m())/(this->GetP_m()));
	return theta_m;
}

Float_t	Mother::Get_AP_alpha_m()
{
	Float_t		alpha;

	Float_t 	px1=daughter1.GetPx();
	Float_t 	py1=daughter1.GetPy();
	Float_t 	pz1=daughter1.GetPz();
	Float_t 	px2=daughter2.GetPx();
	Float_t 	py2=daughter2.GetPy();
	Float_t 	pz2=daughter2.GetPz();

	Double_t	p1=0,
				p2=0;

	Double_t	cos_lab1=0,
				cos_lab2=0;
	Double_t scal1=0,
				scal2=0;
	Double_t	pL_1=0,
				pL_2=0,
			pT_1=0,
			pT_2=0;

	px_m=this->GetPx_m();
	py_m=this->GetPy_m();
	pz_m=this->GetPz_m();
	p_m=sqrt(px_m*px_m+py_m*py_m+pz_m*pz_m);

	p1=sqrt(px1*px1+py1*py1+pz1*pz1);
	p2=sqrt(px2*px2+py2*py2+pz2*pz2);

	scal1=px_m*px1+py_m*py1+pz_m*pz1;
	scal2=px_m*px2+py_m*py2+pz_m*pz2;

	cos_lab1=scal1/(p1*p_m);
	cos_lab2=scal2/(p2*p_m);

	pL_1=p1*cos_lab1;
	pL_2=p2*cos_lab2;

	pT_1=p1*sqrt(1-cos_lab1*cos_lab1);
	pT_2=p2*sqrt(1-cos_lab2*cos_lab2);
	//cout<<pT_1-pT_2<<endl;
	//cout<<pL_1-pL_2<<endl;

	alpha=(pL_1-pL_2)/(pL_1+pL_2);
	return alpha;

}
Float_t Mother::Get_AP_pt_m()
{
	Float_t 	px1=daughter1.GetPx();
	Float_t 	py1=daughter1.GetPy();
	Float_t 	pz1=daughter1.GetPz();
	Float_t 	px2=daughter2.GetPx();
	Float_t 	py2=daughter2.GetPy();
	Float_t 	pz2=daughter2.GetPz();

	Double_t	p1=0,
			p2=0;

	Double_t	cos_lab1=0,
			cos_lab2=0;
	Double_t 	scal1=0,
			scal2=0;
	Double_t	pL_1=0,
			pL_2=0,
			pT_1=0,
			pT_2=0;

	px_m=this->GetPx_m();
	py_m=this->GetPy_m();
	pz_m=this->GetPz_m();
	p_m=sqrt(px_m*px_m+py_m*py_m+pz_m*pz_m);

	p1=sqrt(px1*px1+py1*py1+pz1*pz1);
	p2=sqrt(px2*px2+py2*py2+pz2*pz2);

	scal1=px_m*px1+py_m*py1+pz_m*pz1;
	scal2=px_m*px2+py_m*py2+pz_m*pz2;

	cos_lab1=scal1/(p1*p_m);
	cos_lab2=scal2/(p2*p_m);

	pL_1=p1*cos_lab1;
	pL_2=p2*cos_lab2;

	pT_1=p1*sqrt(1-cos_lab1*cos_lab1);
	pT_2=p2*sqrt(1-cos_lab2*cos_lab2);
	//cout<<pT_1<<" "<<pT_2<<endl;

	return pT_1;
}

Float_t	Mother::GetEt_m()
{
	Float_t		K0sK0s_et=0;
	Float_t		sin_m=(this->GetPt_m())/(this->GetP_m());
	K0sK0s_et=energy_m*sin_m;

	return		K0sK0s_et;
}
Float_t Mother::GetPhi_m()
{
	// returns phi [0,2pi]
	Double_t	pt=this->GetPt_m();
	Double_t	px=this->GetPx_m();
	Double_t	py=this->GetPy_m();
	Double_t	phi=0;
	if (py>0) {phi=acos(px/pt);}
	if (py<0) {phi=2*TMath::Pi()-acos(px/pt);}
	return phi;
}
Float_t Mother::GetE_m(Int_t daughter1_assumption,Int_t daughter2_assumption)
{

	Float_t 	E1=daughter1.GetEnergy(daughter1_assumption);
	Float_t 	E2=daughter2.GetEnergy(daughter2_assumption);
	energy_m=E1+E2;
	return energy_m;
}


