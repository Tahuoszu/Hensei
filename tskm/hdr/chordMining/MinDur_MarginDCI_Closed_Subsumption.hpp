/**
 *
 * @file    MinDur_MarginDCI_Closed_Subsumption.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "MinDur_MarginDCI_Closed_Subsumption.hpp"

/********** Setters **********/

template <class S>
void MinDur_MarginDCI_Closed_Subsumption<S>::setSupportForItems()
{
	supportPerItem.resize(sortedBySupport.size());
	int i = 0;
	typename list<S>::iterator it;
	for (it = sortedBySupport.begin(); it != sortedBySupport.end(); ++it)
		supportPerItem[i++] = support(*it);
}

/********** Member functions **********/

template <class S>
map<set<S>, BitSet >
MinDur_MarginDCI_Closed_Subsumption<S>::run(const IntervalSequence<set<S> >& c)
{

	preprocessing(c);

	set<S> postSet;
	typename map<S, BitSet >::iterator it;
	for (it = item.begin(); it != item.end(); ++iter)
		postSet.insert(it->first);

	// Remove bottom closure from symbol list
	list<S> bottomClosure = getBottomClosure();
	typename list<S>::iterator bc_it;
	for (bc_it = bottomClosure.begin();
		 bc_it != bottomClosure.end(); ++bc_it)
		postSet.erase(*bc_it);

	sortedBySupport = sortedBySupport(postSet);

	setSupportForItems();

	int bottomSupport = std::accumulate(support.begin(), support.end(), 0);

	// Start calculation
	dci_closed(bottomClosure, list<S>(), list<S>(sortedBySupport),
			   g(bottomClosure), bottomSupport);

	// if (bottomSupport >= minSupport) {
	testMargin(set<S>(bottomClosure), g(bottomClosure), bottomSupport);
	//}

	postprocessing();
	return getResult();

}

template <class S>
bool MinDur_MarginDCI_Closed_Subsumption<S>::dci_closed(list<S> closedSet,
													 list<S> preSet,
													 list<S> postSet,
													 BitSet oldGenBitSet,
													 int lastSupport)
{

	int currentSupport;
	BitSet newGenBitSet;
	bool wasMargin  = 1;
	double lastSupp = ((float)lastSupport) * beta;

	while(!postSet.empty()) {  // line 2
		S i = postSet.front(); // line 3
		postSet.pop_front();   // line 4
		list<S> newGen = list<S>(closedSet);
		newGen.insert(i);      // line 5
		// Buffer
		newGenBitSet = oldGenBitSet;
		BitSet bitSet = g(i);
		for (int k = 0; k < bitSet.size(); k++)
			newGenBitSet[k] &= bitSet[k];
	    //newGenBitSet = g(newGen);
		currentSupport = support(newGenBitSet);

		//bool toAdd = 0;
		if((currentSupport >= minSupport) &&
		   (!isDuplicate(newGenBitSet,preSet))) { // line 6
			wasMargin &= (currentSupport < lastSupp);
			//toAdd = 1;
			list<S> closedSetNew = newGen;        // line 7
			list<S> postSetNew	 = list<S>();     // line 8
			typename list<S>::iterator it;
			for (it = postSet.begin(); it != postSet.end(); ++it) { // line 9
				if (isSubSet(newGenBitSet, g(*it)))                 // line 10
					closedSetNew.insert(*it);                       // line 11
				else                                                // line 12
					postSetNew.insert(*it);                         // line 13
			}                                                       // line 14

			//dci_closed(closedSetNew, list<S>(preSet), postSetNew,
			//		   newGenBitSet, currentSupport);			    // line 17
			bool test = (dci_closed(closedSetNew, list<S>(preSet), postSetNew,
									newGenBitSet, currentSupport));	// line 17
			addClosed(set<S>(closedSetNew), newGenBitSet, currentSupport);
			if(test)
				testMargin(set<S>(closedSetNew),
						   newGenBitSet, currentSupport);           // line 16

			preSet.add(i);                                          // line 18
		}                                                           // line 19
	}

	return wasMargin;                                               // line 20
}

template <class S>
void MinDur_MarginDCI_Closed_Subsumption<S>::addClosed(set<S> s, BitSet c_bs,
													int closedSetSupport)
{
	int cSupport = support(c_bs);
	if (!supportMarker[cSupport]) {
		sortedSupport.insert(pair<int, list<set<S> > >(cSupport,
													   list<set<S> >()));
		supportMarker[cSupport] = 1;
	}
	sortedSupport[cSupport].insert(s);
}

template <class S>
void MinDur_MarginDCI_Closed_Subsumption::testMargin(set<S> s, BitSet c_bs,
													 int closedSetSupport)
{
	if (beta != 1) {
		//test = 1;
		int cSupport = support(c_bs);
		int lowerThreshold = std::ceil((cSupport) * beta);
		for (int i = 0; i < supportMarker.size() && i < cSupport; i++) {
			if (supportMarker[i]) {
				list<set<S> > &ss = sortedSupport[i];
				typename list<set<S> >::iterator it;
				for (it = ss.begin(); it != ss.end(); ++it) {
					bool containsAll = 1;
					typename set<S>::iterator set_it;
					for (set_it = it->begin(); set_it != it->end(); ++set_it) {
						if (it->find(*set_it) == it->end()) {
							containsAll = 0;
							break;
						}
					}
					if (containsAll)
						return;
				}
			}
		}
	}
	marginCandidates.insert(pair<BitSet, set<S> >(c_bs, set));
}

template <class S>
void MinDur_MarginDCI_Closed_Subsumption<S>::postprocessing()
{
	typename map<BitSet, set<S> >::iterator it;
	for (it = marginCandidates.begin(); it != marginCandidates.end(); ++it)
		addResult(it->second, support(it->first), it->first);
}

template <class S>
list<S> MinDur_MarginDCI_Closed_Subsumption<S>::getBottomClosure()
{
	list<S> bottomClosure;
	typename map<S, BitSet >::iterator it;
	for (it = item.begin(); it != item.end(); ++it) {
		int counter = std::count((it->second).begin(), (it->second).end(); 1);
		int sup_size = support.size();
		if (counter == sup_size)
			bottomClosure.insert(it->first);
	}
	return bottomClosure;
}

template <class S>
bool MinDur_MarginDCI_Closed_Subsumption<S>::isDuplicate(BitSet newGen,
													  list<S> preSet)
{
	typename list<S>::iterator it;
	for (it = preSet.begin(); it != preSet.end(); ++it)
		if (isSubSet(newGen, g(*it)))
			return 1;
	return 0;
}
