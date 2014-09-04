/**
 *
 * @file    preprocessing.cpp
 * @brief
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "preprocessing.h"

template <class S>
IntervalSet<S> marginalGapFilter(const IntervalSet<S>& tones,
                                 float alpha, float max)
{
    // Parameters
    float alphaComplement  = 1.0 - alpha;
    float gapMaximum       = max;
    bool originalGapFilter = true;

    // Current variables
    int currentStart;
    int currentEnd;
    int currentDur;

    // New values of IntervalSet
    vector<int> newStart;
    vector<int> newEnd;
    vector<int> newSymbol;

    // Stack variables
    int stacksize;
    map<int, int> currentTones;
    stack<int> start;
    stack<int> end;
    stack<int> dur;

    map<int, S> mapping = tones.getMap();
    typename map<int, S>::iterator s ;
    for (s = mapping.begin(); s != mapping.end(); ++s) {
        currentTones = tones.get(s->first);

        // Tones to process
        map<int, int>::iterator e;
        for (e = currentTones.begin(); e != currentTones.end(); ++e) {
            currentStart = e->first;
            currentEnd   = e->second;
            currentDur   = duration(currentStart, currentEnd);

            // Merge backward
            while (!start.empty() &&
                   isMergeable(start.top(), end.top(), dur.top(),
                               currentStart, currentEnd, currentDur,
                               alphaComplement,
                               gapMaximum,
                               originalGapFilter)) {
                // Merging by changing start point of current tone
                //and deleting it from stack
                currentStart = start.top();
                start.pop();
                end.pop();
                currentDur += dur.top();
                dur.pop();
            }

            // Push current Tone
            start.push(currentStart);
            end.push(currentEnd);
            dur.push(currentDur);

        }

        stacksize = start.size();
        newStart = addStack2Vector(newStart, start);
        newEnd   = addStack2Vector(newEnd, end);
        for (int i = 0; i < stacksize; i++) {
            newSymbol.push_back(s->first);
            dur.pop();
        }

        // Verify the stacks are all empty
        if (!(start.empty() && end.empty() && dur.empty())) {
            std::cerr << "All Stacks are not empty !" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    return IntervalSet<S>(newStart, newEnd, newSymbol, tones.getMap());

}

template <class S>
IntervalSet<S> minDurationIntervalSetFilter(const IntervalSet<S>& tones,
                                            int minDuration)
{

    vector<int> start  = tones.getStart();
    vector<int> end    = tones.getEnd();
    vector<int> symbol = tones.getSymbol();

    vector<int> newStart;
    vector<int> newEnd;
    vector<int> newSymbol;

    int tones_size = tones.size();
    for (int i = 0; i < tones_size; i++) {
        if (duration(start[i], end[i]) >= minDuration) {
            newStart.push_back(start[i]);
            newEnd.push_back(end[i]);
            newSymbol.push_back(symbol[i]);
        }
    }

    return IntervalSet<S>(newStart, newEnd, newSymbol, tones.getMap());

}

