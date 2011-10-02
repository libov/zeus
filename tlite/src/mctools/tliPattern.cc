#include "tliPattern.hh"
#include "tliPartTab.hh"

#include <iostream>
#include <algorithm>
#include <functional>

#include "FMCKin.h"

#define ADAMO_INULLREP 2147483647

typedef struct VMCUCOM {
  int J_FMCKIN;
  int J_REC;
  int mc_fmcvtx;
  float vertex[3];
  float Pmom[3];
  int nctdsl_mc[9];
  int nmvdview_mc[4];
  int nctdsl_rc[9];
  int nmvdview_rc[4];
  int lrgrid_mcrc;
  int nmvdview_mcrc[4];
  int ifid_physics;
  int ifid_ctd;
  int istat_ctd;
  int ifid_mvd;
  int istat_mvd;
  int ifid_ctdmvd;
  int istat_ctdmvd;
  int ifid_mvdsa;
  int istat_mvdsa;
};

extern "C" {
  extern VMCUCOM vmcu_fmckco__;
}

//FORTRAN function stubs
extern "C" {
  //adamo
  int coutab_(int& tab);
  void gettab_(int& tab);
  void fettab_(int& tab, int& acc, int& cur);  
  // VMCU
  void vmcu_(int& mode_tracks,int& mode_mc,
             int& mode_rc,int& jdump,
             int& jfmckin,int& jrc,
             int& match,int& ierr);
}

using namespace std;

tliPattern::tliPattern(){
  particleId = 0;
  matchFmckin = 0;
  matchRec = 0;
  reconstructed = 0;
  particleName = "(UNDEF)";
  antiId = 0;
  antiName = "(UNDEF)";
}

tliPattern::tliPattern(const string& theParticleName) {
  particleId = 0;
  matchFmckin = 0;
  matchRec = 0;
  reconstructed = 0;

  // find particle in table
  particleId = tliPartTab::Instance()->getFmcId(theParticleName);
  if (particleId == 0) cout << "tliPattern Constructor: "
			    << " particle " << theParticleName
			    << " not identified " << endl;
  particleName = theParticleName;
  antiId = tliPartTab::Instance()->getAntiFmcId(theParticleName);
  antiName = tliPartTab::Instance()->getAntiName(theParticleName);
}

tliPattern::tliPattern(const tliPattern& tp){
  particleId = tp.particleId;
  particleName = tp.particleName;
  antiId = tp.antiId;
  antiName = tp.antiName;
  matchFmckin = 0;
  matchCC = 0;
  matchRec = 0;
  reconstructed = 0;
  for (vector <tliPattern*>::const_iterator ti=(tp.daughters).begin();
       ti != (tp.daughters).end(); ++ti) {
    //daughters.push_back(new tliPattern((*ti)->particleName));
    daughters.push_back(new tliPattern(*(*ti)));
  }
  // do not copy match information
}


tliPattern::tliPattern(string theParticleName,const tliPattern& tp){
  particleId = 0;
  matchFmckin = 0;
  matchRec = 0;
  matchCC = 0;
  reconstructed = 0;
  // find particle in table
  particleId = tliPartTab::Instance()->getFmcId(theParticleName);
  if (particleId == 0) cout << "tliPattern renaming Constructor: "
			    << " particle " << theParticleName
			    << " not identified " << endl;
  particleName = theParticleName;
  antiId = tliPartTab::Instance()->getAntiFmcId(theParticleName);
  antiName = tliPartTab::Instance()->getAntiName(theParticleName);

  for (vector <tliPattern*>::const_iterator ti=(tp.daughters).begin();
       ti != (tp.daughters).end(); ++ti) {
    daughters.push_back(new tliPattern(*(*ti)));
  }
  // do not copy match information
}



tliPattern& tliPattern::operator=(const tliPattern& tp) {
  if (this != &tp) {
    // first, remove daughters
    for (vector <tliPattern*>::iterator dit=daughters.begin();
	 dit != daughters.end(); ++dit) {
      delete (*dit);
    }
    daughters.clear();
    matchFmckin = 0;
    matchCC = 0;
    matchRec = 0;
    reconstructed = 0;

    // copy daughters
    for (vector <tliPattern*>::const_iterator odit=tp.daughters.begin();
	 odit != tp.daughters.end(); ++odit) {
      // create copy of pattern
      tliPattern* theNewOne = new tliPattern(*(*odit));
      daughters.push_back(theNewOne);
    }
    particleId = tp.particleId;
    particleName = tp.particleName;
    antiId = tp.antiId;
    antiName = tp.antiName;
  }
  return *this;
}


tliPattern tliPattern::operator+(const tliPattern& tp2) const {
  tliPattern result;
  if (particleName == "(COMB)") {
    // extend existing combination
    result = *this;
    result.addDaughter(new tliPattern(tp2));
    return result;
  }
  // create new combination
  result.particleId = 0;
  result.particleName = "(COMB)";
  result.addDaughter(new tliPattern(*this));
  result.addDaughter(new tliPattern(tp2));
  return result;
}


tliPattern tliPattern::spd() {
  tliPattern result;
  result.particleId = 0;
  result.particleName = "(COMB)";
  result.addDaughter(new tliPattern(*this));
  return result;
}

tliPattern* tliPattern::d(const unsigned i) {
  if (i<0 || i>=daughters.size()) {
    cout << "tliPattern::d(): Bad daughter index " << i 
	 << ", number of daughters " << daughters.size() << endl;
    return 0;
  }
  return daughters[i];
}


tliPattern::~tliPattern() {
  for (vector <tliPattern*>::iterator ti=daughters.begin();
       ti != daughters.end(); ++ti) {
    delete *ti;
  }
}


void tliPattern::addDaughter(tliPattern* ti) {
  daughters.push_back(ti);
}


int tliPattern::doMatchFmckin(int fmckinId,int cc) {
  matchFmckin = 0;
  // access corresponding row in fmckin
  if (fmckin_.ID != fmckinId) {
    fmckin_.ID = fmckinId;
    gettab_(fmckin_.fmckin);
  }
  
  // first check id of particle
  if ((cc == 1) && (fmckin_.FMCPrt == particleId)) {
    // match the particle
    matchFmckin = fmckin_.ID;
    matchCC = +1;
    //cout << particleName << " particle match successful for fmckin_.ID=" 
    //	 << fmckin_.ID << endl;
  } else if ((cc == -1) && (fmckin_.FMCPrt == antiId)) {
    // match the anti-particle
    matchFmckin = fmckin_.ID;
    matchCC = -1;
  }
  if (matchFmckin == 0) return 0;

  // if type match successful, check if daughters required
  if (daughters.size() == 0) return 1;

  // find MC daughters
  vector<int> mcdaug;
  unsigned nmcdaug = tliPartTab::getFmcDaug(fmckin_.ID,mcdaug);

  // check if number of daughters is right
#ifdef PRINTALL
  if (nmcdaug!=daughters.size()) {
    cout << "Number of daughters " << nmcdaug << " "
	 << daughters.size() << " WRONG" << endl;
  }
#endif
  if (nmcdaug != daughters.size()) return 0;

  // if number of daughters correct, sort the ids
  sort(mcdaug.begin(),mcdaug.end());

  // try to match daughters

  // loop over permutations of MC daughters
  bool proceed = 1;
  while (proceed) {
    int allMatched = 1; // keep track whether iteration has matched
    for (vector <tliPattern*>::iterator ti=daughters.begin();
	 ti != daughters.end(); ++ti) {
      if (! (*ti)->doMatchFmckin(mcdaug[ti-daughters.begin()],cc)) {
	allMatched = 0;
	break;
      }
    }
    if (allMatched) return 1;
    proceed = next_permutation(mcdaug.begin(),mcdaug.end());
  }

  // no match of any permutation has succeeded
  return 0;
}



int tliPattern::doMatchRec(int mode) {
  cout << "This is doMatchRec for "
    << "(" << particleName << ")"
       << " FMCPrt_id=" << particleId
       << " FMCKin_id=" << matchFmckin 
       << " mode " << mode << endl;
  reconstructed = 0;
  if (!matchFmckin) return 0;  // no MC match
  // if final state, match it
  if (daughters.size() ==0) {
    int mode_tracks = mode; // ZTTRHL etc
    int mode_mc = matchFmckin;
    int mode_rc = 0;
    int jdump = 0;
    int jfmckin;
    int jrc;
    int match;
    int ierr;
    vmcu_(mode_tracks,mode_mc,mode_rc,jdump,jfmckin,jrc,match,ierr);
    if (ierr != 0) {
      cout << "tliPattern::doMatchRec: vmcu returns ierr=" 
	   << ierr << endl;
      return 0;
    }
    if (match>0) {
      matchRec = jrc;
      reconstructed = 1;
      return 1;
    }
    return 0;
  }
  // recursively match daughters
  for (vector <tliPattern*>::iterator dit=daughters.begin();
       dit != daughters.end(); ++dit) {
    if (! (*dit)->doMatchRec(mode)) return 0;
  }
  // all daughters matched successfully
  reconstructed = 1;
  return 1;
}



int tliPattern::fillMatches(vector<tliPattern*>& output) {
  int ADAMO_ID = ADAMO_INULLREP - 1;
  tliPattern* thePattern = 0;
  int nFill = 0;
  // loop over FMCKin table
  for (int i=1; i<=coutab_(fmckin_.fmckin); ++i) {
    // prepare clone of current instance if not already existing
    if (!thePattern) thePattern = new tliPattern(*this); 
    fettab_(fmckin_.fmckin,ADAMO_ID,i);
    // try match as particle
    if (thePattern->doMatchFmckin(fmckin_.ID,+1)) {
      output.push_back(thePattern);
      ++nFill;
      thePattern = 0;
    }
    // try match as anti-particle
    else if (thePattern->doMatchFmckin(fmckin_.ID,-1)) {
      output.push_back(thePattern);
      ++nFill;
      thePattern = 0;
    }
  }
  // clean up left-over clones
  if (thePattern) delete thePattern;
  return nFill;
}


int tliPattern::countMatches() {  
  int ADAMO_ID = ADAMO_INULLREP - 1;
  tliPattern* thePattern = 0;
  int nFill = 0;
  // loop over FMCKin table
  for (int i=1; i<=coutab_(fmckin_.fmckin); ++i) {
    // prepare clone of current instance if not already existing
    if (!thePattern) thePattern = new tliPattern(*this); 
    fettab_(fmckin_.fmckin,ADAMO_ID,i);
    // try match as particle
    if (doMatchFmckin(fmckin_.ID,+1)) {
      ++nFill;
    }
    // try match as anti-particle
    else if (doMatchFmckin(fmckin_.ID,-1)) {
      ++nFill;
    }
  }
  // clean up left-over clones
  if (thePattern) delete thePattern;
  return nFill;
}
    


void tliPattern::print(const string& prefix) {
  cout << prefix << "(" << particleName << ")"
       << " FMCPrt_id=" << particleId
       << " FMCKin_id=" << matchFmckin 
       << " matchRec=" << matchRec 
       << " reconstructed=" << reconstructed << endl;
  for (vector <tliPattern*>::iterator dit=daughters.begin();
       dit != daughters.end(); ++dit) {
    (*dit)->print(prefix+"-");
  }
}
