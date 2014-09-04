/**
 *
 * @file    AbstractMinDurVerticalClosedItemset.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "AbstractMinDurVerticalClosedItemset.h"

/********** Getters **********/

template <class S>
const map<S, BitSet >&
AbstractMinDurVerticalClosedItemset<S>::getItem() const
{
    return item;
}

/********** Setters **********/

template <class S>
void AbstractMinDurVerticalClosedItemset<S>::setMinDuration(int minDur)
{
	minDuration = minDur;
}

/********** Operators  **********/

template <class T>
const ostream& operator<<(const ostream& os,
                    const AbstractMinDurVerticalClosedItemset<T>& amnvcis)
{
    map<T, BitSet > item = amnvcis.getItem();
    typename map<T, BitSet >::iterator it;
    for (it = item.begin; it != item.end(); ++it) {
        os << item->first << "\t";
        print_vector(it->second);
    }
    return os;
}

/********** Member functions  **********/

template <class S>
BitSet AbstractMinDurVerticalClosedItemset<S>::g(S symb)
{
	return BitSet(item[symb]);
}

template <class S>
BitSet AbstractMinDurVerticalClosedItemset<S>::g(const list<S>& symb)
{
	typename list<S>::const_iterator it = symb.begin();
	BitSet v;
	if (!symb.empty())
		v = item[*it];
	else
		v.resize(this->supp.size(), 1);
	while (it != symb.end()) {
		v.bsand(item[*it]);
		++it;
	}
	return v;
}

template <class S>
bool AbstractMinDurVerticalClosedItemset<S>::isSubSet(BitSet a,
                                                      BitSet b)
{
	return std::includes(b.begin(), b.end(), a.begin(), a.end());
}

template <class S>
void AbstractMinDurVerticalClosedItemset<S>::\
preprocessing(const IntervalSequence<set<S> >& maps)
{
	int map_size = maps.size();
	this->supp.resize(map_size, 0);
	vector<set<S> > seq = maps.getSymbol();
	vector<int> start   = maps.getStart();
	vector<int> end     = maps.getEnd();
	for (int i = 0; i < map_size; i++) {
		this->supp[i] = end[i] - start[i] + 1;
		set<S> symbols = seq[i];
		typename set<S>::iterator it;
		for (it = symbols.begin(); it != symbols.end(); ++it) {
			typename map<S, BitSet>::iterator item_index = item.find(*it);
			if (item_index != item.end())
				item_index->second[i] = 1;
			else {
				BitSet v(map_size, 0);
				v[i] = 1;
				item.insert(pair<S, BitSet>(*it, v));
			}
		}
	}
    removeInFrequent();
}

template <class S>
void AbstractMinDurVerticalClosedItemset<S>::removeInFrequent()
{
	set<S> tmp;
	typename map<S, BitSet>::iterator it;
	for (it = item.begin(); it != item.end(); ++it)
		if (support(it->first) < this->minSupport)
			tmp.insert(it->first);
	typename set<S>::iterator sit;
	for (sit = tmp.begin(); sit != tmp.end(); ++sit)
		item.erase(*sit);
}

template <class S>
list<S> AbstractMinDurVerticalClosedItemset<S>::sortBySupports(set<S> postSet)
{
	map<int, list<S> > sorted;
	int currentSupport;
	typename set<S>::iterator it;
	for (it = postSet.begin(); it != postSet.end(); ++it) {
		BitSet v = this->g(*it);
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
int AbstractMinDurVerticalClosedItemset<S>::support(S symb)
{
	BitSet v = item[symb];
	int s = 0;
	int lastZero = -2;
	int duration = 0;
	int v_size   = v.size();
	for (int i = 0; i < v_size; i++) {
		if (v[i]) {
            if (i != lastZero + 1) {
                if (duration > minDuration)
                    s += duration;
                duration = 0;
            }
            duration += this->supp[i];
		}
	}
	return s;
}

template <class S>
int AbstractMinDurVerticalClosedItemset<S>::support(const set<S>& symb)
{
	typename set<S>::const_iterator it = symb.begin();
	BitSet v;
	if (!symb.empty())
		v = item[*it];
	else
		return std::accumulate(this->supp.begin(), this->supp.end(), 0);
	while (it != symb.end()) {
        v.bsand(item[*it]);
		++it;
	}
	int s = 0;
	int duration = 0;
	int v_size   = v.size();
	for (int i = 0; i < v_size; i++) {
		if (v[i]) {
			if (duration > minDuration)
				s += duration;
			duration = 0;
		}
		duration += this->supp[i];
	}
	return s;
}
