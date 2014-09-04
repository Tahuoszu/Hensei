/**
 *
 * @file    sequenceMerging.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef SEQUENCEMERGING_H
#define SEQUENCEMERGING_H

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "BitSet.h"
#include "Chord.h"
#include "ClosedSequence.h"
#include "functions.h"
#include "MergeSequences.h"
#include "Node.h"

using std::list;
using std::map;
using std::pair;
using std::set;
using std::vector;

/**
 * @brief Reduce sets of sequences to sets, where no contained sequence implies
 *        another one of the set (means is superset of another sequence).
 * @param in
 * @param Chord
 * @return
 */
map<set<ClosedSequence>, BitSet>
preprocessingCPO(const map<set<ClosedSequence>, BitSet>& in);

/**
 * @brief Calculate the closed partial orders
 * @param input	closed phrases
 * @return mapping from occurence vector to graph representing the closed partial order
 */
map<BitSet, Node>
closedPartialOrder(const map<set<ClosedSequence>, BitSet>& input);


#endif
