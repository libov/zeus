//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TCROSSSECTIONBIN_H__
#define __TCROSSSECTIONBIN_H__

// ROOT includes
#include <TString.h>

#include <iostream>

class TCrossSectionBin{

        public:
		TCrossSectionBin();
		~TCrossSectionBin(){};

                // setters
                void            set_k_uds (Float_t k_uds) { fk_uds = k_uds; };
                void            set_k_c (Float_t k_c) { fk_c = k_c; };
                void            set_k_b (Float_t k_b) { fk_b = k_b; };
                void            set_k_uds_err (Float_t k_uds_err) { fk_uds_err = k_uds_err; };
                void            set_k_c_err (Float_t k_c_err) { fk_c_err = k_c_err; };
                void            set_k_b_err (Float_t k_b_err) { fk_b_err = k_b_err; };
                void            set_sigma_uds_true (Float_t sigma_uds_true) { fsigma_uds_true = sigma_uds_true; };
                void            set_sigma_c_true (Float_t sigma_c_true) { fsigma_c_true = sigma_c_true; };
                void            set_sigma_b_true (Float_t sigma_b_true) { fsigma_b_true = sigma_b_true; };
                void            set_sigma_uds (Float_t sigma_uds) { fsigma_uds = sigma_uds; };
                void            set_sigma_c (Float_t sigma_c) { fsigma_c = sigma_c; };
                void            set_sigma_b (Float_t sigma_b) { fsigma_b = sigma_b; };
                void            set_sigma_uds_err (Float_t sigma_uds_err) { fsigma_uds_err = sigma_uds_err; };
                void            set_sigma_c_err (Float_t sigma_c_err) { fsigma_c_err = sigma_c_err; };
                void            set_sigma_b_err (Float_t sigma_b_err) { fsigma_b_err = sigma_b_err; };
                void            set_sigma_c_err_syst_up (Float_t sigma_c_err_syst_up) { fsigma_c_err_syst_up = sigma_c_err_syst_up; };
                void            set_sigma_c_err_syst_down (Float_t sigma_c_err_syst_down) { fsigma_c_err_syst_down = sigma_c_err_syst_down; };
                void            set_sigma_b_err_syst_up (Float_t sigma_b_err_syst_up) { fsigma_b_err_syst_up = sigma_b_err_syst_up; };
                void            set_sigma_b_err_syst_down (Float_t sigma_b_err_syst_down) { fsigma_b_err_syst_down = sigma_b_err_syst_down; };
                void            setID (unsigned id) {fID = id;};
                void            setBinWidth (Float_t    bin_width) { fBinWidth = bin_width; };
                void            addSubBin(TString variable_name, Float_t low_edge, Float_t up_edge);

                // getters
                Float_t         get_k_uds () { return fk_uds; };
                Float_t         get_k_c () { return fk_c; };
                Float_t         get_k_b () { return fk_b; };
                Float_t         get_k_uds_err () { return fk_uds_err; };
                Float_t         get_k_c_err () { return fk_c_err; };
                Float_t         get_k_b_err () { return fk_b_err; };
                Float_t         get_sigma_uds_true () { return fsigma_uds_true; };
                Float_t         get_sigma_c_true () { return fsigma_c_true; };
                Float_t         get_sigma_b_true () { return fsigma_b_true; };
                Float_t         get_sigma_uds () { return fsigma_uds; };
                Float_t         get_sigma_c () { return fsigma_c; };
                Float_t         get_sigma_b () { return fsigma_b; };
                Float_t         get_sigma_uds_err () { return fsigma_uds_err; };
                Float_t         get_sigma_c_err () { return fsigma_c_err; };
                Float_t         get_sigma_b_err () { return fsigma_b_err; };
                Float_t         get_sigma_c_err_syst_up () { return fsigma_c_err_syst_up; };
                Float_t         get_sigma_c_err_syst_down () { return fsigma_c_err_syst_down; };
                Float_t         get_sigma_b_err_syst_up () { return fsigma_b_err_syst_up; };
                Float_t         get_sigma_b_err_syst_down () { return fsigma_b_err_syst_down; };
                unsigned        getID () { return  fID; };
                Float_t         getBinWidth () { return  fBinWidth; };
                unsigned        getNSubBins() { return fSubBinList.size(); };

                TString         getSubBinVariable(unsigned subbin_index);
                Float_t         getSubBinLowEdge(unsigned subbin_index);
                Float_t         getSubBinUpEdge(unsigned subbin_index);

                //  = operator
                void            operator= (TCrossSectionBin);
                
                // print some parameters
                void            Print();

	private:
                
                // this duplicates binning.dtd
                Float_t         fk_uds;
                Float_t         fk_c;
                Float_t         fk_b;

                Float_t         fk_uds_err;
                Float_t         fk_c_err;
                Float_t         fk_b_err;
                
                Float_t         fsigma_uds_true;
                Float_t         fsigma_c_true;
                Float_t         fsigma_b_true;

                Float_t         fsigma_uds;
                Float_t         fsigma_c;
                Float_t         fsigma_b;

                Float_t         fsigma_uds_err;
                Float_t         fsigma_c_err;
                Float_t         fsigma_b_err;

                Float_t         fsigma_c_err_syst_up;
                Float_t         fsigma_c_err_syst_down;
                Float_t         fsigma_b_err_syst_up;
                Float_t         fsigma_b_err_syst_down;

                struct SubBin {
                                TString         fVariableName;
                                Float_t         flow_edge;
                                Float_t         fup_edge;
                };

                std::vector<SubBin>  fSubBinList;

                Float_t         fBinWidth;      // multiple of all bin widths

                unsigned        fID;
};

#endif
