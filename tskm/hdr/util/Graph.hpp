/**
 *
 * @file    Graph.hpp
 * @brief   Generate DOT file
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "Graph.h"

/********** Constructor **********/

template <class E>
Graph<E>::Graph() {}

/********** Destructor **********/

template <class E>
Graph<E>::~Graph() {}

/********** Getters **********/

template <class E>
set<E> Graph<E>::getConnected(E e)
{
    set<E> s;
    if (hasNode(e))
        s.insert(graph[e].begin(), graph[e].end());
    return s;
}

template <class E>
multimap<E, E> Graph<E>::getEdges()
{
    multimap<E, E> edges;
    typename map<E, set<E> >::iterator from;
    for (from = graph.begin(); from != graph.end(); ++from) {
        set<E> linked_nodes = from->second;
        if (!linked_nodes.empty()) {
            typename set<E>::iterator to;
            for (to = linked_nodes.begin(); to != linked_nodes.end(); ++to)
                edges.insert(pair<E, E>(from->first, *to));
        }
    }
    return edges;
}

template <class E>
set<E> Graph<E>::getIncoming(E e)
{
    set<E> incoming;
    typename map<E, set<E> >::iterator it;
    for (it = graph.begin(); it != graph.end(); ++it) {
        set<E> s = (it->second);
        if (s.find(e) != s.end())
            incoming.insert(it->first);
    }
    return incoming;
}

template <class E>
set<E> Graph<E>::getNodes()
{
    set<E> nodes;
    typename map<E, set<E> >::iterator from;
    for (from = graph.begin(); from != graph.end(); ++from) {
        nodes.insert(from->first);
        set<E> linked_nodes = from->second;
        if (!linked_nodes.empty()) {
            typename set<E>::iterator to;
            for (to = linked_nodes.begin(); to != linked_nodes.end(); ++to)
                nodes.insert(*to);
        }
    }
    return nodes;
}

template <class E>
set<E> Graph<E>::getSource(E node)
{
    if (source.empty()) {
        typename map<E, set<E> >::iterator it;
        for (it = graph.begin(); it != graph.end(); ++it)
            source.insert(it->first);
        for (it = graph.begin(); it != graph.end(); ++it) {
            set<E> nodes = it->second;
            typename set<E>::iterator n;
            for (n = nodes.begin(); n != nodes.end(); ++n) {
                source.erase(*n);
            }
        }
    }
    return source;
}

template <class E>
set<E> Graph<E>::getSink(E node)
{
    if (sink.empty()) {
        set<E> nodes = getNodes();
        typename set<E>::iterator it;
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            if (graph.find(*it) == graph.end())
                sink.insert(*it);
        }
    }
    return sink;
}

template <class E>
string Graph<E>::getString()
{
    string graph_type = "digraph ";
    string graph_name = "G";
    string rankdir    = "rankdir = ";
    string dir        = "TB"; // "LR"
    string node_lab   = "node[label = \"";
    string shape      = "\", shape = ";
    string shapename  = "record"; // "circle"
    string fontname   = ", fontname = ";
    string font       = "Helvetica";
    string fontsize   = "\", fontsize = ";
    string size       = "10";

    std::stringstream os;
    os << graph_type << graph_name << " {\n";
    os << rankdir << dir <<  "\n";
    os << node_lab << shape << "]\n";

    typename set<E>::iterator node;
    for (node = getNodes().begin(); node != getNodes().end(); ++node) {
        os << node_lab << node->getLabel();
        os << fontname << font << fontsize << size << "];\n";
    }

    typename multimap<E, E>::iterator edge;
    for (edge = getEdges().begin(); edge != getEdges().end(); ++edge)
        os << edge->first  << " -> " << edge->second << ";\n";

    os << "}\n";

    return os.str();
}


/********** Member functions **********/

template <class E>
void Graph<E>::internalReset()
{
    sink.clear();
    source.clear();
}

template <class E>
void Graph<E>::add(E m, E n)
{
    if (graph[m].empty())
        graph.insert(pair<E, set<E> >(m, set<E>()));
    graph[m].insert(n);
    internalReset();
}

template <class E>
void Graph<E>::add(E m)
{
    if (graph[m].empty())
        graph.insert(pair<E, set<E> >(m, set<E>()));
    internalReset();
}

template <class E>
void Graph<E>::clear()
{
    graph.clear();
    internalReset();
}

template <class E>
bool Graph<E>::empty()
{
    return graph.empty();
}

template <class E>
void Graph<E>::erase(E m, E n)
{
    graph[m].erase(n);
    internalReset();
}

template <class E>
void Graph<E>::erase(E node)
{
    graph.erase(node);
    internalReset();
}

template <class E>
bool Graph<E>::hasEdge(E from, E to)
{
    set<E> fromset = graph[from];
    if (!fromset.empty())
        return (fromset.find(to) != fromset.end());
    else
        return false;
}

template <class E>
bool Graph<E>::hasNode(E node)
{
    typename map<E, set<E> >::iterator it;
    for (it = graph.begin(); it != graph.end(); ++it)
        if (it->first == node)
            return true;
    return false;
}
