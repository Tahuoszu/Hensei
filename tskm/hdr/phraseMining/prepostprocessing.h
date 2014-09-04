/**
 *
 * @file    preprocessing.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef PREPOSTPROCESSING_H
#define PREPOSTPROCESSING_H

#include "Chord.h"
#include "ClosedSequence.h"
#include "IntervalSequence.h"
#include "test.h"

/******************************* Preprocessing ********************************/

/**
 * @brief Apply the filter to the specified IntervalSequence
 * @param seq
 * @return
 */
IntervalSequence<set<Chord> >
duplicateSuccessorFilter(const IntervalSequence<set<Chord> >& seq);

/**
 * @brief Converts the specified interval sequence to a list of sequences.
 *        Note: This method actually returns also the remaining last window
 *        even if it is not long enough
 * @param sequence
 * @param windowSize
 * @param S
 * @return
 */
template <class S>
list<list<S> > sequence2TimeSizedWindow(IntervalSequence<S> sequence,
                                        int windowSize);

/******************************* Postprocessing *******************************/

/**
 * @brief Converts sequences and their occurences in windows
 *        to a phrase mining input
 * @param set
 * @return
 */
map<set<ClosedSequence>, int>
closedSetSequence2Transaction(const list<list<set<Chord> > >& windows,
                              const set<list<Chord> >& chords);

#include "prepostprocessing.hpp"

#endif
