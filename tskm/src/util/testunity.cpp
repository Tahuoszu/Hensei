/**
 *
 * @file    testunity.cpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "testunity.h"

void testunity()
{
    cout << "Starting test unity..." << " " << endl;
//    testTones();
//    testChords();
//    testIntervalEventSet();
//    testIntervalSequence();
//    testIntervalSet();
//    testPreprocessing();
//    testPostprocessing();
    cout << "Ending test unity..." << " " << endl;
}

void testTones()
{
    cout << "******************************** ";
    cout << "Test sur les Tones " << endl;
    Tone tone1(4, 5, "ts", "lab1");
    cout << tone1;
    Tone tone2(5, 4, "ts", "lab2");
    cout << tone2;
    cout << "tone1 equal tone 2 ? " << (tone1 == tone2) << " " << endl;
    cout << "tone1 minus tone 2 ? " << (tone1 < tone2) << " " << endl;
    cout << endl;
}

void testChords()
{
    cout << "******************************** ";
    cout << "Test sur les Chords " << endl;
    Tone tone1(4, 5, "ts", "lab1");
    Tone tone2(5, 4, "ts", "lab2");
    Tone tone3(2, 1, "ts", "lab3");
    Tone tone4(3, 2, "ts", "lab4");
    // Set of tones
    set<Tone> tones;
    tones.insert(tone1);
    tones.insert(tone2);
    tones.insert(tone3);
    tones.insert(tone4);
    // Chords
    Chord chord1(tones);
    cout << "Chord 1 : " << endl;
    cout << chord1;
    Chord chord2(1, tones);
    cout << "Chord 2 : " << endl;
    cout << chord2;
    Chord chord3(2, tones, "clab");
    cout << "Chord 3 : " << endl;
    cout << chord3;
    cout << "Size of chords : " << tones.size() << " " << endl;
    cout << endl;
    cout << "chord2 minus chord3 ? " << (chord2 < chord3) << " " << endl;
    cout << endl;
    chord3.insert(tone2);
    cout << "Chord 3 : " << endl;
    cout << chord3;
    chord2.insert(tone4);
    cout << "Chord 2 : " << endl;
    cout << chord2;
    chord1.clear();
    cout << "Chord 1 : " << endl;
    cout << chord1;
    chord1.insertAll(tones);
    cout << "Chord 1 : " << endl;
    cout << chord1;
    tones.erase(tone2);
    chord1.retainAll(tones);
    cout << "Chord 1 : " << endl;
    cout << chord1;
    cout << endl;
}

void testIntervalEventSet()
{
    cout << "******************************** ";
    cout << "Test sur les IntervalEventSet " << endl;
    cout << endl;

    // Parameters
    vector<int> start(10, 0);
    vector<int> end(10, 0);
    vector<int> index(10, 0);
    vector<int> symbol(10, 0);
    vector<double> symbols(10, 0);
    BitSet isStart(10, 0);
    map<int, double> mapp;
    set<Event<double> > es;
    srand(time(NULL));
    for (int i = 0; i < 10 ; i++) {
        start[i]    = randomNumber(20);
        end[i]      = randomNumber(20) + 10;
        index[i]    = randomNumber(10) + 10 * i;
        symbol[i]   = randomNumber(10) + 10 * i;
        symbols[i]  = randomNumber(10) + 10 * i;
        mapp.insert(pair<int, double>(i, randomNumber(10) + 10 * i));
        es.insert(Event<double>(index[i], isStart[i], symbol[i], mapp[i]));
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    cout << "Index Vector   : ";
    print_vector(index);
    cout << "Symbol Vector  : ";
    print_vector(symbol);
    cout << "IsStart Vector : ";
    isStart.print_bitset();
    cout << "Symbols Vector : " << endl;
    print_map(mapp);

    // IntervalEventSet
    IntervalEventSet<double> ies1(index, symbol, isStart, mapp);
    cout << "IntervalEventSet 1 : " << endl;
    cout << ies1;
    cout << endl;
    cout << "Set of events' data : " << endl;
    set<Event<double> >::iterator it;
    for (it = es.begin(); it != es.end(); ++it)
        cout << *it << endl;
    cout << endl;
    IntervalEventSet<double> ies2(es);
    cout << "IntervalEventSet 2 : " << endl;
    cout << ies2;
    cout << endl;
    IntervalSet<double> is(start, end, symbols);
    cout << "IntervalSet : " << endl;
    cout << is;
    IntervalEventSet<double> ies3(is);
    cout << "IntervalEventSet 3 : " << endl;
    cout << ies3;
    cout << endl;

    // Functions
    cout << "IntervalEventSet 1 equal IntervalEventSet 2 ? " \
	 << (ies1 == ies2) << " " << endl;
    cout << "IntervalSet 1 contains event ? ";
    cout << ies1.contains(*(es.begin())) << endl;
    cout << "IntervalSet 1 contains event ? ";
    cout << ies1.contains(Event<double>(10, 4, 2, 2)) << endl;
    cout << "IntervalEventSet 1 contains all es ? ";
    cout << ies1.containsAll(es) << endl;
    cout << "IntervalEventSet 1 size : ";
    cout << ies1.size() << endl;
    cout << "IntervalEventSet 1 is empty ? ";
    cout << ies1.isEmpty() << endl;
    ies1.clear();
    cout << "IntervalEventSet 1 is empty ? ";
    cout << ies1.isEmpty() << endl;
    cout << endl;
}

void testIntervalSequence()
{
    cout << "******************************** ";
    cout << "Test sur les IntervalSequence " << endl;

    // Parameters
    vector<int> start(10, 0);
    vector<int> end(10, 0);
    vector<int> seqId(10, 0);
    vector<double> seq(10, 0);
    map<int, double> m;
    map<int, int> ts;
    srand(time(NULL));
    for (int i = 0; i < 10 ; i++) {
        start[i] = randomNumber(20);
        end[i]   = randomNumber(20) + 10;
        seqId[i] = i;
        seq[i]   = randomNumber(10) + 10 * i;
        m.insert(pair<int, double>(i, randomNumber(100)));
        ts.insert(pair<int, int>(i, randomNumber(10)));
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    std::sort(seq.begin(), seq.end());
    cout << "Start Vector : ";
    print_vector(start);
    cout << "End Vector   : ";
    print_vector(end);
    cout << "Seq Vector   : ";
    print_vector(seq);
    cout << "Seq map : " << endl;
    print_map(m);
    cout << "TotalSupport map : " << endl;
    print_map(ts);

    // IntervalSequence
    IntervalSequence<double> is1(seq, start, end);
    cout << "IntervalSequence 1 : " << endl;
    cout << is1;
    cout << endl;
    IntervalSequence<double> is2(seqId, start, end, m);
    cout << "IntervalSequence 2 : " << endl;
    cout << is2;
    cout << endl;
    IntervalSequence<double> is3(seqId, start, end, m, ts);
    cout << "IntervalSequence 3 : " << endl;
    cout << is3;
    cout << endl;

    // Getters
    cout << "IntervalSequence 3 getters : " << endl;
    cout << "Start Vector    : ";
    print_vector(is3.getStart());
    cout << "End Vector      : ";
    print_vector(is3.getEnd());
    cout << "Sequence Vector : ";
    print_vector(is3.getInternalSequence());
    cout << "Symbol Vector   : ";
    print_vector(is3.getSymbol());
    cout << "Sequence map : " << endl;
    print_map(is3.getInternalMap());
    cout << "TotalSupport map : " << endl;
    print_map(is3.getTotalSupport());
    cout << "map : " << endl;
    print_map(is3.getMap());

    // Functions
    cout << "Element at 5 of IntervalSequence3 :" << endl;
    Element<double> e = is3.get(5);
    cout << e;
    cout << "IntervalSequence 3 size : ";
    cout << is3.size() << endl;
    cout << "IntervalSequence 3 length : ";
    cout << is3.length() << endl;
    cout << "IntervalSet 2 is empty ? ";
    cout << is2.isEmpty() << endl;
    is2.clear();
    cout << "IntervalSet 2 is empty ? ";
    cout << is2.isEmpty() << endl;
    cout << "IntervalSequence 3 contains element e ? ";
    cout << is3.contains(e) << endl;
    Element<double> a = is1.get(9);
    cout << "IntervalSequence 3 contains element a ? ";
    cout << is3.contains(a) << endl;
    set<Element<double> > es;
    es.insert(e);
    cout << "IntervalSequence 3 contains all element ? ";
    cout << is3.containsAll(es) << endl;
    es.insert(a);
    cout << "IntervalSequence 3 contains all element ? ";
    cout << is3.containsAll(es) << endl;
    cout << "Index of e from IntervalSequence 3 : ";
    cout << is3.indexOf(e) << endl;
    cout << "Last index of e from IntervalSequence 3 : ";
    cout << is3.lastIndexOf(e) << endl;
    cout << "Last index of a from IntervalSequence 3 : ";
    cout << is3.lastIndexOf(a) << endl;
    cout << "Subsequence [3 - 8] of IntervalSequence 3 : " << endl;
    cout << is3.subSequence(3, 8)<< endl;
    cout << "Restrictive Subsequence [5 - 25] of IntervalSequence 3 : " << endl;
    cout << is3.restrictiveSubSequence(5, 250) << endl;
    cout << "Lazy Subsequence [5 - 25] of IntervalSequence 3 : " << endl;
    cout << is3.lazySubSequence(5, 25) << endl;

    // Conversion
    vector<int> index(10, 0);
    vector<int> symbol(10, 0);
    BitSet isStart(10, 0);
    map<int, double> mapp;
    IntervalSet<double> is(vector<int>(0), vector<int>(0), vector<double>(0));
    srand(time(NULL));
    for (int i = 0; i < 10 ; i++) {
        index[i]    = randomNumber(20);
        symbol[i]   = randomNumber(20) + 10;
        mapp.insert(pair<int, double>(i, randomNumber(100)));
    }
    cout << "Index Vector   : ";
    print_vector(index);
    cout << "Symbol Vector  : ";
    print_vector(symbol);
    cout << "IsStart Vector : ";
    isStart.print_bitset();
    cout << "Symbols Vector : " << endl;
    for (map<int, double>::const_iterator it = mapp.begin();
        it != mapp.end(); ++it)
        cout << "[" << it->first << " - " << it->second << "]" << endl;
    cout << endl;
    IntervalEventSet<double> ies1(index, symbol, isStart, mapp);
    cout << "IntervalEventSet 1 : " << endl;
    cout << ies1;
    cout << endl;

    //cout << "Conversion to an IntervalSequence : " << endl;
    //IntervalEventSet<set<double> > ies = is3.convert(ies1);
    //cout << ies;
    set<double> s1, s2;
    for (int i = 0; i < 10; i++)
        s1.insert(i);
    for (int i = 0; i < 2; i++)
        s2.insert(i);
    cout << "s2 subsequence of s1    ? ";
    cout << isSubSequence(s1, s2) << endl;
    list<set<double> > l1, l2;
    l1.push_back(s1);
    l1.push_back(s2);
    l2.push_back(s1);
    cout << "l2 subSetSequence of l1 ? ";
    cout << isSubSetSequence(l1, l2) << endl;
    list<double> v1, v2;
    std::copy(s1.begin(), s1.end(), v1.begin());
    cout << "v1 singleSubSetSequence of l1 ? ";
    cout << isSingleSubSetSequence(v1, l1) << endl;
    cout << "v1 singleSubSetSequence of l2 ? ";
    cout << isSingleSubSetSequence(v1, l2) << endl;

}

void testIntervalSet()
{
    cout << "******************************** ";
    cout << "Test sur les IntervalSet " << endl;

    // Parameters
    vector<int> start(10, 0);
    vector<int> end(10, 0);
    vector<int> symbolId(10, 0);
    vector<double> symbols(10, 0);
    map<int, double> mapp;
    set<Interval<double> > intvs;
    srand(time(NULL));
    for (int i = 0; i < 10 ; i++) {
        start[i]    = randomNumber(20);
        end[i]      = randomNumber(20) + 10;
        symbolId[i] = i + 1;
        symbols[i]  = randomNumber(10) + 10 * i;
        mapp.insert(pair<int, double>(i, randomNumber(10) + 10 * i));
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    std::sort(symbolId.begin(), symbolId.end());
    cout << "Start Vector    : ";
    print_vector(start);
    cout << "End Vector      : ";
    print_vector(end);
    cout << "SymbolId Vector : ";
    print_vector(symbolId);
    cout << "Symbols Vector  : ";
    print_vector(symbols);
    for (int i = 0; i < 10 ; i++)
        intvs.insert(Interval<double>(start[i], end[i], symbols[i]));

    // IntervalSet
    IntervalSet<double> is1(start, end, symbols);
    cout << "IntervalSet 1 : " << endl;
    cout << is1;
    cout << endl;
    IntervalSet<double> is2(start, end, symbolId, mapp);
    cout << "IntervalSet 2 : " << endl;
    cout << is2;
    cout << endl;
    set<Interval<double> >::iterator it;
    cout << "Set of Intervals' data: " << endl;
    for (it = intvs.begin(); it != intvs.end(); ++it)
        cout << *it << endl;
    IntervalSet<double> is3(intvs);
    cout << "IntervalSet 3 : " << endl;
    cout << is3;
    cout << endl;

    // Getters
    cout << "IntervalSet 3 getters : " << endl;
    cout << "Start Vector    : ";
    print_vector(is3.getStart());
    cout << "End Vector      : ";
    print_vector(is3.getEnd());
    cout << "SymbolId Vector : ";
    print_vector(is3.getSymbol());

    // Functions
    /*
    cout << "IntervalSet 3 add new intervals : ";
    intvs.clear();
    intvs.insert(Interval<double>(15, 20, 100));
    intvs.insert(Interval<double>(10, 30, 70));
    cout << is3.addAll(intvs) << endl; // Marche pas
    cout << is3 << endl;
    */
    cout << "IntervalSet 3 is empty ? ";
    cout << is3.isEmpty() << endl;
    cout << "IntervalSet 3 is cleared..." << endl;
    is3.clear();
    cout << "IntervalSet 3 is empty ? ";
    cout << is3.isEmpty() << endl;
    cout << "IntervalSet 1 contains interval ? ";
    cout << is1.contains(*(intvs.begin())) << endl;
    cout << "IntervalSet 1 contains interval [1 - 5] ? ";
    cout << is1.contains(Interval<double>(1, 5, 10)) << endl;
    cout << "IntervalSet 1 contains all intvs ? ";
    cout << is1.containsAll(intvs) << endl;
    cout << "Subset [5 - 20] of IntervalSet 1 :" << endl;
    IntervalSet<double> is4 = is1.subSet(5, 20);
    cout << is4 << endl;

}

void testPreprocessing()
{
    cout << "******************************** ";
    cout << "Test sur les methodes de preprocessing " << endl;

    // Parameters
    vector<int> start(10, 0);
    vector<int> end(10, 0);
    vector<int> symbolId(10, 0);
    vector<double> symbols(10, 0);
    map<int, double> mapp;
    srand(time(NULL));
    for (int i = 0; i < 10 ; i++) {
        start[i]    = randomNumber(20);
        end[i]      = randomNumber(20) + 10;
        symbolId[i] = i + 1;
        symbols[i]  = randomNumber(10) + 10 * i;
        mapp.insert(pair<int, double>(i, symbols[i]));
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    std::sort(symbolId.begin(), symbolId.end());
    cout << "Start Vector    : ";
    print_vector(start);
    cout << "End Vector      : ";
    print_vector(end);
    cout << "SymbolId Vector : ";
    print_vector(symbolId);
    cout << "Symbols Vector  : ";
    print_vector(symbols);
    cout << "Map :" << endl;
    print_map(mapp);

    // IntervalSet
    IntervalSet<double> is(start, end, symbolId, mapp);
    cout << "IntervalSet : " << endl;

    // Getters
    cout << "IntervalSet getters : " << endl;
    cout << "Start Vector    : ";
    print_vector(is.getStart());
    cout << "End Vector      : ";
    print_vector(is.getEnd());
    cout << "SymbolId Vector : ";
    print_vector(is.getSymbol());
    cout << "Map :" << endl;
    print_map(is.getMap());

    // Methodes

    cout << "MarginGapFilter" << endl;
    IntervalSet<double> tones = marginalGapFilter(is, 0.1, 100);
    cout << tones << endl;
    cout << "MinDurationIntervalSetFilter" << endl;
    tones = minDurationIntervalSetFilter(is, 100);
    cout << tones << endl;

}

void testPostprocessing()
{
    cout << "******************************** ";
    cout << "Test sur les methodes de postprocessing " << endl;

    // Parameters
    vector<int> start(10, 0);
    vector<int> end(10, 0);
    vector<set<Tone> > symbol;
    set<Tone> tones;
    srand(time(NULL));
    for (int i = 0; i < 10 ; i++) {
        start[i] = randomNumber(10) + 10 * i;
        end[i]   = randomNumber(10) + 10 * i + 10;
    }
    for (int i = 0; i < 10 ; i++) {
        Tone t(start[i], end[i], "", "");
        tones.insert(t);
        cout << t << endl;
    }
    map<set<Tone>, BitSet> closedChords;
    for (int i = 0; i < 5; i++)
        closedChords.insert(std::pair<set<Tone>, BitSet >
                            (tones, BitSet(1)));
    set<Chord> chords;
    map<set<Tone>, BitSet>::iterator it = closedChords.begin();
    for (int i = 0; i < 5; i++) {
        chords.insert(Chord(i, tones));
        symbol.push_back(it->first);
        ++it;
    }

    // Methodes

    cout << "ChordSizeFilter" << endl;
    map<set<Tone>, BitSet> tf = chordSizeFilter(closedChords, 0, 0);
    cout << "Map : " << endl;
    cout << "IntervalSequence2IntervalSet" << endl;
    IntervalSequence<set<Chord> > seq;
    IntervalSet<Chord> is = intervalSequence2IntervalSet(seq);
    cout << is << endl;

    cout << "ToneSetSequence2ChordSetSequence" << endl;
    IntervalSequence<set<Tone> > isst(symbol, end, start);
    IntervalSequence<set<Chord> > issc = \
    toneSetSequence2ChordSetSequence(isst, tf);
    cout << issc << endl;

}
