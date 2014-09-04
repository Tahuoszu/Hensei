/**
 *
 * @file    MergeSequences.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "MergeSequences.h"

Node MergeSequences::run(const set<ClosedSequence>& sequences)
{
    preprocessing(sequences);
    mergeSequences(sequences);
    return Node();
}

void MergeSequences::mergeSequences(const set<ClosedSequence>& sequences)
{
    int counter = 0;
    set<ClosedSequence>::const_iterator seq;
    for (seq = sequences.begin(); seq != sequences.end(); ++seq) {
        list<Chord> chords = seq->getSequence();
        map<int, Node> maps = pointers[chords];
        map<int, Node>::iterator e;
        for (e = maps.begin(); e != maps.end(); ++e) {
            if ((e->second).getInternalID() == -1) {
                int i = e->first;
                list<Chord>::iterator it = chords.begin();
                std::advance(it, i);
                Node c(counter++, *it);
                add(maps, i, c);
                set<ClosedSequence>::const_iterator sec;
                for (sec = sequences.begin(); sec != sequences.end(); ++sec) {
                    if (!(*seq == *sec)) {
                        list<Chord> chds = sec->getSequence();
                        map<int, Node> mapp = pointers[chds];
                        map<int, Node>::iterator f;
                        for (f = mapp.begin(); f != mapp.end(); ++f) {
                            int j = f->first;
                            if (((f->second).getInternalID() == -1) &&
                                (pathPreserving(sequences, chords, i, chds, j)))
                                    add(mapp, j, c);
                        }
                    }
                }
            }
        }
    }
}

bool MergeSequences::pathPreserving(const set<ClosedSequence>& sequences,
                                    const list<Chord>& seq1, int i,
                                    const list<Chord>& seq2, int j)
{

    list<Chord>::const_iterator it1;
    list<Chord>::const_iterator it2;
    std::advance(it1, i);
    std::advance(it2, j);

    if (*it1 == *it2) {

        list<Chord> seq1seq2(seq1.begin(), ++it1);
        list<Chord> seq2seq1(seq2.begin(), ++it2);

        seq1seq2.insert(seq1seq2.end(), it2, seq2.end());
        seq2seq1.insert(seq2seq1.end(), it1, seq1.end());

        bool b1 = false;
        bool b2 = false;

        set<ClosedSequence>::const_iterator seqTmp;
        for (seqTmp = sequences.begin(); seqTmp != sequences.end(); ++seqTmp) {
            list<Chord> chords = seqTmp->getSequence();
            if (isSubSequence(seq1seq2, chords)) {
                if (b2)
                    return true;
                else
                    b1 = true;
            }
            if (isSubSequence(seq2seq1, chords)) {
                if (b1)
                    return true;
                else
                    b2 = true;
            }
        }
    }

    return false;

}

bool MergeSequences::isSubSequence(const list<Chord>& s1, const list<Chord>& s2)
{
    return (std::search(s2.begin(), s2.end(), s1.begin(), s1.end()) != s2.end());
}

void MergeSequences::preprocessing(const set<ClosedSequence>& sequences)
{
    set<ClosedSequence>::const_iterator seq;
    for (seq = sequences.begin(); seq != sequences.end(); ++seq) {
        list<Chord> chords = seq->getSequence();
        int counter = 0;
        map<int, Node> maps;
        int seq_size = chords.size();
        for (int i = 0; i < seq_size; i++)
            maps.insert(pair<int, Node>(counter++, Node()));
        pointers.insert(pair<list<Chord>, map<int, Node> >(chords, maps));
    }
}

void MergeSequences::add(map<int, Node> maps, int i, Node c)
{
    maps.insert(pair<int, Node>(i, c));
    if (maps[i - 1].getInternalID() != -1) // i > 0
        add(maps[i - 1], c);
    if (maps[i + 1].getInternalID() != -1) // i + 1 < maps.size()
        add(c, maps[i + 1]);
}

void MergeSequences::add(Node s1, Node s2)
{
    if (!(s1 == s2))
        graph.add(s1, s2);
}
