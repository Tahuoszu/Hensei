/**
 *
 * @file    AbstractClosedPseudoSequence.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef ABSTRACTCLOSEDPSEUDOSEQUENCE_H
#define ABSTRACTCLOSEDPSEUDOSEQUENCE_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "Chord.h"

using std::list;
using std::map;
using std::pair;
using std::set;
using std::vector;

class AbstractClosedPseudoSequence
{

protected :

	set<Chord> frequent1Sequences;
	int minSupp;
	map<list<set<Chord> >, int>	sequences;
	map<list<set<Chord> >, int> supports;
	set<list<Chord> > closedSequences;

public :

    /********** Getters **********/

	/**
	 * @brief Returns the frequent itemsets
	 * @return
	 */
	set<Chord> getFrequent1Sequences();

    /********** Setters **********/

    /**
	 * @brief Set minimal support
	 * @param min
	 */
    void setMinimalSupport(int min);

	/**
	 * @brief If the valid items, resp sets are known a priori
	 * @param set
	 */
	void setValidFrequent1Sequences(const set<Chord>& set);

    /********** Virtual functions **********/

	/**
	 * @brief This method finds all (single item) closed sequential pattern
	 *        in the specified collection of chord set sequences
	 *        (list of chord sets)
	 * @param seq
	 * @return
	 */
	 virtual set<list<Chord> > run(const list<list<set<Chord> > >& seq) = 0;

    /********** Member functions **********/

	/**
	 * @brief Preprocessing for closed-sequential-pattern algorithm
	 *        Init global support map and all sequences
	 * @param input
	 */
	void preprocessing(const list<list<set<Chord> > >& input);

	/**
	 * @brief Returns the support of a complete db
	 * @param currentDB
	 * @return
	 */
	int support(const map<list<set<Chord> >, int>& currentDB);

	/**
     * @brief
	 * @param s1
	 * @param s2
	 * @return
	 */
	bool isSubSequence(const list<Chord>& s1, const list<set<Chord> >& s2);

	/**
     * @brief
	 * @param s1
	 * @param s2
	 * @return
	 */
	bool isSingleSubSequence(const list<Chord>& s1, const list<Chord>& s2);

	/**
	 * @brief Whether s1 is subset of s2
	 *        (for items: equals, else isSubset)
	 * @param s1
	 * @param s2
	 * @return
	 */
	bool isSubset(const Chord& s1, const set<Chord>& s2);

	/**
	 * @brief Get the local frequent itemsets from the database currentDB
	 *        and their support in the set
	 *        Note: This is not the multiset support, just the nth of occurences
	 *        in the current transactions
	 * @param currentDB
	 * @return
	 */
	map<Chord, int>
	localFrequentItems(const map<list<set<Chord> >, int>& currentDB);

	/**
	 * @brief For every DB entry the first occurence of s is searched and
	 *        the postfix pattern is copied to the projected DB
	 * @param s
	 * @param currentDB
	 * @return
	 */
	map<list<set<Chord> >, int>
	getProjectedDB(const Chord& s,
                   const map<list<set<Chord> >, int>& currentDB);

};

#endif
