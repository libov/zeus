#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>


#include <stdexcept>

#include <iostream>

using namespace std;
using namespace xercesc;

int main (int argc, char* args[]) {

        try {
                XMLPlatformUtils::Initialize();
        }
        catch (const XMLException& toCatch) {
                char* message = XMLString::transcode(toCatch.getMessage());
                cout << "Error during initialization! :\n"
                << message << "\n";
                XMLString::release(&message);

        }

        XercesDOMParser* parser = new XercesDOMParser();
        parser->setValidationScheme(XercesDOMParser::Val_Always);
        parser->setDoNamespaces(true);    // optional

        ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
        parser->setErrorHandler(errHandler);

        char* xmlFile = "/data/zenith226a/libov/analysis/db/samples.data.v04.xml";
        //char* xmlFile = "test.xml";

        try {
            parser->parse(xmlFile);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (const DOMException& toCatch) {
            char* message = XMLString::transcode(toCatch.msg);
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (...) {
            cout << "Unexpected Exception \n" ;
            return -1;
        }

        // -------- from the tutorial -------------
        
        // no need to free this pointer - owned by the parent parser object
        DOMDocument* xmlDoc = parser->getDocument();
        // Get the top-level element: NAme is "root". No attributes for "root"
        DOMElement* elementRoot = xmlDoc->getDocumentElement();
        if( !elementRoot ) throw(runtime_error( "empty XML document" ));

        // Parse XML file for tags of interest
        // Look one level nested within "root". (child of root)

        DOMNodeList*      children = elementRoot->getChildNodes();
        const  XMLSize_t nodeCount = children->getLength();
        
        cout << nodeCount << " samples in the file" << endl;
        unsigned nodeCount_corr = 0;

      for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
      {
         DOMNode* currentNode = children->item(xx);
         if( currentNode->getNodeType() &&  // true is not NULL
             currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
         {
            // Found node which is an Element. Re-cast node as element
                nodeCount_corr++;
            DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
            char * tmp = XMLString::transcode(currentElement->getTagName());
            cout << tmp  << endl;
//            tmp = XMLString::transcode(currentNode->getNodeName());   // gives the same as above, fine
	cout << currentNode->getNodeName() << endl;
//          cout << tmp  << endl;     
            //tmp = XMLString::transcode( currentNode -> getNodeName());        // no man, don't use it, because 
                                                                                // currentNode -> getNodeName() gives 0
            DOMNodeList* list = currentNode->getChildNodes();
            for (XMLSize_t j = 0; j<list->getLength(); j++) {
		cout << "j = " << j <<endl;
                DOMNode* anotherNode = list -> item(j);
                if ( anotherNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
                  cout << XMLString::transcode(anotherNode->getNodeName()) << " has the first child with address: "<<endl;
                  cout << anotherNode->getChildNodes()->item(0) ;
                  cout << " " << anotherNode->getFirstChild() ;
		  DOMNode * textNode = anotherNode->getFirstChild() ;
		  cout << " " << textNode <<endl;
		  if (textNode == NULL) continue;
		  if (textNode -> getNodeType()==DOMNode::TEXT_NODE) {
			cout << XMLString::transcode(textNode -> getNodeValue()) << endl;
		  }
		}
            }
            

/*            if( XMLString::equals(currentElement->getTagName(), TAG_ApplicationSettings))
            {
               // Already tested node as type element and of name "ApplicationSettings".
               // Read attributes of element "ApplicationSettings".
               const XMLCh* xmlch_OptionA
                     = currentElement->getAttribute(ATTR_OptionA);
               m_OptionA = XMLString::transcode(xmlch_OptionA);

               const XMLCh* xmlch_OptionB
                     = currentElement->getAttribute(ATTR_OptionB);
               m_OptionB = XMLString::transcode(xmlch_OptionB);

               break;  // Data found. No need to look at other elements in tree.
            }
*/
         }
      }

        cout << "Man, in fact number of samples is: " << nodeCount_corr << endl;

        // ----------------------------------------

        delete parser;
        delete errHandler;

        return 0;
}

