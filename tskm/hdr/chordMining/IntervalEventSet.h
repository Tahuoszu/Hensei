/**
 *
 * @file    IntervalEventSet.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    18/04/2014
 *
 */

#ifndef INTERVALEVENTSET_H
#define INTERVALEVENTSET_H

#include <algorithm>
#include <map>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include "Event.h"
#include "BitSet.h"
#include "functions.h"
#include "IntervalSet.h"

using std::map;
using std::pair;
using std::ostream;
using std::set;
using std::vector;

template <class S>
class IntervalEventSet
{

private :
    vector<int>  index;
    vector<int>  symbol;
    BitSet isStart;
    map<int, S>  mapping;

public :

    /********** Constructors **********/

    IntervalEventSet(vector<int> i, vector<int> s, BitSet is,
                     map<int, S> maps);

    IntervalEventSet(set<Event<S> > es);

    IntervalEventSet(IntervalSet<S> is);

    /********** Getters **********/

    const vector<int>& getIndex() const;

    const BitSet& getIsStart() const;

    const vector<int>& getSymbol() const;

    const map<int, S>& getMapping() const;

    /********** Operators **********/

    bool operator==(const IntervalEventSet<S>& ies);

    template <class T>
    friend ostream& operator<<(ostream& os, const IntervalEventSet<T>& ies);

    /********** Member functions **********/

    //void add(const int idx, const Event<S>& e);

    //bool add(const Event<S>& e);

    //bool addAll(set<Event<S> >& c);

    void clear();

    bool contains(const Event<S>& e);

    bool containsAll(const set<Event<S> >& es);

    int hashcode();

    bool isEmpty() const;

    //bool remove(const Event<S>& e);

    //bool removeAll(const set<Event<S> >& es);

    //bool retainAll(const set<Event<S> >& es);

    int size() const;

    bool testOrder(const IntervalEventSet<S>& ies);

};

#include "IntervalEventSet.hpp"

#endif
