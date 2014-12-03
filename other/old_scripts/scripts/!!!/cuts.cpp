#include "TROOT.h"
#include "TMath.h"
/*
Header whith cuts applied on data in PHP
Basic version 02.11.2007
Use varisbles from Kt block of ORANGE
*/
Bool_t FLT_Trigger98(Int_t Fltpsw[2])
{

	Bool_t flt40, flt41, flt42, flt43;



	flt40 = (Bool_t)(Fltpsw[1] & (1 << 40-32));
	flt41 = (Bool_t)(Fltpsw[1] & (1 << 41-32));
	flt42 = (Bool_t)(Fltpsw[1] & (1 << 42-32));
	flt43 = (Bool_t)(Fltpsw[1] & (1 << 43-32));


		return (flt40||flt41||flt42||flt43);
}

Bool_t DST_64(Int_t Dstw[4])
{
	static Bool_t dst64;

	dst64 = (Bool_t)(Dstw[3-1] & (1 << (64-64) ));
	return (dst64);
}

Bool_t DST_65(Int_t Dstw[4])
{
	static Bool_t dst65;

	dst65 = (Bool_t)(Dstw[3-1] & (1 << (65-64) ));
	return (dst65);
}

Bool_t SLT_Trigger98(Int_t Sltw[6])
{
	Bool_t HPP01;

HPP01 = (Bool_t)(Sltw[5-1] & (1 << 1+12-1)); //jbit(SLTW(5),13) = HPP01

	return (HPP01);
}

Bool_t TLT_Trigger98(Int_t Tltw[14])
{
	Bool_t HPP01;
	//Bool_t HPP02;

	HPP01 = (Bool_t)(Tltw[5-1] & (1 << (1+16-1) ));
	//HPP02 = (Bool_t)(Tltw[5-1] & (1 << (2+16-1) ));

	return (HPP01);
}

Bool_t Yjb_test(Float_t Caltru_pos[3][600], Float_t Caltru_e[600], Int_t Ncaltru, Float_t Vtx_z)
{
	Float_t yjb=0;
	Float_t x,y,z,z_0,z_v,r,E_cell;
 	for(Int_t i=0;i<Ncaltru;i++)
	{
	 z_0=Caltru_pos[2][i];
	 y=Caltru_pos[1][i];
	 x=Caltru_pos[0][i];
	 E_cell=Caltru_e[i];
	 z_v=Vtx_z;
	 z=z_0+z_v;
	 r=sqrt(z*z+y*y+x*x);
	 yjb+=(E_cell-((z/r)*E_cell));
	}
	if(yjb>=0.16 && yjb<=0.7)return 1;
	return 0;
}
Bool_t Yjb_test(Float_t Siyjb)
{
	if(Siyjb>=0.16 && Siyjb<=0.7)return 1;
	return 0;
}
Bool_t Zvtx_test(Float_t Zvtx)
{
	if((Zvtx >= -34.0) && ( Zvtx<= 33.0))return 1;
	return 0;
}

Bool_t Nvctpar_to_Nvctrhl(Int_t Nvctpar, Int_t Nvctrhl)
{
	if((Float_t)Nvctpar/(Float_t)Nvctrhl > 0.1)return 1;
	else return 0;
}

Bool_t Pt_to_Et_test(Float_t Cal_pt, Float_t Cal_et)
{
	if(Cal_pt/sqrt(Cal_et)<=2.0)return 1;
	else return 0;
}
/*
Bool_t NC_background_test(Float_t Cal_pt, Float_t Cal_et)
{
	if(Cal_pt/sqrt(Cal_et)<=2.0)return 1;
	else return 0;
}

*/
//there are questions to NVctpar
Bool_t Number_bad_tracks(Float_t Vctrhl_zh, Int_t Vctrhl_nax,
			Int_t Vctrhl_nste, Int_t  Vctrhl_ndf,
			Float_t Vctpar_par1, Float_t Vctpar_par3,
			Float_t Vctrhl_pgevc, Float_t Vctrhl_qovr,
			Float_t Vctrhl_tdip)
{
Bool_t Bad;
Float_t theta = Vctpar_par1*(180./TMath::Pi());
Float_t cot = atan(1./Vctrhl_tdip)*(180./TMath::Pi());
Float_t pt = Vctrhl_pgevc*sin(cot/(180./TMath::Pi()))*TMath::Abs(Vctrhl_qovr/Vctpar_par3);

    if(Vctrhl_zh < -75. && Vctrhl_nax > 5 && Vctrhl_nste > 5 && Vctrhl_ndf >= 20 &&
    		(theta > 5. && theta < 70.) && (pt>=0.2))
    {
	Bad = 1;
	return  Bad;
    }
    else
    {
	Bad = 0;
	return Bad;
    }


}
//there are questions to NVctpar
Bool_t Number_good_tracks(Int_t  Vctrhl_ndf, Float_t Vctpar_par1, Float_t Vctpar_par3,Float_t Vctrhl_pgevc, Float_t Vctrhl_qovr, Float_t Vctrhl_tdip)
{
Bool_t Good;
Float_t theta = Vctpar_par1*(180./TMath::Pi());
Float_t cot = atan(1./Vctrhl_tdip)*(180./TMath::Pi());
Float_t pt = Vctrhl_pgevc*sin(cot/(180./TMath::Pi()))*TMath::Abs(Vctrhl_qovr/Vctpar_par3);

    if(Vctrhl_ndf >= 10 && (pt>=0.2 && pt<=150.) && (theta > 15. && theta < 164.))
    {
	Good = 1;
	return  Good;
    }
    else
    {
	Good = 0;
	return Good;
    }
}
//also question
Bool_t DIS_rejection_test(Float_t Siprob, Float_t Siyel)
{
//	Float_t r,x,y,z,theta,Y_el;
//	x=SiPos[0];
//	y=SiPos[1];
//	z=SiPos[2];
//	r=sqrt(x*x+y*y+z*z);
//	theta=z/r;
//	Y_el=1-((Sicalene/27.5)*sin(theta/2)*sin(theta/2));
	//for(Int_t i=0;i<SiNcand;i++)
	//{

	 if(Siprob<0.9 && Siyel>=0.7)return 0;
	//}
	return 1;
}

Bool_t Et_jet_test(Float_t Kt_etjet_a[8], Int_t Kt_njet_a)
{
	for(Int_t i=0;i<Kt_njet_a;i++)
	{
	 if(Kt_etjet_a[i]>13.)return 1;
	}
	return 0;

//	return 1;
}
Bool_t Eta_jet_test(Float_t Kt_etajet_a[8], Int_t Kt_njet_a)
{
	for(Int_t i=0;i<Kt_njet_a;i++)
	{
	 if(Kt_etajet_a[i] > -1. && Kt_etajet_a[i]<2.5 )return 1;
	}
	return 0;
}

Bool_t jet_test(Float_t Kt_etajet_a[8],Float_t Kt_etjet_a[8], Int_t Kt_njet_a)
{
	for(Int_t i=0;i<Kt_njet_a;i++)
	{
	 if(Kt_etjet_a[i]>13. && Kt_etajet_a[i] > -1.
	                      && Kt_etajet_a[i]<2.5 )return 1;
	}
	return 0;
}
