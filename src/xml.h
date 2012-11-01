#include <string>
#include <cstdio.h>
#include <cstdlib.h>
#include <deque>
#include <list>
#include <sstream>

/* STRUCT: Attr (string string)
 * INTENT: Store attributes of a (xml) node in attribute=value pairs
 *      as (attribute, value)
 *
 * ------PARAMETERS------
 * key (string): the key in the attribute-value pairing
 * value (string): the value to be stored
 */
struct Attr {
    std::string key;
    std::string value;
};

/* CLASS: XmlTreeNode
 * INTENT: Store data about a node in an XML tree for parsing or writing
 *
 * ------MEMBER VARIABLES------
 * 
 */
class XmlTreeNode {
    public:
        // CONSTRUCTORS
        /* default */
        XmlTreeNode() { _value = ""; }
        /* main constructor, set a value */
        XmlTreeNode(std::string val) { this->_value = val; }
        /* destructor */
        ~XmlTreeNode() { 
            // delete all of the attributes
            for (std::deque<Attr*>::iterator itr = this->_attributes.begin(); itr != this->_attributes.end(); itr++) {
                delete *itr;
            }
        }
        
        // MUTATORS
        /* FUNCTION: addAttr(std::string, std::string)
         * INTENT: Add an attribute to the current xml node (i.e. 
         *     <node thing="attr">
         *
         * ------PARAMETERS------
         * attribute (std::string): the attribute name (key)
         * value (std::string): the attribute value
         */
        void addAttr(std::string attribute, std::string value) {
            this->_attributes.push_back(new Attr(attribute, value));
        }

        /* FUNCTION: addChild(XmlTreeNode*)
         * INTENT: Add a child node to the current node
         * 
         * ------PARAMETERS------
         * 
         */
        void addChild(XmlTreeNode* node) { this->_children.push_back(node); }

        // String operations
        std::string writeXmlStr() {
            std::stringstream result(std::stringstream::out);
            // write the open bracket and node name
            result << "<" << this->_value;
            // write the attributes
            for (std::deque<Attr*>::iterator itr = this->_attributes.begin(); this->_attributes.end() != itr; itr++) {
                result << " " << itr->key << "=\"" << itr->value << "\"";
            }
            if (this->_children.size() == 0) {
                result << "/>";
            }
            else {
                // write the closing bracket
                result << ">" << std::endl;
                // write the child nodes
                for (std::deque<XmlTreeNode*>::iterator itr = this->_children.begin(); this->children.end() != itr; itr++) {
                    result << (*itr)->writeXmlStr() << std::endl;
                }
                result << "</" << this->_value << ">";
            }
            return result::str;
        }
        
        void readXmlStr(std::string xml) {

        }
       
    private: 
        // member variables
        std::string _value;
        std::deque<Attr*> _attributes;
        std::deque<XmlTreeNode*> _children;
};
