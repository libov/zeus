//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  september 2009                              //
//                                              //
//////////////////////////////////////////////////
#include <inc/TMyFitter.h>
#include <inc/TDistribution.h>
#include <TROOT.h>
#include <TFile.h>
#include <TMinuit.h>
#include <TSystem.h>
#include <iostream>
#include <fstream>
using namespace std;

TMyFitter::TMyFitter(TString BinName, void (*func)(Int_t&, Double_t*, Double_t&, Double_t*, Int_t) , TString HistogramsVersion):
fChi2Min(10000),
bin1(BinName,"significance_massbin1_mirrored",HistogramsVersion),
bin2(BinName,"significance_massbin2_mirrored",HistogramsVersion),
bin3(BinName,"significance_massbin3_mirrored",HistogramsVersion),
UnsubstrTOT(BinName,"significance",HistogramsVersion),
fBinName(BinName),
fHistogramsVersion(HistogramsVersion),
fMinuit(new TMinuit(3)),
fScaleLF(false)
{
    fMinuit->SetFCN(func);
    Initialize();
}

void TMyFitter::Initialize() {
    cout << "INFO: Initializing TMyFitter for " << fBinName << endl;

    if (fScaleLF) {
        cout << "INFO: scaling light flavour component in the mirrored distributions by a factor of " << fScaleLFSize << endl;
        bin1.ScaleInput(1.000, 1.000, fScaleLFSize);
        bin2.ScaleInput(1.000, 1.000, fScaleLFSize);
        bin3.ScaleInput(1.000, 1.000, fScaleLFSize);
        bin1.FillArrays();
        bin2.FillArrays();
        bin3.FillArrays();
    }

    fChi2init = GetChi2(1,1,1);
    cout << "INFO: fChi2init= " << fChi2init << endl;

    TString  ParName[3] = {"p1","p2","p3"};
    Double_t startVal[3]={1.,1.,1.};
    Double_t fitStep[3] = {0.01,0.001,0.001};
    Double_t limitMin[34]={0,0,0};
    Double_t limitMax[34]={10000,10000,10000};

    for (int i=0;i<3;i++) {
        fMinuit->DefineParameter(i,ParName[i],startVal[i],fitStep[i],limitMin[i],limitMax[i]);
    }
}


Double_t TMyFitter::GetChi2(Double_t p1, Double_t p2, Double_t p3) {
    Double_t tempChi2 = 0;
    tempChi2=tempChi2+bin1.CalculateChi2(p1,p2,p3);
    tempChi2=tempChi2+bin2.CalculateChi2(p1,p2,p3);
    tempChi2=tempChi2+bin3.CalculateChi2(p1,p2,p3);
    tempChi2=tempChi2+UnsubstrTOT.CalculateChi2Norm(p1,p2,p3);

    if (tempChi2 < fChi2Min) fChi2Min = tempChi2;
    return tempChi2;
}

Int_t TMyFitter::Fit() {
    
    // print some stuff
    cout<<"INFO: Fitting distributions in "<<fBinName<<" subdirectory"<<endl;
    // perform the fit with Migrad, store the error flag
    Int_t  fit_result = fMinuit->Migrad();
    // check the error flag and print the result
    if (fit_result != 0) {
        cout << "ERROR: The Migrad() command did not finish successfully!! " << endl;
        abort();
    } else {
        cout << "INFO: The Migrad() command finished successfully! " << endl;
    }

    // Call HESSE - that is calculate error matrix
    Double_t    arglist[10];
    arglist[0] = 2000;
    arglist[1] = 0.0;
    Int_t       ierflag=0;
    cout << "INFO: invoking HESSE! " << endl;
    gMinuit->mnexcm("HESSE",arglist,1,ierflag);
    if (ierflag != 0) {
        cout << "ERROR: HESSE didn't finish successfully!! " << endl;
        abort();
    } else {
        cout << "INFO: HESSE finished successfully! " << endl;
    }
    
    // call minos
    cout << "INFO: Performing MINOS error analysis! " << endl;
    fMinuit->mnmnos();
    cout << "INFO: MINOS error analysis finished! " << endl;

    // get the fit parameters and errors
    Double_t    par[3];
    Double_t    par_err[3];
    for (int k=0; k<3;k++) {
        fMinuit->GetParameter(k, par[k], par_err[k]);
    }

    // store them
    k_b = par[0];
    k_c = par[1];
    k_uds = par[2];

    k_b_err=par_err[0];
    k_c_err=par_err[1];
    k_uds_err=par_err[2];

    Double_t    k_b_rel_err=(100.) * k_b_err/k_b;
    Double_t    k_c_rel_err=(100.) * k_c_err/k_c;
    Double_t    k_uds_rel_err=(100.) * k_uds_err/k_uds;

    cout<<"***************************************"<<endl;
    cout<<"Fit results for "<<fBinName<<endl;
    cout<<"k_b="<<k_b<<" +- "<<k_b_err<<" ("<<k_b_rel_err<<"%)"<<endl;
    cout<<"k_c="<<k_c<<" +- "<<k_c_err<<" ("<<k_c_rel_err<<"%)"<<endl;
    cout<<"k_uds="<<k_uds<<" +- "<<k_uds_err<<" ("<<k_uds_rel_err<<"%)"<<endl;
    cout<<"Chi2 of the fit: "<<fChi2Min/(21.+1.-3.)<<endl;
    cout<<"***************************************"<<endl;
    
    bin1.Draw(k_b,k_c,k_uds,"e3");
    bin2.Draw(k_b,k_c,k_uds,"e3");
    bin3.Draw(k_b,k_c,k_uds,"e3");
    UnsubstrTOT.Draw(k_b,k_c,k_uds,"Hist");
    
    TString    path = getenv ("HISTO_PATH");
    TString    FileName = path + "/fitted." + fHistogramsVersion + "." + fBinName;
    cout << FileName+".root" << endl;
    TFile *out=new TFile(FileName+".root","recreate");
    bin1.Write(out);
    bin2.Write(out);
    bin3.Write(out);
    UnsubstrTOT.Write(out);
    
    ofstream myfile;
    myfile.open (FileName+".txt");
    myfile<<"***************************************"<<endl;
    myfile<<"Fit results for "<<fBinName<<endl;
    myfile<<"k_b="<<k_b<<" +- "<<k_b_err<<" ("<<k_b_rel_err<<"%)"<<endl;
    myfile<<"k_c="<<k_c<<" +- "<<k_c_err<<" ("<<k_c_rel_err<<"%)"<<endl;
    myfile<<"k_uds="<<k_uds<<" +- "<<k_uds_err<<" ("<<k_uds_rel_err<<"%)"<<endl;
    myfile<<"Chi2 of the fit: "<<fChi2Min/(21.+1.-3.)<<endl;
    myfile<<"***************************************"<<endl;
    
    myfile.close();
    
    return fit_result;
}
