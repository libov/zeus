//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////

// system headers
#include<iostream>
#include<fstream>
#include <sys/stat.h>
using namespace std;

// ROOT headers
#include<TCollection.h>
#include<TMath.h>
#include<TFile.h>
#include<TRandom3.h>
#include<TSystem.h>
#include<TVector3.h>

// my headers
#include <inc/TMiniNtupleAnalyzer.h>
#include <inc/TGlobalBin.h>
#include<TDataset.h>
#include<TSubSet.h>

// constructor
// is used to initialize some variables and to create certain objects
TMiniNtupleAnalyzer::TMiniNtupleAnalyzer(TString HistoVersion, TString BinningFile, TString    DeclareHistoFileName):
fList_TGlobalBin(new TList()),
fHistogramsFileVersion(HistoVersion),
fBinningFileName(BinningFile),
fApplyQ2g4Weighting(false),
fHistogramDeclarationFile(DeclareHistoFileName),
fCharmQ2g4Weight(1),
fTrueQ2Weight(1),
fRecoQ2Weight(1),
fApplySmearing(true),
fDropTracks(false),
fRun_dCache(true),
fOnlyCalculateEventsPerRun(false),
fEtReweightingLF_histo(NULL),
fFragmentationReweighting_histo(NULL),
fFragmentationReweighting(false),
fEtReweightingLF(true),
fTestFirstEvent(0),
fSeed_rnd(4357),
fSeed_rnd2(4357),
fSeed_rnd_eff(4357),
fJetEnergyUncertainty(0.03),
fVaryTotalJetEnergy(false),
fTrueLevelStudies(false),
fZstring_weight(1),
fCharmFragm_variation_size(1),
fBeautyFragm_variation_size(1),
fJetEtCut(4.2),
fPrintingFreq(10000),
fDoJetEnergyScaleSyst(false),
fSmearingGauss1Prob(0.05),
fSmearingGauss1Width(1.8),
fSmearingGauss2Prob(0.01),
fSmearingGauss2Width(2.3),
fSmearingExpProb(0.1),
fSmearingExpCoeff(5),
fRedoVertexing(false),
fRcut(1),
fpT(0.5),
fSTT(0),
fCTD(3),
fMVD(4),
fUseHelixTrackParameters(false),
fStudyResolutions(true),
fApplyQ2Reweighting(true),
fApplyCharmEtaReweighting(false),
fApplyCharmETReweighting(false),
fCharmEtaReweighting_p0(1),
fCharmEtaReweighting_p1(0),
fCharmEtaReweighting_p2(0),
fCharmETReweighting_p0(1),
fCharmETReweighting_p1(0),
fPionThetaReco(0),
fPionThetaTrue(0),
fApplyPtReweighting(false),
fApplyPhiReweighting(false),
fApplyThetaStarReweighting(false),
fDebugPrintout(true),
fTrack1Id(-1),
fTrack2Id(-1)
{
    fTestMode = false;
    fDebug = new TH1F("fDebug", " Debug histogram for mini ntuples analysis ", 50, 0, 50);
    fDebugSVTX = new TH1F ("fDebugSVTX", "Debug histo for secondary vertex selection", 50, 0, 50);
    fMc_q2_et = new TH2F ("fMc_q2_et", "Q^{2} - E_{T} plane", 200, 0, 35, 200, 0, 3);
    fMc_pt_theta_pi = new TH2F ("fMc_pt_theta_pi", "fate point", 100, -20 , 20, 100, -20, 20);
}

// a public method to initialize the class
void TMiniNtupleAnalyzer::Initialize() {

    // do an initialization of TNutpleAnalyzer
    Init();

    // print welcome message
    cout << "INFO: Initialization of TMiniNtupleAnalyzer object..." << endl;

    // add files to chain
    // depending on fRun_dCache variable (i.e. whether we want to run on dCache or on Mini Ntuples)
    // add files from dCache or from disk
    if (!fRun_dCache) {
        if (fMiniNtuplesOn_dCache) {
            TString  minintuples_filelist = "MiniNtupleList.txt";
            cout << "INFO: path to mini ntuples " << fPathToMiniNtuples << endl;
            system ("ls -1 " + fPathToMiniNtuples + "/* > "+minintuples_filelist);
            // open the text file
            ifstream NtupleListFile;
            NtupleListFile.open (minintuples_filelist);

            // loop over lines of the text file
            string line;
            Int_t   FilesNumber=0;
            if (NtupleListFile.is_open()) {
                while (! NtupleListFile.eof() ) {
                    getline (NtupleListFile, line);
                    // add a ROOT file to chain
                    if (!line.empty()) {
                        line = "zeus:/"+line;
                        fChain -> Add(line.c_str());
                        FilesNumber++;
                        cout << "INFO: added " << line << endl;
                    }
                }
                NtupleListFile.close();
                cout<<"INFO: " << FilesNumber << " files added to chain" << endl;
                remove(minintuples_filelist);
            } else { // complain
                cout<<"Unable to open file with ntuple list ("<<minintuples_filelist<<"). The program will terminate, sorry."<<endl;
                abort();
            }
        } else {
            fChain -> Add(fPathToMiniNtuples+"/*.root");
        }
        cout << "INFO: Added to chain all files from " << fPathToMiniNtuples << " to chain " << fChain->GetName() << endl;
    } else {
        AddFilesToChain();
    }

    //calculates and prints number of events (TNtupleAnalyzer class), sets the internal variable
    if (!fTestMode) {
        CalculateNumberOfEvents();
    } else {
        fNevents = fTestNumberOfEvents;
    }

    // set branch addresses - done in BaseClass
    SetBranchAddresses();

    // create file for histograms saving (fHistogramsFile)
    TString    HistFileName=getenv ("HISTO_PATH");
    HistFileName.Append("/analysis."+fSampleName+"."+fHistogramsFileVersion+".root");
    fHistogramsFile = new TFile(HistFileName, "recreate");
    cout<<"INFO: Histograms will be written to " << HistFileName << endl;

    //Defines binning, see src/TMiniNtupleAnalyzerSetBinning.cxx
    SetBinning();

    // set weighting factor for CHARM
    CalculateCharmQg4WeightingFactor();

    // TODO: comments
    CreateBinHistograms();

    // initialize fEventsPerRun map
    // NOTE: assuming here that run numbers are in range from 0 to 100000
    // TODO: think of more proper initialization of the map (one has to do some
    // initialization, so that we are sure that counting starts from 0), for instance
    // defining a type whose default constructor would initialize it to 0 and
    // then just not doing any map initialization
    for (int i = 0; i < 100000; i++) {
        fEventsPerRun_ALL[i] = 0;
        fEventsPerRun_EVTAKE_MVDTAKE[i] = 0;
    }

    // get a histogram that contains reweighting function (only for LF MC)
    if ( (fSubSet.getTypeENUM() == TSubSet::kMC) && (fSubSet.getFlavourENUM() == TSubSet::kLIGHT) && fEtReweightingLF) {
        cout << "going to get reweighting histogram" << endl;
        GetEtReweightingLF_histo();
    }

    if (fFragmentationReweighting && (fSubSet.getTypeENUM() == TSubSet::kMC) && ((fSubSet.getFlavourENUM() == TSubSet::kCHARM) || (fSubSet.getFlavourENUM() == TSubSet::kBEAUTY)) ) {
        cout << "going to get fragmentation fraction histogram" << endl;
        GetFragmentationReweighting_Histo();
    }

    // initialize random generators
    InitializeRandomGenerators();

    cout << "INFO: Initialization of TMiniNtupleAnalyzer object done!" << endl;
}

// recalculate luminosity of the sample in case of MC
void TMiniNtupleAnalyzer::RecalculateLuminosity () {

    // sanity check: should be done only for MC
    if ( ! fIsMC ) return;

    // first, open the XML file containing information about the samples
    // NOTE: macro are used again here, think if this is not just an additional complication
    // one could introduce another variable to see whcih CN version this is and which file to open!
    // THE FILENAMES ARE HARDCODED!
    TString   XMLfilename;
    #ifdef CN_VERSION_V02
        XMLfilename = "samples.v02.xml";
    #elif CN_VERSION_V04
        XMLfilename = "samples.v04.xml";
    #elif CN_VERSION_V06
        XMLfilename = "samples.v06.xml";
    #else
        cout << " Common Ntuple version is not set or not supported." << endl;
        cout << " Terminating, sorry." << endl;
        abort();
    #endif

    // get the relevant sample from the TDataset structure
    cout << "INFO: Luminosity of the sample before the recalculation: " << fSubSet.getLuminosity() << endl;

    // quite often we need to distinguish charm and beauty so let's define these flags once
    bool            isCharm = (fSubSet.getFlavourENUM() == TSubSet::kCHARM);
    bool            isBeauty = (fSubSet.getFlavourENUM() == TSubSet::kBEAUTY);

    // get true cross-section for this MC sample
    Float_t true_cross_section = 0;
    if        ( isCharm && (fSubSet.getQ2ENUM() == TSubSet::kQ2g1_5) && (fSubSet.getProcessENUM() == TSubSet::kBGF) ) {
        true_cross_section = 61;
    } else if ( isCharm && (fSubSet.getQ2ENUM() == TSubSet::kQ2g4) && (fSubSet.getProcessENUM() == TSubSet::kBGF) ) {
        true_cross_section = 35.346;
    } else if ( isBeauty && (fSubSet.getQ2ENUM() == TSubSet::kQ2g1) && (fSubSet.getProcessENUM() == TSubSet::kBGF)) {
        true_cross_section = 0.907;
    } else if ( isCharm && (fSubSet.getQ2ENUM() == TSubSet::kQ2g1_5) && (fSubSet.getProcessENUM() == TSubSet::kRESOLVED) ) {
        true_cross_section = 26.4;
    } else if ( isCharm && (fSubSet.getQ2ENUM() == TSubSet::kQ2g4) && (fSubSet.getProcessENUM() == TSubSet::kRESOLVED) ) {
        true_cross_section = 12.37;
    } else if ( isBeauty && (fSubSet.getQ2ENUM() == TSubSet::kQ2g1) && (fSubSet.getProcessENUM() == TSubSet::kRESOLVED)) {
        true_cross_section = 1.28;
    } else if ( isBeauty && (fSubSet.getQ2ENUM() == TSubSet::kQ2g1_5) && (fSubSet.getProcessENUM() == TSubSet::kRESOLVED)) {
        true_cross_section = 1.08;
    } else if ( (fSubSet.getFlavourENUM() == TSubSet::kLIGHT) && (fSubSet.getQ2ENUM() == TSubSet::kQ2g4) ) {
        true_cross_section = 319.5;
    } else if ( (fSubSet.getFlavourENUM() == TSubSet::kRHO) && (fSubSet.getQ2ENUM() == TSubSet::kQ2g1_5) ) {
        true_cross_section = 0;
    } else {
        cout << "could not determine true cross section of this sample. please check __FILE__. Terminating" << endl;
        abort();
    }
    cout << "INFO: True cross section of the sample: " << true_cross_section << endl;

    // calculate luminosity; as the cross section is given in nanobarns, multiply it by 1000
    // to get the value in picobarns, so that luminosity is in inverse picobarns
    Float_t   lumi = fNevents / (1000 * true_cross_section);
    cout << "INFO: Estimated luminosity of the sample: " << lumi << endl;

    // set luminosity
    fSubSet.setLuminosity(lumi);

    // modify respective entry in TDataset structure
    fDataset.modifySubSet(fSubSet.getTypeENUM(), fSubSet.getPeriodENUM(), fSubSet.getFlavourENUM(), fSubSet.getQ2ENUM(), fSubSet.getProcessENUM(), fSubSet, fSubSet.getTriggerPeriod());

    // write data to file
    fDataset.WriteXMLfile(XMLfilename);
}

void TMiniNtupleAnalyzer::CalculateCharmQg4WeightingFactor() {

    // Apply weighting factor if this is charm MC
    // NOTE: for the timebeing weight only charm bgf samples, don't weight resolved samples now (only Q2>1.5 for the timebeing)
    // USAGE OF ONLY Q2>1.5 AND Q2>4 GEV2 BGF SAMPLES IS ASSUMED!
    if ( (!fIsMC) || (fSubSet.getFlavourENUM() != TSubSet::kCHARM) ) return;

    // IMPORTANT: for 0607p RESOLVED CHARM there's only Q2>1.5 generated, so there's no need for 
    // additional weighting
    if ((fSubSet.getProcessENUM() == TSubSet::kRESOLVED) && (fSubSet.getPeriodENUM() == TSubSet::k0607P))  return;

    // set the relevant flag
    fApplyQ2g4Weighting = true;

    // define the relevant samples
    TSubSet   cSubSet_q2g1_5 = fDataset.getSubSet(TSubSet::kMC, fSubSet.getPeriodENUM(), TSubSet::kCHARM, TSubSet::kQ2g1_5, fSubSet.getProcessENUM(), fSubSet.getTriggerPeriod());
    TSubSet   cSubSet_q2g4 = fDataset.getSubSet(TSubSet::kMC, fSubSet.getPeriodENUM(), TSubSet::kCHARM, TSubSet::kQ2g4,fSubSet.getProcessENUM(),  fSubSet.getTriggerPeriod());

    // NOTE: here it is assumed that the luminosities of the samples were calculated already;
    // this won't be the case if the program is launched for the first time.
    Float_t   lumi_1_5 = cSubSet_q2g1_5.getLuminosity();
    Float_t   lumi_4 = cSubSet_q2g4.getLuminosity();
    fCharmQ2g4Weight = lumi_1_5 / (lumi_1_5 + lumi_4);
    cout << "INFO: A weighting factor due to 1.5/4 GeV samples:" << fCharmQ2g4Weight << endl;
}

// subdivide fHistogramsFile into subdirectories each corresponding
// to one TGlobalBin (the latter are chosen from src/TMiniNtupleAnalyzerSetBinning.cxx)
// and create histograms for each bin.
// Same set of histograms (according to src/TMiniNtupleAnalyzerDeclareHistograms.cxx) ??
// is created according for each bin.
void TMiniNtupleAnalyzer::CreateBinHistograms() {

    // helping variables
    TGlobalBin     *currentTGlobalBin;
    TIter          Iter_TGlobalBin(fList_TGlobalBin);
    char           currentDirName[256];
    Int_t          currentBinNumber=0;
    
    while ( (currentTGlobalBin=(TGlobalBin *)Iter_TGlobalBin.Next()) ) {
        currentBinNumber++;
        sprintf(currentDirName,"bin%i",currentBinNumber);
        TString    currentDirNameTString=currentDirName;
        currentTGlobalBin->BinName=currentDirNameTString;

        if (fApplyQ2g4Weighting) currentTGlobalBin -> SetWeightingFactor(fCharmQ2g4Weight);    // overriden in Loop.cxx,

        fHistogramsFile->mkdir(currentDirName);

        // after the following command this subdirectory currentDirName becomes 'current'
        // (and can be accessed by global variable gDirectory); newly created histograms belong to objects-in-memory
        // of this directory; command file->Write() or histogram->Write() writes histogram to the directory it belongs.
        // see ROOT manual for more details
        
        fHistogramsFile -> cd(currentDirName);

        // TODO: more info here!
        DeclareHistograms(currentTGlobalBin);
    }
    
    // print info message
    cout<<"INFO: Histograms file is subdivided into "<< currentBinNumber<<" bins"<<endl;
}

void TMiniNtupleAnalyzer::MirrorHistogramOLD(TString    HistName) {
    // in this function, the requested histogram is mirrored for all
    // TGlobalBins.
    // Note: it is assumed that histogram to be mirrored has even number
    // of bins and is symmetric w.r.t. zero

    TGlobalBin        *currentTGlobalBin;
    TIter                Iter_TGlobalBin(fList_TGlobalBin);
    char                currentDirName[256];
    Int_t                currentBinNumber=1;

    // looping over TGlobalBins
    while ( (currentTGlobalBin=(TGlobalBin *)Iter_TGlobalBin.Next()) ) {
        sprintf(currentDirName,"bin%i",currentBinNumber);
        fHistogramsFile->cd(currentDirName);
        currentBinNumber++;

        TList*    HistToFill=currentTGlobalBin->GetHistList();
        TH1F        *h_in=(TH1F*)HistToFill->FindObject(HistName);
        Int_t        NBins_in=h_in->GetNbinsX();

        // upper bound of the histogram to be mirrored
        Float_t        UpBound=h_in->GetBinLowEdge(NBins_in)+h_in->GetBinWidth(NBins_in);

        Int_t        NBins_out=NBins_in/2;
        // create mirrored histogram
        TH1F        *h_out=new TH1F(HistName+"_mirrored",h_in->GetTitle(),NBins_out,0,UpBound);
        h_out->SetStats(0);
        // looping over bins and mirrorring.
        // errors are treated assuming Poisson statistics
        for (int i=1;i<NBins_out+1;i++) {
            Int_t            PosBin=(Int_t)(NBins_out+i);
            Int_t            NegBin=(Int_t)(NBins_out-(i-1));
            Double_t        PosSign=h_in->GetBinContent(PosBin);
            Double_t        NegSign=h_in->GetBinContent(NegBin);
h_out->SetBinContent(i,PosSign-NegSign);
h_out->SetBinError(i,TMath::Sqrt(h_in->GetBinError(PosBin)*h_in->GetBinError(PosBin)+h_in->GetBinError(NegBin)*h_in->GetBinError(NegBin)));
            //h_out->SetBinError(i,TMath::Sqrt(PosSign+NegSign));
        }
        // add to TGlobalBin's list of histograms
        // (although not sure if this is really necessary,
        // because histograms already belong to particular subdirectory)
        HistToFill->Add(h_out);
    }
}
    
void TMiniNtupleAnalyzer::WriteHistograms()
{
    // write histograms to file, for this loop over subdirectories
    cout << "INFO: writing histograms to file" << endl;
    TGlobalBin        *currentTGlobalBin;
    TIter                Iter_TGlobalBin(fList_TGlobalBin);
    char                currentDirName[256];
    Int_t                currentBinNumber=1;

    while ( (currentTGlobalBin=(TGlobalBin *)Iter_TGlobalBin.Next()) ) {
        sprintf(currentDirName,"bin%i",currentBinNumber);
        fHistogramsFile->cd(currentDirName);
        currentTGlobalBin->GetHistList()->Write();
        //currentTGlobalBin->Write();
        currentBinNumber++;
    }
    fHistogramsFile->cd();
    fDebug->Write();
    fDebugSVTX->Write();
    fMc_q2_et->Write();
    fMc_pt_theta_pi -> Write();
    fHistogramsFile->Close();
    cout<<"INFO: Histograms written to file"<<endl;
}

Float_t    TMiniNtupleAnalyzer::CalculateProjDecayLength(Int_t    vertex) {

    // get coordinates of the secondary vertex
    Float_t        Xsv=Vtxsec_x[vertex];
    Float_t        Ysv=Vtxsec_y[vertex];
    Float_t        Zsv=Vtxsec_z[vertex];

    // a feature of vertexing block in v02: returns 666 if there's no vertex for current jet
    if ((Xsv==666)||(Ysv==666)||(Zsv==666)) return (-999);

    // get a primary-secondary vertex distance in transverse plane
    Float_t        deltaX=Xsv-Bspt_x;
    Float_t        deltaY=Ysv-Bspt_y;

    // get a decay length
    Float_t        DecayLength=TMath::Sqrt(deltaX*deltaX+deltaY*deltaY);
    if ( DecayLength > 1. ) return (-998);
    if ( TMath::Abs(Zsv) >30. )    return (-998);

    // get projected decay length
    Float_t        ProjectedDecayLength=0;

    Int_t            jet=vertex;

    Float_t        PhiJet=Kt_phijet_a[jet];
    Float_t        EtaJet=Kt_etajet_a[jet];
    Float_t        SinPhiJet=TMath::Sin(PhiJet);
    Float_t        CosPhiJet=TMath::Cos(PhiJet);
    ProjectedDecayLength=deltaX*CosPhiJet+deltaY*SinPhiJet; // 09/04/2010

    // 04 August 2011: eta-dependend shift of the whole projected decay length distribution
    if (fIsMC) {
        if ( (1.6 < EtaJet) && (EtaJet < 2.2) ) ProjectedDecayLength -= 0.0021913;
        if ( (1.3 < EtaJet) && (EtaJet < 1.6) ) ProjectedDecayLength -= 0.0015827;
        if ( (1.0 < EtaJet) && (EtaJet < 1.3) ) ProjectedDecayLength -= 0.000766;
    }

    return  ProjectedDecayLength;
}

Float_t    TMiniNtupleAnalyzer::CalculateSignificance(Int_t vertex) {

    Float_t    ProjectedDecayLength=CalculateProjDecayLength(vertex);
    if (ProjectedDecayLength == -998) return -998;
    if (ProjectedDecayLength == -999) return -999;

    Int_t   jet=vertex;

    Float_t        PhiJet=Kt_phijet_a[jet];
    Float_t        EtaJet=Kt_etajet_a[jet];
    Float_t        SinPhiJet=TMath::Sin(PhiJet);
    Float_t        CosPhiJet=TMath::Cos(PhiJet);

    Float_t    ProjectedDecayLengthError=0;

    Float_t    d1=CosPhiJet;
    Float_t    d2=SinPhiJet;
    Float_t    sigma_x=TMath::Sqrt(Vtxsec_cov[vertex][0]);
    Float_t    sigma_y=TMath::Sqrt(Vtxsec_cov[vertex][2]);

    /**\todo Now values of beam spot position error (beam spot size) are written to orange variables \a Bspt_xer
and \a Bspt_yer. Change later to avoid confusion!
    */

    TSubSet::Period period = fSubSet.getPeriodENUM();
    if ( (period == TSubSet::k0304P) || (period == TSubSet::k03P) || (period == TSubSet::k04P) || (period == TSubSet::k0607P) || (period == TSubSet::k06P) || (period == TSubSet::k07P) ) {
            Bspt_xer=0.0088;
            Bspt_yer=0.0024;
    } else if ((period==TSubSet::k05E) || (period==TSubSet::k06E)) {
            Bspt_xer=0.0080;
            Bspt_yer=0.0022;
    }

    ProjectedDecayLengthError=TMath::Sqrt(d1*d1*(sigma_x*sigma_x+Bspt_xer*Bspt_xer)+d2*d2*(sigma_y*sigma_y+Bspt_yer*Bspt_yer)+2*d1*d2*Vtxsec_cov[vertex][1]);

    // now apply smearing, code taken from Verena and further tuned to give the best
    // description in our case
    if (fApplySmearing && fIsMC) {

        Double_t nr_rand = rnd->Rndm();
        Float_t exponent = fSmearingExpCoeff;

        // default values - are set outside the class
        Float_t     SmearingGauss1Width = fSmearingGauss1Width;
        Float_t     SmearingGauss1Prob = fSmearingGauss1Prob;
        Float_t     SmearingGauss2Width = fSmearingGauss2Width;
        Float_t     SmearingGauss2Prob = fSmearingGauss2Prob;   

        // for highest eta bin using a bit different parameters
        if ( (1.6 < EtaJet) && (EtaJet < 2.2) ) {
            SmearingGauss1Prob = 0.09;
            SmearingGauss2Prob = 0.006;
        }

        // Smear core by Gaussian
        if( nr_rand < SmearingGauss1Prob ) {
            Double_t nr_rand_gauss = rnd->Gaus();
            Float_t smearvalue = SmearingGauss1Width * ProjectedDecayLengthError * nr_rand_gauss;
            ProjectedDecayLength += smearvalue;
        }

        // Smear intermediate tails by Gaussian
        if( nr_rand < SmearingGauss2Prob ) {
            Double_t nr_rand_gauss = rnd->Gaus();
            Float_t smearvalue = SmearingGauss2Width * ProjectedDecayLengthError * nr_rand_gauss;
            ProjectedDecayLength += smearvalue;
        }

        // Smear extreme tails by exponential function
        if( nr_rand < fSmearingExpProb * ProjectedDecayLengthError ) {
            Double_t nr_rand2 = rnd2->Rndm();
            Double_t randtemp = 2*nr_rand2-1;
            Float_t sign = randtemp/TMath::Abs(randtemp);
            ProjectedDecayLength += sign*TMath::Log(1-TMath::Abs(randtemp))/(-exponent);
        }
    }

    Float_t        Significance=0;

    Significance = ProjectedDecayLength / ProjectedDecayLengthError;
    return         Significance;
}

Bool_t    TMiniNtupleAnalyzer::IsDIS()
{
        fDebug->Fill(0);

        /*! \todo Trigger definitions to be checked again!
        */
//         Bool_t        SPP01=(Bool_t)( (Tltw[2]>>(0+16)) & 1);
        Bool_t        SPP02=(Bool_t)( (Tltw[2]>>(1+16)) & 1);
        Bool_t        SPP09=(Bool_t)( (Tltw[2]>>(8+16)) & 1);
//         Bool_t        DIS03=(Bool_t)( (Tltw[3]>>(2+16)) & 1);
//         Bool_t        DIS04=(Bool_t)( (Tltw[3]>>(3+16)) & 1);
        Bool_t        HFL17=(Bool_t)( (Tltw[13]>>(0+16)) & 1);
//         Bool_t        EXO07=(Bool_t)( (Tltw[5]>>(6+16)) & 1);
        Bool_t        HPP31=(Bool_t)( (Tltw[11]>>(14+16)) & 1);

        //if ( !(SPP01||SPP09||DIS03||DIS04||HFL17||EXO07) ) return false;

        if ( (!fIsMC ) && (Runnr <= 48600) ) return false;
        fDebug->Fill(1);

        // period dependend trigger requirements
        TSubSet::Period period = fSubSet.getPeriodENUM();
        if (period == TSubSet::k0304P || (period == TSubSet::k03P) || (period == TSubSet::k04P)) {
            if ( !(SPP02) ) return false;
            // Using only Runnr > 48600 => Can use the same triggers as for 05e
        } else if (period == TSubSet::k05E) {
            if ( !(SPP02) ) return false;
        } else if (period ==TSubSet::k06E) {
            if ( !(SPP09 || HFL17 || HPP31) ) return false;
        } else if ( (period == TSubSet::k0607P) || (period == TSubSet::k06P) || (period == TSubSet::k07P)) {
            if (!(SPP09 || HFL17 || HPP31)) return false;
        }

        fDebug->Fill(2);
        if (Sincand<1)                             return false;
        fDebug->Fill(3);
        if (Siprob[0]<0.9)                        return false;
        fDebug->Fill(4);
        if (Siq2da[0]<5)                             return false;
        fDebug->Fill(5);

        if (Siq2da[0]>1000)                        return false;
        fDebug->Fill(6);

        if (Siyel[0]>0.7)                         return false;
        fDebug->Fill(7);
         if (Siyjb[0]<0.02)                         return false;
        fDebug->Fill(8);

        Float_t        x_el=Sipos[0][0];
        Float_t        y_el=Sipos[0][1];
//     Float_t        z_el=Sipos[0][2];

        Float_t        x_el_abs=TMath::Abs(x_el);
        Float_t        y_el_abs=TMath::Abs(y_el);

        /*if (z_el<-147)
        {
            if ((x_el_abs<13.)&&(y_el_abs<13.))        return false;
        }*/
        /** changed 02.03.2010
        */
        if ( (x_el_abs<13.) && (y_el_abs<13.) )        return false;

        fDebug->Fill(9);

        if (Siecorr[0][2]<10.)                     return false;
        fDebug->Fill(10);
        if (TMath::Abs(Zvtx)>30.)                return false;
        fDebug->Fill(11);

        Float_t        e_pz_zufos=V_h_e_zu-V_h_pz_zu;
        if ( (e_pz_zufos<44) || (e_pz_zufos>65) ) return false;
        fDebug->Fill(12);

        fDebug->Fill(14);
        fDebug->Fill(15);

        // this part taken from Ramoona's code --> for the timebeing we don't use them (have to be understood)
        // rcal radius cut
        //if ((z_el<-147)&&((TMath::Sqrt(x_el*x_el+y_el*y_el))>175)) return false;
        // Supercrack 1
        //if ((z_el<-98.5)&&(z_el>-104)) return false;
        // Supercrack 2
        //if ((z_el<174)&&(z_el>164)) return false;
        //Chimney
        //if ((z_el<-147)&&(x_el_abs< 12.)&&(y_el>80.))  return false;
        //fDebug->Fill(14);
        // module gap cut
        /*if (z_el<-147)
        {
            if ((y_el>0&&(x_el>6.5&&x_el< 12))||(y_el<0&&(x_el>-14&&x_el<-8.5))) return false;
        }*/
        // bad cell cut (1) ---> see below
        /*if ( z_el < -147)
        {
        if (x_el>=7.515&&x_el<=31.845&&y_el>=7.90&&y_el<=31.90) return false;
        }*/
        // bad cell cut (2)
        /*if ( z_el < -147)
        {
            if (x_el>=-13.315&&x_el<=11.515&&y_el>=0.0&&y_el<=43.80) return false; // cut on y at 0 avoids narrow stave between effective rCTD>20 and bad cell
        }*/

    // module edge cut
        /*Double_t ModuleGap[24] = {-234.78,
                    -214.45,
                    -194.12,
                    -173.79,
                    -153.46,
                    -133.13,
                    -112.80,
                    -92.47,
                    -72.14,
                    -51.81,
                    -31.48,
                    -11.15,
                    9.35,
                    29.68,
                    50.01,
                    70.34,
                    90.67,
                    111.00,
                    131.33,
                    151.66,
                    171.99,
                    192.32,
                    212.65,
                    232.98};
        if (z_el < -147 )
        {
            for (Int_t n=0;n<24;n++)
            {
                if (TMath::Abs(x_el - ModuleGap[n]) < 2) return false;
            }
        }
        fDebug->Fill(15);*/


        // Pt(had)
        //if ()
        //float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
       //float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));

        //    to remove events with no reconstructed primary vertex
        if  ( Ntrkvtx == 0 ) return false;
        fDebug->Fill(16);
        //cout << "Evtake= " << Evtake << endl;
        if (!fIsMC) {

            #ifdef CN_VERSION_V02
            // use evtake for v02
            if ( Evtake <= 0 ) return false;
            #endif

            #if defined CN_VERSION_V04 || defined CN_VERSION_V06
            // use evtake_iwant for v04; added 15 March 2011 (see mail from Philipp 23 February 2011)
            // Q: the same for v06??
            if ( (Evtake_iwant != 1) && (Evtake_iwant != 2) ) return false;
            #endif
        }
        fDebug->Fill(17);

        if (!fIsMC) {
            if ( Mvdtake <= 0 ) return false;
        }
        fDebug->Fill(18);

        // bad cell cut: x,y position cuts are the same as Ramoona's but no zel requirement as well as certain
        // run range. Taken from Philipp
        //if (fIsMC)    Runnr = Simrun;
        Int_t        cRunnr = Runnr;
        if (fIsMC) cRunnr = Simrun;

        if ((cRunnr > 59600 && cRunnr < 60780) || (    cRunnr > 61350 && cRunnr < 61580) ||    (cRunnr > 61800 && cRunnr < 63000))
        {
            if (x_el>=7.515 && x_el<=31.845 && y_el>=7.90 && y_el<=31.90)  return false;
        }

        fDebug->Fill(19);

        return true;
}

Bool_t    TMiniNtupleAnalyzer::IsDIS_Rho() {
    
        // event counter
        fDebug->Fill(0);

        // if ( (!fIsMC ) && (Runnr <= 48600) ) return false;
        // fDebug->Fill(1);

        if (Sincand<1)              return false;
        fDebug->Fill(2);

        if (Siprob[0]<0.9)          return false;
        fDebug->Fill(3);

        if (Siecorr[0][2]<10.)      return false;
        fDebug->Fill(4);

        if (TMath::Abs(Zvtx)>30.)   return false;
        fDebug->Fill(5);

        Float_t e_pz_zufos=V_h_e_zu-V_h_pz_zu;
        if ( (e_pz_zufos<35) || (e_pz_zufos>70) ) return false;
        fDebug->Fill(6);

        //    to remove events with no reconstructed primary vertex
        if  ( Ntrkvtx == 0 ) return false;
        fDebug->Fill(7);

        if (!fIsMC) {
            #ifdef CN_VERSION_V02
            // use evtake for v02
            if ( Evtake <= 0 ) return false;
            #endif

            #if defined CN_VERSION_V04 || defined CN_VERSION_V06
            // use evtake_iwant for v04; added 15 March 2011 (see mail from Philipp 23 February 2011)
            // Q: the same for v06??
            if ( (Evtake_iwant != 1) && (Evtake_iwant != 2) ) return false;
            #endif
        }
        fDebug->Fill(8);

        if (!fIsMC) {
            if ( Mvdtake <= 0 ) return false;
        }
        fDebug->Fill(9);

        // if (Siq2da[0]<5) return false;
        // fDebug->Fill(10);

        // Float_t        x_el_abs=TMath::Abs(Sipos[0][0]);
        // Float_t        y_el_abs=TMath::Abs(Sipos[0][1]);
        // if ( (x_el_abs<13.) && (y_el_abs<13.) )        return false;

        return true;
}

void        TMiniNtupleAnalyzer::DeclareHistograms(TGlobalBin* globalbin) {
    // Declares histograms for particular TGlobalBin
    // helping string
    string line;
    // open the file with binning
    ifstream binning ( (TString)getenv("NTUPLEANALYZER") + "/config/" + fHistogramDeclarationFile);
    
    // if successfull - read the contents, otherwise exit
    if (binning.is_open()) {
        // read the file line by line and  process
        while (! binning.eof() ) {
            // read the line
            getline (binning,line);
            const char*     linechar=line.data();
            // helping variable to decode the line
            char    Title[256];
            Int_t   NBins=0;
            Float_t LowerLimit=0;
            Float_t UpperLimit=0;
            char    mirror[20]="";

            sscanf (linechar, "%s%d%f%f%s", Title, &NBins, &LowerLimit, &UpperLimit, mirror);
            string mirror_str = mirror;
            TString Title_tstring = Title;
            if (mirror_str=="mirror") {
                globalbin -> AddHistogram(new TH1F(Title_tstring+"_pos", "", NBins, LowerLimit, UpperLimit) );
                globalbin -> AddHistogram(new TH1F(Title_tstring+"_neg", "", NBins, LowerLimit, UpperLimit) );
                globalbin -> AddHistogram(new TH1F(Title_tstring+"_sum", "", NBins, LowerLimit, UpperLimit) );
                globalbin -> AddHistogram(new TH1F(Title_tstring+"_diff", "", NBins, LowerLimit, UpperLimit) );
                globalbin -> AddMirroredHistTitle(Title_tstring);
            }
            globalbin -> AddHistogram(new TH1F(Title_tstring,"",NBins,LowerLimit,UpperLimit) );
        }
        binning.close();
    } else {
        cout << "ERROR: Unable to open declarehist.cfg. "<<endl;
        cout<< " Terminating, sorry"<<endl;
        exit(-1);
    }
    
    // loop over histograms - cosmetics
    TList*    GlobBinHistList=globalbin->GetHistList();
    TIter        next(GlobBinHistList);
    TH1F*     h;
    while ( (h = (TH1F*)next()) ) {
        //h->SetTitle(h->GetTitle()+globalbin->BinName+" "+globalbin->GetBinDescription());
        //h->SetTitle(h->GetTitle()+space+globalbin->GetBinDescription());
        //h->SetTitle(h->GetTitle()+globalbin->GetBinDescription()+","+globalbin->BinName);
        h->SetTitle(h->GetTitle()+globalbin->GetBinDescription());
        h->SetXTitle(h->GetName());
        //h->SetStats(0);
        h->Sumw2();
    }
}

void TMiniNtupleAnalyzer::PrintEventsPerRun() {
    // loop over the map and print number of events for runs with non-zero number of events
    for (unsigned i = 0; i < 100000; i++) {
        if (fEventsPerRun_ALL[i] != 0) {
            cout << "Run: " << i << " Nevents_ALL: " << fEventsPerRun_ALL[i] << " Nevents_EVTAKE_MVDTAKE: " << fEventsPerRun_EVTAKE_MVDTAKE[i] << endl;
        }
    }
}

void TMiniNtupleAnalyzer::GetEtReweightingLF_histo() {

    TString DATABASE_PATH = getenv("DATABASE_PATH");
    TFile   * file = new TFile (DATABASE_PATH+"/"+fEtReweightingLF_filename);
    cout << "going to open " << DATABASE_PATH+"/"+fEtReweightingLF_filename << endl;
    fEtReweightingLF_histo = (TH1F*)file -> Get("histo_substr");
    if (fEtReweightingLF_histo == NULL) {
        cout << "was not possible to retrieve a histogram " << endl;
        abort();
    } else {
        cout << "successfully got the Et LF reweighting histogram" << endl;
    }
    
}

void TMiniNtupleAnalyzer::GetFragmentationReweighting_Histo() {

    TString DATABASE_PATH = getenv("DATABASE_PATH");
    TFile   * file = new TFile (DATABASE_PATH+"/"+fFragmentationReweighting_filename);
    cout << "going to open " << DATABASE_PATH+"/"+fFragmentationReweighting_filename << endl;
    fFragmentationReweighting_histo = (TH1F*)file -> Get("reweighting");
    if (fFragmentationReweighting_histo == NULL) {
        cout << "was not possible to retrieve a histogram " << endl;
        abort();
    } else {
        cout << "successfully got the fragmentation function reweighting histogram" << endl;
    }
    
}


// gets a weighting factor for true-ET reweighting of light flavour MC
Float_t    TMiniNtupleAnalyzer::getEtReweighting(Float_t   jet_et) {
    // declare variable to store a weighting factor
    Double_t    weighting_factor = 1;
    
    // get type and flavour of the sample we are analyzing now
    TSubSet::Type type = fSubSet.getTypeENUM();
    TSubSet::Flavour flavour = fSubSet.getFlavourENUM();

    // cross-check that this is light flavour MC
    if ((type == TSubSet::kMC) && (flavour == TSubSet::kLIGHT)) {
        // get a weighting factor
        // sanity check: a pointer to the histogram should be valid
        if (fEtReweightingLF_histo == NULL) {
            cout << "was not possible to retrieve a histogram " << endl;
            abort();
        }
        
        // loop over the histogram bins to get the binning
        unsigned    good_bins=0;
        unsigned    bin = 0;
        for (int i = 1; i < (fEtReweightingLF_histo->GetNbinsX()+1); i++) {
            Float_t     bin_low_edge = fEtReweightingLF_histo->GetBinLowEdge(i);
            Float_t     bin_up_edge = fEtReweightingLF_histo->GetBinLowEdge(i+1);

            if ((jet_et >= bin_low_edge) && (jet_et < bin_up_edge)) {
                good_bins++;
                bin = i;
            }
        }

        if ( good_bins > 1 ) {
            cout << "too many matches found" << endl;
            abort();
        } else if (good_bins == 0 ) {
            if (jet_et >= (fEtReweightingLF_histo->GetBinLowEdge(fEtReweightingLF_histo->GetNbinsX()+1))) bin = fEtReweightingLF_histo->GetNbinsX();
            else {
                cout << "no matches found, but et in the histogram range!" << endl;
                cout << "jet ET: " << jet_et << endl;
                cout << "nbins: " << fEtReweightingLF_histo->GetNbinsX() << endl;
                cout << "lower edge of last bin " << fEtReweightingLF_histo->GetBinLowEdge(fEtReweightingLF_histo->GetNbinsX()) << endl;
                cout << "upper edge of last bin " << fEtReweightingLF_histo->GetBinLowEdge(fEtReweightingLF_histo->GetNbinsX()+1) << endl;
                abort();
            }
        }

        // get a weighting factor
        weighting_factor = fEtReweightingLF_histo -> GetBinContent(bin);
    } else {

        // should not be called for anything else then LF MC
        cout << "called getEtReweighting() for non-LF-MC sample. Terminating" << endl;
        abort();
    }

    // finished successfully, return the weighting factor
    // but first check whether it's non-zero - the LF et reweighting histo I got for 4.2 cut,
    // hence the weight is zero for all the events before!
    if (weighting_factor!=0) return      weighting_factor;
    else return 1;
}

// initializer of random generators that we use;
// before it was in the constructor, now is in another function so that
// a specific seed can be selected
void TMiniNtupleAnalyzer::InitializeRandomGenerators() {
    rnd = new TRandom3(fSeed_rnd);
    rnd2 = new TRandom3(fSeed_rnd2);
    rnd_eff = new TRandom3(fSeed_rnd_eff);
}

// defines a bin number by a value for an arbitrary histogram
Int_t TMiniNtupleAnalyzer::getReweightingHistoBin(TH1F * histo, Float_t   value) {

    // loop over the histogram bins to get the binning
    unsigned    good_bins=0;
    unsigned    bin = 0;
    for (int i = 1; i < (histo->GetNbinsX()+1); i++) {
        Float_t     bin_low_edge = histo->GetBinLowEdge(i);
        Float_t     bin_up_edge = histo->GetBinLowEdge(i+1);

        if ((value >= bin_low_edge) && (value < bin_up_edge)) {
                good_bins++;
                bin = i;
            }
        }

        if ( good_bins > 1 ) {
            cout << "ERROR: too many matches found" << endl;
            abort();
        } else if (good_bins == 0 ) {
            if (value >= (histo->GetBinLowEdge(histo->GetNbinsX()+1))) bin = histo->GetNbinsX();
            else {
                cout << "ERROR: no matches found, but given value is in the histogram range!" << endl;
                cout << "value: " << value << endl;
                cout << "nbins: " << histo->GetNbinsX() << endl;
                cout << "lower edge of last bin " << histo->GetBinLowEdge(histo->GetNbinsX()) << endl;
                cout << "upper edge of last bin " << histo->GetBinLowEdge(histo->GetNbinsX()+1) << endl;
                abort();
            }
        }

    // finished successfully, return the bin index
    return      bin;
}

// some parts of code here are utilized from Loop() function - track efficiency studies
void TMiniNtupleAnalyzer::findVertices() {

    // this function looks for secondary vertices following a method in SECVTX block in orange

    // clear array of vertices, redundant, just to be safe
//   fVerticesRefitted.clear(); // debug case
     fVertices.clear();          // production case
     fSecondaryVertexFound = false; // production case

    // some helping variables
    Float_t     dR=0;
    Float_t     dRmin;
    Int_t       jet_id_min;
    Float_t     trk_eta;
    Float_t     trk_phi;
    Float_t     trackhelix[60][5];
    Float_t     trackhelixcov[60][15];
    Float_t     trackmomentum[60];
    Float_t     trackpT[60];
    Int_t       trackIDs[60];
    unsigned    ntracks=0;
    // map: jet index -> list of tracks matched to it
    map <Int_t, vector <Int_t> >   track_map;

    // loop over tracks to find those that belong to the jet
    for (int trk = 0; trk < Trk_ntracks; trk++) {
        
        // get a vctrhl id of the track
        Int_t vctrhl_id = Trk_id2[trk];
        // print a warning if there's no link to vctrhl; should not happen; orange version terminates in this case
        if (vctrhl_id == 0) cout << "WARNING: track does not have a link to VCTRHL" << endl;
        // Remove any track matched to the first Sinistra electron candidate;
        if ( (Sitrknr[0] > 0) && (Sitrknr[0] == vctrhl_id) ) continue;

        // other tracking quality cuts

        // number of CTD superlayers cut + STT cut
        Int_t       nSTT = Trk_nstt[trk];
        Int_t       nCTD = Trk_layouter[trk] - Trk_layinner[trk] + 1;
        if ((nCTD < fCTD) && (nSTT < fSTT)) continue;
        
        // number of MVD hits cut
        Int_t       nMVD = Trk_nbr[trk] + Trk_nbz[trk] + Trk_nwu[trk] + Trk_nwv[trk];
        if (nMVD < fMVD) continue;

        // get track angles and momentum

        Float_t     phi = Trk_helpar[trk][0];
        Float_t     cot_theta = Trk_helpar[trk][4];
        Float_t     theta = TMath::Pi()/2 - atan(cot_theta);
        Float_t     eta = -log(tan(theta/2));
        trk_eta = eta;
        trk_phi = phi;
        Float_t     pt = Trk_helmom[trk] * sin(theta);

        // eta, phi and pt definition above (from helix parameters) is as in the secvtx block
        // however it might be desirable to use variables from the Tracking blocks,
        // which are corrected for secondary vertices
        TVector3 track(Trk_px[trk], Trk_py[trk], Trk_pz[trk]);
        if (!fUseHelixTrackParameters) {
            trk_eta = track.Eta();
            trk_phi = track.Phi();
            pt = track.Pt();
        }

        if (trk_phi < 0) trk_phi += (2*TMath::Pi());    // to take into account ROOT convention

        // track pT cut
        if (pt < fpT) continue;

        // this track passes selection criteria
        // now have to find a jet which is closest to this track
        dRmin = 99999;
        jet_id_min = -1;
        // loop over DIS jets (ktjetsB) and find the closest jet to this track
        for (int jet = 0; jet < Kt_njet_b; jet++) {

            // jet cuts
            // get eta-phi distance between the track and the jet axis
            Float_t dPhi = TMath::Abs(trk_phi - Kt_phijet_b[jet]);
            if ( dPhi > TMath::Pi() ) dPhi = 2 * TMath::Pi() - dPhi;
            dR = sqrt( pow(trk_eta - Kt_etajet_b[jet], 2) + pow(dPhi, 2) );
            
            // cone cut: check whether closest jet is close enough
            if (dR > fRcut) continue;
            // weight R distance by Et of the jet
            dR = dR / Kt_etjet_b[jet];
            // check whether there was a jet closer to this track or store jet number and R otherwise
            if (dR < dRmin) {
                dRmin = dR;
                jet_id_min = jet;
            }
        }

        // check whether there was at least 1 good jet
        if (jet_id_min == (-1)) continue;

        if ( Kt_etjet_b[jet_id_min] < fJetEtCut) continue;
        if ( ( Kt_etajet_b[jet_id_min] > 2.2 ) || ( Kt_etajet_b[jet_id_min] < -1.6 ) ) continue;

        // ok, matched a track to a jet; fill this information
        track_map[jet_id_min].push_back(trk);
    }

    // jet->tracklist map is ready; loop over it to find which jets have at least two tracks and proceed
    // with the vertex fit in this case

    map <Int_t, vector<Int_t> >::iterator iter;
    for ( iter=track_map.begin() ; iter != track_map.end(); iter++ ) {
        Int_t   jet = (*iter).first;
        vector <Int_t>  track_list = (*iter).second;
        ntracks = track_list.size();

        // proceed only if at least two tracks were found
        if (ntracks < 2) continue;

        // ok, found a vertex candidate
        TVertex cVtx;

        // loop over the track list to get track parameters
        for (int i=0; i < ntracks; i++ ) {
            // index of the track in the Tracking block
            Int_t       trk = track_list[i];
            // helix parameters from the Tracking block

            for (int j=0; j<5; j++){
                trackhelix[i][j] = Trk_helpar[trk][j]; 
            }

            // helix parameters covariance from the Tracking block
            for (int j=0; j<15; j++){
                trackhelixcov[i][j] = Trk_covmat[trk][j];
            }

            // track momentum
            trackmomentum[i] = Trk_helmom[trk];
            TVector3 track(Trk_px[trk], Trk_py[trk], Trk_pz[trk]);
            trackpT[i] = track.Pt();
            // track ID
            trackIDs[i] = trk;
        }

        // set track parameters
        cVtx.SetTrackParameters(ntracks, trackhelix, trackhelixcov, trackmomentum);
        cVtx.SetTrackPt(ntracks, trackpT);
        cVtx.SetVertexTracks(ntracks, trackIDs);

        // check whether smearing should be applied
        if (fApplySmearing && fIsMC) { 
            cVtx.SetApplySmearing(true);
        } else { 
            cVtx.SetApplySmearing(false);
        }

        #if defined CN_VERSION_V06
        Float_t     bsptx;
        Float_t     bspty;
        if (! fIsMC) {
            // v06
            bsptx = Bspt_x + Bspt_dxdz * (Vtxredprim_z[Nr_redprim - 1] - Bspt_z);
            bspty = Bspt_y + Bspt_dydz * (Vtxredprim_z[Nr_redprim - 1] - Bspt_z);
        }

        if (fIsMC) {
            // v06
            bsptx = Bspt_x + Vtxredprim_z[Nr_redprim - 1] * (-0.00027) ;
            bspty = Bspt_y + Vtxredprim_z[Nr_redprim - 1] * (-0.00013) ;
        }
        cVtx.SetPrimaryVertexCoordinates(bsptx, bspty, Vtxredprim_z[Nr_redprim - 1]);
        #endif

        // set reference axis for this vertex
        cVtx.SetAxisVector(Kt_etajet_b[jet], Kt_phijet_b[jet]);

        // period-dependent beam spot size
        TSubSet::Period period = fSubSet.getPeriodENUM();
        if ( (period == TSubSet::k0304P) || (period == TSubSet::k03P) || (period == TSubSet::k04P) || (period == TSubSet::k0607P) || (period == TSubSet::k06P) || (period == TSubSet::k07P) ) {
            Bspt_xer=0.0088;
            Bspt_yer=0.0024;
        } else if ((period==TSubSet::k05E) || (period==TSubSet::k06E))	{
            Bspt_xer=0.0080;
            Bspt_yer=0.0022;
        }

        // set beam spot size as error on primary vertex coordinate
        // only X, Y are relevant, NULL for Z is just dummy
        cVtx.SetPrimaryVertexCoordinatesError(Bspt_xer, Bspt_yer, 0 );

        // perform vertexing!
        bool fit_successful = cVtx.RefitVertex();
        // skip if the fit was not successful or gave too large decay length
        if (!fit_successful) continue;
        // the chi2 cut
         if (cVtx.chi2ndf>6.) continue;
        // and the mass cut
         if ((cVtx.GetVertexMass()<1.) || (cVtx.GetVertexMass()>6) ) continue;

        // set jet ID
        cVtx.fJetB = jet;

        // ok, this is a good vertex/jet; store it to the vector and raise the flag that 
        // there was at least one good vertex in this event
//      fVerticesRefitted.push_back(cVtx); // debug case
        fVertices.push_back(cVtx); // production case
        fSecondaryVertexFound = true;   // production case
    }
}

void TMiniNtupleAnalyzer::SetCharmETReweightingPar(Float_t par0, Float_t par1) {
    fCharmETReweighting_p0 = par0;
    fCharmETReweighting_p1 = par1;
}
