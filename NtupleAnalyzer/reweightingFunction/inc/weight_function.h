#ifndef __WEIGHT_FUNCTION_H_INCLUDED__
#define __WEIGHT_FUNCTION_H_INCLUDED__

#include <TROOT.h>
#include <TSystem.h>
#include <TH1.h>
#include <iostream>
#include <sstream>
#include <TMath.h>
#include <fstream>
using namespace std;

class TRew
{
private:
Int_t *Fmck_id;
Int_t *Fmck_nstor;    
Int_t *Fmck_prt;
Int_t *Fmck_daug;

vector<string> sChannelDplus;
vector<string> sChannelD0;
vector<string> sChannelDs;
vector<string> sChannelLambc;
vector<string> vectPart;
vector<string> vectAntiPart;
vector<Double_t> weightBRDplus;
vector<Double_t> weightBRD0;
vector<Double_t> weightBRDs;
vector<Double_t> weightBRLambc;
vector<Double_t> fragFracWeight;

public:
char chArray[20];
TRew(Int_t*, Int_t*, Int_t*, Int_t*);
~TRew ();
Double_t GetEventWeight(bool isCharm);
vector<Double_t> GetWeights(string path);
Double_t GetFragFracWeight(const string strInput);
vector<Double_t> GetFragFracWeightVector(string filePath);
vector<string> GetPartListForFragFrac(string filePath);
string GetWordFromString(const string str, Int_t number);
vector<string> GetAntiPartListForFragFrac(string filePath);
vector<string> GetDecayListFromFile(string path);
bool read_flag_string(const string line_of_all_flags, const string flag);
Int_t read_nflag_string(const string& flag_all, const char *flag);
string TransformDecayString(string inputStr);
char* SayType(Int_t prt);
string GetStringDecayChannel(Int_t *arr);
void GetHashSummLight(const string& inputString, Int_t* array);

};


#endif
