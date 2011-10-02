//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//  modified: February 2011                     //
//////////////////////////////////////////////////


// ROOT includes
#include <TFile.h>
#include <TKey.h>

// system  includes
#include <iostream>
using namespace std;

// my includes
#include <inc/TMyFitter.h>
#include <TDataset.h>
#include <TSubSet.h>
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

//---------- TEMPORARY ---------
TString   CN_VERSION="v02";
//TString   CN_VERSION="v04";
//TString   CN_VERSION="v06";
bool      use_0304p_true = 0;   // this doesn't work at the moment because it's not in the v02 xml file TODO: fix!!
bool      use_05e_true = 1;
bool      use_06e_true = 1;
bool      use_0607p_true = 1;
bool      use_luminosity_recalculated = true;
//------------------------------

struct  TrueCrossSection{
          TFile     *fCharmFile;
          TFile     *fBeautyFile;
          Double_t  fCharmLuminosity;
          Double_t  fBeautyLuminosity;
};


TMyFitter    *currentFitter;

// very much cumbersome, but don't know how to avoid that:
// the function is here, it's called from TMyFitter, though;
// one could have it as a class method, but I couldn't figure out
// how to pass a pointer to it as an argument for TMinuit::SetFCN(..)
// hence, for the timebeing adopting my "old" solution, namely having
// this function here.

void fcnn(Int_t& npar, Double_t* grad, Double_t& f, Double_t par[], Int_t iflag) {
    Double_t chi2 = currentFitter -> GetChi2(par[0],par[1],par[2]);
    f = chi2;
}

int main(int argc, char **argv) {

    // some declarations
    TString     BinningFileSuffix;
    TString     HistogramsVersionEnding;
    TString     remark = "";
    Bool_t      use_scaling_factors = false;
    Bool_t      include_resolved = false;
    Bool_t      include_direct = false;

    // handle command line options
    opterr = 0;
    int c;
    while ((c = getopt (argc, argv, "b:v:der:h")) != -1) {
        switch (c) {
            case 'b':
                BinningFileSuffix = optarg;
                break;
            case 'v':
                HistogramsVersionEnding = optarg;
                break;
            case 'd':
                include_direct = true;
                break;
            case 'e':
                include_resolved = true;
                break;
            case 's':
                use_scaling_factors = true;
                break;
            case 'r':
                remark = (TString)optarg;
                break;
            case  'h':
                cout<<"usage:\n\t fitter  -b <Binning File Suffix> -v <Histograms Version Ending> [options]\n"<<endl;
                cout << "List of options\n" << endl;
                cout << "-d\tInclude direct part"<<endl;
                cout << "-e\tInclude excitation part"<<endl;
                cout << "-r\tremark; default: .0405e06e07p"<<endl;
                cout << "-h\tprint this help"<<endl;
                exit(0);
                break;
            default:
                abort ();
        }
    }
    for (int index = optind; index < argc; index++) {
        printf ("WARNING: Non-option argument %s\n", argv[index]);
    }

    // print welcome message
    cout<<"******************************************************"<<endl;
    cout<<"* Welcome to ZEUS Common Ntuple analysis framework   *"<<endl;
    cout<<"* Step 4: Fitting of the Histograms                  *"<<endl;
    cout<<"* Input: root files with histograms                  *"<<endl;
    cout<<"******************************************************"<<endl;

    // by default, process all periods
    if (remark == "") remark = ".0405e06e07p";

    if (include_resolved) remark += ".including_resolved";
    cout << "INFO: remark " << remark << endl;

    // construct files suffix as binning file suffix concatenated with version of histograms
    TString     HistogramsVersion = BinningFileSuffix + HistogramsVersionEnding;
    TString     HistogramsVersionRAW=BinningFileSuffix + HistogramsVersionEnding; // used for true stuff

    HistogramsVersion+=remark;
    cout << "INFO: Histograms Version: " << HistogramsVersion << endl;

    // check if there are at least three arguments (first one is always script name)
    if ( argc < 5 ) {
        cout << "ERROR: not enough parameters - see \n\tfitter -h\n for help\n";
    }

    bool      scale_lf = false;      // for LF assymetry studies: scale LF component with a given factor (scale_lf_size)
                                        // in the mirrored distributions and then do the fit
    Float_t   scale_lf_size = 1.0;

    if (argc == 5) {
        scale_lf = true;
        scale_lf_size = atof(argv[4]);
        cout<<"INFO: applying light flavour scaling before the fit by a factor of "<<scale_lf_size<<endl;
    }

    // get environmental variables
    TString        HISTO_PATH=getenv("HISTO_PATH");
    TString        NTUPLE_ANALYZER=getenv("NTUPLEANALYZER");

    // open file with histograms (after merger step)
    TFile    * fInputHistogramsFile = new TFile (HISTO_PATH+"/merged."+HistogramsVersion+".root", "read");;
    if ( ! (fInputHistogramsFile -> IsZombie()) ) {
        cout<<"INFO: Opened "<<fInputHistogramsFile->GetName()<<" for reading"<<endl;
    } else {
        cout<<"ERROR in fitter.cxx: Cannot open file with histograms. Exiting, sorry."<<endl;
        abort();
    }

    // read binning from the XML file
    TString binningXMLfileName = "binning."+BinningFileSuffix+".xml";
    // everything should be ok if this does not crash:
    TCrossSection   cCrossSection(binningXMLfileName);

    // read samples information
    TString datasetXMLfileName = "samples."+CN_VERSION+".xml";
    TDataset        cDataset(datasetXMLfileName);

    // NOTE: now this is for a single sample only. will probably use vectors to generalize to any number...
    // get analysis-step files (MC) for true cross-section calculation
    map <TSubSet::Period, TrueCrossSection>  true_cross_sect_BGF;
    map <TSubSet::Period, TrueCrossSection>  true_cross_sect_RESOLVED;

    vector <TSubSet::Period>  periods_for_true_cross_section;

    if (use_0304p_true) periods_for_true_cross_section.push_back(TSubSet::k0304P);
    if (use_05e_true) periods_for_true_cross_section.push_back(TSubSet::k05E);
    if (use_06e_true) periods_for_true_cross_section.push_back(TSubSet::k06E);
    if (use_0607p_true) periods_for_true_cross_section.push_back(TSubSet::k0607P);

    for (int i = 0; i < periods_for_true_cross_section.size(); i++) {

        TSubSet::Period cPeriod = periods_for_true_cross_section[i];

        // BGF
        // IMPORTANT: reference sample for the current period
        TSubSet cSubSet_charm = cDataset.getSubSet(TSubSet::kMC, cPeriod, TSubSet::kCHARM, TSubSet::kQ2g4, TSubSet::kBGF);
        TSubSet cSubSet_beauty = cDataset.getSubSet(TSubSet::kMC, cPeriod, TSubSet::kBEAUTY, TSubSet::kQ2g1, TSubSet::kBGF);

        // get the files
        true_cross_sect_BGF[cPeriod].fCharmFile = new TFile(HISTO_PATH+"/analysis."+cSubSet_charm.getSampleName()+"."+HistogramsVersionRAW+".root", "read");
        true_cross_sect_BGF[cPeriod].fBeautyFile = new TFile(HISTO_PATH+"/analysis."+cSubSet_beauty.getSampleName()+"."+HistogramsVersionRAW+".root", "read");
            
        // and the luminosity
        Double_t    RefSampleCharmLumi;
        Double_t    RefSampleBeautyLumi;
        if (use_luminosity_recalculated) {
            RefSampleCharmLumi = cSubSet_charm.getLuminosityRecalculated();
            RefSampleBeautyLumi = cSubSet_beauty.getLuminosityRecalculated();
        } else {
            RefSampleCharmLumi = cSubSet_charm.getLuminosity();
            RefSampleBeautyLumi = cSubSet_beauty.getLuminosity();
        }
        true_cross_sect_BGF[cPeriod].fCharmLuminosity = RefSampleCharmLumi;
        true_cross_sect_BGF[cPeriod].fBeautyLuminosity = RefSampleBeautyLumi;
        
        // RESOLVED, now fully duplicated to BGF
        // IMPORTANT: reference sample for the current period
        // note: for 0607p beauty resolved, the Q2 cut is 1.5, not 1!! also for charm, there's no Q2>4 sample
        if (cPeriod == TSubSet::k0607P)  {
            cSubSet_beauty = cDataset.getSubSet(TSubSet::kMC, cPeriod, TSubSet::kBEAUTY, TSubSet::kQ2g1_5, TSubSet::kRESOLVED);
            cSubSet_charm = cDataset.getSubSet(TSubSet::kMC, cPeriod, TSubSet::kCHARM, TSubSet::kQ2g1_5, TSubSet::kRESOLVED);
        } else {
            cSubSet_beauty = cDataset.getSubSet(TSubSet::kMC, cPeriod, TSubSet::kBEAUTY, TSubSet::kQ2g1, TSubSet::kRESOLVED);
            cSubSet_charm = cDataset.getSubSet(TSubSet::kMC, cPeriod, TSubSet::kCHARM, TSubSet::kQ2g4, TSubSet::kRESOLVED);
        }

        // get the files
        if (!include_resolved) continue;
        true_cross_sect_RESOLVED[cPeriod].fCharmFile = new TFile(HISTO_PATH+"/analysis."+cSubSet_charm.getSampleName()+"."+HistogramsVersionRAW+".root", "read");
        true_cross_sect_RESOLVED[cPeriod].fBeautyFile = new TFile(HISTO_PATH+"/analysis."+cSubSet_beauty.getSampleName()+"."+HistogramsVersionRAW+".root", "read");
            
        // and the luminosity
        if (use_luminosity_recalculated) {
            RefSampleCharmLumi = cSubSet_charm.getLuminosityRecalculated();
            RefSampleBeautyLumi = cSubSet_beauty.getLuminosityRecalculated();
        } else {
            RefSampleCharmLumi = cSubSet_charm.getLuminosity();
            RefSampleBeautyLumi = cSubSet_beauty.getLuminosity();
        }
        true_cross_sect_RESOLVED[cPeriod].fCharmLuminosity = RefSampleCharmLumi;
        true_cross_sect_RESOLVED[cPeriod].fBeautyLuminosity = RefSampleBeautyLumi;

    }

    // now loop over the subdirectories in merged-step file
    // some preparations
    fInputHistogramsFile->cd();
    TIter nextBin(gDirectory->GetListOfKeys());
    TKey* keyBins;
    unsigned        counter=1;      // a counter needed to identify bins
        
    // actual loop over subdirectories
    while( ( keyBins = (TKey*) nextBin() ) ) {

        TString SubDirName=keyBins->GetName();

        if ( ((TString)keyBins->GetClassName()) != "TDirectoryFile" )    {
            cout << "WARNING: found non-TDirectory object on root level in " << fInputHistogramsFile->GetName() << endl;
        }

        // create an instance of TMyFitter and perform the fit for this bin
        TMyFitter    *instance=new TMyFitter(SubDirName, fcnn, HistogramsVersion);
        currentFitter = instance;
    
        if (scale_lf) {
            instance -> SetScaleLF (true);
            instance -> SetScaleLFSize (scale_lf_size);
        }
        instance -> Initialize();

        // perform a fit
        instance -> Fit();
        cout << "INFO: Fitted " << SubDirName << endl;

        // now need to calculate true cross-section in this bin
        // for this we need a number of true jets in this bin
        // truejets histogram should be used for this during analysis level
        const TString TRUE_HISTO = SubDirName+"/truejets";

        // BGF
        Double_t      TotalLumi_charm = 0;
        Double_t      TotalLumi_beauty = 0;
        Double_t      TotalGenerated_charm = 0;
        Double_t      TotalGenerated_beauty = 0;

        for (int i = 0; i < periods_for_true_cross_section.size(); i++) {
            TSubSet::Period cPeriod = periods_for_true_cross_section[i];
            TH1F * cHistCharm = (TH1F*)true_cross_sect_BGF[cPeriod].fCharmFile -> Get(TRUE_HISTO);
            TH1F * cHistBeauty = (TH1F*)true_cross_sect_BGF[cPeriod].fBeautyFile -> Get(TRUE_HISTO);

            Int_t       nGeneratedInBin_c=(Int_t)cHistCharm->Integral();
            Int_t       nGeneratedInBin_b=(Int_t)cHistBeauty->Integral();

            Float_t     CrossSect_c_MC = (Float_t) nGeneratedInBin_c;
            Float_t     CrossSect_b_MC = (Float_t) nGeneratedInBin_b;

            TotalGenerated_charm += nGeneratedInBin_c;
            TotalGenerated_beauty += nGeneratedInBin_b;

            TotalLumi_charm += true_cross_sect_BGF[cPeriod].fCharmLuminosity;
            TotalLumi_beauty += true_cross_sect_BGF[cPeriod].fBeautyLuminosity;
        }

        Double_t      CrossSect_c_MC_true_BGF = TotalGenerated_charm / TotalLumi_charm;
        Double_t      CrossSect_b_MC_true_BGF = TotalGenerated_beauty / TotalLumi_beauty;

        // RESOLVED  TODO: make sure this is fine - there are different type of reference samples......
        if (include_resolved) {
            TotalLumi_charm = 0;
            TotalLumi_beauty = 0;
            TotalGenerated_charm = 0;
            TotalGenerated_beauty = 0;
            for (int i = 0; i < periods_for_true_cross_section.size(); i++) {
                TSubSet::Period cPeriod = periods_for_true_cross_section[i];
                TH1F * cHistCharm = (TH1F*)true_cross_sect_RESOLVED[cPeriod].fCharmFile -> Get(TRUE_HISTO);
                TH1F * cHistBeauty = (TH1F*)true_cross_sect_RESOLVED[cPeriod].fBeautyFile -> Get(TRUE_HISTO);
    
                Int_t       nGeneratedInBin_c=(Int_t)cHistCharm->Integral();
                Int_t       nGeneratedInBin_b=(Int_t)cHistBeauty->Integral();
    
                Float_t     CrossSect_c_MC = (Float_t) nGeneratedInBin_c;
                Float_t     CrossSect_b_MC = (Float_t) nGeneratedInBin_b;
    
                TotalGenerated_charm += nGeneratedInBin_c;
                TotalGenerated_beauty += nGeneratedInBin_b;
    
                TotalLumi_charm += true_cross_sect_RESOLVED[cPeriod].fCharmLuminosity;
                TotalLumi_beauty += true_cross_sect_RESOLVED[cPeriod].fBeautyLuminosity;
            }
        }

        Double_t      CrossSect_c_MC_true_RESOLVED = TotalGenerated_charm / TotalLumi_charm;
        Double_t      CrossSect_b_MC_true_RESOLVED = TotalGenerated_beauty / TotalLumi_beauty;

        // and now the total cross-section!
        Double_t      CrossSect_c_MC_true;
        Double_t      CrossSect_b_MC_true;

        if (include_resolved) {
            CrossSect_c_MC_true = CrossSect_c_MC_true_BGF + CrossSect_c_MC_true_RESOLVED;
            CrossSect_b_MC_true = CrossSect_b_MC_true_BGF + CrossSect_b_MC_true_RESOLVED;
        } else {
            CrossSect_c_MC_true = CrossSect_c_MC_true_BGF;
            CrossSect_b_MC_true = CrossSect_b_MC_true_BGF;
        }


        // get TCrossSectionBin object by id
        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(counter);

        // set fit results
        cBin.set_k_uds(instance -> get_k_uds());
        cBin.set_k_c(instance -> get_k_c());
        cBin.set_k_b(instance -> get_k_b());
        cBin.set_k_uds_err(instance -> get_k_uds_err());
        cBin.set_k_c_err(instance -> get_k_c_err());
        cBin.set_k_b_err(instance -> get_k_b_err());
        
        // set true cross-section
        cBin.set_sigma_c_true(CrossSect_c_MC_true);
        cBin.set_sigma_b_true(CrossSect_b_MC_true);

        // compute measured cross-sections and set to TCrossSectionBin object
        Float_t        CrossSect_c_Data = instance->get_k_c() * CrossSect_c_MC_true / cBin.getBinWidth();
        Float_t        CrossSect_b_Data = instance->get_k_b() * CrossSect_b_MC_true / cBin.getBinWidth();
        cBin.set_sigma_c(CrossSect_c_Data);
        cBin.set_sigma_b(CrossSect_b_Data);
        
        cBin.set_sigma_c_err(CrossSect_c_Data * instance -> get_k_c_err() / instance -> get_k_c());
        cBin.set_sigma_b_err(CrossSect_b_Data * instance -> get_k_b_err() / instance -> get_k_b());
        
        
        // finally, modify the accordingly the DOM object (via TCrossSection interface)
        cCrossSection.modifyCrossSectionBin(counter, cBin);
        
        // increment bin counter
        counter++;
            
        // clean up
        delete currentFitter;
    }
        
    // write changes to the XML file before we leave
    // first, construct the the name of the file; might look cumbersome, TODO: revisit...
    TString out_file_name = "results."+HistogramsVersion+"."+CN_VERSION;

    // now add prefix related to how we define the true cross-section; this is for sanity check;
    // if all the periods selected for the true cross-section calculation, no prefix added (default);
    // otherwise, add a prefix for each period
    bool all_periods_for_true_cs = false;
    if (use_0304p_true && use_05e_true && use_06e_true && use_0607p_true) all_periods_for_true_cs = true;
    if (!all_periods_for_true_cs) {
        out_file_name += ".true";
        if (use_0304p_true) out_file_name += "0304p";
        if (use_05e_true)  out_file_name += "05e";
        if (use_06e_true) out_file_name += "06e";
        if (use_0607p_true) out_file_name += "0607p";
    }

    // finally, the extension
    out_file_name += ".xml";

    // write data to file
    cCrossSection.WriteXMLfile(out_file_name);

    // finished successfully
    return 0;
}
