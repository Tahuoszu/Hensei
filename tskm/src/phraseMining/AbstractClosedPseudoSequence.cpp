/**
 *
 * @file    AbstractClosedPseudoSequence.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "AbstractClosedPseudoSequence.h"

/********** Getters **********/

set<Chord> AbstractClosedPseudoSequence::getFrequent1Sequences()
{
    if(frequent1Sequences.empty()) {
        map<Chord, int> candidates;
        map<list<set<Chord> >, int>::iterator seq;
        for (seq = sequences.begin(); seq != sequences.end(); ++seq) {
            set<Chord> added;
            list<set<Chord> > curList = seq->first;
            list<set<Chord> >::iterator setc;
            for (setc = curList.begin(); setc != curList.end(); ++setc) {
                set<Chord>::iterator c;
                for (c = setc->begin(); c != setc->end(); ++c) {
                    if (added.find(*c) == added.end()) {
                        if (frequent1Sequences.find(*c) == \
                            frequent1Sequences.end()) {
                            if (candidates.find(*c) != candidates.end()) {
                                int currentSupp = candidates[*c] + \
                                                  supports[curList];
                                candidates[*c] = currentSupp;
                                if (currentSupp >= minSupp) {
                                    frequent1Sequences.insert(*c);
                                }
                            }
                            else {
                                candidates.insert(pair<Chord, int>(*c, 1));
                            }
                            added.insert(*c);
                        }
                    }
                }
            }
        }
    }
    return frequent1Sequences;
}

/********** Setters **********/

void AbstractClosedPseudoSequence::setMinimalSupport(int min)
{
    minSupp = min;
}

void AbstractClosedPseudoSequence::
    setValidFrequent1Sequences(const set<Chord>& set)
{
    frequent1Sequences = set;
}

/********** Member functions **********/

void AbstractClosedPseudoSequence::
    preprocessing(const list<list<set<Chord> > >& input)
{
    list<list<set<Chord> > >::const_iterator seq;
    for (seq = input.begin(); seq != input.end(); ++seq) {
        if (supports.find(*seq) != supports.end())
            supports[*seq] = supports[*seq] + 1;
        else {
            sequences.insert(pair<list<set<Chord> >, int>(*seq, 0));
            supports.insert(pair<list<set<Chord> >, int>(*seq, 1));
        }
    }
}

int AbstractClosedPseudoSequence::
    support(const map<list<set<Chord> >, int>& currentDB)
{
    int supp = 0;
    map<list<set<Chord> >, int>::const_iterator seq;
    for (seq = currentDB.begin(); seq != currentDB.end(); ++seq)
        supp += supports[seq->first];
    return supp;
}

bool AbstractClosedPseudoSequence::isSubSequence(const list<Chord>& s1,
                                                 const list<set<Chord> >& s2)
{
    if (s1.empty())
        return true;
    list<Chord>::const_iterator it1 = s1.begin();
    list<set<Chord> >::const_iterator it2;
    for (it2 = s2.begin(); it2 != s2.end(); it2++) {
        if (it2->find(*it1) != it2->end()) {
            if (it1 != s1.end())
                it1++;
            else
                return true;
        }
    }
    return false;
}

bool AbstractClosedPseudoSequence::isSingleSubSequence(const list<Chord>& s1,
                                                       const list<Chord>& s2)
{
    if (s1.empty())
        return true;
    list<Chord>::const_iterator it1 = s1.begin();
    list<Chord>::const_iterator it2;
    for (it2 = s2.begin(); it2 != s2.end(); it2++) {
        if (*it1 == *it2) {
            if (it1 != s1.end())
                it1++;
            else
                return true;
        }
    }
    return false;
}

bool AbstractClosedPseudoSequence::isSubset(const Chord& s1,
                                            const set<Chord>& s2)
{
    return (s2.find(s1) != s2.end());
}

map<Chord, int> AbstractClosedPseudoSequence::\
localFrequentItems(const map<list<set<Chord> >, int>& currentDB)
{
    map<Chord, int> candidates;
    map<Chord, int> localFrequent;
    map<list<set<Chord> >, int>::const_iterator seq;
    for (seq = currentDB.begin(); seq != currentDB.end(); ++seq) {
        const list<set<Chord> >& curList = seq->first;
        list<set<Chord> >::const_iterator it = curList.begin();
        std::advance(it, seq->second);
        set<Chord> added;
        for (; it != curList.end(); ++it) {
            set<Chord>::iterator c;
            for (c = it->begin(); c != it->end(); ++c) {
                if (added.find(*c) == added.end()) {
                    if (candidates.find(*c) != candidates.end()) {
                        int currentSupp = candidates[*c] + \
                                          supports[seq->first];
                        candidates[*c] = currentSupp;
                    }
                    else {
                        candidates.insert(pair<Chord, int> \
                                          (*c, supports[seq->first]));
                    }
                    added.insert(*c);
                }
            }
        }
    }
    int currentSupport;
    map<Chord, int>::iterator it;
    for (it = candidates.begin(); it != candidates.end(); ++it) {
        currentSupport = it->second;
        if (currentSupport >= minSupp)
            localFrequent.insert(pair<Chord, int>(it->first, currentSupport));
    }
    return localFrequent;
}


map<list<set<Chord> >, int> AbstractClosedPseudoSequence::\
getProjectedDB(const Chord& s, const map<list<set<Chord> >, int>& currentDB)
{
    map<list<set<Chord> >, int> out;
    map<list<set<Chord> >, int>::const_iterator sequence;
    for (sequence = currentDB.begin(); sequence != currentDB.end(); ++sequence) {
        int pointer = sequence->second;
        list<set<Chord> > curList = sequence->first;
        list<set<Chord> >::iterator it = curList.begin();
        std::advance(it, pointer);
        for (; it != curList.end(); ++it) {
            pointer++;
            // Found an occurence of s the suffix of the first instance
            if (isSubset(s, *it) ) {
                // Add this sequence with an updated pointer of the suffix
                out[sequence->first] = pointer;
                break;
            }
        }
    }
    return out;
}
