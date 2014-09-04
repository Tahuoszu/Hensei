/**
 *
 * @file    BitSet.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef BITSET_H
#define BITSET_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "functions.h"

using std::ostream;

class BitSet
{
private :
    vector<char> bitset;

public :

    /********** Constructors **********/

    BitSet();
    BitSet(char val);
    BitSet(int size, char val);
    BitSet(const BitSet& bs);
    BitSet(const vector<char>& v);

    /********** Destructor **********/

    ~BitSet();

    /********** Getters **********/

    char get(int i) const;
    vector<char> getBitSet() const;
    int size() const;

    /********** Setters **********/

    void setBitSet(const BitSet& bs);
    void setBitSet(const vector<char>& v);

    /********** Operators **********/

    char operator==(const BitSet& bs) const;
    bool operator<(const BitSet& bs) const;
    char& operator[](int i);
    friend ostream& operator<<(ostream& os, const BitSet& bs);

    /********** Member functions **********/

    vector<char>::iterator begin();
    vector<char>::const_iterator begin() const;
    void bsand(const BitSet& bs);
    void bsor(const BitSet& bs);
    void clear();
    int cardinality();
    char empty();
    vector<char>::iterator end();
    vector<char>::const_iterator end() const;
    void flip(int i);
    void print_bitset();
    void reserve(int i);
    void resize(int i);
    void resize(int i, char val);
    void set(int i, char val);

};

#endif
