/**
 *
 * @file    Event.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <map>
#include <sstream>

using std::map;
using std::ostream;

/**
 * @class Event
 *
 * @brief An event in a set of event
 *
 * @param S
 */
template <class S>
class Event
{

private :
    int internalIndex;
    bool started;
    int symbol;
    S mapping;

public :

    /********** Constructors **********/

    Event();
    Event(int index, int is, int symb, S mapp);

    /********** Destructor **********/

    ~Event();

    /********** Getters **********/

    int getIndex() const;
    bool isStart() const;
    int getSymbol() const;
    S getmapping() const;

    /********** Operators **********/

	template <class T>
    friend ostream& operator<<(ostream& os, const Event<T>& e);
    bool operator==(const Event& e) const;
    bool operator<(const Event& e) const;

    /********** Member functions **********/

    int hashCode();

};

#include "Event.hpp"

#endif
