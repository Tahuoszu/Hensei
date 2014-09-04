/**
 *
 * @file	Segment.h
 * @brief	Class segment
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

using std::vector;

/**
 * @class Segment
 * @brief Describe class segment
 */
class Segment {

public :

    int nbSeg;
    vector<int> leftx;
    vector<int> rightx;
    vector<float> lefty;
    vector<float> righty;
    vector<float> mc;
    vector<float> entrp;
    vector<vector<float> > best;
    vector<float> delta;

    /********** Constructor **********/

    Segment();
    Segment(int data_size);
    Segment(const Segment& seg);
    Segment(const Segment& seg, int index);

    /********** Destructor **********/

    ~Segment();

    /********** Member functions **********/

    void clear();

    void printSegment();

    void push_back(const Segment& seg);

    void push_front(const Segment& seg);

    void removePoint(int index);

    void resize();

    void setSegment(const Segment& seg, int index);

    int size();

    Segment subSegment(int from, int to);

};

#endif
