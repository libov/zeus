//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#include<TSubSet.h>

#include <iostream>
using namespace std;

TSubSet::TSubSet():
fTypeENUM(kUNKNOWNTYPE),
fFlavourENUM(kUNKNOWNFLAVOUR),
fPeriodENUM(kUNKNOWNPERIOD),
fQ2ENUM(kUNKNOWNQ2),
fTriggerPeriod(0),
fProcessENUM(kUNKNOWNPROCESS),
fSampleName("DUMMY"),
fID(0)
{
}

void TSubSet::Classify() {

    // define whether it's data or MC
    if (fType.Contains("data")) {
        fTypeENUM = kDATA;
    } else if (fType.Contains("mc")) {
        fTypeENUM = kMC;
    } else {
        cout << "ERROR in TSubSet::Classify(): could not determine type of the sample (data or MC)! ";
        cout << "Terminating!" << endl;
        abort();
    }

    // determine period of the sample. slightly different treatment of data and MC.
    // Far from being elegant, to be revisited.
    // The reason for difference: in data, there's a separate sample for
    // each year: 05e, 06e, 06p, 07p.
    // In MC however there's no distinction between 06p and 07p, it's called just 07p.
    // In our notation this corresponds to Period::k0607p, while for data there will be
    // both Period::k06p and Period::k07p. The same holds for 0304p.

    if (fTypeENUM == kMC) {
        if (fYear.Contains("04") && (!fYear.Contains("05"))) {
            fPeriodENUM = k0304P;
        } else if (fYear.Contains("05")) {
            fPeriodENUM = k05E;
        } else if (fYear.Contains("06") && (!fYear.Contains("07"))) {
            fPeriodENUM = k06E;
        } else if (fYear.Contains("07")) {
            fPeriodENUM = k0607P;
        } else {
            cout << "ERROR in TSubSet::Classify(): was not possible to identify Period of the sample! ";
            cout << "Terminating!" << endl;
            abort();
        }
    } else if (fTypeENUM == kDATA) {

        if (fYear.Contains("03")) fPeriodENUM = k03P;
        else if (fYear.Contains("04")) fPeriodENUM = k04P;
        else if (fYear.Contains("05")) fPeriodENUM = k05E;
        else if (fYear.Contains("06e")) fPeriodENUM = k06E;
        else if (fYear.Contains("06p")) fPeriodENUM = k06P;
        else if (fYear.Contains("07p")) fPeriodENUM = k07P;
        else {
            cout << "ERROR in TSubSet::Classify(): could not determine period of the sample! ";
            cout << "Terminating!" << endl;
            abort();
        }
    }

    // if MC, determine also flavour and Q2 generator cut. otherwise return;
    if (fTypeENUM == kDATA) return;

    // define flavour of the sample
    if (fFlavour.Contains("light")) {
        fFlavourENUM = kLIGHT;
    } else if (fFlavour.Contains("charm")) {
        fFlavourENUM = kCHARM;
    } else if (fFlavour.Contains("beauty")) {
        fFlavourENUM = kBEAUTY;
    } else if (fFlavour.Contains("rho_zeusvm")) {
        fFlavourENUM = kRHO;
    }

    // check if flavour was set and terminate an execution otherwise
    if (fFlavourENUM == kUNKNOWNFLAVOUR) {
        cout << "ERROR in TSubSet::Classify(): was not possible to identify flavour of the sample! ";
        cout << "Terminating!" << endl;
        abort();
    }

    // check if there is information whether this is resolved or direct process
    // note: if fProcessENUM is not defined, the program won't terminate, because for
    // light flavour we don't specify it; in contrast to the variables above, where
    // it terminates if e.g. flavour could not be defined
    bool    bgf = ( fFlavour.Contains("bgf") && (!fFlavour.Contains("noQED")) ) ;
    bool    bgf_noQED = ( fFlavour.Contains("bgf") && fFlavour.Contains("noQED") ) ;
    bool    resolved = fFlavour.Contains("resolved");
    if (bgf) {
        fProcessENUM = kBGF;
    } else if (bgf_noQED) {
        fProcessENUM = kBGFNOQED;
    } else if (resolved) {
        fProcessENUM = kRESOLVED;
    } else if (bgf && resolved) {
        cout << "ERROR in TSubSet::Classify(): both bgf and resolved were specified! ";
        cout << "Terminating!" << endl;
        abort();
    }

    // determine Q2
    if (fQ2 == "1") {
        fQ2ENUM = kQ2g1;
    } else if (fQ2 == "1.5") {
        fQ2ENUM = kQ2g1_5;
    } else if (fQ2 == "4") {
        fQ2ENUM = kQ2g4;
    }

    // check whether Q2 was determined
    if (fQ2ENUM == kUNKNOWNQ2) {
        cout << "ERROR in TSubSet::Classify(): was not possible to identify Q2 of the sample!";
        cout << "Terminating!" << endl;
        abort();
    }
}

// prints info about this sample
void TSubSet::Print(){

    cout << "\n\n** PROPERTIES OF TSUBSET OBJECT **\n";
    cout << "year: " << getYear() << endl;
    cout << "type: " << getType() << endl;
    cout << "flavour: " << getFlavour() << endl;
    cout << "Q2: " << getQ2() << endl;
    cout << "CN_version: " << getCNversion() << endl;
    cout << "name_pattern: " << getNamePattern() << endl;
    cout << "trigger period: " << getTriggerPeriod() << endl;
    cout << "luminosity: " << getLuminosity() << endl;
    cout << "sample name: " << getSampleName() << endl;
    cout << "**********************************\n";
}

// sets all the variables of the current SubSet
void    TSubSet::operator=(TSubSet      newset) {

    fYear = newset.getYear();
    fType = newset.getType();
    fFlavour = newset.getFlavour();
    fQ2 = newset.getQ2();
    fCN_version = newset.getCNversion();
    fName_pattern = newset.getNamePattern();
    fTriggerPeriod = newset.getTriggerPeriod();
    fLuminosity = newset.getLuminosity();

    fFlavourENUM = newset.getFlavourENUM();
    fPeriodENUM = newset.getPeriodENUM();
    fQ2ENUM = newset.getQ2ENUM();
    fProcessENUM = newset.getProcessENUM();
    fTypeENUM = newset.getTypeENUM();
    fID = newset.getID();

    fSampleName = newset.getSampleName();
}
