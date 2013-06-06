//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TDATASET_H__
#define __TDATASET_H__

#include <vector>
#include <map>

// my includes
#include <TXMLparser.h>
#include <TSubSet.h>

// xerces includes
#include <xercesc/dom/DOM.hpp>

class TDataset : public TXMLparser {

    public:

        TDataset() {};
        TDataset(TString xml_filename);
        ~TDataset() {};

        TSubSet     getSubSet(TSubSet::Type, TSubSet::Period p, TSubSet::Flavour f, TSubSet::Q2 q2, TSubSet::Process process, unsigned trigger_period=0);
        TSubSet     getSubSet(TSubSet::Type, TSubSet::Period p);
        void        modifySubSet(TSubSet::Type t, TSubSet::Period p, TSubSet::Flavour f, TSubSet::Q2 q2,  TSubSet::Process process, TSubSet new_set, unsigned trigger_period=0);

        // returns number of samples in the current structure (i.e. in the XML file)
        unsigned    getNSamples() {return fSampleList.size();};

        // returns sample with index i TODO: add sanity check: an argument should not be greater than size of the vector
        TSubSet     getSubSet_byIndex(unsigned i) {return fSampleList[i];};

        void        Print();

    private:
        std::vector<TSubSet>                           fSampleList;
        std::map<unsigned, xercesc::DOMNode*>          fDOMNodeMap;
};

#endif
