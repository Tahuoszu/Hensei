/**
 *
 * @file    Tone.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#ifndef TONE_H
#define TONE_H

#include <iostream>
#include <sstream>
#include <string>

using std::ostream;
using std::string;

class Tone
{

private :
    int globalID;
    int seriesID;
    string series;
    string label;

public :

    /********** Constructors **********/

	Tone();
    Tone(int gID, int sID, string s, string l);

    /********** Destructor **********/

    ~Tone();

    /********** Getters **********/

    int getGlobalID() const;
    string getID() const;
    int getseriesID() const;
    string getLabel() const;
    int hashCode() const;

    /********** Operators **********/

    bool operator==(const Tone& t) const;
    bool operator<(const Tone& t) const;
    friend ostream& operator<<(ostream& os, const Tone& t);

};

#endif
