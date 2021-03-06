#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <deque>
#include <iostream>
#include <fstream>
#include "shellgen.h"

/**************************************************
 * FUNCTION: 
 * PURPOSE: 
 * RETURN VALUE:
 * -------------------PARAMETERS------------------- 
 **************************************************/
int grabConfigs() {
    
}

/**************************************************
 * FUNCTION: 
 * PURPOSE: 
 * RETURN VALUE:
 * -------------------PARAMETERS------------------- 
 **************************************************/
int filterPackages(std::deque<char*> &packages, char** includes, int num_includes, char** excludes, int num_excludes) {
    /* Packages to exclude:
     * acpi
     * accountsservice
     * acl
     * apt
     * apg
     * aptitude
     * aspell
     * 
     */
    // look into aptoncd, apt disc creator
    for(int i = 0; i < packages.size(); i++) {
        for (int j = 0; j < num_excludes; j++) {
            char* temp;
            char* format;

            // format is for sscanf, should be the package name and then %s
            // to catch things like gnome-keyring by scanning for gnome%s
            strcpy(format, includes[j]);
            strcat(format, "%s");

            sscanf(packages[i], format, temp);
        }
    }
    return 6;
}


/**************************************************
 * FUNCTION: genScript(std::deque<char*> &)
 * PURPOSE: 
 * RETURN VALUE:
 * -------------------PARAMETERS------------------- 
 * packages: an STL deque passed by reference containing the list of packages to be installed.
 **************************************************/
int genScript(std::deque<char*> &packages) {
    //std::cout << "gen scripts" << std::endl;
    int dir_exists = system("ls ../scripts");
    std::cout << "ls ../scripts returns: " << dir_exists << std::endl;
    if (dir_exists == 512) {
        std::cerr << "Cannot find scripts directory, making one." << std::endl;
        system("mkdir ../scripts");
    }
    
    // create the file name to include the date
    std::string filename;
    {
        char temp[BUFF_SIZE];
        if (!fgets(temp, BUFF_SIZE, popen("date +'image%m%d%Y.sh'", "r"))) {
            std::cerr << "Unable to create file." << std::endl;
            return 2;
        }
        //std::cout << __LINE__ << "Filename: " << filename << std::endl;
        //sprintf(filename, "image%s.sh", temp);
        filename = std::string(temp);
    }

    // date produces a ? at the end, remove it
    {
        char* temp;
        sscanf(filename.c_str(), "%s?", temp);
        filename = std::string(temp);
    }
    
    // run touch to be sure the file is created 
    { 
        char command[BUFF_SIZE];
        sprintf(command, "touch ../scripts/%s", filename.c_str());
        int make_file = system(command);
        if (make_file) {
            std::cerr << "Cannot create file.  Perhaps you don't have write permissions to this directory? Touch failed with error: " << make_file << std::endl;
            return 3;
        }
    }

    // add the directory onto the filename
    {
        char *temp;
        sprintf(temp, "../scripts/%s", filename.c_str());
        filename = std::string(temp);
    }

    std::ofstream out;
    out.open(filename.c_str());
    if (out.is_open()) { 
        std::cout << "Writing script..." << std::endl;
        out << "sudo apt-get install";
        for (int i = 0; i < packages.size(); i++) {
            out << " " << packages[i];
            std::cout << ".";
        }
        std::cout << std::endl << "Install script generated as: " << filename << std::endl;
        out.close();
    }
    else {
        std::cerr << "Could not open file." << std::endl;
        return 4;
    }
    
    { 
        std::string command = "chmod +x " + filename;
        int chmod_result = system(command.c_str());
        if (chmod_result) {
            std::cerr << "Failed modifying file permissions " << filename << ", attempting with superuser access." << std::endl;
            command = "sudo " + command;
            chmod_result = system(command.c_str());
            if (chmod_result) {
                std::cerr << "Failed to make file executable with chmod error code " << chmod_result << ".  Once execution is finished please run: chmod +x " << filename;
                return 5;
            }
        }
    }
    return 0;
}

/**************************************************
 * FUNCTION: getPackageList(std::deque<char*>&)
 * PURPOSE: retrieve listing of packages
 * RETURN VALUE: an integer representing the error
 *      message or 0 if there is no error
 * -------------------PARAMETERS-------------------
 * entries: an STL deque passed by reference to be
 *      filled with dpkg entries
 **************************************************/
int getPackageList(std::deque<char*> &entries) {
    FILE* f = popen("dpkg -l", "r");
    if (!f) { 
        std::cerr << "Failed to run dpkg." << std::endl;
        return 1;
    }
    else {
        std::cout << "Getting package list" << std::endl;;
        char temp[BUFF_SIZE];
        while (fgets(temp, BUFF_SIZE, f)) {
            char *name, *version, *description;
            name = new char[BUFF_SIZE];
            //sscanf(temp, "ii %s", name);
            sscanf(temp, "ii %s %s %*s", name, version, description);
            //std::cout << name << std::endl;
            entries.push_back(name);
        }
    }
    return 0;
}
