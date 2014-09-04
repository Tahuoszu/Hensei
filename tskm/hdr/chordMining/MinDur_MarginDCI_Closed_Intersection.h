/**
 *
 * @file    MinDur_MarginDCI_Closed_Intersection.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef MINDUR_MARGINDCI_CLOSED_INTERSECTION_H
#define MINDUR_MARGINDCI_CLOSED_INTERSECTION_H

#include "AbstractMinDurVerticalClosedItemset.h"

/**
 * @class MinDur_MarginDCI_Closed_Intersection
 * @brief DCI_Closed implementation
 *        Independent of underlying data
 * @param S
 */

template <class S>
class MinDur_MarginDCI_Closed_Intersection :
    public AbstractMinDurVerticalClosedItemset<S>
{

 private :

	list<S> sortedBySupport;
	vector<int> supportPerItem;

 public :

	/********** Setters **********/

	void setSupportForItems();

	/********** Member functions  **********/

	map<set<S>, BitSet> run(const IntervalSequence<set<S> >& c);

	bool dci_closed(list<S> closedSet, list<S> preSet, list<S> postSet,
					BitSet oldGenBitSet, int lastSupport);

	void testMargin(set<S> closedSet, BitSet closedTransactions,
                    int closedSetSupport);

	list<S> getBottomClosure();

	bool isDuplicate(BitSet newGen, list<S> preSet);

};

#include "MinDur_MarginDCI_Closed_Intersection.hpp"

#endif
