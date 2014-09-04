/**
 *
 * @file    BitSet.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "BitSet.h"

/********** Constructors **********/

BitSet::BitSet() {}

BitSet::BitSet(char val)
{
    bitset = vector<char>(val);
}

BitSet::BitSet(int size, char val)
{
    bitset = vector<char>(size, val);
}

BitSet::BitSet(const BitSet& bs) : bitset(bs.getBitSet()) {}

BitSet::BitSet(const vector<char>& v) : bitset(v) {}

/********** Destructor **********/

BitSet::~BitSet() {}

/********** Getters **********/

char BitSet::get(int i) const
{
    return bitset[i];
}

vector<char> BitSet::getBitSet() const
{
    return bitset;
}

int BitSet::size() const
{
    return bitset.size();
}

/********** Setters **********/

void BitSet::setBitSet(const BitSet& bs)
{
    bitset = bs.getBitSet();
}

void BitSet::setBitSet(const vector<char>& v)
{
    bitset = v;
}

/********** Operators **********/

char BitSet::operator==(const BitSet& bs) const
{
    return (bitset == bs.getBitSet());
}

bool BitSet::operator<(const BitSet& bs) const
{
    vector<char>::const_iterator it1;
    vector<char>::const_iterator it2;
    for (it1 = bitset.begin(), it2 = bs.begin();
         it1 != bitset.end() && it2 != bs.end(); ++it1, ++it2)
        if (*it1 < *it2)
            return true;
    return false;
}

char& BitSet::operator[](int i)
{
    return bitset[i];
}

ostream& operator<<(ostream& os, const BitSet& bs)
{
    int bs_size = bs.size();
    for (int i = 0; i < bs_size; i++)
        if (bs.get(i) == 1)
            os << i << " ";
    return os;
}

/********** Member functions **********/

vector<char>::iterator BitSet::begin()
{
    return bitset.begin();
}

vector<char>::const_iterator BitSet::begin() const
{
    return bitset.begin();
}

void BitSet::bsand(const BitSet& bs)
{
    int bs_size = size();
    for (int i = 0; i < bs_size; i++)
        bitset[i] = bitset[i] && bs.get(i);
}

void BitSet::bsor(const BitSet& bs)
{
    int bs_size = size();
    for (int i = 0; i < bs_size; i++)
        bitset[i] = bitset[i] || bs.get(i);
}

void BitSet::clear()
{
    bitset.clear();
}

int BitSet::cardinality()
{
    return std::count(bitset.begin(), bitset.end(), 1);
}

char BitSet::empty()
{
    return bitset.empty();
}

vector<char>::iterator BitSet::end()
{
    return bitset.end();
}

vector<char>::const_iterator BitSet::end() const
{
    return bitset.end();
}

void BitSet::flip(int i)
{
    bitset[i] = !bitset[i];
}

void BitSet::print_bitset()
{
    for (vector<char>::iterator it = bitset.begin(); it != bitset.end(); ++it)
        std::cout << (int)*it << " ";
    std::cout << endl;
}

void BitSet::reserve(int i)
{
    bitset.reserve(i);
}

void BitSet::resize(int i)
{
    bitset.resize(i);
}

void BitSet::resize(int i, char val)
{
    bitset.resize(i, val);
}

void BitSet::set(int i, char val)
{
    bitset[i] = val;
}

