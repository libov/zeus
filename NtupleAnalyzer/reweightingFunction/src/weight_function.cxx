#include<weight_function.h>

TRew::TRew(Int_t* nstor, Int_t *id, Int_t *prt, Int_t *daug){

  Fmck_nstor = nstor;
  Fmck_id = id;
  Fmck_prt = prt;
  Fmck_daug = daug;
  
  string prefix = "";
  //string prefix = "reweightingFunction/weightTables/";
  
  string path_Dplus = prefix + "finalDplusWithErrors_v1.01";
  string path_D0 = prefix + "finalD0WithErrors_v1.01";
  string path_Ds = prefix + "finalDsWithErrors_v1.01";
  string path_Lambc = prefix + "finalLambcWithErrors_v1.01";
  //string filePathFragFrac = prefix + "cardFragmFrac";
  string filePathFragFrac = prefix + "cardFragmFrac_Erich";
  
  sChannelDplus = GetDecayListFromFile(path_Dplus);
  sChannelD0 = GetDecayListFromFile(path_D0);
  sChannelDs = GetDecayListFromFile(path_Ds);
  sChannelLambc = GetDecayListFromFile(path_Lambc);
 
  weightBRDplus = GetWeights(path_Dplus);
  weightBRD0 = GetWeights(path_D0);
  weightBRDs = GetWeights(path_Ds);
  weightBRLambc = GetWeights(path_Lambc);
    
  vectPart = GetPartListForFragFrac(filePathFragFrac);
  vectAntiPart = GetAntiPartListForFragFrac(filePathFragFrac);
  fragFracWeight = GetFragFracWeightVector(filePathFragFrac);
}

TRew::~TRew () {
}

Double_t TRew::GetEventWeight(bool isCharm){

  Double_t weight = 1.0;
  
  for (Int_t kk=0; kk<*Fmck_nstor; kk++){
    
    Int_t true_type = Fmck_prt[kk];
  
    string strTrueType = SayType(true_type);
           
    bool isDplus = (read_flag_string(strTrueType,"D+")||read_flag_string(strTrueType,"D-"));
    bool isD0 = (read_flag_string(strTrueType,"D0")||read_flag_string(strTrueType,"Dbar0"));
    bool isDs = (read_flag_string(strTrueType,"Ds+")||read_flag_string(strTrueType,"Ds-"));
    bool isLambc = (read_flag_string(strTrueType,"Lambc+")||read_flag_string(strTrueType,"Lambc-"));
    
    if ( ((isDplus)||(isD0)||(isDs)||(isLambc))==false ) continue;
    
    if (isCharm) weight = weight * GetFragFracWeight(strTrueType);
    
    Int_t true_id = Fmck_id[kk];
    string particles = "";
    
    for (Int_t i=0; i<*Fmck_nstor; i++){
      if (Fmck_daug[i]==true_id){
        particles += SayType(Fmck_prt[i]);
      }
    }
    
    string currentDecayString = TransformDecayString(particles);
    
    if (isDplus){
      for (Int_t j=0;j<(sChannelDplus.size());j++){
        if (sChannelDplus[j] == currentDecayString){
          weight = weight * weightBRDplus[j];
          continue;
        }
      }
    }
    if (isD0){
      if (currentDecayString == "K+K*+"){
        if (read_nflag_string(particles,"K*-")!=0){
          weight = weight * weightBRD0[1];
        }
        if (read_nflag_string(particles,"K*+")!=0){
          weight = weight * weightBRD0[0];
        }
      }
      else{
        for (Int_t j=2;j<(sChannelD0.size());j++){
          if (sChannelD0[j] == currentDecayString){
            weight = weight * weightBRD0[j];
            continue;
          }
        }
      }
    }
    if (isDs){
      bool isInChannels = false;
      for (Int_t j=0;j<(sChannelDs.size());j++){
        if (sChannelDs[j] == currentDecayString){
          weight = weight * weightBRDs[j];
          isInChannels = true;
          continue;
        }
      }
      if (isInChannels==false){
          weight = weight * weightBRDs[31];
      }
    }
    if (isLambc){
      bool isInChannels = false;
      for (Int_t j=0;j<(sChannelLambc.size());j++){
        if (sChannelLambc[j] == currentDecayString){
          weight = weight * weightBRLambc[j];
          isInChannels = true;
          continue;
        }
      }
      if (isInChannels==false){
          weight = weight * weightBRLambc[63];
      }
    }
  }
  
  return weight;
  
}

vector<Double_t> TRew::GetWeights(string path){

  vector<Double_t> oldBR;
  vector<Double_t> newBR;

  ifstream myfile (path.c_str());
  string line;
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      if (line=="") continue;
      oldBR.push_back(atof(GetWordFromString(line,2).c_str()));
      newBR.push_back(atof(GetWordFromString(line,3).c_str()));
    }
    myfile.close();
  }
  else cout << endl << "WARNING!!! Unable to open file in GetWeights(): file: " << path << endl; 

  vector<Double_t> vectWeight;

  if (oldBR.size()!=newBR.size()) cout << "WARNING: Sizes of input vectors are different!!!" << endl;
  
  Double_t sumNew = 0.;
  Double_t sumOld = 0.;
  
  for (Int_t i=0; i<oldBR.size(); i++){
    if (TMath::Abs(newBR[i]-oldBR[i])<0.00001) continue;
    sumNew += newBR[i];
    sumOld += oldBR[i];
  }
  
  for (Int_t i=0; i<oldBR.size(); i++){
    if (TMath::Abs(newBR[i]-oldBR[i])<0.00001){
      vectWeight.push_back((1.-sumNew)/(1.-sumOld));
      cout << (i+1) << "  oldBR = " << oldBR[i] << "  newBR = " << newBR[i] << "  weight: " << (1.-sumNew)/(1.-sumOld) << endl;
    }
    else{
      vectWeight.push_back(newBR[i]/oldBR[i]);
      cout << (i+1) << "  oldBR = " << oldBR[i] << "  newBR = " << newBR[i] << "  weight: " << newBR[i]/oldBR[i] << endl;
    }
  }
  vectWeight.push_back((1.-sumNew)/(1.-sumOld));
  
  return vectWeight;

}


Double_t TRew::GetFragFracWeight(const string strInput){

  for (Int_t i=0; i<fragFracWeight.size(); i++){
    if ( (strInput==vectPart[i])||(strInput==vectAntiPart[i]) ){
      return fragFracWeight[i];
    }
  }
  return 1.0;
}



vector<Double_t> TRew::GetFragFracWeightVector(string filePath){
  vector<Double_t> weightFragFrac;
  vector<string> partList;
  vector<Double_t> oldValue;
  vector<Double_t> newValue;
  
  ifstream myfile (filePath.c_str());
  string line;
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      if (line.compare(0,1,"#") == 0) continue;
      bool emptyLine = true;
      for (Int_t qq=0; qq<line.size(); qq++){
        if (line.compare(qq,1," ") != 0){
          emptyLine = false;
          break;
        }
      }
      if ((line=="")||(emptyLine)) continue;

      partList.push_back( GetWordFromString(line,1) );
      oldValue.push_back( atof(GetWordFromString(line,3).c_str()) );
      newValue.push_back( atof(GetWordFromString(line,4).c_str()) );

    }
    Double_t normalizationFactor = 0.0;
    for (Int_t kk=0; kk<partList.size(); kk++){
      if (partList[kk]!="Lambc+"){
        normalizationFactor += newValue[kk];
      }
      else{
        normalizationFactor += newValue[kk] + 0.14*oldValue[kk];
      }
    }
    Double_t floatCheck = 0.0;

    for (Int_t kk=0; kk<partList.size(); kk++){
      weightFragFrac.push_back(newValue[kk]/oldValue[kk]/normalizationFactor);
      cout << "FragmFrac: weight = " << newValue[kk]/oldValue[kk]/normalizationFactor << endl;
      if (partList[kk]!="Lambc+"){
        floatCheck += newValue[kk]/normalizationFactor;
      }
      else{
        floatCheck += newValue[kk]/normalizationFactor + 0.14*oldValue[kk]/normalizationFactor;
      }
    }
//    cout << "BeforeRew (must be appr. 1.0) = " << (oldValue[0] + oldValue[1] + oldValue[2] + 1.14*oldValue[3]) << endl;
//    cout << "AfterRew (must be appr. 1.0) = " << floatCheck << endl;
    myfile.close();
  }
  else cout << endl << "WARNING!!! Unable to open file"  << endl; 
 
  return weightFragFrac;
}


vector<string> TRew::GetPartListForFragFrac(string filePath){
  vector<string> partList;
  
  ifstream myfile (filePath.c_str());
  string line;
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      if (line.compare(0,1,"#") == 0) continue;
      bool emptyLine = true;
      for (Int_t qq=0; qq<line.size(); qq++){
        if (line.compare(qq,1," ") != 0){
          emptyLine = false;
          break;
        }
      }
      if ((line=="")||(emptyLine)) continue;

      partList.push_back( GetWordFromString(line,1) );

    }
    myfile.close();
  }
  else cout << endl << "WARNING!!! Unable to open file" << endl; 
 
  return partList;
}

string TRew::GetWordFromString(const string str, Int_t number)
{

// ***************************************************** 
//
// Function return number'th word from input string;
// If string begins with "#" function will return "";
// If "number" is greater then there are words in string
// function will return "";
//
// *****************************************************

  Int_t spaceCounter = 0;
  Int_t wordCounter = 0;
  Int_t beginWordTemp = 0;

   Int_t firstNonSpaceSymbol = 0;
   while ((str.compare(firstNonSpaceSymbol,1," ") == 0))
   {
     firstNonSpaceSymbol++;
   }

  for (Int_t k=firstNonSpaceSymbol; k<(str.size()+1); k++)
  {
    if ((str.compare(k,1," ") == 0)||(k==str.size()))
    {
      spaceCounter++;
      if (spaceCounter>=2) continue;

      wordCounter++;
      if ((firstNonSpaceSymbol!=0)&&(wordCounter==1)) beginWordTemp=firstNonSpaceSymbol;

      if (wordCounter == number){
        string tempWord (str.begin()+beginWordTemp,str.begin()+k);
        return tempWord;
      }
    }
    else
    {
      if (spaceCounter!=0) beginWordTemp = k;
      spaceCounter = 0;
    }
  }
  return "";
}

vector<string> TRew::GetAntiPartListForFragFrac(string filePath){
  vector<string> antiPartList;
  
  ifstream myfile (filePath.c_str());
  string line;
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      if (line.compare(0,1,"#") == 0) continue;
      bool emptyLine = true;
      for (Int_t qq=0; qq<line.size(); qq++){
        if (line.compare(qq,1," ") != 0){
          emptyLine = false;
          break;
        }
      }
      if ((line=="")||(emptyLine)) continue;

      antiPartList.push_back( GetWordFromString(line,2) );

    }
    myfile.close();
  }
  else cout << endl << "WARNING!!! Unable to open file" << endl; 
 
  return antiPartList;
}


vector<string> TRew::GetDecayListFromFile(string path){

  vector<string> vectStr;

  ifstream myfile (path.c_str());
  string line;
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      if (line.compare(0,1,"#") == 0) continue;
      bool emptyLine = true;
      for (Int_t qq=0; qq<line.size(); qq++){
        if (line.compare(qq,1," ") != 0){
          emptyLine = false;
          break;
        }
      }
      if ((line=="")||(emptyLine)) continue;
      vectStr.push_back( GetWordFromString(line,1) );
    }
    myfile.close();
  }
  else cout << endl << "WARNING!!! Unable to open file" << endl; 
  
  vectStr.push_back("OtherChannels");
  
  cout << "Lenght of file = " << vectStr.size() << endl;
  
  return vectStr;

}

bool TRew::read_flag_string(const string line_of_all_flags, const string flag){
  string flag1 = flag;
  string flag_all = line_of_all_flags;
  Int_t size_all = flag_all.size();
  Int_t size1 = flag1.size();
  if (size_all>=size1){
    bool temp = false;
    Int_t i=0;
    while ((i<=(size_all-size1))&&(temp==false)){
      if (flag_all.compare(i,size1,flag1)==0){temp=true;}
      i++;  
    }
    return temp;
  }
  else{
    return false;
  }
}

Int_t TRew::read_nflag_string(const string& flag_all, const char *flag){

  string flag1 = string(flag);
  Int_t size_all = flag_all.size();
  Int_t size1 = flag1.size();
  if (size_all>=size1){
    Int_t temp = 0;
    for (Int_t i=0; i<=(size_all-size1); i++){
      if (flag_all.compare(i,size1,flag1)==0){temp++;}
    }

    return temp;
  }
  else{
    return 0;
  }
}






char* TRew::SayType(Int_t prt)
{

  switch(prt)
     {

  case 5: return "STRANGE";
  case 6: return "STRANGE_bar";
  case 7: return "CHARM";
  case 8: return "CHARM_bar";
  
  case 17: return "e_Neutrino";
  case 18: return "e_barNeutrino";
  case 19: return "mu_Neutrino";
  case 20: return "mu_barNeutrino";
  case 21: return "tau_Neutrino";
  case 22: return "tau_barNeutrino";
  case 23: return "e-";
  case 24: return "e+";
  case 25: return "mu-";
  case 26: return "mu+";
  case 27: return "tau-";
  case 28: return "tau+";
  case 29: return "gamma";
  
  case 32: return "Z0";
  
  case 54: return "pi+";
  case 55: return "pi-";
  case 56: return "pi0";
  case 57: return "eta";  
  case 58: return "K+";
  case 59: return "K-";
  case 60: return "K0";
  case 61: return "Kbar0";
  case 62: return "K_short";
  
  case 64: return "D+";
  case 65: return "D-";
  case 66: return "D0";
  case 67: return "Dbar0";
  case 68: return "Ds+";
  case 69: return "Ds-";
  case 70: return "Ds*+";
  case 71: return "Ds*-";
  
  case 76: return "rho+";
  case 77: return "rho-";
  case 78: return "rho0";
  case 79: return "omega";
  case 80: return "etp"; // previous was "etap" or "eta'"
  case 81: return "f_0";
  
  case 85: return "phi";
  
  case 90: return "A1+";
  case 91: return "A1-";
  
  case 146: return "K*+";
  case 147: return "K*-";
  case 148: return "K*0";
  case 149: return "K*bar0";
  case 150: return "K1(1270)+";
  case 151: return "K1(1270)-";
  case 152: return "K1(1270)0";
  case 153: return "K1(1270)bar0";
  case 154: return "K1(1400)+";
  case 155: return "K1(1400)-";
  case 156: return "K1(1400)0";
  case 157: return "K1(1400)bar0";
  
  case 186: return "D*+";
  case 187: return "D*-";
  case 188: return "D*0";
  case 189: return "D*bar0";
  case 190: return "PROTON+";
  case 191: return "PROTON-";
  case 192: return "NEUTRON";
  case 193: return "NEUTRO_bar";
  case 194: return "Lambda";
  case 195: return "Lambd_bar"; 
  case 196: return "Sigmau+";
  case 197: return "Sigmau-";
  case 198: return "Sigma0";
  case 199: return "Sigmabar0";

  case 208: return "Lambc+";
  case 209: return "Lambc-";
    
  case 256: return "Delta2+";
  case 257: return "Delta2-";
  case 258: return "DeltaU+";
  case 259: return "DeltaU-";
  case 260: return "Delta0";
  case 261: return "Deltabar0";
  case 262: return "Delta_Dminus";
  case 263: return "Delta_Dplus";
  
  case 352: return "Sigm*u+";
  case 353: return "Sigm*u-";
  case 354: return "Sigm*0";
  case 355: return "Sigm*bar0";
  case 356: return "Sigm*D_minus";
  case 357: return "Sigm*D_plus";
  
  case 404: return "Xi0";
  case 405: return "Xibar0";
  case 406: return "Xi*0";
  case 407: return "Xi*bar0";
  
  case 435: return "Sigmc*2+";
  case 436: return "Sigmc*2-";
  case 437: return "Sigmc*+";
  case 438: return "Sigmc*-";
  case 439: return "Sigmc*0";
  case 440: return "Sigmc*bar0";
  
  case 2091: return "cluster";
  case 2092: return "string";
  case 2093: return "indep.";
  

  default: sprintf(chArray,"%i",prt);
  
  return chArray;
  
     }
  return "We don't have such staff";
}


string TRew::TransformDecayString(string inputStr){
  Int_t typeArray[34];    
  for (Int_t i=0;i<34;i++){
    typeArray[i] = 0;
  }
  GetHashSummLight(inputStr,typeArray);
  return GetStringDecayChannel(typeArray);
}

void TRew::GetHashSummLight(const string& inputString, Int_t* array){

  string sTypeParticlePos[34] = {"pi+","K+","e+","mu+","tau+","K*+","A1+","rho+","PROTON+","K1(1270)+","K*0","K0","e_Neutrino","mu_Neutrino","tau_Neutrino","NEUTRON","K1(1400)0","Delta2+","Lambda","Sigma0","Delta0","Sigm*0","DeltaU+","Sigmc*+","Sigmau+","Sigm*u+","eta","etp","omega","phi","pi0","rho0","f_0","K_short"};
   
  string sTypeParticleNeg[34-8] = {"pi-","K-","e-","mu-","tau-","K*-","A1-","rho-","PROTON-","K1(1270)-","K*bar0","Kbar0","e_barNeutrino","mu_barNeutrino","tau_barNeutrino","NEUTRO_bar","K1(1400)bar0","Delta2-","Lambd_bar","Sigmabar0","Deltabar0","Sigm*bar0","DeltaU-","Sigmc*-","Sigmau-","Sigm*u-"};

  for (Int_t i=0; i<(34-8); i++){
    array[i]+=read_nflag_string(inputString,sTypeParticlePos[i].c_str());
    array[i]+=read_nflag_string(inputString,sTypeParticleNeg[i].c_str());
  }
  for (Int_t i=(34-8); i<34; i++){
    array[i]+=read_nflag_string(inputString,sTypeParticlePos[i].c_str());
  }
}

string TRew::GetStringDecayChannel(Int_t *arr){
  string sTypeParticlePos[34] = {"pi+","K+","e+","mu+","tau+","K*+","A1+","rho+","PROTON+","K1(1270)+","K*0","K0","e_Neutrino","mu_Neutrino","tau_Neutrino","NEUTRON","K1(1400)0","Delta2+","Lambda","Sigma0","Delta0","Sigm*0","DeltaU+","Sigmc*+","Sigmau+","Sigm*u+","eta","etp","omega","phi","pi0","rho0","f_0","K_short"};
  string sOut = "";
  for (Int_t i=0; i<34; i++){
    if (arr[i]==0) continue;
    if (arr[i]==1) {sOut += sTypeParticlePos[i];
        continue;}
    if (arr[i]==2) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==3) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==4) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==5) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==6) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==7) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==8) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==9) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
    if (arr[i]==10) {sOut += sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i] + sTypeParticlePos[i];
        continue;}
        
  }
  return sOut;
}
