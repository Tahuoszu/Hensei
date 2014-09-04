/**
 *
 * @file    ChordSymbol.h
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    19/05/2014
 *
 */

#ifndef CHORDSYMBOL_H
#define CHORDSYMBOL_H

#include <iostream>
#include <string>

using std::string;
using std::ostream;

class ChordSymbol
{

private :
    int globalID;
    string label;
    string toneSet;

public :

    /********** Constructor **********/

    ChordSymbol(int id, string l, string ts);

    /********** Destructor **********/

    ~ChordSymbol();

    /********** Getters **********/

    int getGlobalID() const;
    string getID() const;
    string getLabel() const;
    string getToneSet() const;
    int hashCode() const;

    /********** Operators **********/

    bool operator==(const ChordSymbol& cs) const;
    bool operator<(const ChordSymbol& cs) const;
    friend ostream& operator<<(ostream& os, const ChordSymbol& cs);

};

#endif
