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

vector<int> addStack2Vector(vector<int>& v, stack<int>& s)
{
    int stacksize = s.size();
    int currentvalue;
    for (int i = 0; i < stacksize; i++) {
        currentvalue = s.top();
        v.push_back(currentvalue);
        s.pop();
    }
    return v;
}

bool isMergeable(int start, int end, int dur,
                 int currentStart, int currentEnd, int currentDur,
                 float alphaComplement,
                 float gapMaximum,
                 float originalGapFilter)
{
    if (duration(end, currentStart) > gapMaximum)
        return 0;
    else {
        float durationMerged = 0;
        float durationAll    = duration(start, currentEnd);
        if (originalGapFilter)
            durationMerged = dur + currentDur;
        else
            durationMerged = duration(start, end) + \
            duration(currentStart, currentEnd);
        float durationMergeable = durationMerged / durationAll;
        return (durationMergeable > alphaComplement);
    }
}
