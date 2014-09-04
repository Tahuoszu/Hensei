/**
 *
 * @file    ChordMiner.h
 * @brief   Closed chord mining
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef CHORDMINER_H
#define CHORDMINER_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Chord.h"
#include "Graph.h"
#include "io.h"
#include "IntervalSequence.h"
#include "IntervalSet.h"
#include "preprocessing.h"
#include "postprocessing.h"
#include "Tone.h"

using std::map;
using std::pair;
using std::vector;

class ChordMiner
{
private :

    // Marginal Gap Filter
    float marginalGapFilterAlpha;
	int   marginalGapMaxDuration;

    // Minimal Tone Duration
	int minimalToneDuration;

    // Minimal Chord Duration
	int minimalChordDuration;
	int minimalSupport;
	float marginAlpha;

    // Minimal and maximal chord cardinality
    int minimalChordSize;
    int maximalChordSize;

    // Results
	map<set<Tone>, BitSet> closedChords;
	map<set<Tone>, int> closedChordsWithSupport;
	IntervalSequence<set<Chord> > closedChordSetSequence;
	Graph<Chord> closedChordGraph;

public :

    /********** Constructor **********/

    ChordMiner();

    /********** Destructor **********/

    ~ChordMiner();

    /********** Getters **********/

    /**
     * @brief Make a chord with id via hashcode and support as label
     * @param tones
     * @return chord
     */
	Chord getChord(set<Tone> tones);

	/**
	 * @brief Get the result as map with Closed Chords (set of Tones)
	 *        mapped to their occurence as BitSet
	 * @return closed chords
	 */
	map<set<Tone>, BitSet> getClosedChords();

	/**
	 * @brief Get the Sequence consisting of sets of closed chords
	 * @return closed chord set sequence
	 */
	IntervalSequence<set<Chord> > getClosedChordSetSequence();

	/**
	 * @brief Get map with closed Chords (set of tones) mapped to their support
	 * @return
	 */
	map<set<Tone>, int> getClosedChordsWithSupport();

    /**
     * @brief Generate a dottable graph from the given
     *        Note: This is currently a brute force alternative,
     *        since margin-closed-chords cannot guarantee a complete lattice and
     *        therefore the post-lattice computation will not work.
     * @return
     */
    Graph<Chord> getResultAsLattice();

    /********** Setters **********/

	/**
	 * @brief Set the alpha value for the marginal gap filter
	 * @param alpha	: percentage of enclosing occurences to gap,
	 *                which the filter should fill
	 */
	void setMarginalGapFilterAlpha(float alpha);

	/**
	 * @brief Set the maximal gap that can be filtereds
	 *        by the marginal gap filter
	 * @param duration
	 */
	void setMarginalGapMaxDuration(int duration);

	/**
	 * @brief Set the margin alpha for closed chords
	 * @param alpha
	 */
	void setMarginAlpha(float alpha);

	/**
	 * @brief Set the maximal chord size allowed as result
	 * @param maximal
	 */
	void setMaximalChordSize(int maximal);

	/**
	 * @brief Set the minimal chord duration that is processed
	 *        for support calculation
	 * @param minimal
	 */
	void setMinimalChordDuration(int minimal);

	/**
	 * @brief Set the minimal chord size for closed chords
	 * @param minimal
	 */
	void setMinimalChordSize(int minimal);

	/**
	 * @brief Set the minimal support for closed chords
	 * @param minimal
	 */
	void setMinimalSupport(int minimal);

	/**
	 * @brief Set the minimal tone duration filtered out before processing
	 * @param minimal
	 */
	void setMinimalToneDuration(int minimal);

    /********** Member functions **********/

    /**
	 * @brief Load a tone file
	 * @param data
	 * @param symb
	 * @return
	 */
    IntervalSet<Tone> load(const data& d, const symb& s);

	/**
	 * @brief Load multiple tone files
	 * @param data_symb contains all datas for the Chord Mining
	 * @return
	 */
    IntervalSet<Tone> load(const data_symb* ds);

    /**
	 * @brief Start chord mining for the given interval set
	 *        (Tone is just a class symbolizing label, unique id, and aspect)
	 * @param tones
	 */
    IntervalSequence<set<Chord> > run(const IntervalSet<Tone>& tones);

    /**
	 * @brief Save the result to the specified path
	 * @param pathname
	 */
    void save(string pathname);

	/**
	 * @brief Show the result as graph (requires DOT)
	 */
    void show();

};

#endif
