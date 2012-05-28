//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  March 2011                                  //
//                                              //
//////////////////////////////////////////////////

#include<TCrossSectionBin.h>

#include <iostream>

using namespace std;

TCrossSectionBin::TCrossSectionBin():
fk_uds(0),
fk_c(0),
fk_b(0),
fk_uds_err(0),
fk_c_err(0),
fk_b_err(0),
fsigma_uds_true(0),
fsigma_c_true(0),
fsigma_b_true(0),
fsigma_uds(0),
fsigma_c(0),
fsigma_b(0),
fsigma_uds_err(0),
fsigma_c_err(0),
fsigma_b_err(0),
fsigma_c_err_syst(0),
fsigma_b_err_syst(0),
fBinWidth(0)
{
}

// sets all the variables of the current TCrossSectionBin
// note: ID is not overwritten
void    TCrossSectionBin::operator=(TCrossSectionBin      newbin){

        fk_uds = newbin.get_k_uds();
        fk_c = newbin.get_k_c();
        fk_b = newbin.get_k_b();

        fk_uds_err = newbin.get_k_uds_err();
        fk_c_err = newbin.get_k_c_err(); 
        fk_b_err = newbin.get_k_b_err(); 
                
        fsigma_uds_true = newbin.get_sigma_uds_true(); 
        fsigma_c_true = newbin.get_sigma_c_true(); 
        fsigma_b_true = newbin.get_sigma_b_true(); 

        fsigma_uds = newbin.get_sigma_uds(); 
        fsigma_c = newbin.get_sigma_c(); 
        fsigma_b = newbin.get_sigma_b(); 

        fsigma_uds_err = newbin.get_sigma_uds_err(); 
        fsigma_c_err = newbin.get_sigma_c_err(); 
        fsigma_b_err = newbin.get_sigma_b_err(); 

        fsigma_c_err_syst = newbin.get_sigma_c_err_syst(); 
        fsigma_b_err_syst = newbin.get_sigma_b_err_syst(); 
}

void    TCrossSectionBin::Print(){

        cout << "(shortened) information about this object:\n";
        cout << "ID= " << fID << endl;

        cout << "k_uds= " << fk_uds << endl;
        cout << "k_c= " << fk_c << endl;
        cout << "k_b= " << fk_b << endl;

        cout << "sigma_uds= " << fsigma_uds << endl;
        cout << "sigma_c= " << fsigma_c << endl;
        cout << "sigma_b= " << fsigma_b << endl;

        cout << "sigma_uds_err= " << fsigma_uds_err << endl;
        cout << "sigma_c_err= " << fsigma_c_err << endl;
        cout << "sigma_b_err= " << fsigma_b_err << endl;

        cout << "sigma_c_err_syst= " << fsigma_c_err_syst << endl;
        cout << "sigma_b_err_syst= " << fsigma_b_err_syst << endl;
}

void    TCrossSectionBin::addSubBin(TString variable_name, Float_t low_edge, Float_t up_edge){
        
        // create an instance of SubBin structure
        SubBin cSubBin;
        
        // set it's parameters as given with arguments
        cSubBin.fVariableName = variable_name;
        cSubBin.flow_edge = low_edge;
        cSubBin.fup_edge = up_edge;

        // add it to the list of SubBins of this bin
        fSubBinList.push_back(cSubBin);
}

TString         TCrossSectionBin::getSubBinVariable(unsigned subbin_index) {
        // first check if index is not too high
        if (subbin_index >= fSubBinList.size() ) {
                cout << "ERROR TCrossSectionBin::getSubBinVariable(..): requested subbin index too high\n";
                cout << "Terminating!\n";
                abort();
        }

        return fSubBinList[subbin_index].fVariableName;
}
Float_t         TCrossSectionBin::getSubBinLowEdge(unsigned subbin_index) {
        // first check if index is not too high
        if (subbin_index >= fSubBinList.size() ) {
                cout << "ERROR TCrossSectionBin::getSubBinLowEdge(..): requested subbin index too high\n";
                cout << "Terminating!\n";
                abort();
        }
        return fSubBinList[subbin_index].flow_edge;
}
Float_t         TCrossSectionBin::getSubBinUpEdge(unsigned subbin_index) {
        // first check if index is not too high
        if (subbin_index >= fSubBinList.size() ) {
                cout << "ERROR TCrossSectionBin::getSubBinUpEdge(..): requested subbin index too high\n";
                cout << "Terminating!\n";
                abort();
        }
        return fSubBinList[subbin_index].fup_edge;
}
