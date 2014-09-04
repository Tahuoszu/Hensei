/**
 *
 * @file    postprocessing.hpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    25/04/2014
 *
 */

#include "postprocessing.h"

map<set<Tone>, BitSet > chordSizeFilter(
    const map<set<Tone>, BitSet >& closedChords,
    const int minChordSize,
    const int maxChordSize)
{
    int nbChords = 0;
    map<set<Tone>, BitSet > newmap;
    for (map<set<Tone>, BitSet >::const_iterator it = closedChords.begin();
            it != closedChords.end(); ++it)
    {
        nbChords = (it->first).size();
        if ((nbChords <= maxChordSize) && (nbChords >= minChordSize))
            newmap.insert(pair<set<Tone>, BitSet > \
                          (it->first, it->second));
    }
    return newmap;
}

IntervalSet<Chord> intervalSequence2IntervalSet(
    const IntervalSequence<set<Chord> >& seq)
{
    vector<int> sseq   = seq.getInternalSequence();
    vector<int> sstart = seq.getStart();
    vector<int> send   = seq.getEnd();
    vector<set<Chord> > ssymb = seq.getSymbol();
    map<int, int> sts  = seq.getTotalSupport();
    vector<int> start;
    vector<int> end;
    vector<int> symbol;
    map<int, Chord> mapping;
    int index;
    int seqSize = seq.size();
    for (int i = 0; i < seqSize; i++)
    {
        index = sseq[i];
        Element<set <Chord> > e(index, sstart[i], send[i], ssymb[i], sts[index]);
        set<Chord> chords = e.getSymbol();
        for (set<Chord>::iterator c = chords.begin(); c != chords.end(); ++c)
        {
            start.push_back(e.getStart());
            end.push_back(e.getEnd());
            symbol.push_back(c->getGlobalID());
            mapping.insert(pair<int, Chord>(c->getGlobalID(), *c));
        }
    }
    return IntervalSet<Chord>(start, end, symbol, mapping);
}

/**
 * @brief Converts a set of Tones to a sequence of a set of Chords
 *
 * @param tones      tone set sequence
 * @param occurences closed Chords and their occurence
 *
 * @return seq sequence of Chord sets
 */
IntervalSequence<set<Chord> > toneSetSequence2ChordSetSequence(
    const IntervalSequence<set<Tone> >& tones,
    const map<set<Tone>, BitSet>& occurences)
{
    string label = "";
    map<Chord, BitSet> chordOccurrences;

    for (map<set<Tone>, BitSet>::const_iterator it = occurences.begin();
            it != occurences.end(); ++it) {
        label = Chord::getTonesLabel(it->first);
        Chord current(chordOccurrences.size(), it->first, label);
        chordOccurrences.insert(pair<Chord, BitSet>(current, it->second));
    }

    int nbset = tones.size();
    vector<int> tstart = tones.getStart();
    vector<int> tend   = tones.getEnd();
    vector<int> tseq   = tones.getInternalSequence();
    vector<set<Tone > > tsymb = tones.getSymbol();
    vector<int> start(nbset, 0);
    vector<int> end(nbset, 0);
    vector<set<Chord> > chordSeq;
    chordSeq.resize(nbset);

    Chord c;
    set<Chord> tmp;
    for (int i = 0; i < nbset; i++) {
        Element<set<Tone> > e(tseq[i], tstart[i], tend[i], tsymb[i], 0);
        map<Chord, BitSet>::iterator it;
        for (it = chordOccurrences.begin(); it != chordOccurrences.end(); ++it)
        {
            c = it->first;
            if (containsSet(e.getSymbol(), c.getTones()))
                tmp.insert(c);
        }
        chordSeq[i] = tmp;
        start[i]    = e.getStart();
        end[i]      = e.getEnd();
        tmp.clear();
    }

    return IntervalSequence<set<Chord> >(chordSeq, start, end);
}
