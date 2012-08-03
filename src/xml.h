#include <string>
#include <cstdio.h>
#include <cstdlib.h>
#include <deque>
#include <list>
#include <sstream>

class Entry {
    
    
    //protected:
    public:
        Entry() {};
        std::string src_path; // path to the item in question
        std::string dest_path; // destination path for the item in question
        std::string name; // name of the item in question
        std::string type; // type of the item (config, package, external_program, source, misc)
        std::string family; // if this is in a family (such as 'git' for 'git-gui'), stores the family of the program; helps associate configs with programs as well
        std::string location; // location in the archive
};

class Program : public Entry {
    public:
        Program() {};
    //private:
        std::deque<Entry*> files; // associated config files
}

std::deque<std::string> parseTags(std::string input) {
    std::deque<std::deque> tags;
    //std::deque<std::string> tag_stack;
    std::list<std::string> tag_stack;
    std::deque<Program*> programs;
    std::sstream instream(input);
    {
        std::string temp;
        Program* prgm;
        /*
        <program type="" src dest family location>
            <config src dest things/>
        </program>
        */
        while (instream >> temp) {
            if (tag_stack.size() == 0) {
                prgm = new Program();
            }
            char out[32];
            char temp2[32];
            if (sscanf(out, "<%s/>", temp)) {
                // a singleton tag
            }
            else if (sscanf(out, "</%s>", temp)) {
                // end tag
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

void writeTags() {

}
