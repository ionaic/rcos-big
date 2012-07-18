#ifndef _SHELLGEN_H_
#define _SHELLGEN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <deque>
#include <iostream>
#include <fstream>

// buffer size for reading in strings
#define BUFF_SIZE 256

/**************************************************
 * FUNCTION: 
 * PURPOSE: 
 * RETURN VALUE:
 * -------------------PARAMETERS------------------- 
 **************************************************/
int grabConfigs();

/**************************************************
 * FUNCTION: 
 * PURPOSE: 
 * RETURN VALUE:
 * -------------------PARAMETERS------------------- 
 **************************************************/
int filterPackages(std::deque<char*> &packages);

/**************************************************
 * FUNCTION: genScript(std::deque<char*> &)
 * PURPOSE: 
 * RETURN VALUE:
 * -------------------PARAMETERS------------------- 
 * packages: an STL deque passed by reference containing the list of packages to be installed.
 **************************************************/
int genScript(std::deque<char*> &packages);

/**************************************************
 * FUNCTION: getPackageList(std::deque<char*>&)
 * PURPOSE: retrieve listing of packages
 * RETURN VALUE: an integer representing the error
 *      message or 0 if there is no error
 * -------------------PARAMETERS-------------------
 * entries: an STL deque passed by reference to be
 *      filled with dpkg entries
 **************************************************/
int getPackageList(std::deque<char*> &entries);

#endif
