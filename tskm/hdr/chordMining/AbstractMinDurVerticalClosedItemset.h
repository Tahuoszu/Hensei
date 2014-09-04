/**
 *
 * @file    AbstractMinDurVerticalClosedItemset.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef ABSTRACTMINDURVERTICALCLOSEDITEMSET_H
#define ABSTRACTMINDURVERTICALCLOSEDITEMSET_H

#include "AbstractMinDurClosedItemset.h"

/**
 * @class AbstractMinDurVerticalClosedItemset
 * @param S
 */

template <class S>
class AbstractMinDurVerticalClosedItemset :
    public AbstractMinDurClosedItemset<S>
{

 protected :

	map<S, BitSet> item;
	int minDuration;

 public :

    /********** Getters **********/

    const map<S, BitSet >& getItem() const;

	/********** Setters **********/

	void setMinDuration(int minDur);

	/********** Operators  **********/

    template <class T>
	friend const ostream&
	operator<<(const ostream& os,
               const AbstractMinDurVerticalClosedItemset<T>& amnvcis);

	/********** Member functions  **********/

	BitSet g(S symb);
	BitSet g(const list<S>& symb);
	bool isSubSet(BitSet a, BitSet b);
	void preprocessing(const IntervalSequence<set<S> >& maps);
	void removeInFrequent();
	list<S> sortBySupports(set<S> postSet);

	using AbstractMinDurClosedItemset<S>::support;
	int support(S symb);
	int support(const set<S>& symb);

};

#include "AbstractMinDurVerticalClosedItemset.hpp"

#endif
