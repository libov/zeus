//////////////////////////////////////////////////
//////////////                   /////////////////
//////////////   K0s   analysis  /////////////////
//////////////    with V0lite    /////////////////
//////////////                   /////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                August 2008                   //
//                                              //
//                                              //
//////////////////////////////////////////////////
//////////                             ///////////
//////////    Combining      K0sK0s    ///////////
//////////                             ///////////
//////////////////////////////////////////////////
//                                              //
//   1. Reading data from small trees           //
//   2. Event & K0s selection                   //
//   3. Combining into K0s and writing          //
//                                              //
//////////////////////////////////////////////////
#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TFile.h>
#include <TROOT.h>
#include <TVector3.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif
Int_t aa=-1;
//aa=19;
void nigga(Int_t b)
{
	cout<<"in function (begin)"<<endl;
	cout<<b<<endl;
	cout<<"change value"<<endl;
	b=5;
	cout<<b<<endl;
	cout<<"in function (end)"<<endl;
}
void analysis()
{
	Int_t	lk=3;
	cout<<lk<<endl;
	cout<<"before function"<<endl;
	nigga(lk);
	cout<<"after function"<<endl;
	cout<<lk<<endl;
	cout<<aa<<endl;

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

