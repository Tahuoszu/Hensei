/**
 *
 * @file    MarginDCI_Closed_Intersection.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef MARGINDCI_CLOSED_INTERSECTION_H
#define MARGINDCI_CLOSED_INTERSECTION_H

#include "AbstractVerticalClosedItemset.h"

/**
 * @class MarginDCI_Closed_Intersection
 * @brief MarginDCI_Closed implementation using intersection with single items
 *        to obtain direct supersets for margin decision
 *        Independent of underlying data
 * @param S
 */

template <class S>
class MarginDCI_Closed_Intersection :
    public AbstractVerticalClosedItemset<S>
{

 private :

	list<S> sortedBySupport;
	vector<int> supportPerItem;

 public :

	/********** Setters **********/

	void setSupportForItems();

	/********** Member functions  **********/

	map<set<S>, BitSet> run(const map<set<S>, int>&  m);
	bool dci_closed(list<S> closedSet, list<S> preSet, list<S> postSet,
					BitSet oldGenBitSet, int lastSupport);
	void testMargin(set<S> closedSet, BitSet closedTransactions,
                    int closedSetSupport);
	list<S> getBottomClosure();
	bool isDuplicate(BitSet newGen, list<S> preSet);

};

#include "MarginDCI_Closed_Intersection.hpp"

#endif
