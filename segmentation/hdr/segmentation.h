/**
 *
 * @file	segmentation.h
 * @brief	Main functions for the segmentation of time series
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

#include "functions.h"
#include "Segment.h"

using std::vector;

/****************************** Main functions ********************************/

/**
 * @brief Approximate the entropy of a time series
 * Input  -----
 * @param data : time series data
 * @param dim  : embedded dimension
 * @param r    : tolerance (typically 0.2 * std)
 * Output -----
 * @return entropy : approximated entropy
 */
float approx_entropy(const vector<float>& data, int dim, float r);

/**
 * @brief Create a fine segmented representation and merge the lowest cost
 *        segments until only 'nb_seg' remain.
 * Input  -----
 * @param data      : time series data
 * @param nb_seg    : number of segments
 * Output -----
 * @return segment  : segmented time series
 */
Segment simpleSegment(const vector<float>& data, int nb_seg);

/**
 * @brief Create a multi-level segmentation of time series
 * Input  -----
 * @param tmpSeries : time series data
 * @param nb_seg    : number of segments
 * @param tmpOn     : offset of segments
 * @param durations : duration of segments
 * Output -----
 * @return segment  : multi-level segmented time series
 */
vector<vector<float> > multiSimpleSegment(vector<float> tmpSeries,
                                          int nb_seg,
                                          vector<int>* tmpOn,
                                          vector<int>* durations);

/**
 * @brief Create a fine segmented representation and merge the lowest cost
 *        segments until only 'nb_seg' remain.
 * Input  -----
 * @param data      : time series data
 * @param nb_seg    : number of segments
 * Output -----
 * @return segment  : segmented time series
 */
Segment bottomUpSegmentation(const vector<float>& data, int nb_seg);

/**
 * @brief Create a multi-level segmentation of time series
 * Input  -----
 * @param tmpSeries : time series data
 * @param nb_seg    : number of segments
 * @param tmpOn     : offset of segments
 * @param durations : duration of segments
 * Output -----
 * @return segment  : multi-level segmented time series
 */
vector<vector<float> > tsMultiLevelSegment(vector<float> tmpSeries,
                                           int nb_seg,
                                           vector<int>* tmpOn,
                                           vector<int>* durations);

/************************ SimpleSegment sub-functions *************************/

/**
 * @brief Calculate the mc of segment
 * Input  -----
 * @param data  : time series data
 * @param seg   : segment
 * @param ind   : segment's index
 * @param delay : delay by the number of segments
 * Output -----
 * @return mc   : mc value
 */
float calculate_mc(const vector<float>& data,
                   const Segment& seg,
                   int ind, int delay);

/**
 * @brief Calculate the best vector of segment
 * Input  -----
 * @param data  : time series data
 * @param seg   : segment
 * @param ind   : segment's index
 * @param delay : delay by the number of segments
 * Output -----
 * @return best : best vector
 */
vector<float> calculate_best(const vector<float>& data,
                             const Segment& seg,
                             int ind, int delay);

/**
 * @brief Reconstruct a segment with a percentage of error
 * Input  -----
 * @param seg    : segment
 * @param data   : time series data
 * Output -----
 * @return error : error
 */
float reconstruct_error(const Segment& seg, const vector<float>& data);

/********************* BottomUpSegmentation sub-functions *********************/

/**
 * @brief Calculate the mc of segment
 * Input  -----
 * @param data  : time series data
 * @param seg   : segment
 * @param ind   : segment's index
 * @param delay : delay by the number of segments
 * Output -----
 * @return mc   : mc value
 */
float compute_mc(const vector<float>& data,
                 const Segment& seg,
                 int ind, int delay);

/**
 * @brief Calculate the best vector of segment
 * Input  -----
 * @param data  : time series data
 * @param seg   : segment
 * @param ind   : segment's index
 * @param delay : delay by the number of segments
 * Output -----
 * @return best : best vector
 */
vector<float> compute_best(const vector<float>& data,
                           const Segment& seg,
                           int ind, int delay);

/**
 * @brief Calculate the best vector of segment
 * Input  -----
 * @param data  : time series data
 * @param seg   : segment
 * @param ind   : segment's index
 * Output -----
 * @return      :
 */
void compute_recons(vector<float>& data, const Segment& seg, int ind);

/**
 * @brief Reconstruct a segment with a percentage of error
 * Input  -----
 * @param data  : original time series data
 * @param recd  : reconstructured time series data
 * Output -----
 * @return error : error
 */
float compute_error(const vector<float>& data, const vector<float>& recd);

/************************** Get results sub-function **************************/

/**
 * @brief Reconstruct the segmented times series for the output file
 * Input  -----
 * @param data      : matrix of segmented time series
 * @param tmpOn     : offset of segments
 * @param durations : duration of segments
 * Output -----
 * @return results  : symbol, start and end of each segment
 */
void parseSegments(const vector<vector<float> >& matrix,
                   const vector<int>& tmpOn,
                   const vector<int>& durations,
                   vector<float>& results);

#endif
