/**
 *
 * @file    Chord.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "Chord.h"
#include "functions.h"

/********** Friend functions **********/

int getSum(set<Tone> ctones)
{
    int sum = 0;
    for (set<Tone>::iterator it = ctones.begin(); it != ctones.end(); ++it)
	sum += it->hashCode();
    return sum;
}

/********** Constructors **********/

Chord::Chord() {}

Chord::Chord(set<Tone> ctones) :
    id(getSum(ctones)), label(intToString(id)), tones(ctones) {}

Chord::Chord(int cid, set<Tone> ctones) :
    id(cid), label(intToString(id)), tones(ctones) {}

Chord::Chord(int cid, set<Tone> ctones, string clabel) :
    id(cid), label(clabel), tones(ctones) {}

/********** Destructor **********/

Chord::~Chord() {}

/********** Getters **********/

int Chord::getGlobalID() const
{
    return id;
}

string Chord::getID() const
{
    static string str = intToString(id);
    return str;
}

string Chord::getLabel() const
{
    return label;
}

const set<Tone>& Chord::getTones() const
{
    return tones;
}

int Chord::hashCode() const
{
    return id;
}

/********** Operators **********/

bool Chord::operator==(const Chord& c) const
{
    return (id == c.id);
}

bool Chord::operator<(const Chord& c) const
{
    return (id < c.id);
}

ostream& operator<<(ostream& os, const Chord& c)
{
    os << "------------------ Chord ------------------" << "\n";
    os << "globalid : " << c.getGlobalID() << "\n";
    os << "stringid : " << c.getID() << "\n";
    os << "label    : " << c.getLabel() << "\n";
    os << "hashcode : " << c.hashCode() << "\n";
    set<Tone> tones = c.getTones();
    os << "Tones    : " << "\n";
    for (set<Tone>::iterator t = tones.begin(); t != tones.end(); ++t)
	os << *t;
    os << "\n";
    return os;
}

/********** Member functions **********/

void Chord::insert(const Tone& t)
{
    tones.insert(t);
}

void Chord::erase(const Tone& t)
{
    tones.erase(t);
}

void Chord::clear()
{
    tones.clear();
}

void Chord::insertAll(const set<Tone>& ctones)
{
    for (set<Tone>::iterator it = ctones.begin(); it != ctones.end(); ++it)
	tones.insert(*it);
}

void Chord::retainAll(const set<Tone>& ctones)
{
    set<Tone>::iterator itmp;
    for (set<Tone>::iterator it = ctones.begin(); it != ctones.end(); ++it) {
	itmp = tones.find(*it);
	if (itmp != tones.end())
	    tones.erase(itmp);
    }
}

string Chord::getTonesLabel(const set<Tone>& s)
{
    string label = "";
    label += "[";
    set<Tone>::const_iterator it;
    for (it = s.begin(); it != s.end(); it++) {
        if (it != s.begin())
            label += " ";
        label += it->getLabel();
    }
    label += "]";
    return label;
}
