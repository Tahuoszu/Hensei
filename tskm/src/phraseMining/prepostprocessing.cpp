/**
 *
 * @file    prepostprocessing.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "prepostprocessing.h"

/******************************* Preprocessing ********************************/

IntervalSequence<set<Chord> >
duplicateSuccessorFilter(const IntervalSequence<set<Chord> >& seq)
{

    vector<int> start;
    vector<int> end;
    vector<set<Chord> > symbol;

    vector<int> seqStart = seq.getStart();
    vector<int> seqEnd   = seq.getEnd();
    vector<set<Chord> > seqSymb = seq.getSymbol();

    int seq_size = seq.size();
    for (int i = 0 ; i < seq_size; i++) {
        if (!symbol.empty() &&
            seqSymb[i] == symbol.back() &&
            end.back() == seqStart[i]) {
            end.pop_back();
            end.push_back(seqEnd[i]);
        }
        else {
            start.push_back(seqStart[i]);
            end.push_back(seqEnd[i]);
            symbol.push_back(seqSymb[i]);
        }
    }

    return IntervalSequence<set<Chord> >(symbol, start, end);

}

/******************************* Postprocessing *******************************/

map<set<ClosedSequence>, int>
closedSetSequence2Transaction(const list<list<set<Chord> > >& windows,
                              const set<list<Chord> >& chords)
{
    map<set<ClosedSequence>, int> maps;
    list<list<set<Chord> > >::const_iterator it;
    for (it = windows.begin(); it != windows.end(); ++it) {
        set<ClosedSequence> tmp;
        int idCounter = 0;
        set<list<Chord> >::const_iterator cIt;
        for (cIt = chords.begin(); cIt != chords.end(); ++cIt) {
            if (isSingleSubSetSequence(*cIt, *it))
                tmp.insert(ClosedSequence(*cIt, idCounter));
            idCounter++;
        }
        if (maps.find(tmp) != maps.end())
            maps[tmp] = maps[tmp] + 1;
        else
            maps[tmp] = 1;
    }
    return maps;
}
