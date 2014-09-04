/**
 *
 * @file    PhraseMiner.cpp
 * @brief   Phrase mining steps of the TSKM
 *          Sequence mining, closed phrase mining and sequence merging
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "PhraseMiner.h"

/********** Constructor **********/

PhraseMiner::PhraseMiner() {}

/********** Destructor **********/

PhraseMiner::~PhraseMiner() {}


/********** Getters **********/

map<set<ClosedSequence>, BitSet > PhraseMiner::getClosedPhrases()
{
    return closedPhrases;
}

map<set<ClosedSequence>, int> PhraseMiner::getClosedPhrasesWithSupport()
{
    return closedPhrasesWithSupport;
}

set<list<Chord> > PhraseMiner::getClosedSequences()
{
    return closedSequences;
}

map<BitSet, Node> PhraseMiner::getPhraseLattice()
{
    return phraseLattice;
}

/********** Setters **********/

void PhraseMiner::setAlphaForClosedPhrases(float alpha)
{
    alphaForClosedPhrases = alpha;
}

void PhraseMiner::setMinimalClosedPhraseSupport(int minCPS)
{
    minimalClosedPhraseSupport = minCPS;
}

void PhraseMiner::setMinimalClosedSequenceSupport(int minCSS)
{
    minimalClosedSequenceSupport = minCSS;
}

void PhraseMiner::setSequenceWindowSize(int seqWinSize)
{
    sequenceWindowSize = seqWinSize;
}

/********** Member functions **********/

IntervalSequence<set<Chord> > PhraseMiner::load(const data_symb* ds)
{
    data d = ds[0].datas;
    vector<int> start = d.start;
    vector<int> end   = d.end;
    vector<int> symID = d.symbol;

    map<int, Chord> symbolMap;

    symb s = ds[0].symbs;
    int symb_size = s.symb_size;
    for (int i = 0; i < symb_size; ++i) {
        string label = s.label[i];
        int globalID = s.symbol[i];
        symbolMap.insert(pair<int, Chord>(globalID,
                                          Chord(globalID, set<Tone>(), label)));
    }

    vector<int> newStart;
    vector<int> newEnd;
    vector<int> newSymID;

    int symID_size = symID.size();
    for (int i = 0; i < symID_size; i++) {
        if (symbolMap.find(symID[i]) != symbolMap.end()) {
            newStart.push_back(start[i]);
            newEnd.push_back(end[i]);
            newSymID.push_back(symID[i]);
        }
    }

    IntervalSet<Chord> iSet(newStart, newEnd, newSymID, symbolMap);
    return IntervalSequence<Chord>::convert(IntervalEventSet<Chord>(iSet));

}

map<BitSet, Node> PhraseMiner::run(const IntervalSequence<set<Chord> >& seq)
{
    std::cout << "chordSeq = " << seq.size() << std::endl;
    map<set<ClosedSequence>, int> phrases = closedSequenceMining(seq);
    std::cout << "phrases  = " << phrases.size() << std::endl;
    map<set<ClosedSequence>, BitSet>
                            closedPhrases = closedPhraseMining(phrases);
    std::cout << "closedPhrases = " << closedPhrases.size() << std::endl;
    exit(1);
    map<BitSet, Node> phraseLattice = sequenceMerging(closedPhrases);
    std::cout << "phraseLattice = " << phraseLattice.size() << std::endl;
    return phraseLattice;
}

map<set<ClosedSequence>, int>
PhraseMiner::closedSequenceMining(const IntervalSequence<set<Chord> >& seq)
{

    // Filtering duplicate successors
    IntervalSequence<set<Chord> > sequence = duplicateSuccessorFilter(seq);
    std::cout << "sequence = " << sequence.size() << std::endl;

    // Windowing
    list<list<set<Chord> > > windows = \
    sequence2TimeSizedWindow(sequence, sequenceWindowSize);
    std::cout << "windows  = " << windows.size() << std::endl;

    std::cout << "Closed sequence mining : " << std::endl;

    // Closed sequence mining init
	PseudoBide bide;
	bide.setMinimalSupport(minimalClosedSequenceSupport);

    // Closed sequence mining run
    set<list<Chord> > closedSeq = bide.run(windows);

    std::cout << "Found " << closedSeq.size() << " closed sequences";
    std::cout << std::endl;

    // Output transformed to phrase mining input
    return closedSetSequence2Transaction(windows, closedSeq);

}

map<set<ClosedSequence>, BitSet>
PhraseMiner::closedPhraseMining(const map<set<ClosedSequence>, int>& phrases)
{

    std::cout << "Closed phrase mining :" << std::endl;

    // Closed phrase mining init
    MarginDCI_Closed_Intersection<ClosedSequence> cp;
    cp.setMinimalSupport(minimalClosedPhraseSupport);
    cp.setAlpha(alphaForClosedPhrases);
    std::cout << "minSup = " << minimalClosedPhraseSupport << std::endl;
    std::cout << "alpha  = " << alphaForClosedPhrases << std::endl;

    // closed phrase mining run
    closedPhrases = cp.run(phrases);
    closedPhrasesWithSupport = cp.getSupportMap();

    std::cout << "Found " << closedPhrases.size() << " closed phrases";
    std::cout << std::endl;

    return closedPhrases;

}

map<BitSet, Node>
PhraseMiner::sequenceMerging(const map<set<ClosedSequence>, BitSet>&
                             closedPhrases)
{
    std::cout << "Sequence merging" << std::endl;

    map<set<ClosedSequence>, BitSet>
    reducedPhrases = preprocessingCPO(closedPhrases);
	std::cout << "Reducing phrases" << std::endl;
	phraseLattice = closedPartialOrder(reducedPhrases);

	std::cout << "Created " << phraseLattice.size() << " closed partial orders";
	std::cout << std::endl;

	return phraseLattice;

}
