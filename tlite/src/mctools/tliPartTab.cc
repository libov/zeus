#include "tliPartTab.hh"

#include "FMCKin.h"
#include "FMCVtx.h"
#include "FMCPCd.h"

#include <iostream>
#include <string>

#include <algorithm>
#include <vector>

#define ADAMO_INULLREP 2147483647


using std::cout;
using std::endl;
using std::string;
using std::vector;

//FORTRAN function stubs
extern "C" {
  //adamo
  int coutab_(int& tab);
  void gettab_(int& tab);
  void fettab_(int& tab, int& acc, int& cur);
}

tliPartTab* tliPartTab::pinstance = 0;// initialize pointer
tliPartTab* tliPartTab::Instance ()
{
  if (pinstance == 0)  { // is it the first call?
    pinstance = new tliPartTab; // create sole instance
  }
  return pinstance; // address of sole instance
}


tliPartTab::tliPartTab() {
  int ADAMO_ID = ADAMO_INULLREP - 1;

  for (int i=1; i<=coutab_(fmcprt_.fmcprt); ++i) {
    fettab_(fmcprt_.fmcprt,ADAMO_ID,i);
    mcvec.push_back(fmcprt_);

    int stable = 0;
    fmcpcd_.ID = fmcprt_.ID;
    gettab_(fmcpcd_.fmcpcd);
    int PdgCode = fmcpcd_.StandCod;
    pdgCodes.push_back(PdgCode);
    if ( PdgCode ==  211  || // Pi+
         PdgCode == -211  || // Pi-
         PdgCode ==  321  || // K+
         PdgCode == -321  || // K-
         PdgCode ==  2212 || // Proton
         PdgCode == -2212 || // Antiproton
         PdgCode == -11   || // e+
         PdgCode ==  11   || // e-
         PdgCode == -13   || // mu+
         PdgCode ==  13      // mu-
         ) stable = 1;
  }
  cout << "tliPartTab constructor: mcvec size " 
       << mcvec.size() << endl;
}
    
int tliPartTab::getFmcId(const string& partName) {
  for (vector<FMCPRT_DEF>::iterator fit=mcvec.begin();
       fit != mcvec.end(); ++fit) {

    string tabName((*fit).Name,16);
    tliPartTab::chopTrailBlanks(tabName);
    string thePartName = partName;
    tliPartTab::chopTrailBlanks(thePartName);

    if (partName == tabName) {
      return fit-mcvec.begin()+1;
    }
  }
  return 0;
}

int tliPartTab::getAntiFmcId(const string& partName){
  int theId = getFmcId(partName);
  if (theId != mcvec[theId-1].ID) {
    cout << "tliPartTab::getAntiFmcId: " << theId << " fmckin_id="
	 << mcvec[theId-1].ID << endl;
  }
  int thePdg = pdgCodes[theId-1];
  // look for entry with negative PDG code
  vector<int>::iterator pn = find(pdgCodes.begin(),pdgCodes.end(),-thePdg);
  if (pn != pdgCodes.end()) {
    return (pn-pdgCodes.begin()+1);
  }
  cout << " Anti-particle not found for " << partName << endl;
  return 0;
}

string tliPartTab::getAntiName(const string& partName){
  int theAntiId = tliPartTab::getAntiFmcId(partName);
  if (theAntiId == 0) return "notFound";
  string antiName(mcvec[theAntiId-1].Name,16);
  tliPartTab::chopTrailBlanks(antiName);
  return antiName;
}

void tliPartTab::chopTrailBlanks(string& s) {
  // remove trailing blanks
  unsigned lb=s.size()-1;
  while (s[lb]==' ' && lb>0) {
    --lb;
  }
  if (lb<s.size()-1) {
    s.erase(lb+1,s.size()-1-lb);
  }
}

int tliPartTab::getFmcDaug(const int fmckinId,vector<int>& output){
  int ADAMO_ID = ADAMO_INULLREP - 1;
  int nDgt = 0;
  // find daughters using the Daughter_of attribute
  for (int i=1; i<=coutab_(fmckin_.fmckin); ++i) {
    fettab_(fmckin_.fmckin,ADAMO_ID,i);
    if (fmckin_.DaughterOf == fmckinId) {
      output.push_back(fmckin_.ID);
      ++nDgt;
    }
  }
  return nDgt;
}
    
  
extern "C" {
  void iniparttab_() {
    cout << " pi+ "
	 << tliPartTab::Instance()->getFmcId("PI     +") << endl;  
    cout << "D0      "
	 << tliPartTab::Instance()->getFmcId("D0") << endl;
    cout << " id for anti- D0 "
	 << tliPartTab::Instance()->getAntiFmcId("D0") << endl
	 << " name " 
	 << tliPartTab::Instance()->getAntiName("D0") << endl;
  }
}
