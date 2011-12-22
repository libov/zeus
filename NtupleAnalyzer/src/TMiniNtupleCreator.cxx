//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
//#include <includes.h>

// my headers
#include <inc/TMiniNtupleCreator.h>
#include <inc/TNtupleAnalyzer.h>

// system headers
#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// ROOT headers
#include<TSystem.h>

TMiniNtupleCreator::TMiniNtupleCreator():
fCurrentFileNumber(0),
fCurrentNumberEventsInFile(0),
fCreateFile(true),
fCurrentTreeFile(NULL),
fStore_dCache(false)
{

    fTestMode=false;        //! This variable is used during adding of files to the chain.
                            //!< If false - all files wil be added
                            //!< If true - only first fTestFilesNumber files are added. Good for test purpose.
}

void TMiniNtupleCreator::Initialize() {

    // do an initialization of TNutpleAnalyzer
    Init();

    // some other initializations
    AddFilesToChain();
    CalculateNumberOfEvents();
    SetBranchAddresses();

    if (fPathToMiniNtuples.Contains("acs")) fStore_dCache = true;

    // in case directory does not exist - create it
    struct stat st;
    if(stat(fPathToMiniNtuples.Data(), &st) != 0){
        cout << "INFO: minintuples directory does not exist; creating one!" << endl;
        system("mkdir "+fPathToMiniNtuples);
    }

    // if store to dCache, also create a temporary directory locally
    if (fStore_dCache) {
        fPathToMiniNtuplesTEMP += "/" + fSampleName;
        if (stat(fPathToMiniNtuplesTEMP.Data(), &st) != 0) {
            system("mkdir "+fPathToMiniNtuplesTEMP);
        }
    }

    cout << " INFO: Minintuples will be stored to " << fPathToMiniNtuples << endl;
    if (fStore_dCache) {
        cout << " INFO: Temporary location before copying to dCache: " << fPathToMiniNtuplesTEMP << endl;
    }

    cout << " INFO: initialisation done " << endl;
}

void TMiniNtupleCreator::CreateMiniNtuples(Int_t    firstEvent, Int_t    lastEvent)
{
        char    temp[256];
        sprintf(temp, "%09d", firstEvent);
        TString    Suffix=temp;
        if (fStore_dCache) {
            fDebugHistoFile=new TFile(fPathToMiniNtuplesTEMP+"/debugHisto"+"_"+Suffix+"_.root","recreate");
        } else {
            fDebugHistoFile=new TFile(fPathToMiniNtuples+"/debugHisto"+"_"+Suffix+"_.root","recreate");
        }
        fDebugHistoFile->cd();            // smth of it is redundant
        //if (!(fDebug=(TH1F*)fDebugHistoFile->Get("fDebug")))
        fDebug = new TH1F("fDebug", " Debug histogram for mini ntuples creation ", 50, 0, 50);
        fDebug->SetDirectory(fDebugHistoFile);            // smth of it is redundant

        cout<<"\n******** START MAIN LOOP ********\n"<<endl;
        for (int i=firstEvent; i<lastEvent; i++){
            if ( i % 1000 == 0 )    cout<< " processing event " << i << endl;
            fChain->GetEntry(i);

            if (fCreateFile){ 
                CreateFile(i);
            }
            if ( IsGoodEvent () ) {
                fCurrentTree->Fill();
                fCurrentNumberEventsInFile++;
            }
            if ( (fCurrentNumberEventsInFile==500000) || (i==(lastEvent-1)) )    WriteFile();
        }

        cout<<"\n******** MAIN LOOP FINISHED ********\n"<<endl;

        End();
}

void    TMiniNtupleCreator::CreateFile(Int_t    currentEvent)
{
        // something is redundand here!!
        char        temp[256];
        sprintf(temp, "%09d", currentEvent);
        TString     Suffix=temp;
        char        name[256];
        TString        file_name;
        //TString        file_name=fPathToMiniNtuples+"/"+fSampleName+"_"+Suffix+"_%d.root";    // why neede thish?
        if (fStore_dCache) {
            file_name=fPathToMiniNtuplesTEMP+"/"+fSampleName+"_"+Suffix+"_.root";
        } else {
            file_name=fPathToMiniNtuples+"/"+fSampleName+"_"+Suffix+"_.root";
        }
        
        sprintf(name, file_name, fCurrentFileNumber);
        fCurrentTreeFile = new TFile(name,"recreate");
        fCurrentTreeFile->cd();
        cout << "INFO: " << name << " created" << endl;
        CreateTree();
        fCurrentFileNumber++;
        fCreateFile=false;
}

void    TMiniNtupleCreator::CreateTree() {
        
        fCurrentTree = new TTree("orange","reduced ntuple");
        
        if (fCurrentTree != NULL) {
            cout << "INFO: created a TTree obejct\n" << endl;
            AddTreeBranches();
        } else {
            cout << "ERROR: failed to create a tree!\n";
            abort();
        }
}

void    TMiniNtupleCreator::WriteFile()
{
        fCurrentTree->Write();
        delete fCurrentTree;
        fCurrentTreeFile->Close();
        cout << "INFO: copying mini ntuple file to the dCache" << endl;
        TString     filename(fCurrentTreeFile -> GetName());
        TString     command = "dccp -d4 " + filename + " " + fPathToMiniNtuples;
        int result = system (command);
        if (result != 0) {
            cout << "ERROR: copying failed! Terminating! " << endl;
            abort();
        }
        cout << "INFO: removing mini ntuple file from local space" << endl;
        result = system ("rm -rf " + filename);
        if (result != 0) {
            cout << "ERROR: removing failed! Terminating! " << endl;
            abort();
        }
        fCurrentNumberEventsInFile=0;
        fCreateFile=true;
}

Bool_t TMiniNtupleCreator::IsGoodEvent()
{
    // here only soft cuts are applied; maybe in the future make a common routine that can be used by TMiniNtupleAnalyzer
    // as well and do not hardcode cuts anymore; for the timebeing stick to this...
    /*fDebug->Fill(1);

    if  return false;
    fDebug->Fill(2);

    if ( Siprob[0] < 0.9 ) return false;
    fDebug->Fill(3);*/

    fDebug->Fill(0);

    //Bool_t        not_recoDIS = ( (Sincand < 1) && (Siprob[0] < 0.9) && (Siq2el[0] < 4.) && (Siq2da[0] < 4.) );
        // changed 15 February 2011
        Bool_t        not_recoDIS = ( (Sincand < 1) || (Siprob[0] < 0.9) || ((Siq2da[0] < 4.)&& (Siq2el[0] < 4.)) );
    Bool_t        not_trueDIS = ( ( Mc_q2 < 4. ) && ( Mc_q2_cr < 4. ) );

    if (fIsMC) {
        if ( not_recoDIS && not_trueDIS ) return false;
    }
    else {
        if ( not_recoDIS ) return false;
    }

    fDebug->Fill(1);

    if (fIsMC) {
        if ( ( Kt_njet_b == 0  ) && ( Nhbmjets == 0  ) ) return false;
    }
    else {
        if ( Kt_njet_b == 0 ) return false;
/*                // 15/02/2011. more cn-level cuts so that minintuples are smaller
                if (Nr_secvtx == 0) return false;

                bool HighEtJetPresent = false;
                for (int k=0; k < Kt_njet_b; k++) {
                        if (Kt_etjet_b[k] >= 4.2) { 
                                HighEtJetPresent = true;
                                break;
                        }
                }
                if (!HighEtJetPresent) return false;*/
    }

    fDebug->Fill(2);

    return true;
}

Bool_t TMiniNtupleCreator::IsGoodRhoEvent()
{
    fDebug->Fill(0);

    Bool_t not_recoDIS = ( (Sincand < 1) || (Siprob[0] < 0.9) );
    if ( not_recoDIS ) return false;
    fDebug->Fill(1);

    int good_tracks=0;
    for (int i = 0; i<Trk_ntracks; i++) {
        if (Trk_id[i] == Sitrknr[0]) continue;
        if (Trk_prim_vtx[i] != 1) continue;
        good_tracks++;
    }
    if (good_tracks > 2) return false;
    fDebug->Fill(2);

    return true;
}

void    TMiniNtupleCreator::End() {
    //! Here should come steps necessary to properly finish the program
    //! 1. create a file for debug histo, write and close
    fDebugHistoFile->cd();                  // smth of it is redundant
    fDebug->SetDirectory(fDebugHistoFile);  // smth of it is redundant
    fDebug->Write();
    fDebugHistoFile->Close();
    if (fStore_dCache){
        cout << "INFO: copying debug histo file to the dCache" << endl;
        TString     filename(fDebugHistoFile -> GetName());
        TString     command = "dccp -d4 " + filename + " " + fPathToMiniNtuples;
        int result = system (command);
        if (result != 0) {
            cout << "ERROR: copying failed! Terminating! " << endl;
            abort();
        }
        // clean up
        cout << "INFO: removing temporary directory from local space" << endl;
        result = system ("rm -rf " + fPathToMiniNtuplesTEMP);
        if (result != 0) {
            cout << "ERROR: removing failed! Terminating! " << endl;
            abort();
        }
    }
    cout << "\n \t SUCCESSFULLY FINISHED, GOOD BYE\n\n";
}
