/**
 *
 *  @file    ffdesc.h
 *  @brief   Functions for Frequency Fundamental Descriptor
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#ifndef FFDES_H
#define FFDES_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using std::set;
using std::string;
using std::vector;

/**
 * @brief Structure for MIDIs, frequencies and notes equivalents
 */
typedef struct _notes {
	int midi[128];
	float freq[128];
	string desc[128];
} notes;

/********************** Preparing tones files functions ***********************/

/**
 * @brief Create associated symbols file for a tones file
 * 
 * @param filename file's name
 * @param symbols  set of symbols extracted
 *
 * @return boolean 0 if symbols file created, otherwise 1 if not
 */
int extractFrequencyFiles(string filename, set<float>& symbols);
/**
 * @brief Rewrite the frequency fundamental descriptor file
 * 
 * @param filename file's name
 *
 * @return boolean 0 if rewriting done, otherwise 1 if not
 */
int rewrite(string filename);

/**************************** Conversion functions ****************************/

/**
 * @brief Give the nearest note frequency 
 * 
 * @param f frequency
 * @param n notes structure
 *
 * @return i indice of the nearest note frequency in the notes structure
 */
int approxFreq(float f, const notes& n);

/**
 * @brief Convert frequency to MIDI
 * 
 * @param f frequency
 *
 * @return m MIDI
 */
int freq2midi(float f);

/**
 * @brief Initialize notes structure
 *
 * @return structure with MIDIs, frequencies and notes information
 */
notes generateMFD();

/**
 * @brief Convert MIDI to frequency
 * 
 * @param m MIDI
 *
 * @return f frequency
 */
float midi2freq(int m);

#endif
