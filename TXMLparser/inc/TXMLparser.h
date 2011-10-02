//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TXMLPARSER_H__
#define __TXMLPARSER_H__

// ROOT headers
#include <TString.h>

// XERCES headers
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMDocument.hpp>

class TXMLparser {

    public:
        TXMLparser(){};
        TXMLparser(TString	xml_filename);
        ~TXMLparser();
                
        void        WriteXMLfile(TString file_name);
        void        setVerbose(bool is_verbose){fIsVerbose = is_verbose;};  // NOTE: useless at the moment (is using during constructor of the object)  
                                                                            // hence relies just on the default value
        xercesc::DOMDocument*    getDOMDocument(){return fXMLdocument;};
        
    protected:
        // is called from constructor
        void        OpenFile();
        // XML file name
        TString     fXMLfileName;
        // a flag saying whether messages should be printed or not
        bool        fIsVerbose;
    
        // underlying Xerces objects to store the structure from an XML file
        xercesc::XercesDOMParser	*fXMLparser;
        xercesc::DOMDocument            *fXMLdocument;
};
#endif
