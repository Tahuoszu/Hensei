/**
 *
 * @file    IntervalSet.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "IntervalSet.h"

/********** Constructors **********/

template <class S>
IntervalSet<S>::IntervalSet() {}

template <class S>
IntervalSet<S>::IntervalSet(vector<int> s, vector<int> e, vector<S> symbols)
{
    start  = s;
    end    = e;
    symbol.resize(size());
    // Map intervals and symbols
    map<S, int> invmap;
    int i = 0;
    int l = 0;
    for (typename vector<S>::iterator symb = symbols.begin();
        symb != symbols.end(); ++symb) {
        if (invmap.find(*symb) == invmap.end()) {
            l = invmap.size();
            invmap.insert(pair<S, int>(*symb, l));
            mapping.insert(pair<int, S>(l, *symb));
        }
        symbol[i] = invmap[*symb];
        i++;
    }
}

template <class S>
IntervalSet<S>::IntervalSet(vector<int> s, vector<int> e, vector<int> symbols,
			    map<int, S> mapp)
{
    start   = s;
    end     = e;
    symbol  = symbols;
    mapping = mapp;
}

template <class S>
IntervalSet<S>::IntervalSet(set<Interval<S> > intvs)
{
    int size = intvs.size();
    S symb;
    start.resize(size);
    end.resize(size);
    symbol.resize(size);
    // Map intervals and symbols
    map<S, int> invmap;
    int i = 0;
    int l = 0;
    for (typename set<Interval<S> >::iterator it = intvs.begin();
        it != intvs.end(); ++it) {
        symb = it->getSymbol();
        if (invmap.find(symb) == invmap.end()) {
            l = invmap.size();
            invmap.insert(pair<S, int>(symb, l));
            mapping.insert(pair<int, S>(l, symb));
        }
        start[i]  = it->getStart();
        end[i]    = it->getEnd();
        symbol[i] = invmap[it->getSymbol()];
        i++;
    }
}

/********** Destructor **********/

template <class S>
IntervalSet<S>::~IntervalSet() {}

/********** Getters **********/

template <class S>
const vector<int>& IntervalSet<S>::getStart() const
{
    return start;
}

template <class S>
const vector<int>& IntervalSet<S>::getEnd() const
{
    return end;
}

template <class S>
const vector<int>& IntervalSet<S>::getSymbol() const
{
    return symbol;
}

template <class S>
const map<int, S>& IntervalSet<S>::getMap() const
{
    return mapping;
}

template <class S>
map<int, int> IntervalSet<S>::get(int sid) const
{
    map<int, int> mapsid;
    int symbol_size = symbol.size();
    for (int i = 0; i < symbol_size; i++)
	if (symbol[i] == sid)
	    mapsid.insert(pair<int, int>(start[i], end[i]));
    return mapsid;
}

/********** Setters **********/

template <class S>
void IntervalSet<S>::setStart(int s[])
{
    start = s;
}

template <class S>
void IntervalSet<S>::setEnd(int e[])
{
    end = e;
}

template <class S>
void IntervalSet<S>::setSymbol(vector<S> symbols)
{
    symbol = new int[symbol.size()];
    map<S, int> invmap = new map<S, int>();
    int i = 0;
    for (typename vector<S>::iterator it = symbols.start(); \
	 it != symbols.end(); ++it) {
	if (symbols.end() == symbols.find(it)) {
	    const int l = invmap.size();
	    invmap.insert(pair<S, int>(it, l));
	    mapping.insert(pair<int, S>(l, it));
	}
	symbol[i] = invmap[it];
	i++;
    }
}

/********** Operators **********/

template <class T>
ostream& operator<<(ostream& os, const IntervalSet<T>& is)
{
    int is_size = is.size();
    vector<int> start   = is.getStart();
    vector<int> end     = is.getEnd();
    vector<int> symbol  = is.getSymbol();
    map<int, T> mapping = is.getMap();
    os << "------------------ IntervalSet ------------------" << "\n";
    os << "Start" << "\t" << "End" << "\t" << "Symbol" << "\t";
    os << "Value" << "\n";
    int symb = 0;
    for (int i = 0; i < is_size; i++) {
        symb = symbol[i];
        os << start[i] << "\t" << end[i] << "\t" << symb << "\t" \
           << mapping[symb] << "\n";
    }
    os << "------------------ IntervalSet ------------------" << "\n";
    return os;
}

template <class S>
bool IntervalSet<S>::operator==(const IntervalSet& ints)
{
    return (ints.getStart() == getStart() &&
	    ints.getEnd() == getEnd() &&
	    ints.getSymbol() == getSymbol() &&
	    ints.getMap() == getMap());
}

/********** Member functions **********/

template <class S>
bool IntervalSet<S>::addAll(set<Interval<S> > intvs)
{
    if (intvs.empty())
        return false;
    else {
        bool changed = false;
        for (typename set<Interval<S> >::iterator it = intvs.begin();
            it != intvs.end(); ++it) {
            if (!contains(*it))
                changed = true;
            else
                intvs.erase(*it);
        }
        if (changed) {
            map<S, int> invmap;
            for (typename map<int, S>::iterator it = mapping.begin();
                it != mapping.end(); ++it) {
                invmap.insert(std::pair<S, int>(it->second, it->first));
            }
            int issize = size() + intvs.size();
            vector<int> startTmp(issize, 0);
            vector<int> endTmp(issize, 0);
            vector<int> symbolTmp(issize, 0);
            std::copy(start.begin(), start.end(), startTmp.begin());
            std::copy(end.begin(), end.end(), endTmp.begin());
            std::copy(symbol.begin(), symbol.end(), symbolTmp.begin());
            typename set<Interval<S> >::iterator intvit = intvs.begin();
            for (int i = size(); i < issize; i++) {
                Interval<S> interval = *intvit;
                start[i] = interval.getStart();
                end[i]   = interval.getEnd();
                if (invmap.find(interval.getSymbol()) != invmap.end())
                    symbol[i] = invmap[interval.getSymbol()];
                else {
                    int size  = mapping.size();
                    symbol[i] = size;
                    mapping.insert(std::pair<int, S>(size,
                                                     interval.getSymbol()));
                }
            }
        }
        return changed;
    }
}

template <class S>
int IntervalSet<S>::size() const
{
    return start.size();
}

template <class S>
bool IntervalSet<S>::isEmpty()
{
    return(start.size() == 0);
}

template <class S>
bool IntervalSet<S>::contains(const Interval<S>& intv)
{
    int intv_size = start.size();
    for (int i = 0; i < intv_size; i++)
	if (intv.getStart() == start[i] &&
	    intv.getEnd() == end[i] &&
	    mapping[symbol[i]] == intv.getSymbol())
	    return true;
    return false;
}

// template <class S>
// bool IntervalSet<S>::add(const Interval& intv);

// template <class S>
// bool IntervalSet<S>::remove(const Interval& intv);

template <class S>
bool IntervalSet<S>::containsAll(const set<Interval<S> >& intvs)
{
    bool tmp = true;
    for (typename set<Interval<S> >::iterator it = intvs.begin();
        tmp && (it != intvs.end()); ++it)
        tmp &= contains(*it);
    return tmp;
}

// template <class S>
// bool IntervalSet<S>::removeAll(const set<S>& c)；

// template <class S>
// bool IntervalSet<S>::retainAll(const set<S>& c);

template <class S>
void IntervalSet<S>::clear()
{
    start.clear();
    end.clear();
    symbol.clear();
    mapping.clear();
    return;
}

template <class S>
IntervalSet<S> IntervalSet<S>::subSet(int stintv, int eintv)
{
    int size = start.size();
    set<Interval<S> > intvs;
    for (int i = 0; i < size; i++)
	if ((start[i] >= stintv) && (end[i] < eintv))
	    intvs.insert(Interval<S>(start[i], end[i], mapping[symbol[i]]));
    return IntervalSet<S>(intvs);
}

// template <class S>
// const int IntervalSet<S>::hashCode();
