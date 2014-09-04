/**
 *
 *  @file    config.h
 *  @brief   Parser for the configuration file
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::vector;

/**
 * @brief Check if descriptor exists
 *
 * @param str  descriptor's name
 * @param sets set of descriptors
 *
 * @return boolean 0 if descriptor exists, otherwise 1 if not
 */
bool checkDescriptor(string str, const set<string>& sets);

/**
 * @brief Skip comment lines
 *
 * @return boolean 0 if lines skiped, otherwise 1 if not
 */
bool commentLine(string str);

/**
 * @brief Generate list of descriptors
 *
 * @return List of descriptors
 */
set<string> descList();

/**
 * @brief Generate list of TSKM parameters
 *
 * @return List of TSKM parameters
 */
set<string> paramList();

/**
 * @brief Read value of one parameter
 *
 * @param line  line
 * @param param parameter
 * @param value value read
 *
 * @return boolean 0 if parameter read, otherwise 1 if not
 */
int readValue(string line, string& param, float& value);

/**
 * @brief Read configuration file and save all parameters values
 *
 * @param filename file's name
 * @param desc_val list of descriptors
 * @param tskm_val list of TSKM parameters
 *
 * @return boolean 0 if parameters read, otherwise 1 if not
 */
int readConfigFile(string filename,
				   set<string>& desc_val,
				   map<string, float>& tskm_val);

/**
 * @brief Remove space before reading lines
 *
 * @param str line reading
 */
void removeSpace(string& str);

#endif
