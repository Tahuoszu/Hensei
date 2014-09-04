/**
 *
 * @file    functions.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    21/05/2014
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::set;
using std::string;
using std::vector;

/**
 * @brief Convert an integer to string
 * @param num
 * @return string
 */
string intToString(int num);

/**
 * @brief Calculate duration between two points
 * @param x
 * @param y
 * @return int
 */
int duration(int x, int y);


/**
 * @brief Test if a set contains all elements of another set
 * @param st1 a set (bigger than st2)
 * @param st2 a subset
 * @return bool
 */
template <class T>
bool containsSet(const set<T>& st1, const set<T>& st2);

/**
 * @brief Generate a random number from 1 to range
 * @param range
 * @return int
 */
int randomNumber(int range);

/**
 * @brief Print a set of type T elements
 * @param set
 * @return
 */
template <class T>
void print_set(const set<T>& s);

/**
 * @brief Print a vector of type T elements
 * @param vector
 * @return
 */
template <class T>
void print_vector(const vector<T>& v);

/**
 * @brief Print a map S of type T elements
 * @param map
 * @return
 */
template <class S, class T>
void print_map(const map<S, T>& m);

/**
 * @brief Return the indices of the elements after sorting to ascending order
 * @param vector
 * @return
 */
template <class T>
vector<T> getIndexOfSort(const vector<T>& v);

/**
 * @brief Return the sublist between fromIndex (inclusive)
 *        to toIndex (exclusive)
 * @param fromIndex
 * @param toIndex
 * @return
 */
template <class T>
list<T> subList(const list<T>& liste, int fromIndex, int toIndex);

/**
 * @brief Test if the specified list is a subList of the superList
 * @param subList
 * @param superList
 * @return
 */
template <class T>
bool isSubList(const list<T>& subList, const list<T>& superList);

/**
 * @brief Test if a map contains the specified key
 * @param map
 * @param key
 * @return
 */
template <class T>
bool containsKey(const map<int, T>& m, int key);

#include "functions.hpp"

#endif
