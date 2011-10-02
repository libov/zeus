//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  March 2011                                  //
//                                              //
//////////////////////////////////////////////////

#include<TXMLparser.h>
#include<TCrossSection.h>

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

TCrossSection::TCrossSection(TString xml_file):
TXMLparser(xml_file)
{

        // get root element of it
	DOMElement* elementRoot = fXMLdocument->getDocumentElement();
	if( !elementRoot ) throw(runtime_error( "empty XML document" ));

	// get list of all child nodes of the root element
        DOMNodeList*      children = elementRoot->getElementsByTagName(XMLString::transcode("bin"));

	// loop over all child nodes of the root element, that is sample structure
	for ( unsigned	i = 0; i<children->getLength(); i++ ) {

		// get a child node
		DOMNode* currentNode = children -> item(i);
		if ( ! (currentNode->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;
                
		// check if the node represents "bin" structure
		// this is an element node, hence it's NodeName property equals to it's tag
		if (! XMLString::equals (XMLString::transcode(currentNode->getNodeName()), "bin" )) {
			cout << "ERROR: non-bin tag was found!" << endl;
			abort();
		}

		// create TCrossSectionBin object
		TCrossSectionBin       cCrossSectionBin;

                // get id of this bin;
                // cast DOMElemet so that attribute can be accessed easily
                DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
                // get value of an "id" attribute
                const XMLCh* idAttribute = currentElement->getAttribute(XMLString::transcode("id"));
                // convert to char
                char * idAttribute_c = XMLString::transcode(idAttribute);
                unsigned        id;
                // convert to integer
                sscanf(idAttribute_c, "%d", &id);
                // set this value
                cCrossSectionBin.setID(id);

		// get a list of children of sample tag
		DOMNodeList * sampleChildrenList = currentNode->getChildNodes();

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
			const XMLCh * nodeText = cSampleChildNode->getFirstChild()->getNodeValue();

			// transform to TString
			TString	nodeText_tstr(XMLString::transcode(nodeText));

			// depending on the tag name, store it's text node value to a respective field of TCrossSectionBin
			if ( XMLString::equals (nodeName, "k_uds") ) cCrossSectionBin.set_k_uds(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "k_c") ) cCrossSectionBin.set_k_c(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "k_b") ) cCrossSectionBin.set_k_b(nodeText_tstr.Atof());
			if ( XMLString::equals (nodeName, "k_uds_err") ) cCrossSectionBin.set_k_uds_err(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "k_c_err") ) cCrossSectionBin.set_k_c_err(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "k_b_err") ) cCrossSectionBin.set_k_b_err(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_uds_true") ) cCrossSectionBin.set_sigma_uds_true(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_c_true") ) cCrossSectionBin.set_sigma_c_true(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_b_true") ) cCrossSectionBin.set_sigma_b_true(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_uds") ) cCrossSectionBin.set_sigma_uds(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_c") ) cCrossSectionBin.set_sigma_c(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_b") ) cCrossSectionBin.set_sigma_b(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_uds_err") ) cCrossSectionBin.set_sigma_uds_err(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_c_err") ) cCrossSectionBin.set_sigma_c_err(nodeText_tstr.Atof());
                        if ( XMLString::equals (nodeName, "sigma_b_err") ) cCrossSectionBin.set_sigma_b_err(nodeText_tstr.Atof());
                        
		}

                // also need to read values of bin ranges, so that bin width can be calculated;
                // this is very important for the cross-section calculation, as we divide it by bin width
                // to get a differential cross-section
                // I do it in a separate loop so that things are not getting too messy in the previous one

                // declare a vector that will store bin widths; in this way, any number of bins is allowed
                vector<Float_t> bin_width;

                // loop over "bin" structure to find "subbin"
		for ( unsigned	j = 0; j<sampleChildrenList->getLength(); j++ ) {

			DOMNode* cSampleChildNode = sampleChildrenList -> item(j);

			// again, skip if non-element node
			if ( ! (cSampleChildNode->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;

			// get name of this node
			char * nodeName = XMLString::transcode( cSampleChildNode->getNodeName() );

                        // check that this is "subbin" tag
                        if ( ! XMLString::equals (nodeName, "subbin") ) continue;

                        // get a list of children of this "subbin" tag and loop over them
                        DOMNodeList * cList =  cSampleChildNode->getChildNodes();

                        // helping variables
                        TString         bin_variableName="";
                        Float_t         bin_low_edge=0;
                        Float_t         bin_up_edge=-0;
                        bool            variableName_found = false; 
                        bool            bin_low_edge_found = false; 
                        bool            bin_up_edge_found = false; 

                        // actual loop over "subbin" children
                        for (int k = 0; k < cList->getLength(); k++ ) {
                                // get an element from the list
                                DOMNode * cSubbinChild = cList -> item(k);
                        
                                // check if this is an element node
                                if ( ! (cSubbinChild->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;

                                // get name of this node
                                char * nodeName = XMLString::transcode( cSubbinChild->getNodeName() );

                                // this should be a text node
                                DOMNode * cSubbinChildTextNode =  cSubbinChild->getFirstChild();
                
                                // if it's empty, there will be actually no node, so we have
                                // to check if the pointer is not NULL. Otherwise - continue 
                                // without any actions
                                if (cSubbinChildTextNode == NULL) continue;

                                // now check that it's actually a text node
                                if (cSubbinChildTextNode->getNodeType() != DOMNode::TEXT_NODE) {
                                        cout <<"WARNING: the first child of the node isn't a text node!"<<endl;
                                        continue;
                                }

                                // get content of that text node
                                const XMLCh * SubbinChildnodeText = cSubbinChildTextNode->getNodeValue();

                                // convert to char (in order to convert to TString)
                                const char * SubbinChildnodeText_ch = XMLString::transcode(SubbinChildnodeText);

                                // convert to TString (in order to convert to float. Could use sscanf but that's
                                // not much easier than this way(?))
                                TString SubbinChildnodeText_tstr(SubbinChildnodeText_ch);
                                if ( XMLString::equals (nodeName, "variable") ) {
                                        bin_variableName = SubbinChildnodeText_tstr;
                                        variableName_found = true;
                                } else if ( XMLString::equals (nodeName, "low_edge") ) {
                                        bin_low_edge = SubbinChildnodeText_tstr.Atof();
                                        bin_low_edge_found = true;
                                } else if ( XMLString::equals (nodeName, "up_edge") ) {
                                        bin_up_edge = SubbinChildnodeText_tstr.Atof();
                                        bin_up_edge_found = true;
                                }
                        }

                        // sanity check: both up and low edge valus should be found
                        if ( ! (bin_low_edge_found &&  bin_up_edge_found && variableName_found) ) {
                                cout  << "ERROR in TCrossSection: a subbin tag was found but no bin edge values and/or variable name \n";
                                cout << "won't be able to compute bin width and value of a differential cross-section\n";
                                cout << "Terminating!\n";
                                abort();
                        }
                        
                        // add subbin to TCrossSection object
                        cCrossSectionBin.addSubBin(bin_variableName, bin_low_edge, bin_up_edge);

                        // all fine, compute bin width and push it to a vector
                        Float_t cbin_width = bin_up_edge - bin_low_edge;
                        bin_width.push_back(cbin_width);
		}

                // get the bin width
                // TODO: this is a hardcoded hack; if one needs more flexibility, a public method be added
                Float_t         total_bin_width;
                // single differential cross-section (one subbin) ...
                // double differential cross-sections (two variables)
                // more: not supported
                if (bin_width.size() == 1) {
                    total_bin_width = bin_width[0];
                } else if (bin_width.size() == 2) {
                    total_bin_width = bin_width[1];
                } else {
                    cout << "ERROR: More than two subbins in the bin group. Not supported right now. Terminating!" << endl;
                    abort();
                }

                // set bin width
                cCrossSectionBin.setBinWidth(total_bin_width);

		// finally, push this object to the list
		fBinList.push_back(cCrossSectionBin);

                // See comments in TDataset
                fDOMNodeMap[cCrossSectionBin.getID()] = currentNode;
	}

        linkBinGroupWithBins();
}


unsigned        TCrossSection::getCrossSectionBinIndex(unsigned id){

        // declare some helping variables
        unsigned        bin_index = 0;
        unsigned        bins_found = 0;
        
        // loop over list of bins and check their IDs
        for (unsigned i=0; i<fBinList.size(); i++) {
                if (fBinList[i].getID() == id) {
                        bin_index = i;
                        bins_found++;
                }
        }

	// sanity check
	if ( bins_found == 0 ) { // check whether at least one bin was found
		cout << "ERROR in TCrossSection::getCrossSectionBinIndex("<<id<<"): no bin found! Terminating!"<<endl;
		abort();
	} else if (bins_found>1) { // check that only one bin was found
		cout << "ERROR in  TCrossSection::getCrossSectionBinIndex(...): more than one bin found! Terminating!"<<endl;
		abort();
	} else {	// found exactly one bin
		return bin_index;
	}

}

TCrossSectionBin        TCrossSection::getCrossSectionBin(unsigned id){
        // get index by id
        unsigned        bin_index = getCrossSectionBinIndex(id);

        // return object itself
        return  fBinList[bin_index];
}

void        TCrossSection::modifyCrossSectionBin(unsigned id, TCrossSectionBin bin){

        // get index by id
        unsigned        bin_index = getCrossSectionBinIndex(id);

        // modify actual object in the list
        fBinList[bin_index] = bin;

        // get a local copy
        TCrossSectionBin cBin = fBinList[bin_index];

        // get a DOMNode for it
        DOMNode *cNode = fDOMNodeMap[cBin.getID()];

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

                // if it's empty, there will be actually no node, so we have
                // to check if the pointer is not NULL. 
                // Otherwise - continue create a text Node
                if (cTextNode == NULL) {
                        cTextNode = fXMLdocument->createTextNode(XMLString::transcode(""));
                        cSampleChildNode -> appendChild (cTextNode);
                }

                // now check that it's actually a text node
                if (cTextNode->getNodeType() != DOMNode::TEXT_NODE) {
                        cout <<"WARNING: the first child of the node isn't a text node!"<<endl;
                        continue;
                }

                // float containing text that has to be written to a node
                Float_t         newText_fl;

                // depending on the tag name, different value has to be stored
                if ( XMLString::equals (nodeName, "k_uds") ) newText_fl =cBin.get_k_uds();
                else if ( XMLString::equals (nodeName, "k_c") ) newText_fl =cBin.get_k_c();
                else if ( XMLString::equals (nodeName, "k_b") ) newText_fl =cBin.get_k_b();
                else if ( XMLString::equals (nodeName, "k_uds_err") ) newText_fl =cBin.get_k_uds_err();
                else if ( XMLString::equals (nodeName, "k_c_err") ) newText_fl =cBin.get_k_c_err();
                else if ( XMLString::equals (nodeName, "k_b_err") ) newText_fl =cBin.get_k_b_err();
                else if ( XMLString::equals (nodeName, "sigma_uds_true") ) newText_fl =cBin.get_sigma_uds_true();
                else if ( XMLString::equals (nodeName, "sigma_c_true") ) newText_fl =cBin.get_sigma_c_true();
                else if ( XMLString::equals (nodeName, "sigma_b_true") ) newText_fl =cBin.get_sigma_b_true();
                else if ( XMLString::equals (nodeName, "sigma_uds") ) newText_fl =cBin.get_sigma_uds();
                else if ( XMLString::equals (nodeName, "sigma_c") ) newText_fl =cBin.get_sigma_c();
                else if ( XMLString::equals (nodeName, "sigma_b") ) newText_fl =cBin.get_sigma_b();
                else if ( XMLString::equals (nodeName, "sigma_uds_err") ) newText_fl =cBin.get_sigma_uds_err();
                else if ( XMLString::equals (nodeName, "sigma_c_err") ) newText_fl =cBin.get_sigma_c_err();
                else if ( XMLString::equals (nodeName, "sigma_b_err") ) newText_fl =cBin.get_sigma_b_err();
                else continue;

                stringstream    str;
                str << newText_fl;
                // covert to char
                const char * newText = str.str().c_str();

                // finally, write the text to a node
                cSampleChildNode->getFirstChild()->setNodeValue(XMLString::transcode( newText ));
       }
}

// the purpose of this function is to loop over bin_group objects,
// and get a list of IDs of all bins associated to each of those bin_group

void TCrossSection::linkBinGroupWithBins() {

        // get root element of the document
	DOMElement* elementRoot = fXMLdocument->getDocumentElement();
	if( !elementRoot ) throw(runtime_error( "empty XML document" ));

	// get list of all child nodes of the root element
        DOMNodeList*      binGroupList = elementRoot->getElementsByTagName(XMLString::transcode("bin_group"));

	// loop over all child nodes of the root element, that is sample structure
	for ( unsigned	i = 0; i<binGroupList->getLength(); i++ ) {

		// get a child node
		DOMNode* currentBinGroup = binGroupList -> item(i);
		if ( ! (currentBinGroup->getNodeType() == DOMNode::ELEMENT_NODE) ) continue;

                // sanity check
		if (! XMLString::equals (XMLString::transcode(currentBinGroup->getNodeName()), "bin_group" )) {
			cout << "ERROR: non-bin_group tag was found!!" << endl;
			abort();
		}

                // ok, this is a bin_group element; get name of the group

                // cast DOMElemet so that attribute and children-by-tag-name can be accessed easily
                DOMElement* currentBinGroup_el = dynamic_cast< xercesc::DOMElement* >( currentBinGroup );
                // get title of the gtoup which is an "id" attribute
                const XMLCh* currentBinGroup_el_id = currentBinGroup_el->getAttribute(XMLString::transcode("id"));
                // convert it to TString (via char)
                char * currentBinGroup_el_id_c = XMLString::transcode(currentBinGroup_el_id);
                TString         currentBinGroup_el_id_c_tstr(currentBinGroup_el_id_c);
                
                // just to be sure it does not contain some crap
                fBinIDsMap[currentBinGroup_el_id_c_tstr].clear();

                // get list of bins within this group
	        DOMNodeList*      bins = currentBinGroup_el->getElementsByTagName(XMLString::transcode("bin"));

                for (int j = 0; j < bins->getLength(); j++) {

                        // get an ID of this bin (usual procedure as everywhere above)
                        DOMNode * bin = bins -> item(j);
                        DOMElement * bin_element = dynamic_cast< xercesc::DOMElement* >( bin );
                        const   XMLCh  * bin_id = bin_element -> getAttribute(XMLString::transcode("id"));
                        char  * bin_id_char = XMLString::transcode(bin_id);
                        unsigned        bin_id_int;
                        sscanf(bin_id_char, "%d", &bin_id_int);

                        // add this id to the list of bin-ids of the current bin_group
                        fBinIDsMap[currentBinGroup_el_id_c_tstr].push_back(bin_id_int);
                }
        }
}

void TCrossSection::Print() {
        for (int i = 0; i < fBinList.size(); i++) {
                fBinList[i].Print();
        }
}
