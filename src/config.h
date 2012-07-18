#include <fstream>
#include <iostream>
#include <string>
#include <deque>

#define CONF_BUFF 16

// read in and store in a usable way the configuration from the config file(s)
class Configuration {
    public:
        Configuration() {}
            Configuration() {
                //std::string temp;
                char* temp;
                std::deque<std::string> options;
                FILE* conf = fopen("big.conf", "r");
                while (fgets(temp, CONF_BUFF, conf)) {
                    char setting[128];
                    char option[CONF_BUFF];
                    // if (sscanf(temp, "%s\n", setting) < 1) #define CONF_BUFF 2*CONF_BUFF
                    
                    // attempt to parse line as a comment
                    if (sscanf(temp, "#%s", setting) >= 1) {
                        // comment lines begin with #, simply ignore them
                        continue;
                    }
                    else if (sscanf(temp, "%s=%s", setting, option)) {
                        // parse a normal setting
                        char* include;
                        std::deque<std::string> temp;
                        if (strcmp(setting, "include-packages") == 0) {
                            parse_to_deque(temp, option);
                            num_incl = temp.size();
                            includes = new char*[num_incl];
                            for (int i = 0; i < num_incl; i++) {
                                includes[i] = temp[i];
                            }
                        }
                        else if (strcmp(setting, "exclude-packages") == 0) {
                            parse_to_deque(temp, option);
                            num_excl = temp.size();
                            excludes = new char*[num_excl];
                            for (int i = 0; i < num_excl; i++) {
                                excludes[i] = temp[i];
                            }
                        }
                        // else if (strcmp(setting, "") == 0) {

                        // }
                    }
                    else {
                        // attempt to parse it as un-grabbed remainder of the last setting
                        // if it fails, give an error of bad config file, could not recover
                    }
                }

                // failed attempt with STL streams
                // while (in >> temp) {
                //     std::cout << "Temp: " << temp;
                //     // parse the string temp
                //     {
                //         char setting[128];
                //         char option[128]

                //         // parse comments
                //         if (sscanf(temp.c_str(), "# %s", setting) >= 1) {
                //             // comment lines begin with #, ignore them
                //             continue;
                //         }

                //         // parse settings
                //         else if (sscanf(temp.c_str(), "%s=%s", setting, option)) {
                //             // associate setting with option
                //         }
                //         
                //         // attempt to parse as extended setting (e.g. option=thing1 thing2 thing3)
                //         else {
                //             // associate option with last changed setting
                //         }
                //         
                //         
                //     }
                //     // char* parse_temp;
                //     // if (sscanf(parse_temp, "apt%s", temp.c_str())) {
                //     //     
                //     // }
                // }
            }
    private:
        void parse_to_deque(std::deque<std::string> &packages, std::string option) {
            // make a new string stream and set option as the string
            std::stringstream parser;
            parser.str(option);
            
            // read out of the stringstream into temp variable, packages separated by a space
            std::string temp;
            while (parser >> temp) {
                packages.push_back(temp);
            }
        }

        int num_excl, num_incl;
        char** excludes, includes;
};
