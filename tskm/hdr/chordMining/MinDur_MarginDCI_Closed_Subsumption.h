/**
 *
 * @file    MinDur_MarginDCI_Closed_Subsumption.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef MINDUR_MARGINDCI_CLOSED_SUBSUMPTION_H
#define MINDUR_MARGINDCI_CLOSED_SUBSUMPTION_H

#include <cmath>

#include "AbstractMinDurVerticalClosedItemset.h"

/**
 * @class MinDur_MarginDCI_Closed_Subsumption
 * @brief DCI_Closed implementation of the closed chord calculation
 *        (Margin decision via subsumption check)
 * @param S
 */

template <class S>
class MinDur_MarginDCI_Closed_Subsumption :
    public AbstractMinDurVerticalClosedItemset<S>
{

 private :

	list<S> sortedBySupport;
	map<BitSet, set<S> > marginCandidates;
	BitSet supportMarker;
	map<int, list<set<S> > > sortedSupport;
	vector<int> supportPerItem;

 public :

	/********** Setters **********/

	void setSupportForItems();

	/********** Member functions  **********/

	map<set<S>, BitSet > run(IntervalSequence<set<S> > c);
	bool dci_closed(list<S> closedSet, list<S> preSet, list<S> postSet,
					BitSet oldGenBitSet, int lastSupport);
	void addClosed(set<S> s, BitSet c_bs, int closedSetSupport);
	void testMargin(set<S> s, BitSet c_bs, int closedSetSupport);
	void postprocessing();
	list<S> getBottomClosure();
	bool isDuplicate(BitSet newGen, list<S> preSet);

};

#include "MinDur_MarginDCI_Closed_Subsumption.hpp"

#endif
