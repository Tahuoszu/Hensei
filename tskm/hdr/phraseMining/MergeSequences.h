/**
 *
 * @file    MergeSequences.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef MERGESEQUENCES_H
#define MERGESEQUENCES_H

#include <algorithm>
#include <iterator>
#include <iostream>
#include <list>
#include <map>
#include <set>

#include "Chord.h"
#include "ClosedSequence.h"
#include "Graph.h"
#include "Node.h"

using std::list;
using std::map;
using std::pair;
using std::set;

/**
 * @brief Creates a single closed partial order from a set of sequences.
 *        For creating multiple partial orders out of a a set of sequences,
 *        see ClosedPartialOrder
 * @param Chord
 */
class MergeSequences
{

private :

    Graph<Node> graph;
	map<list<Chord>, map<int, Node> > pointers;

public :

    /**
     * @brief Create the closed partial order for the specified set of sequences
     * @param sequences
     * @return closed partial order
     */
    Node run(const set<ClosedSequence>& sequences);

	/**
	 * @brief Merge the given set of sequences
	 * @param sequences
	 */
    void mergeSequences(const set<ClosedSequence>& sequences);

	/**
	 * @brief Check whether a merge at index i in sequence seq1
	 *        and index j in seq2 is path preserving
	 * @param sequences
	 * @param seq1
	 * @param i
	 * @param seq2
	 * @param j
	 * @return bool
	 */
	bool pathPreserving(const set<ClosedSequence>& sequences,
                        const list<Chord>& seq1, int i,
                        const list<Chord>& seq2, int j);

	/**
	 * @brief Whether the specified sequence s1 is a subset of
	 *        the specified sequence s2
	 * @param s1
	 * @param s2
	 * @return bool
	 */
	bool isSubSequence(const list<Chord>& s1, const list<Chord>& s2);

	/**
	 * @brief Prepare internal pointers
	 * @param sequences
	 */
	void preprocessing(const set<ClosedSequence>& sequences);

	/**
	 * @brief Adds a node
	 * @param map
	 * @param i
	 * @param c
	 */
	void add(map<int, Node> maps, int i, Node c);

	/**
     * @brief Add new edge between the specified nodes
     * @param s1
     * @param s2
     */
    void add(Node s1, Node s2);

};

#endif
