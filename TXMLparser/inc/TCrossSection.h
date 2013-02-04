//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TCROSSSECTION_H__
#define __TCROSSSECTION_H__

// ROOT includes
#include <TString.h>

// my includes
#include <TCrossSectionBin.h>
#include <TXMLparser.h>

// xerces includes
#include <xercesc/dom/DOM.hpp>

#include <map>

class TCrossSection : public TXMLparser  {

    public:

        TCrossSection(TString xml_filename);
        ~TCrossSection(){};

        TCrossSectionBin        getCrossSectionBin(unsigned id);
        unsigned                getCrossSectionBinIndex(unsigned id);
        TCrossSectionBin        getCrossSectionBinbyIndex(unsigned id) {return fBinList[id];};// TODO: CHECK THAT ID IS NOT GREATER THAN SIZE OF THE VECTOR!!!!
        void                    modifyCrossSectionBin(unsigned id, TCrossSectionBin bin);

        unsigned                getNBins() { return fBinList.size(); };

        void                    linkBinGroupWithBins();

        unsigned                getNBinGroups(){return fBinIDsMap.size();}
        // NOTE:
        // 1. here one has to check that group_index is not greater than map size!!!
        // 2. is it ok to return vector??
        std::map<TString, std::vector<unsigned> >         getBinIDsMap() {return fBinIDsMap;}

        void                    Print();

    private:

        std::vector<TCrossSectionBin>                  fBinList;
        std::map<unsigned, xercesc::DOMNode*>          fDOMNodeMap;

        // the following is to handle groups of bins selected by tag <bin_group>
        // NOTE: terrible naming here...
        // this is to give a link between a group id and a vector of CrossSectionBin 's (via their ids)
        std::map<TString, std::vector<unsigned> >      fBinIDsMap;
};

#endif
