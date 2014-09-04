/**
 *
 * @file    Element.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "Element.h"

/********** Constructor **********/

template <class S>
Element<S>::Element(int mapi, int intvs, int intve, S symb, int ts) :
    mapIndex(mapi), intervalStart(intvs), intervalEnd(intve),
    duration(intvs + intve - 1), totalSupport(ts)
{
    symbol = symb;
}

/********** Destructor **********/

template <class S>
Element<S>::~Element() {}

/********** Getters **********/

template <class S>
int Element<S>::getInternalID() const
{
    return mapIndex;
}

template <class S>
int Element<S>::getStart() const
{
    return intervalStart;
}

template <class S>
int Element<S>::getEnd() const
{
    return intervalEnd;
}

template <class S>
int Element<S>::getDuration() const
{
    return duration;
}

template <class S>
int Element<S>::getTotalLength() const
{
    return totalSupport;
}

template <class S>
S Element<S>::getSymbol() const
{
    return symbol;
}

/********** Operators **********/

template <class T>
ostream& operator<<(ostream& os, const Element<T>& e)
{
    os << "------------------ Element ------------------" << "\n";
    os << "(" << e.getSymbol() << " [" << e.getStart() << "," << e.getEnd() \
       << "]" << ")" << "\n";
    return os;
}

template <class S>
bool Element<S>::operator==(const Element<S>& e) const
{
    return (e->getInternalID == mapIndex);
}

template <class S>
bool Element<S>::operator<(const Element<S>& e) const
{
    return (intervalStart < e.getStart());
}

/********** Member functions **********/

template <class S>
int Element<S>::hashCode()
{
    return mapIndex;
}
