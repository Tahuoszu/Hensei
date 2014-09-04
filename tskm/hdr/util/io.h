/**
 *
 * @file    io.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef IO_H
#define IO_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "functions.h"

#ifdef _WIN32
    #include "wdirent.h"
#elif _WIN64
    #include "wdirent.h"
#else
    #include <dirent.h>
    #include <stdio.h>
    #include <sys/types.h>
#endif

using std::map;
using std::pair;
using std::string;
using std::stringstream;
using std::vector;

typedef struct _data {
    int data_size;
    vector<int> symbol;
    vector<int> start;
    vector<int> end;
} data;

typedef struct _symb {
    int symb_size;
    vector<int> symbol;
    vector<string> label;
    vector<string> descp;
} symb;

typedef struct _data_symb {
    string filename;
    bool lastfile;
    data datas;
    symb symbs;
} data_symb;

data_symb* loadfiles(string path, string prefix);

data readData(string pathname, string filename);

symb readSymb(string pathname, string filename);

void saveFile(string pathname, string filename, const stringstream& ss);

#endif
