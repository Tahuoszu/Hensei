/**
 *
 * @file    Interval.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "Interval.h"

/********** Constructor **********/

template <class S>
Interval<S>::Interval(int starti, int endi, S symboli) :
    start(starti), end(endi), symbol(symboli) {}

/********** Destructor **********/

template <class S>
Interval<S>::~Interval() {}

/********** Getters **********/

template <class S>
int Interval<S>::getStart() const
{
    return start;
}

template <class S>
int Interval<S>::getEnd() const
{
    return end;
}

template <class S>
S Interval<S>::getSymbol() const
{
    return symbol;
}

/********** Operator **********/

template <class T>
ostream& operator<<(ostream& os, const Interval<T>& i)
{
    os << "------------------ Interval ------------------" << "\n";
    os << "(" << i.getSymbol() << " [" << i.getStart() << "," << i.getEnd() \
       << "]" << ")" << "\n";
    return os;
}

template <class S>
bool Interval<S>::operator==(const Interval<S>& i) const
{
    return (i.getStart() == start &&
            i.getEnd() == end &&
            i.getSymbol() == symbol);
}

template <class S>
bool Interval<S>::operator<(const Interval<S>& i) const
{
    return (start <= i.getStart() &&
            end <= i.getEnd() &&
            symbol != i.getSymbol());
}

/********** Member functions **********/

template <class S>
int Interval<S>::hashCode()
{
    return hashcode;
}
