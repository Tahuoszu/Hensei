/**
 *
 * @file    AbstractMinDurClosedItemset.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef ABSTRACTMINDURCLOSEDITEMSET_H
#define ABSTRACTMINDURCLOSEDITEMSET_H

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#include "functions.h"
#include "IntervalSequence.h"

using std::list;
using std::map;
using std::pair;
using std::set;
using std::vector;

/**
 * @class AbstractMinDurClosedItemset
 * @brief Closed Chord Calculation with integrated minimal Duration
 *        for a chord occurence and its support calculation.
 * @param S
 */
template <class S>
class AbstractMinDurClosedItemset
{

 protected :

	float beta;
	int minSupport;
	vector<int> supp;
	map<set<S>, BitSet> resultMap;

 public :

	/********** Getters **********/

	const map<set<S>, BitSet>& getResult() const;
	map<set<S>, int> getSupportMap();

	/********** Setters **********/

	void setMinimalSupport(int min);
	void setAlpha(float alpha);

	/********** Member functions  **********/

	void addResult(const set<S>& closedSet,
                   int support, const BitSet& transactions);
	bool isMargin(int superset, int set);
	int support(const BitSet& vb);

	/********** Virtual functions  **********/

	virtual BitSet g(S symb) = 0;
	virtual BitSet g(const list<S>& symb) = 0;
	virtual void preprocessing(const IntervalSequence<set<S> >& maps) = 0;
	virtual map<set<S>, BitSet> run(const IntervalSequence<set<S> >& c) = 0;
	virtual int support(S symb) = 0;
	virtual int support(const set<S>& symb) = 0;

};

#include "AbstractMinDurClosedItemset.hpp"
#endif
