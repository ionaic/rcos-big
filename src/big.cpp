#include <deque>
#include <iostream>
#include "big.h"
#include "args.h"
#include "shellgen.h"

int Args::_mode;
bool Args::_flags[NUM_FLAGS];
char* Args::_location;
std::deque<char*> Args::_i_packages, Args::_e_packages, Args::_i_config, Args::_e_config, Args::_temp_set, Args::_write_set;

void display_help() {
    // display the version
    //std::cout << "Version:" << std::endl;

    // display the usage
    std::cout << "USAGE: " << "\tbig command [options]" << std::endl
        << "\tbig crunch [options]" << std::endl
        << "\tbig bang|crunch [location] [options]" << std::endl
        << "\tbig set [option]" << std::endl << std::endl;
    
    // display description
    std::cout << "big is a command line for storing and restoring system setups.  It is intended to generate a system configuration by storing installed packages, programs and related configuration files with some user configuration and input to help users recover after a reinstall or to create system configurations for distribution or transfer to another machine." << std::endl << std::endl;

    // display commands
    std::cout << "COMMANDS: " << std::endl
        << "\tbang - Re-download and install or unpack and install all packages and configs named or stored in the archive.  Can provide a location to read package from, or will default to location in config file or ~/.big/archives if none named and fail if no archive found in that location." << std::endl
        << "\tcrunch - Store installed packages, including or excluding packages and config files as named in the config file.  Can provide location to store archive to, otherwise big will default to the location named in the config or ~/.big/archives." << std::endl
        << "\tset - Store the setting in the config file.  If it conflicts with an existing setting, a confirmation will ask what to do (this can be disabled in the config)." << std::endl;

    // display flags/options
    std::cout << "OPTIONS: " << std::endl
        << "Mandatory arguments to long options mandatory for short options as well." << std::endl
        << "  -h, --help                            Display this help text." << std::endl
        << "  -c, --include-config <config(s)>      Include the following package(s) or config file(s)." << std::endl
        << "  -x, --exclude-config <config(s)>      Exclude the following package(s) or config file(s)." << std::endl
        << "  -p, --include-package <package(s)>    Include the following package(s) or config file(s)." << std::endl
        << "  -e, --exclude-package <package(s)>    Exclude the following package(s) or config file(s)." << std::endl
        << "      --offline                         Store all packages locally in the archive to allow " << std::endl
            << "\t\t\t\t\t\tfor offline bangs." << std::endl
        << "  -s, --set <option>                    Set this option just for this execution only. Works" << std::endl
            << "\t\t\t\t\t\twith any of the options available for the config file." << std::endl
        << "  -f, --find-config [true|false]        Set whether big searches for config " << std::endl
            << "\t\t\t\t\t\tfiles or not." << std::endl
        << "      --find-programs [true|false]      Set whether big searches for programs" << std::endl
            << "\t\t\t\t\t\tnot in the package manager or not." << std::endl
        << "  -l, --latest                          Adds (or subtracts) from the most recent archive instead" << std::endl
            << "\t\t\t\t\t\tof creating a new one." << std::endl
        << "  -u, --update <big archive>            Updates specified archive instead of creating" << std::endl
            << "\t\t\t\t\t\ta new archive." << std::endl
        << "      --no-config                       Tells big not to store any configs, even those specified" << std::endl
            << "\t\t\t\t\t\tin the configuration file.  The only config files included will be" << std::endl
            << "\t\t\t\t\t\tthose specified at the command line." << std::endl
        << "      --no-packages                     Don't store any packages locally, even those specified" << std::endl
            << "\t\t\t\t\t\tin the configuration file.  The only packages stored will be " << std::endl
            << "\t\t\t\t\t\tthose specified at the command line." << std::endl
        << "  -v, --verbose                         Verbose output." << std::endl;
}

int big_crunch() {

}

int main(int argc, char** argv) {
    Args::parseArgs(argc, argv);
    //args = new Arguments(argc, argv);
    if(Args::mode() == 1) {
        // bang (unpack)
    }
    else if(Args::mode() == 2) {
        // crunch (grab and pack)
        big_DBG("Args::mode() == %d in main\n", Args::mode());
        std::deque<char*> entries;
        if (!getPackageList(entries)) {
            return genScript(entries);
        }
    }
    else if(Args::mode() == 3) {
        // set (change config)
    }
    else { // mode
        big_DBG("Failed to find valid mode.  Args::mode() == %d in main\n", Args::mode());
        display_help();
    }
    return 0;
}
