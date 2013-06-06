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
        ~TXMLparser();

        void            WriteXMLfile(TString file_name);
        void            setVerbose(bool is_verbose) { fIsVerbose = is_verbose;} // NOTE: useless at the moment (is used during constructor of the object) hence relies just on the default value

        DOMDocument*    getDOMDocument() { return fXMLdocument; }

    protected:

        void            OpenFile();     //!< is called from constructor
        TString         fXMLfileName;   //!< name of the XML file
        bool            fIsVerbose;     //!< a flag saying whether messages should be printed or not

        //@{
        /** underlying Xerces objects to store the structure from an XML file */
        XercesDOMParser *fXMLparser;
        DOMDocument     *fXMLdocument;
        //@}
};
#endif
