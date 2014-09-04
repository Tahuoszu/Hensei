/**
 *
 * @file    testunity.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#ifndef TESTUNITY_H
#define TESTUNITY_H

#include <algorithm>
#include <iostream>

#include "Chord.h"
#include "Event.h"
#include "functions.h"
#include "Interval.h"
#include "IntervalEventSet.h"
#include "IntervalSequence.h"
#include "IntervalSet.h"
#include "postprocessing.h"
#include "preprocessing.h"
#include "Tone.h"

using std::cout;
using std::endl;

void testunity();

void testTones();

void testChords();

void testIntervalEventSet();

void testIntervalSequence();

void testIntervalSet();

void testPreprocessing();

void testPostprocessing();

#endif
