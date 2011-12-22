//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                             //
//  libov@mail.desy.de                          //
//  January 2010                                //
//                                              //
//////////////////////////////////////////////////

#ifndef __TMININTUPLECREATOR_H__
#define __TMININTUPLECREATOR_H__
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h>
#include <TList.h>
#include <TFile.h>
#include <inc/TNtupleAnalyzer.h>

#include <vector>
using namespace std;

//! Class for mini ntuples creation
/*! Inherited from TMiniNtupleAnalyzer
*/

class    TMiniNtupleCreator : public TNtupleAnalyzer
{
    public:
        TMiniNtupleCreator();
        ~TMiniNtupleCreator() {};

        //! Main function.
        /*! Loops over events and writes output to root mini ntuple.
        *    \param firstEvent an integer specifying first event to be processed
        *    \param lastEvent an integer specifying last event to be processed
        */
        void        CreateMiniNtuples(Int_t    firstEvent, Int_t    lastEvent);
        void        Initialize();                       //<! initialisator the class
        void        SetPathToMiniNtuplesTEMP (TString path) {fPathToMiniNtuplesTEMP = path;};
        void        SetStore_dCache (bool store_dcache) {fStore_dCache = store_dcache;};

    private:

        TFile*      fCurrentTreeFile;                   //<! Pointer to file that contains current tree
        Int_t       fCurrentFileNumber;
        Int_t       fCurrentNumberEventsInFile;
        Bool_t      fCreateFile;
        TFile       *fDebugHistoFile;
        bool        fStore_dCache;                      //<! tells whether the output directory is on dCache
        TString     fPathToMiniNtuplesTEMP;             //<! if selected to store minintuples to the dCache,
                                                        //<! write them first locally to this location and
                                                        //<! then move do dCache space
    
        void        CreateFile(Int_t    currentEvent);  //<! creates file object pointed by fCurrentTreeFile
        void        CreateTree();
        void        WriteFile();
        Bool_t      IsGoodEvent();
        Bool_t      IsGoodRhoEvent();
        void        End();
};
#endif
