/**
 *
 * @file    prepostprocessing.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "prepostprocessing.h"

template <class S>
list<list<S> > sequence2TimeSizedWindow(IntervalSequence<S> sequence,
                                        int windowSize)
{
    list<list<S> > out;
    int maxIndex = sequence.getEnd()[sequence.size() - 1];

    IntervalSequence<S> seq;
    vector<S> symbol;
    for(int sum = 0; sum < maxIndex; sum += windowSize) {
        seq = sequence.lazySubSequence(sum, sum + windowSize);
        symbol = seq.getSymbol();
        list<S> symbols(symbol.begin(), symbol.end());
        out.push_back(symbols);
        seq.clear();
        symbol.clear();
    }
    return out;
}
