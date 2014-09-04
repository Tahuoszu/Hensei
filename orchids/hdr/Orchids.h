/**
 *
 *  @file			Orchids.h
 *  @brief			Main header of the project
 *  @version        0.04
 *  @author			Antoine Bouchereau
 *	@date			16-12-2013
 *
 */

#ifndef Orchids_Orchids_h
#define Orchids_Orchids_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <cassert>
#include <float.h>
#include <sys/time.h>
#include <sys/stat.h>
#ifndef _WIN32
    #include <sys/types.h>
#endif
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif


using namespace std;


//-----------------Include librairies & utilities-----------------
#include "../lib/sdif.h"
#include "matrix.hpp"

#ifndef min
    #define _min(x, y)	((x) < (y) ? (x) : (y))
#endif
#ifndef max
    #define	_max(x, y)	((x) > (y) ? (x) : (y))
#endif

#define     pi                      3.14159265358979323846
#define     MAX_SIZE_BUFFER         32768

//-----------------Define structures-----------------

/**
 *  @struct ircamDescriptor_param
 *  @brief Parameters for the IRCAM descriptor analysis
 */
struct ircamDescriptor_param
{
    string      type;
    string      name;
    float       fVal;
    string      sVal;

    ircamDescriptor_param(string Type, string Name, float Val): type(Type), name(Name), fVal(Val) {};
    ircamDescriptor_param(string Type, string Name, string Val): type(Type), name(Name), sVal(Val) {};
};

/**
 *  @struct analysis_params
 *  @brief Parameters for the analysis
 */
struct analysis_params
{
    vector<ircamDescriptor_param>   irc_desc_params;
};

/**
 *  @struct feature
 *  @brief Contains all datas retrieved by the analysis for a descriptor
 */
template<class T>
struct feature
{
    string      name;
    string      sig;
    TArray2<T>  values;
    vector<T>   times;
    float       mean;
    float       stdDev;
    float       max;
    float       min;
    TArray2<T>  normalized_val;
    TArray2<T>  resampled_val;
    
    //Default constructor: values matrix is initialized to (0, 0) in order to have a size = 0 (cf merging)
    ///Default constructor
    feature(string Name, string Sig):
        name(Name),
        sig(Sig),
        values(0,0),
        mean(0),
        stdDev(0),
        max(0),
        min(0),
        normalized_val(0,0),
        resampled_val(0,0) {};
    
    ///Constructor
    feature(){};
};

/**
 *  @struct frame_reader
 *  @brief Structure that retrieve the frames from an SDIF file between frames number first_frame and last_frame. Fill the frames vector with matrix datas.
 */
struct frame_reader
{
    int                         first_frame;
    int                         last_frame;
    size_t                      bytesread;
    size_t                      previous_pos;
    int                         previous_index;
    vector< TArray2<float> >    frames;
};

#endif
