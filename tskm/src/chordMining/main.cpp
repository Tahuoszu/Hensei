/**
 *
 * @file    main.cpp
 * @brief   Main file
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include <iostream>
#include <climits>
#include <string>

#include "ChordMiner.h"
#include "ChordSymbol.h"
#include "PhraseMiner.h"
#include "IntervalSequence.h"
#include "IntervalSet.h"
#include "io.h"
#include "testunity.h"

int main (int argc, char * const argv[])
{

    /*************************** Global Parameters ****************************/

    string pathToIntervalFiles = "./sipo/other/";
	string IntervalFilePrefix  = "";

    string pathToSave = "./tmpfiles/";
    bool saveFiles = false;
	data_symb* ds;

	ChordMiner cm;
	PhraseMiner pm;

    /********************* Input / Output Files Settings **********************/

    if (argc < 2 || argc > 4) {
        std::cout << "Usage :" << std::endl;
        std::cout << "./tskm [input] [output : optional] [prefix : optional]";
        std::cout << std::endl;
		std::cout << "****************" << std::endl;
		std::cout << "1st argument : Path, where the input files can be found";
		std::cout << std::endl;
        std::cout << "2nd argument : ";
        std::cout << "Path, where the output files should be saved";
        std::cout << std::endl;
		std::cout << "3rd argument : Prefix for the input files" << std::endl;
		std::cout << "****************" << std::endl;
		std::cout << "Example :";
		std::cout << "./tskm 01_tone_input/ ATE-7,89_  yourPathWhereToSave";
        std::cout << std::endl;
		return 1;
    }
    else
        pathToIntervalFiles = argv[1];

    if (argc > 2) {
        saveFiles  = true;
        pathToSave = argv[2];
    }

    if (argc > 3)
        IntervalFilePrefix  = argv[3];

	/******************** Setting all Chord mining params *********************/

	// Marginal Gap Filter Settings
    cm.setMarginalGapFilterAlpha(0.5);
    cm.setMarginalGapMaxDuration(100);
    // Minimal Tone Duration
    cm.setMinimalToneDuration(20);
    // Closed Chord Settings
    cm.setMinimalChordDuration(50);
    cm.setMinimalSupport(2000);
    cm.setMarginAlpha(0.1);
    // Minimal and maximal chord cardinality
    cm.setMinimalChordSize(2);
    cm.setMaximalChordSize(3);

    /******************** Setting all Phrase mining params ********************/

    pm.setSequenceWindowSize(1000);
    pm.setAlphaForClosedPhrases(0.3);
    pm.setMinimalClosedPhraseSupport(8);
    pm.setMinimalClosedSequenceSupport(8);

    /****************************** Chord mining ******************************/

    ds = loadfiles(pathToIntervalFiles, IntervalFilePrefix);
    std::cout << "Loading Tones..." << std::endl;
    IntervalSet<Tone> tones = cm.load(ds);
    std::cout << "Starting Chord mining..." << std::endl;
    IntervalSequence<set<Chord> > seq = cm.run(tones);
	// Show Chord mining result
    cm.show();
    if (saveFiles)
        cm.save(pathToSave);
    std::cout << "Chord Mining done..." << std::endl;
    std::cout << std::endl;

    /****************************** Phrase mining *****************************/

    ds = loadfiles(pathToSave, IntervalFilePrefix);
    std::cout << "Loading Chords..." << std::endl;
    IntervalSequence<set<Chord> > chordSeq;
    chordSeq = pm.load(ds);
    std::cout << "Starting Phrase mining..." << std::endl;
    map<BitSet, Node> phrases = pm.run(chordSeq);
//    map<BitSet, Node>::iterator it = phrases.begin();
//    for (; it != phrases.end(); ++it)
//        std::cout << it->first << std::endl << it->second << std::endl;
//    return 1;
	// Show Chord mining result
    //pm.show();
	if (saveFiles)
    //    pm.save(pathToSave);
    std::cout << "Phrase Mining done..." << std::endl;

    return 0;

}

