#include <TLorentzVector.h>
#include <TVector3.h>
int LorentzVectorTest()
{
	TLorentzVector		mom_Sprime(1,0,0,1);
	TVector3	boost(0.9,0,0);
	TLorentzVector		mom_S=mom_Sprime.Boost(boost);
	cout<<mom_S.Px()<<endl;
	cout<<mom_S.Py()<<endl;
	cout<<mom_S.Pz()<<endl;
	cout<<mom_S.E()<<endl;

	cout<<mom_Sprime.Px()<<endl;
	cout<<mom_Sprime.Py()<<endl;
	cout<<mom_Sprime.Pz()<<endl;
	cout<<mom_Sprime.E()<<endl;

	return 0;
}


