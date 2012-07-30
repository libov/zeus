//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
#include <inc/TBin.h>
#include <inc/VariablePhase.h>

#include <iostream>
using namespace std;

TBin::TBin()
{
}

TBin::TBin(TString VarDescr, Float_t* Variable, Float_t LowerEdge, Float_t UpperEdge, VariablePhase VarPhase):
fVariable(Variable),
fLowerEdge(LowerEdge),
fUpperEdge(UpperEdge),
fVarPhase(VarPhase)
{
    char low_char[256];
    char up_char[256];
    sprintf(low_char,"%3.4f<",fLowerEdge);
    sprintf(up_char,"<%3.4f",fUpperEdge);
    TString low = low_char;
    TString up = up_char;
    fVariableDescription = low + VarDescr + up;
}

// check whether current event satisfies this subbin
Bool_t TBin::CheckBin() {

    // get a value of a relevant variable for this event
    Float_t Value;
    Value= *fVariable;

    // check if it is within allowed range of this bin
    if ( (Value>fLowerEdge) && (Value<fUpperEdge) ) return true;
    return false;
}

TString TBin::GetDescription() {
    return fVariableDescription;
}

VariablePhase TBin::GetVarPhase() {
    return fVarPhase;
}
