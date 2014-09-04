/**
 *
 * @file    Chord.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    21/05/2014
 *
 */

#ifndef CHORD_H
#define CHORD_H

#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include "Tone.h"

using std::ostream;
using std::set;
using std::string;

class Chord
{
private :
    int id;
    string label;
    set<Tone> tones;

public :

    /********** Constructors **********/

    Chord();
    Chord(set<Tone> ctones);
    Chord(int cid, set<Tone> ctones);
    Chord(int cid, set<Tone> ctones, string clabel);

    /********** Destructor **********/

    ~Chord();

    /********** Getters **********/

    int getGlobalID() const;
    string getID() const;
    string getLabel() const;
    const set<Tone>& getTones() const;
    int hashCode() const;

    /********** Operators **********/

    bool operator==(const Chord& c) const;
    bool operator<(const Chord& c) const;
    friend ostream& operator<<(ostream& os, const Chord& c);

    /********** Member functions **********/

    void insert(const Tone& t);
    void erase(const Tone& t);
    void clear();
    void insertAll(const set<Tone>& ctones);
    void retainAll(const set<Tone>& ctones);
    static string getTonesLabel(const set<Tone>& s);

    /********** Friend functions **********/

    friend int getSum(const set<Tone>& ctones);

};

#endif
