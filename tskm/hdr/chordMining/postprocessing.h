/**
 *
 * @file    postprocessing.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    25/04/2014
 *
 */

#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <iostream>
#include <list>
#include <map>
#include <set>

#include "Chord.h"
#include "functions.h"
#include "IntervalSequence.h"
#include "IntervalSet.h"
#include "Tone.h"

using std::list;
using std::map;
using std::pair;
using std::set;

/**
 * @brief Filters the result of a Chord mining process for minimal and maximal
 *        number of allowed tones
 *
 * @param closedChords closed chords
 * @param minChordSize minimal chord size to pass through filter
 * @param maxChordsize maximal chord size to pass through filter
 *
 * @return
 */
map<set<Tone>, BitSet > chordSizeFilter(
                            const map<set<Tone>, BitSet >& closedChords,
                            const int minChordSize,
                            const int maxChordSize);


/**
 * @brief Converts an interval sequence to an interval set, used to save Chords
 *
 * @param seq
 *
 * @return
 */
IntervalSet<Chord> intervalSequence2IntervalSet(
                        const IntervalSequence<set<Chord> >& seq);


/**
 * @brief Converts a set of Tones to a sequence of a set of Chords
 *
 * @param tones      tone set sequence
 * @param occurences closed Chords and their occurence
 *
 * @return seq sequence of Chord sets
 */
IntervalSequence<set<Chord> > toneSetSequence2ChordSetSequence(
							       const IntervalSequence<set<Tone> >& tones,
							       const map<set<Tone>, BitSet >& occurences);

#endif
