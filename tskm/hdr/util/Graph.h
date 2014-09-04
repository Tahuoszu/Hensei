/**
 *
 * @file    Graph.h
 * @brief   Generate DOT file
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <sstream>

#include "Node.h"

using std::map;
using std::multimap;
using std::pair;
using std::set;

template <class E>
class Graph
{
private :
    map<E, set<E> > graph;
	set<E> sink;
	set<E> source;

	void internalReset();

public :

    /********** Constructor **********/

    Graph();

    /********** Destructor **********/

    ~Graph();

    /********** Getters **********/

	set<E> getConnected(E e);

	set<E> getIncoming(E e);

	multimap<E, E> getEdges();

	set<E> getNodes();

    set<E> getSource(E node);

    set<E> getSink(E node);

    string getString();

    /********** Member functions **********/

	void add(E m, E n);

	void add(E m);

	void clear();

	bool empty();

	void erase(E m, E n);

	void erase(E node);

	bool hasEdge(E from, E to);

	bool hasNode(E node);

};

#include "Graph.hpp"

#endif
