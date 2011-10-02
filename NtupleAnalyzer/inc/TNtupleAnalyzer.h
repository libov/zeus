//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//  last modified: July 2011                    //
//////////////////////////////////////////////////

#ifndef __TNTUPLEANALYZER_H__
#define __TNTUPLEANALYZER_H__

// ROOT includes
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h>
#include <TList.h>

// my includes
#include <TSubSet.h>
#include <TDataset.h>
#include <inc/BaseClass.h>

/** \brief Base class for TMiniNtupleCreator and TMiniNtupleAnalyzer. 
 * 
 * Implements functionality which is common for both cases: analysis (both on dCache and minintuples) and creation of minintuples.
 */
class	TNtupleAnalyzer : public BaseClass
{
    public:
        TNtupleAnalyzer();
        ~TNtupleAnalyzer() {};

        void        Init();                     //!< initializes the class. Should be done AFTER all the settings have been done. Common for analyzer and creator. Should be called by analyzer or creator before any other actions.

        void        CalculateNumberOfEvents();  //!< Calculates number of entries in an underlying chain and sets #fNevents variable
        Int_t       GetNumberOfEvents();        //!< Returns value of #fNevents variable
        void        SetTestMode (Bool_t	mode);  //!< Enables or disables a test mode (see #fTestMode)
        void        SetTestNumberOfEvents (Int_t TestNumberOfEvents);   //!< Sets number of events to be processed in a test mode (see #fTestNumberOfEvents)

        /** @name 
         * The following methods are used to set properties (identify) of the sample to be analyzed.
         */
        //@{
        /**\brief Sets type of the sample (data or MC)*/
        void        setType(TSubSet::Type type) {fSubSet.setTypeENUM(type);};

        /**\brief Sets flavour of the sample (MC only). Implemented are: beauty, charm and light flavors*/
        void        setFlavour(TSubSet::Flavour flav) {fSubSet.setFlavourENUM(flav);};

        /**\brief Sets run period of the sample. Implemented are: 0304p, 05e, 06e, 0607p*/
        void        setPeriod(TSubSet::Period period) {fSubSet.setPeriodENUM(period);};

        /**\brief Sets Q2 of the sample (MC only).*/
        void        setQ2(TSubSet::Q2 q2) {fSubSet.setQ2ENUM(q2);};

        /**\brief Sets Process type (BGF/RESOLVED) of the sample (MC only).*/
        void        setProcess(TSubSet::Process process) {fSubSet.setProcessENUM(process);};

        /**\brief Sets trigger subperiod of the sample. Important for 0304p run period*/
        void        setTriggerPeriod(unsigned trigger_period) {fSubSet.setTriggerPeriod(trigger_period);};
        //@}

        void        getSubSet(); //!< gets subset from an XML file (which is unique for each CN version and is created manually)

        void        CheckIfMC();    //!< Checks whether this sample is data or MC based on #fSubSet and sets #fIsMC flag accordingly

        /** \brief  Sets name of the file (#fFileList) containing list of files to be processed (default is constructed from the sample name).
         */
        void        setFileListName(TString filename) { fFileList=filename;};

        /** \brief  adds ROOT files from dCache to a chain (BaseClass::fChain). If #fFileList was explicitly (with #setFileListName), the list is taken from this file. Otherwise, a default file is used, namely #fSampleName .txt. The method loops over lines of the selected file and adds each to the chain.
         */
        void        AddFilesToChain();

        void        getSampleName();    //!< constructs sample name (#fSampleName) based on its properties

        void        SetPathToMiniNtuples(TString path) {fPathToMiniNtuples = path;}; //!< sets path to Mini Ntuples. In case of creator - this will be the destination of files; in case of analyzer - this will be the source of the files (if not selected to run on dCache)
        void            SetMiniNtuplesOn_dCache(bool on_cache) {fMiniNtuplesOn_dCache = on_cache;};
    
    protected:

        TDataset    fDataset;           //!< keeps the whole TDataset structure
        TSubSet     fSubSet;            //!< TSubSet object which keeps information about the sample and enables modifications to an XML database

        TString     fSampleName;        //!< Name of sample to be processed. It is constructed based on the information about the sample
        Int_t       fNevents;           //!< Number of events in the current chain
        TH1F        *fDebug;            //!< A pointer to the debug histogram which indicates effect of different cuts
        TString     fPathToMiniNtuples; //!< Specifies location where MiniNtuples are stored. Not needed when selected to run on dCache

        Bool_t      fTestMode;          //!< Test mode means not to run over the full sample, but only process specified event range.
        Int_t       fTestNumberOfEvents;//!< Relevant for the test mode. Specifies number of events to be processed.

        TString     fFileList;          //!< Name of the file with the list of root files to be processed. By default it's constructed from the sample name (plus "txt" extension), but can be optionally selected to have arbitrary value.
        bool        fMiniNtuplesOn_dCache;
};
#endif
