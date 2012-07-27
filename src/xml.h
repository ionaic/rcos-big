#include <string>
#include <cstdio.h>
#include <cstdlib.h>
#include <deque>
#include <sstream>

class Entry {
    
    
    private:
        std::string src_path; // path to the item in question
        std::string dest_path; // destination path for the item in question
        std::string name; // name of the item in question
        std::string type; // type of the item (config, package, external_program, source, misc)
        std::string family; // if this is in a family (such as 'git' for 'git-gui'), stores the family of the program; helps associate configs with programs as well
        std::string location; // location in the archive
};

std::deque<std::string> parseTags(std::string input) {
    std::deque<std::deque> tags;
    std::deque<std::string> tag_stack;
    std::sstream instream(input);
    {
        std::string temp;
        while (instream >> temp) {
            char out[32];
            // sscanf(out, "<%s>", temp);
            // if (out[0] == '/') {
            //     // closing tag
            // }
            char temp2[32];
            if (sscanf(out, "<%s/>", temp)) {
                // a singleton tag
            }
            // how to handle singleton tags?
            // else if (sscanf(temp2, "%s/", out) == 0) {
            //     // singleton tag
            // }
            else if (sscanf(out, "</%s>", temp)) {

            }
            else if (sscanf(out, "<%s>", temp)) {
                // start tag
            }
            else {
                // random content such as <tag>thing</tag>
            }
        }
    }
    return tags;
}

//std::string makeTag(

// class XMLTreeNode {
//     public:
//         void addChild(XMLTreeNode* child) {
//             _children.push_back(child);
//         }
//     private:
//         std::deque<XMLTreeNode*> _children;
//         std::string tag;
//         void* value;
// };
// 
// class XMLTree {
//     private: 
//       XMLTreeNode _root;
// };
