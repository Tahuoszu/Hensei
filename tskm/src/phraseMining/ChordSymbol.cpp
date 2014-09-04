/**
 *
 * @file    ChordSymbol.cpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    19/05/2014
 *
 */

#include "ChordSymbol.h"
#include "functions.h"

/********** Constructor **********/

ChordSymbol::ChordSymbol(int id, string l, string ts) :
    globalID(id), label(l), toneSet(ts) {}

/********** Destructor **********/

ChordSymbol::~ChordSymbol() {}

/********** Getters **********/

int ChordSymbol::getGlobalID() const
{
    return globalID;
}

string ChordSymbol::getID() const
{
    static string str = intToString(globalID);
    return str;
}

string ChordSymbol::getLabel() const
{
    return label;
}

string ChordSymbol::getToneSet() const
{
    return toneSet;
}

/********** Operators **********/

bool ChordSymbol::operator==(const ChordSymbol& cs) const
{
    return (globalID == cs.globalID);
}

bool ChordSymbol::operator<(const ChordSymbol& cs) const
{
    return (globalID - cs.globalID);
}

int ChordSymbol::hashCode() const
{
    return globalID;
}

ostream& operator<<(ostream& os, const ChordSymbol& cs)
{
    os << "------------------ ChordSymbol ------------------" << "\n";
    os << "globalID : " << cs.getGlobalID() << "\n";
    os << "stringID : " << cs.getID() << "\n";
    os << "label    : " << cs.getLabel() << "\n";
    os << "hashcode : " << cs.hashCode() << "\n";
    return os;
}
