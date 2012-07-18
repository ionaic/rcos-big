#ifndef _BIG_H_
#define _BIG_H_

#include <string>
#include <iostream>
#include "args.h"

// error code definitions
#define big_ERR_NODPKG 1 // Failed to run dpkg
#define big_ERR_MKFNAME 2 // Couldn't run date to create file
#define big_ERR_MKFILE 3 // Couldn't touch the file
#define big_ERR_NOWRITE 4 // Couldn't write to file
#define big_ERR_CHMOD 5 // Couldn't run chmod on file

// debug definitions
#define big_DBG_LOC_FORMAT  "[In file %s:%d] "
#define big_DBG_LOC_ARG  __FILE__, __LINE__
#define big_DBG_PRINT(...)       fprintf(stderr, __VA_ARGS__)
#define big_DBG(_fmt, ...)  big_DBG_PRINT(big_DBG_LOC_FORMAT _fmt, big_DBG_LOC_ARG, __VA_ARGS__)

// verbose and other error output
//#define big_VERB_STREAM(_msg) std::cerr << _msg << std::endl;
//#define big_VERB_CONDITION(_contents) if (Args::verbose()) { _contents }
//#define big_VERB(x) big_VERB_CONDITION(big_VERB_STREAM(x))

//Arguments *args;

void display_help(); //display the help dialog

void verbose_out(std::string message) { if (Args::verbose()) { std::cerr << message << std::endl; } }
#endif
