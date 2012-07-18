#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_
#include <stdlib.h>
#include <iostream>
#include <string>
#include "big.h"

#define NUM_FLAGS 15
#define h_flag 0 // help
#define c_flag 1 // include config
#define x_flag 2 // exclude config
#define p_flag 3 // include package
#define e_flag 4 // exclude package
#define offline_flag 5 // store locally
#define s_flag 6 // set temporarily
#define f_flag 7 // find configs
#define findprog_flag 8 // find programs not in package manager
#define l_flag 9 // add to latest
#define u_flag 10 // update specified archive
#define noconf_flag 11 // store no configs
#define nopack_flag 12 // store no packages
#define v_flag 13 // verbose
#define silent_flag 14 // run silent

// parse the arguments for the program
class Args {
    public:
        // constructors
        //Args() {}
        //Args(int argc, char** argv) {
        //    parseArgs(argc, argv);
        //}

        static int parseArgs(int argc, char** argv) {
            #define is_f(arg) (arg[0] == '-')
            int i = 2;

            // test what mode, storing, unpacking, setting or other
            //if (argv[1] == "bang") {
            if (!std::string(argv[1]).compare("bang")) {
                // unpacking/installing/script creation
                //sscanf();
                _mode = 1;
                if (i < argc) {
                    if (!is_f(argv[i])) {
                        if (Args::verbose()) { std::cerr << "No archive location given, using location from config." << std::endl; }
                        
                    }
                }
            }
            //else if (argv[1] == "crunch") {
            else if (!std::string(argv[1]).compare("crunch")) {
                // storing/archive creation
                _mode = 2;
            }
            //else if (argv[1] == "set") {
            else if (!std::string(argv[1]).compare("set")) {
                // store setting to config file
                _mode = 3;
                for (; i < argc; ++i) {
                    if (is_f(argv[i])) {
                        --i;
                        break;
                    }
                }
            }
            else {
                //big_DBG("argv[0] = %s", argv[0]);
                std::cout << "argv[1] = " << argv[1] << std::endl;
                _mode = 0;
            }
            #define f1(a) (argv[i] == a)
            #define f2(a,b) (argv[i] == a || argv[i] == b)
            #define tru(flag) (Args::_flags[flag] = 1)
            #define fal(flag) (_flags[flag] = 0)
            for (; i < argc; ++i) {
                //if (argv[i] == "-h" || argv[i] == "--help") {
                if (f2("-h", "--help")) {
                    // help text
                    //_flags[h_flag] = 1; 
                    tru(h_flag);
                }
                //else if (argv[i] == "--offline") {
                else if (f1("--offline")) {
                    // offline mode
                    //flags[offline_flag] = 1;
                    tru(offline_flag);
                }
                //else if (argv[i] == "-c" || argv[i] == "--include-config") {
                else if (f2("-c", "--include-config")) {
                    // include specified config file
                    tru(c_flag);
                    for (; i < argc; ++i) {
                        //if (argv[i][0] == '-') {
                        if (is_f(argv[i])) {
                            --i; break; } _i_config.push_back(argv[i]);
                    }
                }
                //else if (argv[i] == "-x" || argv[i] == "--exclude-config") {
                else if (f2("-x", "--exclude-config")) {
                    // exclude specified config file
                    tru(x_flag);
                    for (; i < argc; ++i) {
                        if (is_f(argv[i])) {
                            --i;
                            break;
                        }
                        _e_config.push_back(argv[i]);
                    }
                }
                else if (f2("-p", "--include--package")) {
                    // include specified packages
                    tru(p_flag);
                    for (; i < argc; ++i) {
                        if (is_f(argv[i])) {
                            --i;
                            break;
                        }
                        _i_packages.push_back(argv[i]);
                    }
                }
                else if (f2("-e", "--exclude-package")) {
                    // exclude specified packages
                    tru(e_flag);
                    for (; i < argc; ++i) {
                        if (is_f(argv[i])) {
                            --i;
                            break;
                        }
                        _e_packages.push_back(argv[i]);
                    }
                }
                else if (f2("-s", "--set")) {
                    // set temporarily
                    tru(s_flag);
                    for (; i < argc; ++i) {
                        //if (argv[i][0] == '-') {
                        if (is_f(argv[i])) {
                            --i;
                            break;
                        }
                        _temp_set.push_back(argv[i]);
                    }
                }
                else if (f2("-f", "--find-config")) {
                    // find configs
                    
                    // if there is a next argument, grab it
                    if (i < argc - 1) ++i;
                    else continue;
                    // set it as true 
                    if (argv[i] == "false") fal(f_flag);
                    else tru(f_flag);
                    
                }
                else if (f1("--find-programs")) {
                    // find programs

                    // if there is a next argument, grab it
                    if (i < argc - 1) ++i;
                    else continue;
                    // set it as true 
                    if (argv[i] == "false") fal(findprog_flag);
                    else tru(findprog_flag);
                }
                else if (f2("-l", "--latest")) {
                    // update latest
                    tru(l_flag);
                }
                else if (f2("-u", "--update")) {
                    // update specified
                    tru(u_flag);
                }
                else if (f1("--no-config")) {
                    // store no configs except those on command line
                    tru(noconf_flag);
                }
                else if (f1("--no-packages")) {
                    // store no packages locally
                    tru(nopack_flag);
                }
                else if (f2("-v", "--verbose")) {
                    // verbose output
                    tru(v_flag);
                }
                else if (f1("--silent")) {
                    // run silently (no output)
                    tru(silent_flag);
                }
                else {
                    //if (Args::verbose()) std::cerr << "Ignoring unsupported flag: " << argv << std::endl << "\t Use the -h or --help flags for usage." << std::endl;
                    std::cerr << "Ignoring unsupported flag: " << argv << std::endl << "\t Use the -h or --help flags for usage." << std::endl;
                }
            } 
            #undef f1
            #undef f2
            #undef tru
            #undef fal
            #undef is_f
        }
 
        #define flag(x) _flags[x]
        // public getters and setters
        static const int mode() { return _mode; }
        static const std::deque<char*> incl_pkgs() { return _i_packages; }
        static std::deque<char*> excl_pkgs() { return _e_packages; }
        static std::deque<char*> incl_confs() { return _i_config; }
        static std::deque<char*> excl_confs() { return _e_config; }
        static std::deque<char*> temp_settings() { return _temp_set; }
        static std::deque<char*> write_settings() { return _write_set; }
        
        // to test individual flags
        static bool help() { return flag(h_flag); }
        static bool i_confs() { return flag(c_flag); }
        static bool e_confs() { return flag(x_flag); }
        static bool i_pkgs() { return flag(p_flag); }
        static bool e_pkgs() { return flag(e_flag); }
        static bool offline() { return flag(offline_flag); }
        static bool set_temp() { return flag(s_flag); }
        static bool find_conf() { return flag(f_flag); }
        static bool find_prog() { return flag(findprog_flag); }
        static bool latest() { return flag(l_flag); }
        static bool update() { return flag(u_flag); }
        static bool no_confs() { return flag(noconf_flag); }
        static bool no_pkgs() { return flag(nopack_flag); }
        static bool verbose() { return flag(v_flag); }
    
    private:
        static int _mode;
        static bool _flags[NUM_FLAGS];
        static char* _location;
        static std::deque<char*> _i_packages, _e_packages, _i_config, _e_config, _temp_set, _write_set;
};

#endif
