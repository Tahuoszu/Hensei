/**
 *
 *  @file    misc.h
 *  @brief   Miscellaneous functions for input/output files
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#ifndef MISC_H
#define MISC_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ffdesc.h"

using std::set;
using std::string;
using std::vector;

/************************ Getting files name functions ************************/

/**
 * @brief Returns a vector of audio files name from a directory
 * 
 * @param dir    directory with audio files
 *
 * @return files vector of audio files name
 */
vector<string> getAudioFilesName(string dir);

/**
 * @brief Returns a vector of files name from a directory
 * 
 * @param dir    directory with files
 *
 * @return files vector of files name
 */
vector<string> getFilesName(string dir);

/**
 * @brief Returns a vector of tone files name from a directory
 * 
 * @param dir    directory with files
 *
 * @return files vector of tone files name
 */
vector<string> getToneFilesName(string dir);

/********************** Preparing tones files functions ***********************/

/**
 * @brief Preprocessing function for TSKM (see functions below)
 * 
 * @param filename file's name
 *
 * @return boolean 0 if all is done, otherwise 1 if not
 */
int preprocess(string filename);

/**
 * @brief Create associated symbols file for a tones file
 * 
 * @param filename file's name
 * @param symbols  set of symbols extracted
 *
 * @return boolean 0 if symbols file created, otherwise 1 if not
 */
int extractSymbolFiles(string filename, set<float>& symbols);

/**
 * @brief Write tones file according to associated symbols file
 * 
 * @param filename file's name
 *
 * @return boolean 0 if tones file created, otherwise 1 if not
 */
int rewriteTones(string filename, const set<float>& symbols);

#endif
