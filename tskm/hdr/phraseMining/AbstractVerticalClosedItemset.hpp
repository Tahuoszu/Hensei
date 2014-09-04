/**
 *
 * @file    AbstractVerticalClosedItemset.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "AbstractVerticalClosedItemset.h"

/********** Getters **********/

template <class S>
const map<S, BitSet >&
AbstractVerticalClosedItemset<S>::getItem() const
{
    return item;
}

/********** Operators  **********/

template <class T>
const ostream& operator<<(const ostream& os,
                    const AbstractVerticalClosedItemset<T>& avcis)
{
    map<T, BitSet > item = avcis.getItem();
    typename map<T, BitSet >::iterator it;
    for (it = item.begin; it != item.end(); ++it) {
        os << item->first << "\t";
        print_vector(it->second);
    }
    return os;
}

/********** Member functions  **********/

template <class S>
BitSet AbstractVerticalClosedItemset<S>::g(S symb)
{
	return BitSet(item[symb]);
}

template <class S>
BitSet AbstractVerticalClosedItemset<S>::g(const list<S>& symb)
{
	typename list<S>::const_iterator it = symb.begin();
	BitSet v;
	if (!symb.empty())
		v = item[*it];
	else
		v.resize(this->supportLength, 1);
	while (it != symb.end()) {
		v.bsand(item[*it]);
		++it;
	}
	return v;
}

template <class S>
bool AbstractVerticalClosedItemset<S>::isSubSet(BitSet a,
                                                BitSet b)
{
	return std::includes(b.begin(), b.end(), a.begin(), a.end());
}

template <class S>
void AbstractVerticalClosedItemset<S>::\
preprocessing(const map<set<S>, int>& maps)
{
	int bs_size = 64;
    this->supportLength = 0;
    int counter = 0;
    typename map<set<S>, int>::const_iterator current;
    for (current = maps.begin(); current != maps.end(); ++current) {
        for (int j = 0; j < current->second; j++) {
            set<S> curSet = current->first;
            typename set<S>::iterator i;
            for (i = curSet.begin(); i != curSet.end(); ++i) {
                if (item.find(*i) != item.end())
                    item[*i][counter] = 1;
                else {
                    BitSet bs(bs_size, 0);
                    bs[counter] = 1;
                    item[*i] = bs;
                    //item.insert(pair<S, BitSet >(*i, bs));
                }
            }
            counter++;
        }
    }
    removeInFrequent();
    this->supportLength = counter;
}

template <class S>
void AbstractVerticalClosedItemset<S>::removeInFrequent()
{
	set<S> tmp;
	typename map<S, BitSet>::iterator it;
	for (it = item.begin(); it != item.end(); ++it) {
		//std::cout << "sup = " << support(it->first) << std::endl;
		if (support(it->first) < this->minSupport)
			tmp.insert(it->first);
	}
	typename set<S>::iterator sit;
	for (sit = tmp.begin(); sit != tmp.end(); ++sit)
		item.erase(*sit);
}

template <class S>
list<S> AbstractVerticalClosedItemset<S>::sortBySupports(set<S> postSet)
{
	map<int, list<S> > sorted;
	int currentSupport;
	typename set<S>::iterator it;
	for (it = postSet.begin(); it != postSet.end(); ++it) {
		BitSet v = g(*it);
		currentSupport = v.cardinality();
		if (sorted.find(currentSupport) == sorted.end())
			sorted.insert(pair<int, list<S> >(currentSupport, list<S>()));
		sorted[currentSupport].push_back(*it);
	}
	list<S> out;
	typename map<int, list<S> >::iterator mit;
	for (mit = sorted.begin(); mit != sorted.end(); ++mit)
		out.insert(out.end(), mit->second.begin(), mit->second.end());
	return out;
}

template <class S>
int AbstractVerticalClosedItemset<S>::support(S symb)
{
    return g(symb).cardinality();
}

template <class S>
int AbstractVerticalClosedItemset<S>::support(const set<S>& symb)
{
	typename set<S>::const_iterator it = symb.begin();
	BitSet v;
	if (!symb.empty())
		v = (item.begin())->second;
	else
		return this->supportLength;
	while (it != symb.end()) {
		v.bsand(item[*it]);
		++it;
	}
	return this->support(v);
}
