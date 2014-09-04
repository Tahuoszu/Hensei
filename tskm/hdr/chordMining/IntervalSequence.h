/**
 *
 * @file    IntervalSequence.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    18/04/2014
 *
 */

#ifndef INTERVALSEQUENCE_H
#define INTERVALSEQUENCE_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Element.h"
#include "functions.h"
#include "IntervalEventSet.h"
#include "test.h"

using std::list;
using std::map;
using std::ostream;
using std::pair;
using std::set;
using std::string;
using std::vector;

template <class S>
class IntervalSequence
{
private :
    vector<int>   sequence;
    vector<int>   start;
    vector<int>   end;
    map<int, S>   mapping;
    map<int, int> totalSupport;

public :

    /********** Constructors **********/

    IntervalSequence();

    IntervalSequence(vector<S> seq, vector<int> s, vector<int> e);

    IntervalSequence(vector<int> seq, vector<int> s, vector<int> e,
                     map<int, S> m);

    IntervalSequence(vector<int> seq, vector<int> s, vector<int> e,
                     map<int, S> m, map<int, int> ts);

    /********** Getters **********/

    const vector<int>& getEnd() const;

    const vector<int>& getInternalSequence() const;

    const map<int, S>& getInternalMap() const;

    const map<S, int> getMap() const;

    const vector<int>& getStart() const;

    const vector<S> getSymbol() const;

    const map<int, int>& getTotalSupport() const;

    /********** Operators **********/

    template <class T>
    friend ostream& operator<<(ostream& os, const IntervalSequence<T>& is);

    /********** Member functions **********/

    Element<S> get(int index);

    bool isEmpty();

    //bool remove(const Element<S>& e);

    //bool removeAll(const set<Element<S> >& es);

    int size() const;

    int length();

    void clear();

    //bool add(const Element<S>& e);

    //void add(const int index, const Element<S>& e);

    //bool addAll(const set<Element<S> >& es);

    //bool addAll(const int index, const set<Element<S>& es);

    //bool retainAll(const set<Element<S> >& es);

    bool contains(const Element<S>& e);

    bool containsAll(const set<Element<S> >& es);

    static IntervalSequence<set<S> > convert(const IntervalEventSet<S>& intves);

    int indexOf(const Element<S>& e);

    int lastIndexOf(const Element<S>& e);

    IntervalSequence<S> subSequence(const int fromIndex, const int toIndex);

    IntervalSequence<S> restrictiveSubSequence(const int from, const int to);

    IntervalSequence<S> lazySubSequence(const int from, const int to);

    bool testOrder(const vector<int>& input);

    bool testSanity(const IntervalSequence<S>& seq);

    bool testValideIntervals(const vector<int>& start, const vector<int>& end);

};

#include "IntervalSequence.hpp"

#endif
