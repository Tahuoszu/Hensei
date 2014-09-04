/**
 *
 * @file    AbstractVerticalClosedItemset.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef ABSTRACTVERTICALCLOSEDITEMSET_H
#define ABSTRACTVERTICALCLOSEDITEMSET_H

#include "AbstractClosedItemset.h"

/**
 * @class AbstractVerticalClosedItemset
 * @param S
 */

template <class S>
class AbstractVerticalClosedItemset :
    public AbstractClosedItemset<S>
{

 protected :

	map<S, BitSet> item;

 public :

    /********** Getters **********/

    const map<S, BitSet>& getItem() const;

	/********** Operators  **********/

    template <class T>
	friend const ostream&
	operator<<(const ostream& os,
               const AbstractVerticalClosedItemset<T>& avcis);

	/********** Member functions  **********/

	BitSet g(S symb);
	BitSet g(const list<S>& symb);
	bool isSubSet(BitSet a, BitSet b);
	void preprocessing(const map<set<S>, int>& maps);
	void removeInFrequent();
	list<S> sortBySupports(set<S> postSet);

	using AbstractClosedItemset<S>::support;
    int support(S symb);
	int support(const set<S>& symb);

    /********** Virtual functions  **********/


};

#include "AbstractVerticalClosedItemset.hpp"

#endif
