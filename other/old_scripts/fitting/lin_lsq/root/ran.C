#include  <TRandom1.h>
#include  <TF1.h>

void ran() {
  Double_t x;
  TRandom *r1 = new TRandom1();
  //  x = r1->Rndm(1);
  //  cout << "x = " << x << endl;
  x = r1->Gaus(0.,1.); 
  cout << "x = " << x << endl;
}
