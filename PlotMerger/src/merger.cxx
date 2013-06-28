//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

// this program deals with normalizing properly the histogram before the fit;
// Each type (as listed in DataType except kData which is not normalized at all)
// has to be normalized separately, because of the different cross-sections;
// moreover, this has to be done separately for each period, as generally we 
// have different amount of the mc generated for each period.
// There is one more complication: for charm we have typically samples
// with different Q2min cuts; For instance, there might be samples
// with Q2>1.5 GeV2 and Q2>4 GeV. They should be treated differently already
// at analysis level: there should be a proper weight (done by TMiniNtupleAnalyzer::CalculateCharmQg4WeightingFactor) 
// for events with Q2>4 (for both samples). Then these samples can be added together without any weighting
// or in other words normalized by the same factor to data lumi. The factor is then determined by
// the luminosity of Q2>1.5 sample only.

// System headers
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>
#include <getopt.h>
using namespace std;

// ROOT headers
#include <TChain.h>
#include <TMath.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TSystem.h>

// my headers
#include <inc/TPlotMerger.h>
#include <../NtupleAnalyzer/inc/periods.h>
#include <TCrossSection.h>
#include <TDataset.h>
#include <TSubSet.h>


// this structure duplicates a bit what is done already in TSubSet
// however it can't be eliminated at the moment: in TSubset
// we have separately charm/beauty and resolved/direct information;
// here we treat them as independend, so we need to introduce these
// types. (of course we could equally introduce them in TSubSet, but
// that could be as confusing...)
enum    DataType {
    kData,
    kCharm,
    kBeauty,
    kLight,
    kCharmResolved,
    kBeautyResolved,
    kRho
};

struct    Sample {
    TString     Name;
    TString     Year;
    Float_t     Lumi;
    period      Period;
    DataType    Type;
};


// helping functions declaration, see description below
DataType    getDataType(TSubSet::Type, TSubSet::Process, TSubSet::Flavour);
TSubSet::Period getPeriod(TSubSet::Type, TSubSet::Period);

// the main function
int main(int argc, char **argv) {

    // check whether number of arguments is at least two and print help message otherwise
    if ( argc < 3 ) {
        cout<<"Please provide necessary parameters\n"<<endl;
        cout<<"usage:\n\t merger -b <Binning File Suffix> -v <Histograms Version Ending> [options]\n"<<endl;
        cout<<"List of options:"<<endl;
        cout<<"-d\tInclude direct part"<<endl;
        cout<<"-e\tInclude excitation part"<<endl;
        cout<<"-s\tScale plots"<<endl;
        cout<<"-r\tremark; default: .0405e06e07p"<<endl;
        cout<<"--no_beauty_resolved\tdon't add beauty resolved samples, if -e options is selected"<<endl;
        cout<<"--no_charm_resolved\tdon't add charm resolved samples, if -e options is selected"<<endl;
        cout<<"Terminating, sorry."<<endl;
        exit(-1);
    }

    // print welcome message
    cout<<"******************************************************"<<endl;
    cout<<"* Welcome to ZEUS Common Ntuple analysis framework   *"<<endl;
    cout<<"* Step 3: analyis of Histograms                      *"<<endl;
    cout<<"* Input: root files with histograms                  *"<<endl;
    cout<<"******************************************************"<<endl;

    // some declarations
    TString     BinningFileSuffix;
    TString     HistogramsVersionEnding;
    TString     remark = "";
    Bool_t      use_scaling_factors = false;
    Bool_t      include_resolved = false;
    Bool_t      include_direct = false;
    Bool_t      no_beauty_resolved = false;
    Bool_t      no_charm_resolved = false;
    Bool_t      tracking = false;
    Bool_t      normalize_rho = false;

    // declare long options
    static struct option long_options[] = {
        {"no_beauty_resolved", no_argument, 0, 1},
        {"no_charm_resolved", no_argument, 0, 2},
        {"tracking", no_argument, 0, 3},
        {"normalize_rho", no_argument, 0, 4},
    };

    // handle command line options
    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option

    opterr = 0;
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "b:v:desr:", long_options, &option_index)) != -1) {
        switch (option) {
            case 'b':
                BinningFileSuffix=optarg;
                break;
            case 'v':
                HistogramsVersionEnding=optarg;
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
            case 1:
                no_beauty_resolved = true;
                break;
            case 2:
                no_charm_resolved = true;
                break;
            case 3:
                tracking = true;
                break;
            case 4:
                normalize_rho = true;
                break;
            default:
                abort ();
        }
    }
    for (int index = optind; index < argc; index++) {
        printf ("WARNING: Non-option argument %s\n", argv[index]);
    }

    // construct files suffix as binning file suffix concatenated with version of histograms
    TString     HistogramsVersion = BinningFileSuffix + HistogramsVersionEnding;
    cout << "INFO: Histograms Version: " << HistogramsVersion << endl;

    // by default, process all periods
    if (remark == "") remark = ".0405e06e07p";
    // in case selected to add resolved, but no charm and beauty - switch off including resolved,
    // i.e. no_beauty_resolved and no_charm_resolved options override include_resolved
    if (no_beauty_resolved && no_charm_resolved) include_resolved = false;
    if (include_resolved) {
        remark += ".including_resolved";
        if (no_beauty_resolved) remark += ".no_beauty_resolved";
        if (no_charm_resolved) remark += ".no_charm_resolved";
    }

    // get the CN version from the environment
    TString CN_VERSION=getenv("CN_VERSION");

    // in case k-factors scaling was requested, determine these factors
    // depending on the version of the factors
    TString XMLfilename;
    if (use_scaling_factors) {
        XMLfilename = "results."+HistogramsVersion+remark+"."+CN_VERSION+".true05e06e0607p.xml";
        //XMLfilename = "results."+HistogramsVersion+remark+"."+CN_VERSION+".true06e.xml";
        cout << "INFO: Reading xml file with fit results to obtain scaling factors: " << XMLfilename << endl;

        TCrossSection   cCrossSection(XMLfilename);
    }

    if (use_scaling_factors) {
        remark += ".scaled";
    }

    cout << "INFO: remark " << remark << endl;

    // add periods to be analyzed
    map <TSubSet::Period, bool> period_list;
    if (remark.Contains("04")) { 
        period_list[TSubSet::k0304P] = true;
    } else {
        period_list[TSubSet::k0304P] = false;
    }
    if (remark.Contains("05e")) { 
        period_list[TSubSet::k05E] = true;
    } else {
        period_list[TSubSet::k05E] = false;
    }
    if (remark.Contains("06e")) { 
        period_list[TSubSet::k06E] = true;
    } else {
        period_list[TSubSet::k06E] = false;
    }
    if (remark.Contains("07p")) { 
        period_list[TSubSet::k0607P] = true;
    } else {
        period_list[TSubSet::k0607P] = false;
    }

    // declare a map that will contain TOTAL luminosity for every data type and period
    map <TSubSet::Period, map <DataType, Float_t> > luminosity_map;

    // get an XML file with samples info
    TString     sampleXMLfile = "samples."+CN_VERSION+".xml";
    TDataset    cDataset(sampleXMLfile);

    // initialize luminosity_map with zeros, in order to be able to safely
    // add the luminosity in the loop
    const unsigned number_of_data_types = 7;
    const unsigned number_of_periods = 4;
    DataType    DataTypeArray[number_of_data_types] = { kData, kCharm, kBeauty, kLight, kCharmResolved, kBeautyResolved, kRho };
    TSubSet::Period PeriodArray[number_of_periods] = { TSubSet::k0304P, TSubSet::k05E, TSubSet::k06E, TSubSet::k0607P };
    for (int period_ind = 0; period_ind < number_of_periods; period_ind++) {
        for (int type_ind = 0; type_ind < number_of_data_types; type_ind++) {
            luminosity_map[PeriodArray[period_ind]][DataTypeArray[type_ind]] = 0;
        }
    }

    // loop over all samples, present in the file, to sum all the luminosities
    // for each DataType and Period
    for (unsigned i = 0; i < cDataset.getNSamples(); i++) {

        TSubSet cSubSet  = cDataset.getSubSet_byIndex(i);

        // get information about the sample
        TSubSet::Flavour flavour = cSubSet.getFlavourENUM();
        TSubSet::Process process = cSubSet.getProcessENUM();
        TSubSet::Type    type = cSubSet.getTypeENUM();
        TSubSet::Period  period = cSubSet.getPeriodENUM();
        TSubSet::Q2      q2 = cSubSet.getQ2ENUM();
        Float_t luminosity = cSubSet.getLuminosity();

        // determine the type of the sample, i.e. which of the DataType entities our sample is. See also comments there
        DataType data_type = getDataType(type, process, flavour);

        // now get the period of the sample. As discussed elsewhere, normalization of MC should
        // be done wrt to e.g. luminosity of 0304p, not separately for 03p and 04p; hence we have
        // to calculate luminosity for those 0304p
        period = getPeriod(type, period);

        // no need to process if this period is not selected by the user
        if (!period_list[period]) continue;

        // add the luminosity; skip if this sample is charm q2>4 while there was also q2>1.5; it's
        // only the luminosity of the latter which enters the normalization, see the comments above;
        // for the timebeing (September 2011) all the charm samples (bgf and resolved) come with both
        // q2>1.5 and q2 > 4 samples (with the only exception: resolved charm for 0607p exists only for 1.5 GeV2 and
        // this is already taken into account in the weighting during analysis, TMiniNtupleAnalyzer::CalculateCharmQg4WeightingFactor);
        // hence, as discussed above for the charm we need the luminosity only of q2>1.5 sample - skip those with 4
        if ( (flavour == TSubSet::kCHARM) && (q2 == TSubSet::kQ2g4) ) continue;
        // all the others go into the sum
        luminosity_map[period][data_type] += luminosity;
    }

    // create an instance of TPlotMerger and initialize
    TPlotMerger *instance=new TPlotMerger(HistogramsVersion, remark);
    instance -> SetXMLFileName(XMLfilename);
    if (use_scaling_factors) instance -> SetScaleFitResults(true);
    instance -> Initialize();

    // add the so called groups - these will be the histograms available
    // after histogram and represent the weighted (to the relative luminosity and/or
    // the scaling factors from the fit) of the samples added to the group with TPlotMerger::AddSample(..)
    // all the data samples
    instance->AddSampleGroup("data", kNone);
    // all the mc samples
    instance->AddSampleGroup("mc", kLumi);
    // light flavour samples
    instance->AddSampleGroup("light", kLumi);
    // all the charm samples
    instance->AddSampleGroup("charm", kLumi);
    // all the beauty samples
    instance->AddSampleGroup("beauty", kLumi);

    // brand new: resolved samples and bgf samples separately
    instance->AddSampleGroup("charm_resolved", kLumi);
    instance->AddSampleGroup("beauty_resolved", kLumi);
    instance->AddSampleGroup("charm_bgf", kLumi);
    instance->AddSampleGroup("beauty_bgf", kLumi);

    // rho samples for tracking studies; can be normalized (for control plots only) or not (for tracking efficiency determination)
    if (normalize_rho) {
        instance -> AddSampleGroup("rho", kArea);
    } else {
        instance -> AddSampleGroup("rho", kNone);
    }

    // now loop over the samples one more time and add them to the instance of TPlotMerger;
    // this is done in the 2nd loop as we have to know the relative luminosities already,
    // so in the 1st loop (see above) they are summed up for each period/data type; see the comments above
    for (unsigned i = 0; i < cDataset.getNSamples(); i++) {

        // first part is duplicated from the 1st loop, sorry
        TSubSet cSubSet  = cDataset.getSubSet_byIndex(i);

        // get information about the sample
        TSubSet::Flavour flavour = cSubSet.getFlavourENUM();
        TSubSet::Process process = cSubSet.getProcessENUM();
        TSubSet::Type    type = cSubSet.getTypeENUM();
        TSubSet::Period  period = cSubSet.getPeriodENUM();
        TSubSet::Q2      q2 = cSubSet.getQ2ENUM();
        Float_t luminosity = cSubSet.getLuminosity();

        // determine the type of the sample, i.e. which of the DataType entities our sample is. See also comments there
        DataType data_type = getDataType(type, process, flavour);

        // get the period of the sample. As discussed elsewhere, normalization of MC should
        // be done wrt to e.g. luminosity of 0304p, not separately for 03p and 04p; hence we have
        // to calculate luminosity for those 0304p
        period = getPeriod(type, period);

        // no need to process if this period is not selected by the user
        if (!period_list[period]) continue;

        // start adding the samples
        // get the name of the sample, to be able to uniquely identify it
        TString     sample_name = cSubSet.getSampleName();
        // get a scaling factor which - the relative luminosity to data (from the same period)
        Float_t     relative_luminosity = luminosity_map[period][kData]/luminosity_map[period][data_type];
        switch (data_type) {
            case kData:
                // data type; note that there is no scaling of data, hence no need to pass the luminosity value
                instance->AddSample("data", cSubSet, 0);
                break;
            case kLight:
                // light flavour; add to "light" and "mc" groups
                if (!tracking) {
                    instance->AddSample("light", cSubSet, relative_luminosity);
                    instance->AddSample("mc", cSubSet, relative_luminosity);
                }
                break;
            case kCharm:
                if (include_direct) {
                    instance->AddSample("charm", cSubSet, relative_luminosity);
                    instance->AddSample("mc", cSubSet, relative_luminosity);
                    instance->AddSample("charm_bgf", cSubSet, relative_luminosity);
                }
                break;
            case kCharmResolved:
                if (include_resolved && (!no_charm_resolved)) {
                    instance->AddSample("charm", cSubSet, relative_luminosity);
                    instance->AddSample("mc", cSubSet, relative_luminosity);
                    instance->AddSample("charm_resolved", cSubSet, relative_luminosity);
                }
                break;
            case kBeauty:
                if (include_direct) {
                    instance->AddSample("beauty", cSubSet, relative_luminosity);
                    instance->AddSample("mc", cSubSet, relative_luminosity);
                    instance->AddSample("beauty_bgf", cSubSet, relative_luminosity);
                }
                break;
            case kBeautyResolved:
                if (include_resolved && (!no_beauty_resolved)) {
                    instance->AddSample("beauty", cSubSet, relative_luminosity);
                    instance->AddSample("mc", cSubSet, relative_luminosity);
                    instance->AddSample("beauty_resolved", cSubSet, relative_luminosity);
                }
                break;
            case kRho:
                if (tracking) {
                    instance -> AddSample("rho", cSubSet, relative_luminosity);
                }
                break;
            default:
                cout << "ERROR: could not indentify type of the sample. Terminating!\n";
                abort();
        }
    }

    // ok, after the samples were added, can merge now
    cout<<" INFO: summoning instance->Merge()"<<endl;
    instance -> Merge();
    cout<<" INFO: instance->Merge() done"<<endl;
    cout<<"\n\n   *********  Successfully finished, good bye  *********   \n\n";
    return 0;
}

// determine the type of the sample, i.e. which of the DataType entities our sample is
DataType    getDataType(TSubSet::Type type, TSubSet::Process process, TSubSet::Flavour flavour) {
    DataType    data_type;
    if (type == TSubSet::kDATA) data_type = kData;
    if (type == TSubSet::kMC) {
        if (flavour == TSubSet::kLIGHT) data_type = kLight;
        if ((flavour == TSubSet::kCHARM) && (process == TSubSet::kBGF)) data_type = kCharm;
        if ((flavour == TSubSet::kCHARM) && (process == TSubSet::kRESOLVED)) data_type = kCharmResolved;
        if ((flavour == TSubSet::kBEAUTY) && (process == TSubSet::kBGF)) data_type = kBeauty;
        if ((flavour == TSubSet::kBEAUTY) && (process == TSubSet::kRESOLVED)) data_type = kBeautyResolved;
        if ( flavour == TSubSet::kRHO ) data_type = kRho;
    }
    return data_type;
}

// get the period of the sample. As discussed elsewhere, normalization of MC should
// be done wrt to e.g. luminosity of 0304p, not separately for 03p and 04p; hence we have
// to calculate luminosity for those 0304p
TSubSet::Period getPeriod(TSubSet::Type type, TSubSet::Period period) {
    if (type == TSubSet::kDATA) {
        if ( (period == TSubSet::k03P) || (period == TSubSet::k04P) ) period = TSubSet::k0304P;
        if ( (period == TSubSet::k06P) || (period == TSubSet::k07P) ) period = TSubSet::k0607P;
    }
    return period;
}
