#ifndef TLIPARTTAB_HH
#define TLIPARTTAB_HH

// interface class to ZEUS particle table
//   singleton class

#include "FMCPrt.h"

#include <vector>
#include <string>

class tliPartTab {

 private:
  std::vector<FMCPRT_DEF> mcvec;
  std::vector<int> pdgCodes;

 protected:
  tliPartTab();

 public:
  static tliPartTab* Instance();
  static tliPartTab* pinstance;
  int getFmcId(const std::string& partName); // convert particle name to id
  int getAntiFmcId(const std::string& partName); // get id of anti-particle
  std::string getAntiName(const std::string& partName); // get name of anti-particle
  static void chopTrailBlanks(std::string& s);
  static int getFmcDaug(const int fmckinId,std::vector<int>& output); // find daughters
};



#endif
