/**
 *
 * @file    PhraseMiner.h
 * @brief   Phrase mining steps of the TSKM
 *          Sequence mining, closed phrase mining and sequence merging
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef PHRASEMINER_H
#define PHRASEMINER_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "Chord.h"
#include "ClosedSequence.h"
#include "IntervalSequence.h"
#include "io.h"
#include "MarginDCI_Closed_Intersection.h"
#include "Node.h"
#include "PseudoBide.h"
#include "prepostprocessing.h"
#include "sequenceMerging.h"

using std::list;
using std::map;
using std::set;
using std::vector;

class PhraseMiner
{

private :
	// Sequence Mining
	int sequenceWindowSize;
	int minimalClosedSequenceSupport;
    // Phrase Mining
	int minimalClosedPhraseSupport;
	double alphaForClosedPhrases;
    // Result : sequenceMining
	set<list<Chord> > closedSequences;
	// Result : phraseMining
	map<set<ClosedSequence>, BitSet> closedPhrases;
	map<set<ClosedSequence>, int> closedPhrasesWithSupport;
	// Result : sequenceMerging
	map<BitSet, Node> phraseLattice;

public :

    /********** Constructor **********/

    PhraseMiner();

    /********** Destructor **********/

    ~PhraseMiner();

    /********** Getters **********/

    map<set<ClosedSequence>, BitSet > getClosedPhrases();

    map<set<ClosedSequence>, int> getClosedPhrasesWithSupport();

    set<list<Chord> > getClosedSequences();

    map<BitSet, Node> getPhraseLattice();

    /********** Setters **********/

    void setAlphaForClosedPhrases(float alpha);

    void setMinimalClosedPhraseSupport(int minCPS);

    void setMinimalClosedSequenceSupport(int minCSS);

    void setSequenceWindowSize(int seqWinSize);

    /********** Member functions **********/

    IntervalSequence<set<Chord> > load(const data_symb* ds);

	/**
	 * @brief Run PhraseMiner for the specified ChordsetSequence.
	 *        You can either load an altered chord file or
	 *        use a chord mining result directly.
	 * @param seq : Sequence of chord sets
	 * @return
	 */
	 map<BitSet, Node> run(const IntervalSequence<set<Chord> >& seq);

	/**
	 * @brief Searching for closed sequences
	 * @param seq
	 * @return A horizontal representation of phrases :
	 *         set of closed sequences mapped to the number of
	 *         the occurence of those sets
	 */
	map<set<ClosedSequence>, int>
	closedSequenceMining(const IntervalSequence<set<Chord> >& seq);

	/**
	 * @brief Mining margin closed phrases
	 * @param phrases
	 * @return
	 */
	map<set<ClosedSequence>, BitSet >
    closedPhraseMining(const map<set<ClosedSequence>, int>& phrases);

	/**
	 * @brief Creating closed partial orders for each concept
	 * @param closedPhrases
	 * @return
	 */
	map<BitSet, Node>
	sequenceMerging(const map<set<ClosedSequence>, BitSet>& closedPhrases);

};

#endif
