//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __THISTOGRAM_H__
#define __THISTOGRAM_H__

#include <vector>
#include <map>

// my includes
#include <TXMLparser.h>
#include <TSubSet.h>

// xerces includes
#include <xercesc/dom/DOM.hpp>

// NOTE: NOT IMPLEMENTED (DECIDED TO JUST USE ROOT HISTOGRAM)

class THistogram : public TXMLparser {

    public:
        THistogram() {};
        THistogram(TString	xml_filename);
        ~THistogram();

    private:
};

#endif



