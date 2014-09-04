/**
 *
 * @file    PseudoBide.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "PseudoBide.h"

/********** Member functions **********/

set<list<Chord> > PseudoBide::run(const list<list<set<Chord> > >& sequence)
{
    preprocessing(sequence);
    bide();
    return closedSequences;
}

set<list<Chord> > PseudoBide::bide()
{
    set<Chord> frequent1Sequences = getFrequent1Sequences();
    list<Chord> slist;
    map<list<set<Chord> >, int> currentDB;
    set<Chord>::iterator it;

    for(it = frequent1Sequences.begin(); it != frequent1Sequences.end(); ++it) {
        // Project DB and test whether there are enough transactions
        currentDB = getProjectedDB(*it, sequences);
        if (support(currentDB) < minSupp)
            continue;

        slist.push_back(*it);
        if (backScan(slist, currentDB))
            bide(currentDB, slist);

        currentDB.clear();
        slist.clear();
    }
    //exit(1);

    return closedSequences;
}

void PseudoBide::bide(const map<list<set<Chord> >, int>& currentDB,
                      const list<Chord>& seqPrefix)
{
    map<Chord, int> localFI = localFrequentItems(currentDB);
    //TODO: test whether to switch the conditions
    if (!frequentExtensionItems(localFI, support(currentDB))) // Forward check
        if (backwardClosednessCheck(seqPrefix, currentDB))    // Backward check
            closedSequences.insert(list<Chord>(seqPrefix));

    list<Chord> iSeqPrefix;
    map<list<set<Chord> >, int> iSeqDB;
    map<Chord, int>::iterator it;
    for (it = localFI.begin(); it != localFI.end(); ++it) {
        iSeqPrefix = seqPrefix;
        iSeqPrefix.push_back(it->first);
        iSeqDB = getProjectedDB(it->first, currentDB);

        if (support(iSeqDB) < minSupp)
            continue;

        if (backScan(iSeqPrefix, iSeqDB))
            bide(iSeqDB, iSeqPrefix);
    }
}

bool PseudoBide::frequentExtensionItems(const map<Chord, int>& freq,
                                        int currentSupport)
{
    map<Chord, int>::const_iterator it;
    for (it = freq.begin(); it != freq.end(); ++it)
        if (it->second == currentSupport)
            return true;
    return false;
}

bool PseudoBide::backScan(const list<Chord>& prefix,
                          const map<list<set<Chord> >, int>& currentDB)
{
    if (currentDB.empty())
        return false;

    map<list<set<Chord> >, vector<vector<int> > > borders;
    list<set<Chord> > lsc;
    list<set<Chord> > sublsc;
    map<list<set<Chord> >, int>::const_iterator seq;
    for (seq = currentDB.begin(); seq != currentDB.end(); seq++) {
        lsc = seq->first;
        sublsc = subList(lsc, 0, seq->second);
        borders.insert(pair<list<set<Chord> >, vector<vector<int> > >\
                       (lsc, getPeriodBorders(prefix, sublsc)));
    }

    int prefix_size = prefix.size();
    for(int i = 0; i < prefix_size; i++) {
        set<Chord> commonInMaxPeriod;
        map<list<set<Chord> >, int>::const_iterator seqIt = currentDB.begin();
        // First found fills the list of elements common to all periods
        list<set<Chord> > seq = seqIt->first;
        vector<int> border    = borders[seq][i];
        list<set<Chord> > subSeq = subList(seq, border[0], border[1]);
        if (subSeq.empty())
            commonInMaxPeriod.clear();
        list<set<Chord> >::iterator s;
        for (s = subSeq.begin(); s != subSeq.end(); ++s)
            commonInMaxPeriod.insert(s->begin(), s->end());

        // All successive found
        set<Chord> tmp;
        for (seqIt = currentDB.begin(); seqIt != currentDB.end(); ++seqIt) {
            seq    = seqIt->first;
            border = borders[seq][i];
            set<Chord> commonInThisPeriod;
            list<set<Chord> > subSeq = subList(seq, border[0], border[1]);
            for (s = subSeq.begin(); s != subSeq.end(); ++s)
                commonInThisPeriod.insert(s->begin(), s->end());
            set<Chord>::iterator it = commonInMaxPeriod.begin();
            tmp = commonInMaxPeriod;
            for (; it != commonInMaxPeriod.end(); ++it)
                if (commonInThisPeriod.find(*it) == commonInThisPeriod.end())
                    tmp.erase(*it);
            commonInMaxPeriod = tmp;
            if (commonInMaxPeriod.empty())
                break;
        }
        if (!commonInMaxPeriod.empty())
            return false; // Found a valid expansion
    }

    return true;          // All were empty
}

bool PseudoBide::backwardClosednessCheck(const list<Chord>& prefix,
                                         const map<list<set<Chord> >,
                                         int>& currentDB)
{
    if (currentDB.empty())
        return false;

    map<list<set<Chord> >, vector<vector<int> > > borders;
    map<list<set<Chord> >, int>::const_iterator seq;
    for (seq = currentDB.begin(); seq != currentDB.end(); ++seq)
        borders.insert(pair<list<set<Chord> >, vector<vector<int> > >\
                       (seq->first, getPeriodBorders(prefix, seq->first)));

    int prefix_size = prefix.size();
    for(int i = 0; i < prefix_size; i++) {
        set<Chord> commonInMaxPeriod;
        map<list<set<Chord> >, int>::const_iterator seqIt = currentDB.begin();
        // First found fills the list of elements common to all periods
        list<set<Chord> > seq = seqIt->first;
        vector<int> border    = borders[seq][i];
        list<set<Chord> > subSeq = subList(seq, border[0], border[1]);
        list<set<Chord> >::iterator s;
        for (s = subSeq.begin(); s != subSeq.end(); ++s)
            commonInMaxPeriod.insert(s->begin(), s->end());

        // All successive found
        set<Chord> tmp;
        for (seqIt = currentDB.begin(); seqIt != currentDB.end(); ++seqIt) {
            seq    = seqIt->first;
            border = borders[seq][i];
            set<Chord> commonInThisPeriod;
            list<set<Chord> > subSeq = subList(seq, border[0], border[1]);
            for (s = subSeq.begin(); s != subSeq.end(); ++s)
                commonInThisPeriod.insert(s->begin(), s->end());
            set<Chord>::iterator it = commonInMaxPeriod.begin();
            tmp = commonInMaxPeriod;
            for (; it != commonInMaxPeriod.end(); ++it)
                if (commonInThisPeriod.find(*it) == commonInThisPeriod.end())
                    tmp.erase(*it);
            commonInMaxPeriod = tmp;
            if (commonInMaxPeriod.empty())
                break;
        }
        if (!commonInMaxPeriod.empty())
            return false; // Found a valid expansion
    }

    return true;          // All were empty
}

vector<vector<int> >
PseudoBide::getPeriodBorders(const list<Chord>& prefix,
                             const list<set<Chord> >& currentSequence)
{
    vector<vector<int> > last(prefix.size(), vector<int>(2,0));
    if (prefix.empty())
        return last;

    // Start of max periods
    list<set<Chord> >::const_iterator seqIt = currentSequence.begin();
    list<Chord>::const_iterator prefixIt    = prefix.begin();
    int idx	 = 0;
    int incr = 0;
    int lastIdx	= 0;
    for (; seqIt != currentSequence.end(); ++seqIt) {
        if (isSubset(*prefixIt, *seqIt)) {
            last[idx++][0] = lastIdx;
            if (++prefixIt == prefix.end())
                break;
            lastIdx = incr + 1;
        }
        incr++;
    }

    // End of max periods
    list<set<Chord> >::const_reverse_iterator rseqIt = currentSequence.rbegin();
    list<Chord>::const_reverse_iterator rprefixIt    = prefix.rbegin();
    idx      = last.size() - 1;
    lastIdx	 = currentSequence.size() - 1;
    for (; rseqIt != currentSequence.rend(); ++rseqIt) {
        if (isSubset(*rprefixIt, *rseqIt)) {
            last[idx--][1] = lastIdx;
            if (++rprefixIt == prefix.rend())
                break;
        }
        lastIdx--;
    }

    return last;
}
