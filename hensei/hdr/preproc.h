/**
 *
 *  @file    preproc.h
 *  @brief   Preprocessing for descriptors labels
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#ifndef PREPROC_H
#define PREPROC_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "config.h"
#include "ffdesc.h"

using std::set;
using std::string;
using std::vector;

/*************************** Descriptors Strutures ****************************/

/**
 * @brief Structure for MIDIs, frequencies and notes equivalents
 */
typedef struct ffreq {
    int nb;
	float freq[128];
	string desc[128];
} ffreq;

/**
 * @brief Structure for harmonicity
 */
typedef struct _harmo {
    int nb;
	float *min;
	float *max;
	string *desc;
} harmo;

/**
 * @brief Structure for loudness
 */
typedef struct _loudn {
    int nb;
	float *min;
	float *max;
	string *desc;
} loudn;

/**
 * @brief Structure for noisiness
 */
typedef struct _noisi {
    int nb;
	float *min;
	float *max;
	string *desc;
} noisi;

/**
 * @brief Structure for spectral centroid
 */
typedef struct _spcen {
    int nb;
	float *min;
	float *max;
	string *desc;
} spcen;

/******************************* Main function ********************************/

/**
 * @brief Label all audio descriptors values
 *
 * @param desc descriptor's name
 * @param pathname path's name
 * @param filenmae file's name
 * @param outpath  output's name
 *
 * @return boolean 0 if file labelised, otherwise 0 if not
 */
int label(string desc, string pathname, string filename, string outpath);

/*************************** Create bins functions ****************************/

/**
 * @brief Create note bins
 */
ffreq FundamentalFrequency_bins();

/**
 * @brief Create inharmonicity bins
 */
harmo Inharmonicity_bins();

/**
 * @brief Create loudness bins
 */
loudn Loudness_bins();

/**
 * @brief Create noisiness bins
 */
noisi Noisiness_bins();

/**
 * @brief Create spectral centroid bins
 */
spcen SpectralCentroid_bins();

/**************************** Conversion functions ****************************/

/**
 * @brief Convert frequency to note bins
 *
 * @param data values
 *
 * @return notes bins
 */
vector<string> convert_notes(const vector<float>& data);

/**
 * @brief Convert inharmonicity to bins
 *
 * @param data values
 *
 * @return inharmonicity bins
 */
vector<string> convert_harmo(const vector<float>& data);

/**
 * @brief Convert loudness to bins
 *
 * @param data values
 *
 * @return loudness bins
 */
vector<string> convert_loudn(const vector<float>& data);

/**
 * @brief Convert noisiness to bins
 *
 * @param data values
 *
 * @return noisiness bins
 */
vector<string> convert_noisi(const vector<float>& data);

/**
 * @brief Convert spectral centroid to bins
 *
 * @param data values
 *
 * @return spectral centroid bins
 */
vector<string> convert_spcen(const vector<float>& data);

/**
 * @brief Round value to the second decimal
 *
 * @param f value
 *
 * @return f value
 */
float roundf2d(float f);

/**
 * @brief Give the nearest note frequency
 *
 * @param f frequency
 * @param n notes structure
 *
 * @return i indice of the nearest note frequency in the notes structure
 */
int approxFreq(float f, const ffreq& n);

#endif
