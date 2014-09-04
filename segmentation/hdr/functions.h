/**
 *
 * @file	functions.h
 * @brief	Various fonctions for the segmentation of time series
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include <samplerate.h>

#define	BUFFER_LEN 1024

using std::string;
using std::vector;

/*************************** Elementary functions *****************************/

/**
 * @brief Harmonize a vector with the mean
 * Input  -----
 * @param v  : vector
 * Output -----
 * @return v : harmonized vector
 */
template <class T>
vector<T> harmonize(const vector<T>& v);

/**
 * @brief Return the index and the max value of the given vector
 * Input  -----
 * @param v     : vector
 * Output -----
 * @return vmax : maximum
 * @return vind : index
 */
template <class T>
void max_vector(const vector<T>& vect, T* vmax, int* vind);

/**
 * @brief Return the index and the min value of the given vector
 * Input  -----
 * @param v     : vector
 * Output -----
 * @return vmin : minimum
 * @return vind : index
 */
template <class T>
void min_vector(const vector<T>& vect, T* vmin, int* vind);

/**
 * @brief Resample the input vector at upRate/downRate times
 *        This resample function comes from Secret Rabbit Code,
 *        aka libsamplera implementation.
 * Input  -----
 * @param input    : vector
 * @param upRate   : int
 * @param downRate : int
 * Output -----
 * @return output  : resampled input vector
 */
template <class T>
vector<T> resample(vector<T>& input, int upRate, int downRate);

/**
 * @brief Calculate the standart deviation of a vector
 * Input  -----
 * @param v    : vector
 * Output -----
 * @return std : standart deviation
 */
template <class T>
float standard_deviation(const vector<T>& v);

/**
 * @brief Calculate a vector with values separated by step distance
 * Input  -----
 * @param start : start value
 * @param end   : end value
 * @param step  : step value
 * Output -----
 * @return v    : vector
 */
template <class T>
vector<T> step_vector(T start, T end, T step);

/**
 * @brief Calculate the sum of the square vector
 * Input  -----
 * @param v    : vector
 * Output -----
 * @return sum : sum
 */
template <class T>
T sum_sqr(const vector<T>& v);

/**
 * @brief Calculate the sum of the vector
 * Input  -----
 * @param v    : vector
 * Output -----
 * @return sum : sum
 */
template <class T>
T sum_vector(const vector<T>& v);

/***************************** Display functions ******************************/

/**
 * @brief Print the vector's values
 * Input  -----
 * @param v : vector
 */
template <class T>
void print_vector(const vector<T>& v);

/**
 * @brief Print the matrix's values
 * Input  -----
 * @param m : matrix (vector of vector)
 */
template <class T>
void print_matrix(const vector<vector<T> >& m);

/*************************** Input/Output functions ***************************/

/**
 * @brief Write segmentation's data to text file
 * Input  -----
 * @param pathname  : path's name
 * @param filename  : file's name
 * @param data      : data
 * Output -----
 * @return boolean  : 0 if done, otherwise 1 if failed
 */
template <class T>
int writeToFile(string pathname, string filename, const vector<T>& data);

/**
 * @brief Read data from text file
 * Input  -----
 * @param pathname  : path's name
 * @param filename  : file's name
 * @param data      : data
 * Output -----
 * @return data     : vector
 */
template <class T>
int readFromFile(string pathname, string filename, vector<T>& data);

#include "functions.hpp"

#endif
