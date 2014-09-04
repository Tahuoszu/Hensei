/**
 *
 * @file    Event.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "Event.h"

/********** Constructors **********/

template <class S>
Event<S>::Event() {}

template <class S>
Event<S>::Event(int index, int is, int symb, S mapp) :
    internalIndex(index), started(is), symbol(symb), mapping(mapp) {}

/********** Destructor **********/

template <class S>
Event<S>::~Event() {}

/********** Getters **********/

template <class S>
int Event<S>::getIndex() const
{
    return internalIndex;
}

template <class S>
bool Event<S>::isStart() const
{
    return started;
}

template <class S>
int Event<S>::getSymbol() const
{
    return symbol;
}

template <class S>
S Event<S>::getmapping() const
{
    return mapping;
}

/********** Operators **********/

template <class T>
ostream& operator<<(ostream& os, const Event<T>& e)
{
    os << "------------------ Event ------------------" << "\n";
    os << "[" << e.getIndex() << "\t" << e.getSymbol() << "\t";
    os << (e.isStart() ? "1" : "0") << "]\n";
    return os;
}

template <class S>
bool Event<S>::operator==(const Event& e) const
{
    return (e.getIndex() == internalIndex &&
            e.getSymbol() == symbol &&
            e.isStart() == started);
}

template <class S>
bool Event<S>::operator<(const Event& e) const
{
    bool compare = true;
    int diff = internalIndex - e.getIndex();
    if (diff != 0)
        compare = (diff < 0);
    else {
        const bool thisIsStart  = started;
        const bool eventIsStart = e.isStart();
        if (!thisIsStart && eventIsStart)
            compare = false;
        if (thisIsStart && !eventIsStart)
        	compare = true;
    }
    return compare;
}

/********** Member functions **********/

template <class S>
int Event<S>::hashCode()
{
    return 0;
}
