/**
 *
 * @file    AbstractClosedItemset.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef ABSTRACTCLOSEDITEMSET_H
#define ABSTRACTCLOSEDITEMSET_H

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#include "functions.h"

using std::list;
using std::map;
using std::pair;
using std::set;
using std::vector;

/**
 * @class AbstractClosedItemset
 * @brief Closed Chord Calculation with integrated minimal Duration
 *        for a chord occurence and its support calculation.
 * @param S
 */
template <class S>
class AbstractClosedItemset
{

 protected :

	float beta;
	int minSupport;
	int supportLength;
	list<set<S> > resultItemset;
	list<BitSet> resultBitSet;

 public :

	/********** Getters **********/

	/**
	 * @brief Prepare result for output
	 * @return
	 */
	map<set<S>, BitSet> getResult();

	/**
	 * @brief Returns the support for each corresponding bit in bitset
	 * @return
	 */
	const vector<int> getSupport() const;

	/**
	 * @brief Get result with support instead of occurence bitset
	 * @return
	 */
	map<set<S>, int> getSupportMap();

	/********** Setters **********/

    /**
	 * @brief Set the minimal support
	 * @param min
	 */
	void setMinimalSupport(int min);

    /**
	 * @brief Set the margin alpha
	 * @param alpha
	 */
	void setAlpha(float alpha);

	/********** Member functions  **********/

	/**
	 * @brief Add an itemset to the result
	 * @param closedSet
	 * @param support
	 * @param transactions
	 */
	void addResult(const set<S>& closedSet, int support,
                   const BitSet& transactions);

    /**
	 * @brief Test, if the corresponding set is margin-closed
	 *        for the specified superset via it's support
	 * @param superset
	 * @param set
	 * @return bool
	 */
	bool isMargin(int superset, int set);

	/**
	 * @brief Support of a transaction mask
	 * @param sym
	 * @return
	 */
	int support(const BitSet& vb);

	/********** Virtual functions  **********/

    /**
	 * @brief Transactions containing item
	 * @param sym
	 * @return
	 */
	virtual BitSet g(S symb) = 0;

    /**
	 * @brief Transactions containing itemset
	 * @param sym
	 * @return
	 */
	virtual BitSet g(const list<S>& symb) = 0;

	/**
	 * @brief Transform the given HashMap of transactions
	 *        and their support to internal representation
	 * @param map
	 * @return
	 */
	virtual void preprocessing(const map<set<S>, int>& maps) = 0;

	/**
	 * @brief Call all necessary methods to compute closed itemsets
	 * @param m
	 * @return
	 */
	virtual map<set<S>, BitSet> run(const map<set<S>, int>&  m) = 0;

    /**
	 * @brief Support of an item
	 * @param sym
	 * @return
	 */
	virtual int support(S symb) = 0;

    /**
	 * @brief Support of an itemset
	 * @param sym
	 * @return
	 */
	virtual int support(const set<S>& symb) = 0;

};

#include "AbstractClosedItemset.hpp"

#endif
