//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
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

using namespace xercesc;

class TXMLparser {

    public:

        TXMLparser(){};
        TXMLparser(TString xml_filename);
        ~TXMLparser(){};

        void            WriteXMLfile(TString file_name);

        DOMDocument*    getDOMDocument() { return fXMLdocument; }

    protected:

        void            OpenFile();     //!< is called from constructor

        TString         fXMLfileName;   //!< name of the XML file

        //@{
        /** underlying Xerces objects to store the structure from an XML file */
        XercesDOMParser *fXMLparser;
        DOMDocument     *fXMLdocument;
        //@}
};
#endif
