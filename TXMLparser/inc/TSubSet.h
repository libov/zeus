//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TSUBSET_H__
#define __TSUBSET_H__

// ROOT headers
#include <TString.h>

class TSubSet {

    public:

        TSubSet();
        ~TSubSet() {};

        // enum structures to uniquely specify sample properties
        enum Type {
            kDATA = 1,
            kMC = 2,
            kUNKNOWNTYPE=99
        };

        enum Flavour {
            kLIGHT=1,
            kCHARM=2,
            kBEAUTY=3,
            kRHO=4,
            kUNKNOWNFLAVOUR=99
        };

        enum Process {
            kBGF=1,
            kRESOLVED=2,
            kBGFNOQED=3,
            kUNKNOWNPROCESS=99
        };

        enum Period {
            k03P = 1,       // NOTE: for DATA only
            k04P = 2,       // NOTE: for DATA only
            k0304P = 3,     // NOTE: for MC only
            k05E=4,
            k06E=5,
            k06P=6,         // NOTE: for DATA only
            k07P=7,         // NOTE: for DATA only
            k0607P=8,       // NOTE: for MC only
            kUNKNOWNPERIOD=99
        };

        enum Q2 {
            kQ2g1=1,
            kQ2g1_5=2,
            kQ2g4=3,
            kQ2g8=4,
            kQ2g16=5,
            kUNKNOWNQ2=99
        };

        // getters
        // variables in the xml file
        TString       getYear() {return    fYear;};
        TString       getType() {return    fType;};
        TString       getFlavour() {return    fFlavour;};
        TString       getQ2() {return fQ2;};
        TString       getCNversion() {return    fCN_version;};
        TString       getNamePattern() {return    fName_pattern;};
        unsigned      getTriggerPeriod() {return fTriggerPeriod;};
        Float_t       getLuminosity() {return    fLuminosity;};
        // enumerated variables, defined from the above ones
        Flavour       getFlavourENUM() {return fFlavourENUM;};
        Period        getPeriodENUM() {return fPeriodENUM;};
        Q2            getQ2ENUM() {return fQ2ENUM;};
        Type          getTypeENUM() {return fTypeENUM;};
        Process       getProcessENUM() {return fProcessENUM;};
        unsigned      getID() {return fID;};

        // setters
        void          setYear(TString year) {fYear = year;};
        void          setType(TString type) {fType = type;};
        void          setFlavour(TString flavour) {fFlavour = flavour;};
        void          setQ2(TString q2) {fQ2 = q2;};
        void          setCNversion(TString CN_version) {fCN_version = CN_version;};
        void          setNamePattern(TString name_pattern) {fName_pattern = name_pattern;};
        void          setTriggerPeriod(unsigned trigger_period) {fTriggerPeriod = trigger_period;};
        void          setLuminosity(Float_t luminosity) {fLuminosity = luminosity;};
        void          setID(unsigned id) {fID = id;};
        void          setFlavourENUM(Flavour flav) {fFlavourENUM = flav;};
        void          setPeriodENUM(Period period) {fPeriodENUM = period;};
        void          setQ2ENUM(Q2 q2) {fQ2ENUM = q2;};
        void          setTypeENUM(Type type) {fTypeENUM = type;};
        void          setProcessENUM(Process process) {fProcessENUM = process;};

        // others
        void          Classify();
        void          Print();
        void          defineSampleName() {fSampleName = fType+fYear+fCN_version+fName_pattern;};
        TString       getSampleName(){ return fSampleName;};
        void          operator= (TSubSet);

    private:

        // this duplicates the "sample" structure in the xml file
        TString       fYear;
        TString       fType;
        TString       fFlavour;
        TString       fQ2;
        TString       fCN_version;
        TString       fName_pattern;
        unsigned      fTriggerPeriod;      // id of the trigger subperiod; 0 if all used simultaneously
        Float_t       fLuminosity;

        // variables to allow easy random-access;
        // are defined from above ones but can also be set with public setters
        Flavour       fFlavourENUM;
        Period        fPeriodENUM;        // this is different from "year" because data from several years
                                          //  several years (03-04, 06-07) can form a single period; see comments in Classify()
        Q2            fQ2ENUM;
        Type          fTypeENUM;
        Process       fProcessENUM;

        // other variables defined from an xml-file
        TString       fSampleName;

        // a unique identifier of the subset
        unsigned      fID;
};
#endif
