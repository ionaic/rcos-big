#include <iostream>
#include <stdio.h>
//#include <cstdlib.h>
#define MANI_BUFF

class Manifest {
    public:
        void parseManifest() {
            FILE *manifest = fopen("big.manifest", "r");
            if (!manifest) {
                
            }
            else {
                char* temp;
                while(fgets(temp, MANI_BUFF, manifest)) {
                    char entry[128];
                    char option[MANI_BUFF];
                    
                    // attempt to parse line as a comment
                    if (sscanf(temp, "#%s", setting) >= 1) {
                        // comment lines begin with #, simply ignore them
                        continue;
                    }
                    else if (sscanf(temp, "[%s]", entry)) {
                        // new program
                        
                    }
                    else if (sscanf(temp, "%s=%s", setting, option)) {
                        // parse it as a setting
                    }
                } 
            }
        }
 
        void writeManifest(std::deque<Entry> entries) {
            
        }
};
