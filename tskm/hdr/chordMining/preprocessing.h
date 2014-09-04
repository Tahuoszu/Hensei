/**
 *
 * @file    preprocessing.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "functions.h"
#include "IntervalSet.h"

using std::pair;
using std::map;
using std::set;
using std::stack;
using std::vector;

/**
 * @brief Apply gap filter to given list of int tones
 *
 * @param tones list of tones
 * @param alpha percentage of interruptions to be filtered out
 * @param max   maximal gap which can be filtered out
 *
 * @return
 */
template <class S>
IntervalSet<S> marginalGapFilter(const IntervalSet<S>& tones,
                                 float alpha, float gapMaximum);

/**
 * @brief Filter the intervals which do not exceed the minimal duration
 *        threshold
 *
 * @param tones       list of tones
 * @param minDuration minimal duration of an interval required to pass
 *                    this filter
 *
 * @return tones
 */
template <class S>
IntervalSet<S> minDurationIntervalSetFilter(const IntervalSet<S>& tones,
                                            int minDuration);

/**
 * @brief Add stack's values to vector and return vector
 *
 * @param v vector
 * @param s stack
 *
 * @return vector
 */
vector<int> addStack2Vector(vector<int>& v, stack<int>& s);

/**
 * @brief Test if current and last tones are mergeable
 *
 * @param start last element of starts' stack
 * @param end
 * @param dur
 * @param currentStart
 * @param currentEnd
 * @param gapMAximum
 * @param originalGapFilter
 * @param alphaComplement
 *
 * @return bool
 */
bool isMergeable(int start, int end, int dur,
                 int currentStart, int currentEnd, int currentDur,
                 float alphaComplement,
                 float gapMaximum,
                 float originalGapFilter);

#include "preprocessing.hpp"

#endif
