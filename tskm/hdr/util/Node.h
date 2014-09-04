/**
 *
 * @file    Node.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <sstream>
#include <string>

#include "Chord.h"

using std::ostream;
using std::string;

/**
 * @class Node
 * @brief Chords have to be represented by this node,
 *        since those can reoccur several times.
 * @param Chord
 */
class Node
{

private :
    int internalID;
    Chord content;

public :

    /********** Constructors **********/

    Node();
    Node(int id, Chord c);

    /********** Destructor **********/

    ~Node();

    /********** Getters **********/

    Chord getContent() const;
    string getID() const;
    int getInternalID() const;
    string getLabel() const;
    int hashCode() const;

    /********** Operators **********/

    bool operator==(const Node& n) const;
    bool operator<(const Node& n) const;
    friend ostream& operator<<(ostream& os, const Node& n);

};

#endif
