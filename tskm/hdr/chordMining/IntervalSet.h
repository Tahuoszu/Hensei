/**
 *
 * @file    IntervalSet.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#ifndef INTERVALSET_H
#define INTERVALSET_H

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Interval.h"

using std::map;
using std::pair;
using std::ostream;
using std::set;
using std::string;
using std::vector;

/**
 * @class IntervalSet
 *
 * @brief An IntervalSet represents an unordered set of elements consisting of
 *	  an interval and an attached symbol.
 *	  Internally those elements are organized in arrays, so simple adding is
 *	  not cheap. Iterator is provided for convenience (means not for speed).
 *	  Note: This does not check for duplicates
 *
 * @param <S>
 */
template <class S>
class IntervalSet
{

private :
    vector<int> start;   // Interval start points
    vector<int> end;     // Interval end points
    vector<int> symbol;  // Symbol id
    map<int, S> mapping; // Mapping from symbol id to symbol

public :

    /********** Constructors **********/

	/**
     * @brief Default constructor
     * @param S
     */
	IntervalSet();

    /**
     * @brief Creates an IntervalSet.
     *        (start[i], end[i], symbols[i]) represents interval "i"
     * @param start	start points
     * @param end	end points
     * @param symbols	symbols
     */
    IntervalSet(vector<int> s, vector<int> e, vector<S> symbols);

    /**
     * @brief Creates an IntervalSet.
     *	      (start[i], end[i], symbol[j], mapping[j]) represents interval
     *	      "i" with symbol "s", where j is the id for the attached symbol "s"
     * @param start
     * @param end
     * @param symbol
     * @param mapping
     */
    IntervalSet(vector<int> s, vector<int> e, vector<int> symbols,
                map<int, S> mapp);

    /**
     * @brief See Interval class
     * @param intvs
     */
    IntervalSet(set<Interval<S> > intvs);

    /********** Destructor **********/

    ~IntervalSet();

    /********** Getters **********/

    /**
     * @brief Get start points
     * @return start
     */
    const vector<int>& getStart() const;

    /**
     * @brief Get end points
     * @return end
     */
    const vector<int>& getEnd() const;

    /**
     * @brief Get symbols
     * @return symbol
     */
    const vector<int>& getSymbol() const;

    /**
     * @brief Get "symbol id to symbol" mapping
     * @return mapping
     */
    const map<int, S>& getMap() const;

    /**
     * @brief Get all interval start and end points (sorted by start points)
     *		  for the given id
     * @param sid "symbol id"
     * @return map
     */
    map<int, int> get(int sid) const;

    /********** Setters **********/

    /**
     * @brief Set start points
     * @param start
     */
    void setStart(int s[]);

    /**
     * @brief Set end points
     * @param end
     */
    void setEnd(int e[]);

    /**
     * @brief Set symbols
     * @param symbol
     */
    void setSymbol(vector<S> symbol);

    /********** Operators **********/

    /**
     * @brief Operator ==
     * @param intvs Interval set
     * @return bool
     */
    bool operator==(const IntervalSet& intvs);

    /**
     * @brief Operator <<
     * @param os  ostream
     * @param is  IntervalSet<T>
     * @return os ostream
     */
    template <class T>
    friend ostream& operator<<(ostream& os, const IntervalSet<T>& is);

    /********** Member functions **********/

    /**
     * @brief Adds all intervals to this interval set. Duplicates are allowed.
     * @param intvs : Interval set
     * @return bool
     */
    bool addAll(set<Interval<S> > intvs);

    /**
     * @brief Returns the number of intervals.
     * @return size
     */
    int size() const;

    /**
     * @brief Whether this set is empty.
     * @return bool
     */
    bool isEmpty();

    /**
     * @brief Whether this set contains the specified object.
     * @param intv Interval
     * @return bool
     */
    bool contains(const Interval<S>& intv);

    // bool insert(const Interval& intv);

    // bool erase(const Interval& intv);

    /**
     * @brief Whether the set contains the specified objects.
     * @param intvs Interval Set
     * @return bool
     */
    bool containsAll(const set<Interval<S> >& intvs);

    // bool removeAll(const set<S>& c);

    // bool retainAll(const set<S>& c);

    /**
     * @brief Clears this interval set.
     */
    void clear();

    /**
     * @brief Get all intervals completely contained in [stintv, eintv].
     * @param stintv	start point
     * @param eintv		end point (exclusive)
     * @return intvs	Interval Set
     */
    IntervalSet<S> subSet(int stintv, int eintv);

    // const int hashCode();

};

#include "IntervalSet.hpp"

#endif
