/**
 *
 * @file    Node.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "functions.h"
#include "Node.h"

using std::ostream;
using std::string;

/********** Constructors **********/

Node::Node() {
    internalID = -1;
    content = Chord();
}

Node::Node(int id, Chord c) : internalID(id), content(c) {}

/********** Destructor **********/

Node::~Node() {}

/********** Getters **********/

Chord Node::getContent() const
{
    return content;
}

string Node::getID() const
{
    static string str = intToString(internalID);
    return str;
}

int Node::getInternalID() const
{
    return internalID;
}

string Node::getLabel() const
{
    return content.getLabel();
}

int Node::hashCode() const
{
    return internalID;
}

/********** Operators **********/

bool Node::operator==(const Node& n) const
{
    return (internalID == n.internalID);
}

bool Node::operator<(const Node& n) const
{
    return (internalID < n.internalID);
}

ostream& operator<<(ostream& os, const Node& n)
{
    os << "InternalID : " << n.getID() << std::endl;
    os << n.getContent();
    return os;
}
