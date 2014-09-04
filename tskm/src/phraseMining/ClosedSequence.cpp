/**
 *
 * @file    ClosedSequence.cpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    19/05/2014
 *
 */

#include "ClosedSequence.h"
#include "functions.h"

/********** Constructor **********/

ClosedSequence::ClosedSequence(list<Chord> seq, int i) :
    sequence(seq), id(i)
{
    label = intToString(id);
}

ClosedSequence::ClosedSequence(list<Chord> seq, int i, string l) :
    sequence(seq), id(i), label(l) {}

/********** Destructor **********/

ClosedSequence::~ClosedSequence() {}

/********** Getters **********/

list<Chord> ClosedSequence::getSequence() const
{
    return sequence;
}

int ClosedSequence::getID() const
{
    return id;
}

/********** Operators **********/

bool ClosedSequence::operator==(const ClosedSequence& cs) const
{
    return (id == cs.getID());
}

bool ClosedSequence::operator<(const ClosedSequence& cs) const
{
    return (id < cs.getID());
}

ostream& operator<<(ostream& os, const ClosedSequence& cs)
{
    os << "------------------ ClosedSequence ------------------" << "\n";
    os << "closedSeqID : " << cs.getID() << "\n";
    os << "sequence    : ";
    list<Chord>::const_iterator it = cs.begin();
    os << "[ ";
    for (; it != cs.end(); ++it)
        os << it->getLabel() << " ";
    os << "]" << endl;
    return os;
}

/********** Member functions **********/

list<Chord>::iterator ClosedSequence::begin()
{
    return sequence.begin();
}

list<Chord>::const_iterator ClosedSequence::begin() const
{
    return sequence.begin();
}

list<Chord>::iterator ClosedSequence::end()
{
    return sequence.end();
}

list<Chord>::const_iterator ClosedSequence::end() const
{
    return sequence.end();
}
