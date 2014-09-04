/**
 *
 * @file    Element.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    21/05/2014
 *
 */

#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <map>
#include <sstream>

using std::map;
using std::ostream;

/**
 * @class Element
 *
 * @brief An element in a sequence
 *
 * @param S
 */
template <class S>
class Element
{

private :
    int mapIndex;
    int intervalStart;
    int intervalEnd;
    int duration;
    int totalSupport;
    S symbol;

public :

    /********** Constructor **********/

    Element(int mapi, int intvs, int intve, S symb, int ts);

    /********** Destructor **********/

    ~Element();

    /********** Getters **********/

    int getInternalID() const;
    int getStart() const;
    int getEnd() const;
    int getDuration() const;
    int getTotalLength() const;
    S getSymbol() const;

    /********** Operators **********/

	template <class T>
    friend ostream& operator<<(ostream& os, const Element<T>& e);
    bool operator==(const Element<S>& e) const;
    bool operator<(const Element<S>& e) const;

    /********** Member functions **********/

    int hashCode();

};

#include "Element.hpp"

#endif
