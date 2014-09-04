/**
 *
 * @file    IntervalEventSet.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    18/04/2014
 *
 */

#include "IntervalEventSet.h"

/********** Constructors **********/

template <class S>
IntervalEventSet<S>::IntervalEventSet(vector<int> i, vector<int> s,
                                      BitSet is, map<int, S> maps) :
    index(i), symbol(s), isStart(is), mapping(maps)
{
    testOrder(*this);
}

template <class S>
IntervalEventSet<S>::IntervalEventSet(set<Event<S> > es)
{
    int es_size = es.size();
    index.resize(es_size);
    symbol.resize(es_size);
    isStart.resize(es_size);
    map<int, int> maps;
    int i = 0;
    for (typename set<Event<S> >::iterator it = es.begin();
        it != es.end(); ++it) {
        index[i]   = it->getIndex();
        isStart[i] = it->isStart();
        if (maps.find(it->getSymbol()) == maps.end()) {
            int msize = maps.size();
            maps.insert(pair<int, int>(it->getSymbol(), msize));
            mapping.insert(pair<int, S>(msize, it->getmapping()));
        }
        symbol[i] = maps[it->getSymbol()];
        i++;
    }
    testOrder(*this);
}

template <class S>
IntervalEventSet<S>::IntervalEventSet(IntervalSet<S> is)
{
    vector<int> indextmp  = is.getEnd();
    vector<int> symboltmp = is.getSymbol();
    map<int, S> maptmp    = is.getMap();
    int isize = indextmp.size();
    BitSet isStarttmp(isize, 0);

    indextmp.insert(indextmp.end(), is.getStart().begin(), is.getStart().end());
    symboltmp.insert(symboltmp.end(), is.getSymbol().begin(),
                     is.getSymbol().end());
    isize *= 2;
    isStarttmp.resize(isize, 1);

    vector<int> sorted = getIndexOfSort(indextmp);
    vector<int>	sortedSymbol(isize, 0);
    vector<int> sortedIndex(isize, 0);
    BitSet sortedIsStart(isize, 0);

    for (int i = 0; i < isize; i++) {
        sortedIndex[i]	 = indextmp[sorted[i]];
        sortedSymbol[i]  = symboltmp[sorted[i]];
        sortedIsStart[i] = isStarttmp[sorted[i]];
    }

    index   = sortedIndex;
    symbol  = sortedSymbol;
    isStart = sortedIsStart;
    mapping = maptmp;
    testOrder(*this);

}

/********** Getters **********/

template <class S>
const vector<int>& IntervalEventSet<S>::getIndex() const
{
    return index;
}

template <class S>
const BitSet& IntervalEventSet<S>::getIsStart() const
{
    return isStart;
}

template <class S>
const vector<int>& IntervalEventSet<S>::getSymbol() const
{
    return symbol;
}

template <class S>
const map<int, S>& IntervalEventSet<S>::getMapping() const
{
    return mapping;
}

/********** Operators **********/

template <class S>
bool IntervalEventSet<S>::operator==(const IntervalEventSet<S>& ies)
{
    return (ies.getIsStart() == isStart &&
	    ies.getSymbol() == symbol &&
	    ies.index == index);
}

template <class S>
ostream& operator<<(ostream& os, const IntervalEventSet<S>& ies)
{
    int ies_size = ies.size();
    vector<int> index   = ies.getIndex();
    vector<int> symbol  = ies.getSymbol();
    BitSet isStart      = ies.getIsStart();
    map<int, S> mapping = ies.getMapping();
    os << "------------------ IntervalEventSet ------------------" << "\n";
    os << "Index" << "\t" << "Symbol" << "\t" << "IsStart" << "\t";
    os << "Value" << "\n";
    int symb = 0;
    for (int i = 0; i < ies_size; i++) {
        symb = symbol[i];
        os << index[i] << "\t" << symb << "\t" << (int)isStart[i] << "\t";
        os << mapping[symb] << "\n";
    }
    os << "------------------ IntervalEventSet ------------------" << "\n";
    return os;
}

/********** Member functions **********/

//template <class S>
//void IntervalEventSet<S>::add(const int idx, const Event<S>& e);

//template <class S>
//bool IntervalEventSet<S>::add(const Event<S>& e);

//template <class S>
//bool addAll(const set<Event<S> >& c);

template <class S>
void IntervalEventSet<S>::clear()
{
    index.clear();
    symbol.clear();
    isStart.clear();
    mapping.clear();
}

template <class S>
bool IntervalEventSet<S>::contains(const Event<S>& e)
{
    int length = index.size();
    for (int i = 0; i < length; i++)
	if (index[i]   == e.getIndex() &&
	    symbol[i]  == e.getSymbol() &&
	    isStart[i] == e.isStart())
	    return 1;
    return 0;
}

template <class S>
bool IntervalEventSet<S>::containsAll(const set<Event<S> >& es)
{
    bool tmp = 1;
    for (typename set<Event<S> >::iterator it = es.begin();
        tmp && (it != es.end()); ++it)
        tmp &= contains(*it);
    return tmp;
}

template <class S>
int IntervalEventSet<S>::hashcode()
{
    return 0;
}

template <class S>
bool IntervalEventSet<S>::isEmpty() const
{
    return mapping.empty();
}

//template <class S>
//bool IntervalEventSet<S>::remove(const Event<S>& e);

//template <class S>
//bool IntervalEventSet<S>::removeAll(const set<Event<S> >& es);

//template <class S>
//bool IntervalEventSet<S>::retainAll(const set<Event<S> >& es);

template <class S>
int IntervalEventSet<S>::size() const
{
    return index.size();
}


template <class S>
bool IntervalEventSet<S>::testOrder(const IntervalEventSet<S>& ies)
{
    if (ies.isEmpty())
        return true;
    vector<int> index    = ies.getIndex();
    vector<int> symbol   = ies.getSymbol();
    BitSet isStart       = ies.getIsStart();
    map<int, S> mapping  = ies.getMapping();
    int ies_size = ies.size();

    Event<S> previous(index[0], isStart[0], symbol[0], mapping[symbol[0]]);
    for (int i = 1; i < ies_size; i++) {
        Event<S> current(index[i], isStart[i], symbol[i], mapping[symbol[i]]);
        if (!(previous < current)) {
            std::cerr << "The given IntervalEventSet violates ";
            std::cerr << "the internal order !"  << std::endl;
            return false;
        }
        previous = current;
    }
    return true;
}
