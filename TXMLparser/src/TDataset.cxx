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
#include<TDataset.h>

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

// this constructor loops over the content of the XML file
// and creates a structure keeping all the information available.
// this burns down to a vector containing all the samples that are
// listed in the file
TDataset::TDataset(TString xml_file):
TXMLparser(xml_file)
{
    // get root element of it
    DOMElement* elementRoot = fXMLdocument -> getDocumentElement();
    if( !elementRoot ) throw(runtime_error( "empty XML document" ));

    // get list of all child nodes of the root element
    DOMNodeList*      children = elementRoot->getChildNodes();

    // introduce variable to count and mark samples
    unsigned        SubSetCounter=0;
        
    // loop over all child nodes of the root element, i.e. loop over all samples
    for ( unsigned i = 0; i < children->getLength(); i++ ) {

        // get a child node
        DOMNode* sampleNode = children -> item(i);
        if ( ! (sampleNode->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;
                
        // check if the node represents "sample" structure
        // this is an element node, hence it's NodeName property equals to it's tag
        if (! XMLString::equals (XMLString::transcode(sampleNode->getNodeName()), "sample" )) {
            cout << "ERROR: non-sample tag was found among direct children of a root element!" << endl;
            abort();
            continue;
        }

        // create TSubSet object
        TSubSet cSubSet;

        // get a list of children of sample structure
        DOMNodeList * sampleChildrenList = sampleNode->getChildNodes();

        //loop over them
        for ( unsigned	j = 0; j<sampleChildrenList->getLength(); j++ ) {

            DOMNode* cSampleChildNode = sampleChildrenList -> item(j);

            // again, skip if non-element node
            if ( ! (cSampleChildNode->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;

            // get name of this node
            char * nodeName = XMLString::transcode( cSampleChildNode->getNodeName() );
        
            // get first child of the child element of sample.
            // this should be a text node containing value of that tag.
            DOMNode * cTextNode =  cSampleChildNode->getFirstChild();

            // if it's empty, there will be actually no node, so we have
            // to check if the pointer is not NULL. Otherwise - continue 
            // without any actions
            if (cTextNode == NULL) continue;

            // now check that it's actually a text node
            if (cTextNode->getNodeType() != DOMNode::TEXT_NODE) {
                cout <<"WARNING: the first child of the node isn't a text node!"<<endl;
                continue;
            }

            // get content of that text node
            const XMLCh * nodeText = cTextNode->getNodeValue();

            // transform to TString
            TString	nodeText_tstr(XMLString::transcode(nodeText));

            // depending on the tag name, store it's text node value to a respective field of TSubSet
            if ( XMLString::equals (nodeName, "year") ) cSubSet.setYear(nodeText_tstr);
            if ( XMLString::equals (nodeName, "type") ) cSubSet.setType(nodeText_tstr);
            if ( XMLString::equals (nodeName, "flavour") ) cSubSet.setFlavour(nodeText_tstr);
            if ( XMLString::equals (nodeName, "q2") ) cSubSet.setQ2(nodeText_tstr);
            if ( XMLString::equals (nodeName, "CN_version") ) cSubSet.setCNversion(nodeText_tstr);
            if ( XMLString::equals (nodeName, "name_pattern") ) cSubSet.setNamePattern(nodeText_tstr);
            if ( XMLString::equals (nodeName, "trigger_period") ) cSubSet.setTriggerPeriod(nodeText_tstr.Atoi());
            if ( XMLString::equals (nodeName, "luminosity") ) cSubSet.setLuminosity(nodeText_tstr.Atof());
            if ( XMLString::equals (nodeName, "luminosity_recalculated") ) cSubSet.setLuminosityRecalculated(nodeText_tstr.Atof());
        }

        // now "classify" this sample, i.e. define variables for random access from xml-file data
        cSubSet.Classify();

        // define name of the sample
        cSubSet.defineSampleName();

        // now mark this SubSet
        cSubSet.setID(SubSetCounter);

        // and increment the counter
        SubSetCounter++;

        // finally, push this object to the list
        fSampleList.push_back(cSubSet);

        // Link the subset and it's node; needed for a possible modification of the SubSet in the XML file;
        // using associative map for this; there are other ways to do it,
        // like implement pointer to DOMNode object as a member of TSubSet,
        // but decided to do this linking at this level, so that TSubSet is
        // separated and independent of XML machinery. Might be revisited.
        fDOMNodeMap[cSubSet.getID()] = sampleNode;
    }

    // sanity check: size of the array should be the same as the value of the counter
    if (SubSetCounter != fSampleList.size()) {
        cout << "ERROR in TDataset::TDataset(...): size of the vector isn't equal to sample counter.! Terminating!\n";
        abort();
    }
}

// this function gets a sample from the list by it's type, period, flavour, Q2 and trigger period
// only for MC!! data analogue is in the next function
TSubSet TDataset::getSubSet(TSubSet::Type t, TSubSet::Period p, TSubSet::Flavour f, TSubSet::Q2 q2, TSubSet::Process process, unsigned trigger_period) {

    // book some helping variables
    unsigned    samples_found = 0;
    unsigned    sample_index=0;

    // loop over all samples to find a correct one
    for (int i = 0; i< fSampleList.size(); i++) {
        TSubSet cSubSet = fSampleList[i];
        bool    typeOK = (cSubSet.getTypeENUM() == t);
        bool    periodOK = (cSubSet.getPeriodENUM() == p);
        bool    flavourOK = (cSubSet.getFlavourENUM() == f);
        bool    q2OK = (cSubSet.getQ2ENUM() == q2);
        bool    processOK = (cSubSet.getProcessENUM() == process);
        bool    triggerOK = (trigger_period == 0) ? true : (cSubSet.getTriggerPeriod() == trigger_period);
        if (  typeOK && periodOK && flavourOK && q2OK && processOK && triggerOK) {
            sample_index = i;
            samples_found++;
        }
    }

    // sanity check
    if (samples_found == 0) { // check whether at least one was found
        cout << "ERROR from TDataset::getSubSet(...): no sample found! Terminating!"<<endl;
        abort();
    } else if (samples_found>1) { // check that only one sample was found
        cout << "ERROR from TDataset::getSubSet(...): more than one sample found! Terminating!"<<endl;
        abort();
    } else {    // found exactly one sample, ok!
        return fSampleList[sample_index];
    }
}

// for DATA
TSubSet	TDataset::getSubSet(TSubSet::Type t, TSubSet::Period p) {

    // book some helping variables
    unsigned    samples_found = 0;
    unsigned    sample_index=0;

    // loop over all samples to find a correct one
    for (int i = 0; i< fSampleList.size(); i++) {
        TSubSet cSubSet = fSampleList[i];
        bool    typeOK = (cSubSet.getTypeENUM() == t);
        bool    periodOK = (cSubSet.getPeriodENUM() == p);
        if (  typeOK && periodOK ) {
            sample_index = i;
            samples_found++;
        }
    }

    // sanity check
    if (samples_found==0) { // check whether at least one was found
        cout << "ERROR in TDataset::getSubSet(...): no sample found! Terminating!"<<endl;
        abort();
    } else if (samples_found>1) {   // check that only one sample was found
        cout << "ERROR in TDataset::getSubSet(...): more than one sample found! Terminating!"<<endl;
        abort();
    } else {    // found exactly one sample
        return fSampleList[sample_index];
    }
}

// NOTE: the code is just duplicated from TDataset::getSubSet
// to be improved
void	TDataset::modifySubSet(TSubSet::Type t, TSubSet::Period p, TSubSet::Flavour f, TSubSet::Q2 q2, TSubSet::Process process, TSubSet new_set, unsigned trigger_period) {

    // book some helping variables
    unsigned    samples_found = 0;
    unsigned    sample_index=0;

    // loop over all samples to find a correct one
    for (int i = 0; i< fSampleList.size(); i++) {
        TSubSet	cSubSet = fSampleList[i];
        bool    typeOK = (cSubSet.getTypeENUM() == t);
        bool    periodOK = (cSubSet.getPeriodENUM() == p);
        bool    flavourOK = (cSubSet.getFlavourENUM() == f);
        bool    q2OK = (cSubSet.getQ2ENUM() == q2);
        bool    processOK = (cSubSet.getProcessENUM() == process);
        bool    triggerOK = (trigger_period == 0) ? true : (cSubSet.getTriggerPeriod() == trigger_period);
        if (  typeOK && periodOK && flavourOK && q2OK && processOK && triggerOK) {
            sample_index = i;
            samples_found++;
        }
    }

    // sanity check
    if (samples_found==0) { // check whether at least one was found
        cout << "ERROR in TSubSet::modifySubSet(...): no sample found! Terminating!"<<endl;
        abort();
    } else if (samples_found>1) { // check that only one sample was found
        cout << "ERROR in TSubSet::modifySubSet(...): more than one sample found! Terminating!"<<endl;
        abort();
    }
        
    // sanity check: IDs of both samples should be the same. This is to avoid the situation
    // when subset is overwritten by accident with another one that has a different ID, and hence
    // will spoil DOMNode -> SubSet link
    if (fSampleList[sample_index].getID() != new_set.getID()) {
        cout << "ERROR in TDataset::modifySubSet(): ID of two SubSets are not equal!! Terminating!\n";
        abort();
    }

    // now overwrite the sample; uses operator= as implemented in TSubSet
    fSampleList[sample_index] = new_set;
        
    // get a local copy
    TSubSet cSubSet = fSampleList[sample_index];

    // get a DOMNode for it
    DOMNode *cNode = fDOMNodeMap[cSubSet.getID()];

    // now modify the node accordingly
    // NOTE: CODE DUPLICATION FROM TDataset::TDataset(...)!!! TO BE IMPROVED!!!

    // get a list of children of it
    DOMNodeList * sampleChildrenList = cNode->getChildNodes();

    //loop over them
    for ( unsigned	j = 0; j<sampleChildrenList->getLength(); j++ ) {

        DOMNode* cSampleChildNode = sampleChildrenList -> item(j);

        // again, skip if non-element node
        if ( ! (cSampleChildNode->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;

        // get name of this node
        char * nodeName = XMLString::transcode( cSampleChildNode->getNodeName() );

        // get first child of the child element of sample.
        // this should be a text node containing value of that tag.
        DOMNode * cTextNode =  cSampleChildNode->getFirstChild();

        // TODO: review this stuff, in particular, empty/non-empty text nodes
        // if it's empty, there will be actually no node, so we have
        // to check if the pointer is not NULL. Otherwise - continue 
        // without any actions
/*      if (cTextNode == NULL) continue;

        // now check that it's actually a text node
        if (cTextNode->getNodeType() != DOMNode::TEXT_NODE) {
        cout <<"WARNING: the first child of the node isn't a text node!"<<endl;
        continue;
        }*/

        // char pointing to text that has to be written to a node
        const char *newText;
        stringstream str1;
        stringstream str2;
        stringstream str3;
        if ( XMLString::equals (nodeName, "year") ) newText = cSubSet.getYear().Data();
        if ( XMLString::equals (nodeName, "type") ) newText = cSubSet.getType().Data();
        if ( XMLString::equals (nodeName, "flavour") ) newText = cSubSet.getFlavour().Data();
        if ( XMLString::equals (nodeName, "q2") ) newText = cSubSet.getQ2().Data();
        if ( XMLString::equals (nodeName, "CN_version") ) newText = cSubSet.getCNversion().Data();
        if ( XMLString::equals (nodeName, "name_pattern") ) newText = cSubSet.getNamePattern().Data();
        if ( XMLString::equals (nodeName, "trigger_period") ) {
            // this is unsigned; convert to char first
            str3 << cSubSet.getTriggerPeriod();
            newText = str3.str().c_str();
        }
        if ( XMLString::equals (nodeName, "luminosity") ) {
            // this is float; convert to char first
            str1 << cSubSet.getLuminosity();
            newText = str1.str().c_str();
        }
        if ( XMLString::equals (nodeName, "luminosity_recalculated") ) {
            // this is float; convert to char first
            str2 << cSubSet.getLuminosityRecalculated();
            newText = str2.str().c_str();
        }
        // finally, write the text to a node
        cSampleChildNode->getFirstChild()->setNodeValue(XMLString::transcode( newText ));
    }
}

// function prints infomation about all the samples
void TDataset::Print(){
    // loop over sample list and print put each of them
    for (int i = 0; i < fSampleList.size(); i++){
        TSubSet cSubSet = fSampleList[i];
        cout << "*** Sample " << i << " ***"<<endl;
        cSubSet.Print();
        cout << endl;
    }
}
