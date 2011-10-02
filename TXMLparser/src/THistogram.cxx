//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                                 //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#include<TXMLparser.h>
#include<THistogram.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>

#include <stdexcept>
#include <iostream>
#include <sstream>
using namespace std;

using namespace xercesc;

THistogram::THistogram(TString xml_file):
TXMLparser(xml_file)
{
    // get root element of it
    DOMElement* elementRoot = fXMLdocument->getDocumentElement();
    if( !elementRoot ) throw(runtime_error( "empty XML document" ));

}

THistogram::~THistogram(){
}
