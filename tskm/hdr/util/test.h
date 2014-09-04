/**
 *
 * @file    test.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    21/05/2014
 *
 */

#ifndef TEST_H
#define TEST_H

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using std::list;
using std::map;
using std::ostream;
using std::pair;
using std::vector;

template <class S>
inline bool isSubSequence(const set<S>& s1, const set<S>& s2);

template <class S>
inline bool isSubSetSequence(const list<set<S> >& s1, const list<set<S> >& s2);

template <class S>
inline bool isSingleSubSetSequence(const list<S>& s1, const list<set<S> >& s2);

#include "test.hpp"

#endif
