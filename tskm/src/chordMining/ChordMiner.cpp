/**
 *
 * @file    ChordMiner.cpp
 * @brief   Closed chord mining
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "ChordMiner.h"
#include "MinDur_MarginDCI_Closed_Intersection.h"
#include "preprocessing.h"
#include "postprocessing.h"
#include "test.h"

/********** Constructor **********/

ChordMiner::ChordMiner() {}

/********** Destructor **********/

ChordMiner::~ChordMiner() {}

/********** Getters **********/

Chord ChordMiner::getChord(set<Tone> tones)
{
    string label = "(support : ";
    label += closedChordsWithSupport[tones];
    label += ")";
	return Chord(0, tones, label);
}

map<set<Tone>, BitSet > ChordMiner::getClosedChords()
{
	return closedChords;
}

IntervalSequence<set<Chord> > ChordMiner::getClosedChordSetSequence()
{
	return closedChordSetSequence;
}

map<set<Tone>, int> ChordMiner::getClosedChordsWithSupport()
{
	return closedChordsWithSupport;
}

Graph<Chord> ChordMiner::getResultAsLattice()
{
    Graph<Chord> graph;
    // For each remaining closed Chord
    map<set<Tone>, BitSet>::iterator e;
    for (e = closedChords.begin(); e != closedChords.end(); ++e) {
        set<Tone> tones = e->first;
        graph.add(getChord(tones));
        // Get all superNode candidates
        set<set<Tone> > superNodeCandidates;
        map<set<Tone>, BitSet>::iterator eSuper;
        for (eSuper = closedChords.begin();
             eSuper != closedChords.end(); ++eSuper) {
            set<Tone> superTones = eSuper->first;
            if (std::includes(superTones.begin(), superTones.end(),
                              tones.begin(), tones.end()) &&
                (superTones != tones))
                superNodeCandidates.insert(superTones);
        }
        // Test if there exists any subNode between the current closed Chord
        // and the super node candidate
        set<set<Tone> > superNodes;
        set<set<Tone> >::iterator it1;
        for (it1 = superNodeCandidates.begin();
             it1 != superNodeCandidates.end(); ++it1) {
            set<Tone> t1 = *it1;
            bool toAdd = true;
            set<set<Tone> >::iterator it2;
            for (it2 = superNodeCandidates.begin();
                 it2 != superNodeCandidates.end(); ++it2) {
                set<Tone> t2 = *it2;
                if (std::includes(t1.begin(), t1.end(), t2.begin(), t2.end()) &&
                    (t1 != t2)) {
                    toAdd = false;
                    break;	// This node is no direct super node
                }
            }
            if (toAdd && (tones != t1))
                graph.add(getChord(t1), getChord(tones));
        }
    }
    return graph;
}

/********** Setters **********/

void ChordMiner::setMarginalGapFilterAlpha(float alpha)
{
	marginalGapFilterAlpha = alpha;
}

void ChordMiner::setMarginalGapMaxDuration(int duration)
{
	marginalGapMaxDuration = duration;
}

void ChordMiner::setMarginAlpha(float alpha)
{
	marginAlpha = alpha;
}

void ChordMiner::setMaximalChordSize(int maximal)
{
	maximalChordSize = maximal;
}

void ChordMiner::setMinimalChordDuration(int minimal)
{
	minimalChordDuration = minimal;
}

void ChordMiner::setMinimalChordSize(int minimal)
{
	minimalChordSize = minimal;
}

void ChordMiner::setMinimalSupport(int minimal)
{
	minimalSupport = minimal;
}

void ChordMiner::setMinimalToneDuration(int minimal)
{
	minimalToneDuration = minimal;
}

/********** Member functions **********/

IntervalSet<Tone> ChordMiner::load(const data& d, const symb& s)
{
    map<int, Tone> symbolMap;
    map<string, int> seriesName;
    for (int i = 0; i < s.symb_size; i++) {
        string label = s.label[i];
        int globalID = s.symbol[i];
        if (seriesName.find(label) == seriesName.end())
            seriesName.insert(pair<string, int>(label, seriesName.size()));
        int seriesID = seriesName[label];
        symbolMap.insert(pair<int, Tone>
                         (globalID, Tone(globalID, seriesID, label, label)));
    }
    return IntervalSet<Tone>(d.start, d.end, d.symbol, symbolMap);
}

IntervalSet<Tone> ChordMiner::load(const data_symb* ds)
{
    vector<int> start;
    vector<int> end;
    vector<int> symbol;

    int seriesID = -1;
    map<int, Tone> globalID;
    map<string, int> lastTones;
    do {

        seriesID++;
        IntervalSet<Tone> tones = load(ds[seriesID].datas, ds[seriesID].symbs);

        start.insert(start.end(), tones.getStart().begin(),
                     tones.getStart().end());
        end.insert(end.end(), tones.getEnd().begin(), tones.getEnd().end());

        map<int, Tone> s = tones.getMap();
        int symb_size = tones.getSymbol().size();
        for (int i = 0; i < symb_size; i++) {
            int symbID = tones.getSymbol()[i];
            Tone t = s[symbID];
            string series = ds[seriesID].filename + "_" + t.getLabel();
            if (lastTones.find(series) != lastTones.end())
                symbol.push_back(lastTones[series]);
            else {
                int currentID = lastTones.size();
                lastTones.insert(pair<string, int>(series, currentID));
                symbol.push_back(currentID);
                globalID.insert(pair<int, Tone>(currentID,
                                                Tone(currentID, seriesID,
                                                ds[seriesID].filename,
                                                series)));
            }
        }
    } while (!ds[seriesID].lastfile);
    return IntervalSet<Tone>(start, end, symbol, globalID);
}

IntervalSequence<set<Chord> > ChordMiner::run(const IntervalSet<Tone>& tones)
{

	/***** PREPROCESSING *****/

	// Apply marginal gap filter and minimal duration filter
	std::cout << "Tones = " << tones.size() << std::endl;
	IntervalSet<Tone> filtered;
	filtered = marginalGapFilter<Tone>(tones, marginalGapFilterAlpha,
									   marginalGapMaxDuration);
    std::cout << "Tones filtered MGF = " << filtered.size() << std::endl;

	filtered = minDurationIntervalSetFilter<Tone>(tones, minimalToneDuration);
    std::cout << "Tones filtered MDI = " << filtered.size() << std::endl;

	// Convert from tone intervals to sequence of chords (set of tones)
	IntervalEventSet<Tone> iEvents(filtered);
    std::cout << "Interval Event = " << iEvents.size() << std::endl;

	IntervalSequence<set<Tone> > chordSequence = \
	IntervalSequence<Tone>::convert(iEvents);
    std::cout << "Chord Sequence = " << chordSequence.size() << std::endl;

	/***** CLOSED CHORD MINING *****/

	// Init closed chord mining

	MinDur_MarginDCI_Closed_Intersection<Tone> ci;
	ci.setMinDuration(minimalChordDuration);
	ci.setMinimalSupport(minimalSupport);
	ci.setAlpha(marginAlpha);
	// Run closed chord mining
	closedChords            = ci.run(chordSequence);
	closedChordsWithSupport = ci.getSupportMap();
	cout << "Found " << closedChords.size() << " Closed Chords" << endl;

	/***** POSTPROCESSING *****/

	closedChords = \
	chordSizeFilter(closedChords, minimalChordSize, maximalChordSize);
	std::cout << "closedChords = " << closedChords.size() << std::endl;
	map<set<Tone>, BitSet>::iterator it;
	closedChordSetSequence = \
	toneSetSequence2ChordSetSequence(chordSequence, closedChords);
	std::cout << "closedChordSetSequence = " << closedChordSetSequence.size() << std::endl;
	closedChordGraph = getResultAsLattice();

	return closedChordSetSequence;

}

void ChordMiner::save(string pathname)
{

    // Output Chords Filename
    string chord_filename = "chord_sequence.int";
    string symbs_filename = "chord_sequence.int.tskm";
    string graph_filename = "chord_graph.dot";

    // Output Stream
    std::stringstream ss;

    // Write Chords Intervals Data
    IntervalSet<Chord> chords = \
    intervalSequence2IntervalSet(closedChordSetSequence);
    int chords_size = chords.size();
    for (int i = 0; i < chords_size; i++) {
        ss << chords.getSymbol()[i] << "\t" << chords.getStart()[i] << "\t";
        ss << chords.getEnd()[i] << "\n";
    }
    saveFile(pathname, chord_filename, ss);
    ss.str(string());

    // Write Chords Symbols
    string label = "";
    map<int, Chord>::const_iterator it;
    for (it = chords.getMap().begin(); it !=  chords.getMap().end(); ++it) {
        label = it->second.getLabel();
        ss << it->first << "\t" << label << "\t" << label << "\n";
    }
    saveFile(pathname, symbs_filename, ss);
    ss.str(string());

    // Write Chords Graph
    //ss << closedChordGraph.getString();
	//saveFile(pathname, graph_filename, ss);
    //ss.str(string());

}

void ChordMiner::show()
{
    //system("dot -Tps -o graphe.ps graphe.dot");
}

