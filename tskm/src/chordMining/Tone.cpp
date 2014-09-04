/**
 *
 * @file    Tone.cpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "functions.h"
#include "Tone.h"

/********** Constructors **********/

Tone::Tone() {}

Tone::Tone(int gID, int sID, string s, string l) :
    globalID(gID), seriesID(sID), series(s), label(l) {}

/********** Destructor **********/

Tone::~Tone() {}

/********** Getters **********/

int Tone::getGlobalID() const
{
    return globalID;
}

string Tone::getID() const
{
    string str = intToString(globalID);
    return str;
}

int Tone::getseriesID() const
{
    return seriesID;
}

string Tone::getLabel() const
{
    return label;
}

int Tone::hashCode() const
{
    return globalID;
}

/********** Operator **********/

bool Tone::operator==(const Tone& t) const
{
    return (globalID == t.globalID);
}

bool Tone::operator<(const Tone& t) const
{
    return (globalID < t.globalID);
}

ostream& operator<<(ostream& os, const Tone& t)
{
    os << "------------------ Tone ------------------" << "\n";
    os << "\t\t\t" << "globalid : " << t.getGlobalID() << "\n";
    //os << "\t\t\t" << "stringid : " << t.getID() << "\n";
    os << "\t\t\t" << "series   : " << t.getseriesID() << "\n";
    os << "\t\t\t" << "label    : " << t.getLabel() << "\n";
    return os;
}
