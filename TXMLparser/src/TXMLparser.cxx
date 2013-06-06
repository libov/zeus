//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#include<TXMLparser.h>
#include <TString.h>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMWriter.hpp>

#include <stdexcept>

#include <iostream>

using namespace std;
using namespace xercesc;

TXMLparser::TXMLparser(TString xml_filename):
fXMLfileName(xml_filename)
{

    // initialize xerces
    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"<< message << "\n";
        XMLString::release(&message);
        abort();
    }

    // initialize xerces DOM parser
    fXMLparser = new XercesDOMParser();

    fXMLparser->setValidationScheme(XercesDOMParser::Val_Always);
    fXMLparser->setDoNamespaces(true);    // optional

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    fXMLparser->setErrorHandler(errHandler);

    // now open the file
    OpenFile();
}

void    TXMLparser::OpenFile() {

    // get path to the XML file
    TString XMLfilePath = getenv("DATABASE_PATH");
    XMLfilePath += "/" + fXMLfileName;

    // parse the XML file!
    cout << "INFO: Opening " <<XMLfilePath << endl;
    try {
        fXMLparser->parse(XMLfilePath.Data());
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        abort();
    } catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        abort();
    } catch (...) {
        cout << "ERROR: Cannot open file: " << XMLfilePath << "\n Unexpected Exception... \n" ;
        abort();
    }

    // get current XML document
    fXMLdocument = fXMLparser -> getDocument();
}

void TXMLparser::WriteXMLfile(TString file_name) {

    // DOMImplementationLS contains factory methods for creating objects
    // that implement the DOMBuilder and the DOMWriter interfaces
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);

    // construct the DOMBuilder
    DOMBuilder* myParser = ((DOMImplementationLS*)impl) -> createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

    // construct the DOMWriter
    DOMWriter* myWriter = ((DOMImplementationLS*)impl)->createDOMWriter();

    XMLFormatTarget *myFormTarget;
    // get path to the XML file
    TString	XMLfilePath = getenv("DATABASE_PATH");
    XMLfilePath += "/" + file_name;
    // set it
    myFormTarget = new LocalFileFormatTarget(XMLfilePath.Data());
    // write to file!
    cout << "INFO: Writing data to " << XMLfilePath << endl;
    myWriter -> writeNode(myFormTarget, *fXMLdocument);
}
