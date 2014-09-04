/**
 *
 * @file    MarginDCI_Closed_Intersection.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "MarginDCI_Closed_Intersection.h"

/********** Setters **********/

template <class S>
void MarginDCI_Closed_Intersection<S>::setSupportForItems()
{
	supportPerItem.resize(sortedBySupport.size());
	int i = 0;
	typename list<S>::iterator it;
	for (it = sortedBySupport.begin(); it != sortedBySupport.end(); ++it)
		supportPerItem[i++] = this->support(*it);
}

/********** Member functions **********/

template <class S>
map<set<S>, BitSet>
MarginDCI_Closed_Intersection<S>::run(const map<set<S>, int>&  m)
{

	this->preprocessing(m);

	set<S> postSet;
	typename map<S, BitSet>::iterator it;
	for (it = this->item.begin(); it != this->item.end(); ++it)
		postSet.insert(it->first);

	// Remove bottom closure from symbol list
	list<S> bottomClosure = getBottomClosure();
	typename list<S>::iterator bc_it;
	for (bc_it = bottomClosure.begin();
		 bc_it != bottomClosure.end(); ++bc_it)
		postSet.erase(*bc_it);

	sortedBySupport = this->sortBySupports(postSet);

	setSupportForItems();

	int bottomSupport = this->supportLength;
	if (bottomSupport >= this->minSupport)
		testMargin(set<S>(bottomClosure.begin(), bottomClosure.end()),
                   this->g(bottomClosure), bottomSupport);

	// Start calculation
	dci_closed(bottomClosure, list<S>(), list<S>(sortedBySupport),
			   this->g(bottomClosure), bottomSupport);

	return this->getResult();

}

template <class S>
bool MarginDCI_Closed_Intersection<S>::\
dci_closed(list<S> closedSet, list<S> preSet, list<S> postSet,
           BitSet oldGenBitSet, int lastSupport)
{

	int currentSupport;
	BitSet newGenBitSet;
	bool wasMargin = true;
	float lastSupp = (float)lastSupport * this->beta;
	std::cout << "lastSupp = " << lastSupp << std::endl;

	while(!postSet.empty()) {  // line 2
		S i = postSet.front(); // line 3
		postSet.pop_front();   // line 4
		list<S> newGen = list<S>(closedSet);
		newGen.push_back(i);      // line 5
		// Buffer
		newGenBitSet = oldGenBitSet;
		newGenBitSet.bsand(this->g(i));
	    //newGenBitSet = g(newGen);
		currentSupport = this->support(newGenBitSet);

		//bool toAdd = false;
		if((currentSupport >= this->minSupport) &&
		   (!isDuplicate(newGenBitSet,preSet))) { // line 6
			wasMargin &= (currentSupport < lastSupp);
			//toAdd = true;
			list<S> closedSetNew = newGen;        // line 7
			list<S> postSetNew	 = list<S>();     // line 8
			typename list<S>::iterator it;
			for (it = postSet.begin(); it != postSet.end(); ++it) { // line 9
				if (this->isSubSet(newGenBitSet, this->g(*it)))     // line 10
					closedSetNew.push_back(*it);                    // line 11
				else                                                // line 12
					postSetNew.push_back(*it);                      // line 13
                //std::cout << this->isSubSet(newGenBitSet, this->g(*it)) << " ";
			}                                                       // line 14
			                                                        // line 16
            //std::cout << std::endl;

            std::cout << "closedSetNew = " << closedSetNew.size() << std::endl;
            std::cout << "preSet       = " << preSet.size() << std::endl;
            std::cout << "postSetNew   = " << postSetNew.size() << std::endl;
            std::cout << "newGenBitSet = " << newGenBitSet << std::endl;
            std::cout << "currentSupport = " << currentSupport << std::endl;
			if (dci_closed(closedSetNew, list<S>(preSet), postSetNew,
						   newGenBitSet, currentSupport))
				testMargin(set<S>(closedSetNew.begin(), closedSetNew.end()),
						   newGenBitSet, currentSupport);           // line 17
			preSet.push_back(i);                                    // line 18
		}                                                           // line 19
	}                                                               // line 20
	std::cout << "wasMargin = " << wasMargin << std::endl;
	std::cout << "***************************" << std::endl;
	exit(1);
	return wasMargin;                                               // line 21
}

template <class S>
void MarginDCI_Closed_Intersection<S>::\
testMargin(set<S> closedSet, BitSet closedTransactions, int closedSetSupport)
{
	if (this->beta != 1) {
		float closedSupp = (float)closedSetSupport * this->beta;
		int i = supportPerItem.size() - 1;
		typename list<S>::reverse_iterator it;
		for (it = sortedBySupport.rbegin(); it != sortedBySupport.rend(); ++it)
        {
			if (closedSet.find(*it) != closedSet.end())
				continue;
			if (supportPerItem[i--] < closedSupp)
				break;
			BitSet bs = this->g(*it);
			bs.bsand(closedTransactions);
			float currentSupport = this->support(bs);
			if ((currentSupport >= this->minSupport) &&
				((float)currentSupport >= closedSupp))
				return;
		}
	}
	this->addResult(closedSet, closedSetSupport, closedTransactions);
}

template <class S>
list<S> MarginDCI_Closed_Intersection<S>::getBottomClosure()
{
	list<S> bottomClosure;
	int counter = 0;
	typename map<S, BitSet>::iterator it;
	for (it = this->item.begin(); it != this->item.end(); ++it) {
		counter = (it->second).cardinality();
		if (counter == this->supportLength)
			bottomClosure.push_back(it->first);
	}
	return bottomClosure;
}

template <class S>
bool MarginDCI_Closed_Intersection<S>::\
isDuplicate(BitSet newGen, list<S> preSet)
{
	typename list<S>::iterator it;
	for (it = preSet.begin(); it != preSet.end(); ++it)
		if (this->isSubSet(newGen, this->g(*it)))
			return true;
	return false;
}
