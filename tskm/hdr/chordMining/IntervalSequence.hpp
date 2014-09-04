/**
 *
 * @file    IntervalSequence.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    18/04/2014
 *
 */

#include "IntervalSequence.h"

/********** Constructors **********/

template <class S>
IntervalSequence<S>::IntervalSequence() {}

template <class S>
IntervalSequence<S>::IntervalSequence(vector<S> seq, vector<int> s,
                                      vector<int> e)
{
    typename vector<S>::iterator symbIt = seq.begin();
    vector<int>::iterator startIt = s.begin();
    vector<int>::iterator endIt = e.begin();
    map<S, int> invmap;
    while (symbIt != seq.end()) {
        S symbv = *symbIt;
        int sv  = *startIt;
        int ev  = *endIt;
        if (invmap.find(symbv) == invmap.end())
            invmap.insert(pair<S, int>(symbv, invmap.size()));
        int index = invmap[symbv];
        mapping.insert(pair<int, S>(index, symbv));
        sequence.push_back(index);
        start.push_back(sv);
        end.push_back(ev);
        if (totalSupport.find(index) != totalSupport.end())
            totalSupport.insert(pair<int, int>(index, totalSupport[index] + \
                               duration(*startIt, *endIt)));
        else
            totalSupport.insert(pair<int, int>(index,
                               duration(*startIt, *endIt)));
        startIt++;
        endIt++;
        symbIt++;
    }
    testSanity(*this);
}

template <class S>
IntervalSequence<S>::IntervalSequence(vector<int> seq, vector<int> s,
				      vector<int> e, map<int, S> m)
{
    vector<int>::iterator seqIt   = seq.begin();
    vector<int>::iterator startIt = s.begin();
    vector<int>::iterator endIt   = e.begin();
    map<S, int> invmap;
    while (seqIt != seq.end()) {
        int seqv = *seqIt;
        int sv   = *startIt;
        int ev   = *endIt;
        S symbv  = m[seqv];
        if (invmap.find(symbv) == invmap.end())
            invmap.insert(pair<S, int>(symbv, invmap.size()));
        int index = invmap[symbv];
        mapping.insert(pair<int, S>(index, symbv));
        sequence.push_back(index);
        start.push_back(sv);
        end.push_back(ev);
        if (totalSupport.find(index) != totalSupport.end())
            totalSupport.insert(pair<int, int>(index, totalSupport[index] + \
                               duration(*startIt, *endIt)));
        else
            totalSupport.insert(pair<int, int>(index,
                               duration(*startIt, *endIt)));
        startIt++;
        endIt++;
        seqIt++;
    }
    testSanity(*this);
}

template <class S>
IntervalSequence<S>::IntervalSequence(vector<int> seq, vector<int> s,
				      vector<int> e,
				      map<int, S> m, map<int, int> ts) :
    sequence(seq), start(s), end(e), mapping(m), totalSupport(ts)
{
    testSanity(*this);
}

/********** Getters **********/

template <class S>
const vector<int>& IntervalSequence<S>::getEnd() const
{
    return end;
}

template <class S>
const vector<int>& IntervalSequence<S>::getInternalSequence() const
{
    return sequence;
}

template <class S>
const map<int, S>& IntervalSequence<S>::getInternalMap() const
{
    return mapping;
}

template <class S>
const map<S, int> IntervalSequence<S>::getMap() const
{
    map<S, int> imaps;
    map<int, int> ts = getTotalSupport();
    for (typename map<int, S>::const_iterator it = mapping.begin();
        it != mapping.end(); ++it)
        imaps.insert(pair<S, int>(it->second, ts[it->first]));
    return imaps;
}

template <class S>
const vector<int>& IntervalSequence<S>::getStart() const
{
    return start;
}

template <class S>
const vector<S> IntervalSequence<S>::getSymbol() const
{
    vector<S> symbols;
    map<int, S> mapping = getInternalMap();
    for (vector<int>::const_iterator it = sequence.begin();
        it != sequence.end(); ++it)
        symbols.push_back(mapping[*it]);
    return symbols;
}


template <class S>
const map<int, int>& IntervalSequence<S>::getTotalSupport() const
{
    return totalSupport;
}

/********** Operators **********/

template <class T>
ostream& operator<<(ostream& os, const IntervalSequence<T>& is)
{
    /*if (is.isEmpty())
        return os;*/
    vector<int> sequence = is.getInternalSequence();
    vector<int> start    = is.getStart();
    vector<int> end      = is.getEnd();
    vector<T> symbol     = is.getSymbol();
    map<int, int> ts     = is.getTotalSupport();
    vector<int>::iterator seqIt	  = sequence.begin();
    vector<int>::iterator startIt = start.begin();
    vector<int>::iterator endIt	  = end.begin();
    typename vector<T>::iterator symbIt	  = symbol.begin();
    os << "------------------ IntervalSequence ------------------" << "\n";
    /*for (; endIt != end.end(); seqIt++, startIt++, endIt++, ++symbIt) {
        Element<T> e(*seqIt, *startIt, *endIt, *symbIt, ts[*seqIt]);
        os << e;
    }*/
    os << "Seq" << "\t" << "Start" << "\t" << "End" << "\t";
    os << "TotalSupport" << "\t";
    //os << "Map" << "\t";
    os << "\n";
    for (;seqIt != sequence.end(); ++seqIt, ++startIt, ++endIt, ++symbIt) {
        os << *seqIt << "\t" << *startIt << "\t" << *endIt << "\t";
        os << (ts.find(*seqIt))->second << "\t";
        //os << *symbIt << "\t";
        os << "\n";
    }
    os << "------------------ IntervalSequence ------------------" << "\n";
    return os;
}

/********** Member functions **********/

template <class S>
Element<S> IntervalSequence<S>::get(int index)
{
    int mapindex = sequence[index];
    return Element<S>(mapindex, start[index], end[index], mapping[mapindex],
		      totalSupport[mapindex]);
}

template <class S>
bool IntervalSequence<S>::isEmpty()
{
    return sequence.empty();
}

//template <class S>
//bool IntervalSequence<S>::remove(const Element<S>& e);

//template <class S>
//bool IntervalSequence<S>::removeAll(const set<Element<S> >& es);

template <class S>
int IntervalSequence<S>::size() const
{
    return sequence.size();
}

template <class S>
int IntervalSequence<S>::length()
{
    int seq_size = size();
    return (end[seq_size - 1] - start[0] + 1);
}

template <class S>
void IntervalSequence<S>::clear()
{
    sequence.clear();
    start.clear();
    end.clear();
    mapping.clear();
    totalSupport.clear();
}

//template <class S>
//bool IntervalSequence<S>::add(const Element<S>& e);

//template <class S>
//void IntervalSequence<S>::add(const int index, const Element<S>& e);

//template <class S>
//bool IntervalSequence<S>::addAll(const set<Element<S> >& es);

//template <class S>
//bool IntervalSequence<S>::addAll(const int index, const set<Element<S>& es);

//template <class S>
//bool IntervalSequence<S>::retainAll(const set<Element<S> >& es);

template <class S>
bool IntervalSequence<S>::contains(const Element<S>& e)
{
    for (typename map<int, S>::iterator it = mapping.begin();
        it != mapping.end(); ++it)
        if (it->second == e.getSymbol())
            return 1;
    return 0;
}

template <class S>
bool IntervalSequence<S>::containsAll(const set<Element<S> >& es)
{
    bool tmp = 1;
    for (typename set<Element<S> >::iterator it = es.begin();
        tmp && (it != es.end()); ++it)
        tmp &= contains(*it);
    return tmp;
}

template <class S>
IntervalSequence<set<S> >
IntervalSequence<S>::convert(const IntervalEventSet<S>& intves)
{

    map<int, list<Event<S> > > startEvents;
    map<int, list<Event<S> > > endEvents;
    BitSet events;

    vector<int> index  = intves.getIndex();
    vector<int> symbol = intves.getSymbol();
    map<int, S>  mapp  = intves.getMapping();
    BitSet isStart = intves.getIsStart();
    int ies_size   = intves.size();

    int event_index;
    events.resize(index[ies_size - 1] + 1, 0);
    for (int i = 0; i < ies_size; i++) {
        Event<S> e(index[i], isStart[i], symbol[i], mapp[symbol[i]]);
        event_index = e.getIndex();
        events[event_index] = 1;
        if (e.isStart()) {
            if (startEvents.find(event_index) == startEvents.end())
                startEvents.insert(pair<int, list<Event<S> > >
                           (event_index, list<Event<S> >()));
            startEvents[event_index].push_back(e);
        } else {
            if (endEvents.find(event_index) == endEvents.end())
                endEvents.insert(pair<int, list<Event<S> > >
                         (event_index, list<Event<S> >()));
            endEvents[event_index].push_back(e);
        }
    }

    vector<set<S> > chords;
    vector<int> start;
    vector<int> end;

    set<S> current;
    list<Event<S> > currentEvent;
    int lastIndex = 0;
    int events_size = events.size();
    for (int i = 0; i < events_size; i++) {
        if (events[i]) {
            // Write last chord
            if (!current.empty()) {
                start.push_back(lastIndex);
                end.push_back(i);
                chords.push_back(set<S>(current));
            }
            // Refresh current chord
            lastIndex = i;
            if (endEvents.find(i) != endEvents.end()) {
                currentEvent = endEvents[i];
                typename list<Event<S> >::iterator e;
                for (e = currentEvent.begin(); e != currentEvent.end(); ++e)
                    current.erase(mapp[e->getSymbol()]);
            }
            if (startEvents.find(i) != startEvents.end()) {
                currentEvent = startEvents[i];
                typename list<Event<S> >::iterator e;
                for (e = currentEvent.begin(); e != currentEvent.end(); ++e)
                    current.insert(mapp[e->getSymbol()]);
            }
        }
    }

    return IntervalSequence<set<S> >(chords, start, end);

}

template <class S>
int IntervalSequence<S>::indexOf(const Element<S>& e)
{
    int index = -1;
    for (typename map<int, S>::iterator it = mapping.begin();
        it != mapping.end(); ++it) {
        index++;
        if (it->second == e.getSymbol())
            return index;
    }
    return index;
}

template <class S>
int IntervalSequence<S>::lastIndexOf(const Element<S>& e)
{
    vector<S> symbol  = getSymbol();
    for (int index = size() - 1; index >= 0; index--)
        if (e.getSymbol() == symbol[index])
            return index;
    return -1;
}

template <class S>
IntervalSequence<S>
IntervalSequence<S>::subSequence(const int fromIndex, const int toIndex)
{
    vector<int> subSeq(sequence.begin() + fromIndex,
                       sequence.begin() + toIndex);
    vector<int> subStart(start.begin() + fromIndex,
                         start.begin() + toIndex);
    vector<int> subEnd(end.begin() + fromIndex,
                       end.begin() + toIndex);
    map<int, S> subMap;
    map<int, int> subSup;

    int curSeq = 0;
    int durSeq = 0;
    int subSeq_size = subSeq.size();
    for (int i = 0; i < subSeq_size; i++) {
        curSeq = subSeq[i];
        durSeq = duration(subStart[i], subEnd[i]);
        if (subSup.find(curSeq) != subSup.end())
            subSup.insert(pair<int, int>(curSeq, subSup[curSeq] + durSeq));
        else {
            subMap.insert(pair<int, S>(curSeq, mapping[curSeq]));
            subSup.insert(pair<int, int>(curSeq, durSeq));
        }
    }
    return IntervalSequence<S>(subSeq, subStart, subEnd, subMap, subSup);
}

template <class S>
IntervalSequence<S>
IntervalSequence<S>::restrictiveSubSequence(const int from, const int to)
{
    int seq_size = sequence.size();
    int currentStart = 0;
    int currentEnd   = 0;
    int fromIndex    = 0;
    int toIndex      = 0;
    for (int i = 0; (i < seq_size) && (currentStart < from); i++) {
        fromIndex    = i;
        currentStart = start[i];
    }
    if ((fromIndex > seq_size) || (currentEnd >= to))
        return IntervalSequence<S>(vector<S>(), vector<int>(), vector<int>());
    toIndex = fromIndex;
    for (int i = fromIndex; (i < seq_size) && (currentEnd < to); i++) {
        toIndex    = i;
        currentEnd = end[i];
    }
    return subSequence(fromIndex, toIndex);
}

template <class S>
IntervalSequence<S>
IntervalSequence<S>::lazySubSequence(const int from, const int to)
{
    int counter   = 0;
    int fromIndex = start.size();
    int toIndex   = 0;
    int size      = sequence.size();
    for(int i = 0; i < size; i++) {
        if (end[i] >= from) {
            fromIndex = counter;
            break;
        }
        counter++;
    }
    counter = 0;
    for(int i = 0; i < size; i++) {
        if(start[i] >= to) {
            toIndex = counter;
            break;
        }
        counter++;
    }
    if (fromIndex >= toIndex)
	    return IntervalSequence<S>(vector<S>(), vector<int>(), vector<int>());
    else
	    return subSequence(fromIndex, toIndex);
}

template <class S>
bool IntervalSequence<S>::testOrder(const vector<int>& input)
{
    if (input.empty())
        return true;
    int current = input[0];
    int size = input.size();
    for (int i = 1; i < size; i++) {
        if (current > input[i])
            return false;
        current = input[i];
    }
    return true;
}

template <class S>
bool IntervalSequence<S>::testSanity(const IntervalSequence<S>& seq)
{
    if (!testOrder(seq.start)) {
        std::cerr << "You tried to initialize the sequence ";
        std::cerr << "with inequal sized start and end indices." << std::endl;
        return false;
    }
    if (!testOrder(seq.end)) {
        std::cerr << "You tried to initialize the sequence ";
        std::cerr << "with inequal sized start and end indices." << std::endl;
        return false;
    }
    if (!testValideIntervals(seq.start, seq.end)) {
        std::cerr << "You tried to initialize the sequence ";
        std::cerr << "with invalid intervals." << std::endl;
        return false;
    }
    return true;
}

template <class S>
bool IntervalSequence<S>::testValideIntervals(const vector<int>& start,
                                              const vector<int>& end)
{
    if (start.size() != end.size())
        return false;
    int size = start.size();
    for (int i = 0; i < size; i++)
        if (start[i] > end[i])
            return false;
    return true;
}
