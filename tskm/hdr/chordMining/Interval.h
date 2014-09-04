/**
 *
 * @file    Interval.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#ifndef INTERVAL_H
#define INTERVAL_H

#include <sstream>

using std::ostream;

/**
 * @class Interval
 * @brief Shallow object reflecting to the internal representation from
 *		  the surrounding IntervalSet.
 */
template <class S>
class Interval
{

private :
    int start;
    int end;
    S symbol;
    int hashcode;

public :

    /********** Constructor **********/

    Interval(int starti, int endi, S symboli);

    /********** Destructor **********/

    ~Interval();

    /********** Getters **********/

    int getStart() const;
    int getEnd() const;
    S getSymbol() const;

    /********** Operator **********/

    template <class T>
    friend ostream& operator<<(ostream& os, const Interval<T>& i);
    bool operator==(const Interval<S>& i) const;
    bool operator<(const Interval<S>& i) const;

    /********** Member functions **********/

    int hashCode();

};

#include "Interval.hpp"

#endif
