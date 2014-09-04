/**
 *
 * @file    ClosedSequence.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    19/05/2014
 *
 */

#ifndef CLOSEDSEQUENCE_H
#define CLOSEDSEQUENCE_H

#include <iostream>
#include <iterator>
#include <list>
#include <string>

#include "Chord.h"

using std::list;
using std::string;
using std::ostream;

class ClosedSequence
{

private :
    list<Chord> sequence;
    int id;
    string label;

public :

    /********** Constructor **********/

    ClosedSequence(list<Chord> seq, int i);
    ClosedSequence(list<Chord> seq, int i, string l);

    /********** Destructor **********/

    ~ClosedSequence();

    /********** Getters **********/

    list<Chord> getSequence() const;
    int getID() const;

    /********** Operators **********/

    bool operator==(const ClosedSequence& cs) const;
    bool operator<(const ClosedSequence& cs) const;
    friend ostream& operator<<(ostream& os, const ClosedSequence& cs);

    /********** Member functions **********/

    list<Chord>::iterator begin();
    list<Chord>::const_iterator begin() const;
    list<Chord>::iterator end();
    list<Chord>::const_iterator end() const;

};

#endif
