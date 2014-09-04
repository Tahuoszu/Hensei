/**
 *
 * @file	Segment.cpp
 * @brief	Class segment
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#include "functions.h"
#include "Segment.h"

 /********** Constructor **********/

Segment::Segment() {}

Segment::Segment(int data_size) {
	nbSeg = floor(data_size / 2);
    leftx.resize(nbSeg, 0);
	rightx.resize(nbSeg, 0);
	for (int i = 0; i < nbSeg; i++) {
		leftx[i]  = 2 * i;
		rightx[i] = leftx[i] + 1;
	}
	rightx[nbSeg - 1] = data_size - 1;
	lefty.resize(nbSeg, 0);
	righty.resize(nbSeg, 0);
	mc.resize(nbSeg, FLT_MAX);
    entrp.resize(nbSeg, 0);
    best.resize(nbSeg);
    delta.resize(nbSeg, 0);
}

Segment::Segment(const Segment& seg)
{
    nbSeg  = seg.nbSeg;
    leftx  = seg.leftx;
    rightx = seg.rightx;
    lefty  = seg.lefty;
    righty = seg.righty;
    mc     = seg.mc;
    entrp  = seg.entrp;
    best   = seg.best;
    delta  = seg.delta;
}

Segment::Segment(const Segment& seg, int index)
{
    if (index < seg.nbSeg) {
        nbSeg = 1;
        leftx.push_back(seg.leftx[index]);
        rightx.push_back(seg.rightx[index]);
        lefty.push_back(seg.lefty[index]);
        righty.push_back(seg.lefty[index]);
        mc.push_back(seg.mc[index]);
        entrp.push_back(seg.entrp[index]);
        best.push_back(seg.best[index]);
        delta.push_back(seg.delta[index]);
    }
}

/********** Destructor **********/

Segment::~Segment() {}

/********** Member functions **********/

void Segment::clear()
{
    nbSeg = 0;
    leftx.clear();
    rightx.clear();
    lefty.clear();
    righty.clear();
    mc.clear();
    entrp.clear();
    best.clear();
    delta.clear();
    return;
}

void Segment::push_back(const Segment& seg)
{
    if (seg.nbSeg > 0) {
        for (int i = 0; i < seg.nbSeg; i++) {
            nbSeg++;
            leftx.push_back(seg.leftx[i]);
            rightx.push_back(seg.rightx[i]);
            lefty.push_back(seg.lefty[i]);
            righty.push_back(seg.righty[i]);
            mc.push_back(seg.mc[i]);
            entrp.push_back(seg.entrp[i]);
            best.push_back(seg.best[i]);
            delta.push_back(seg.delta[i]);
        }
    }
}

void Segment::push_front(const Segment& seg)
{
    if (seg.nbSeg > 0) {
        for (int i = 0; i < seg.nbSeg; i++) {
            nbSeg++;
            leftx.insert(leftx.begin(), seg.leftx[i]);
            rightx.insert(rightx.begin(), seg.rightx[i]);
            lefty.insert(lefty.begin(), seg.lefty[i]);
            righty.insert(righty.begin(), seg.righty[i]);
            mc.insert(mc.begin(), seg.mc[i]);
            entrp.insert(entrp.begin(), seg.entrp[i]);
            best.insert(best.begin(), seg.best[i]);
            delta.insert(delta.begin(), seg.delta[i]);
        }
    }
}

void Segment::printSegment()
{
    std::cout << "-------------------- Segment's data" << std::endl;
    std::cout << "Segment length = " << nbSeg << std::endl;
    std::cout << "Seg" << "\t" << "Leftx" << "\t" << "Rightx" << "\t";
    std::cout << "Lefty" << "\t\t" << "Righty" << "\t\t" << "MC" << "\t\t";
    std::cout << "Entropy" << std::endl;
    for (int i = 0; i < nbSeg; i++) {
        std::cout << i + 1 << "\t" << leftx[i] << "\t" << rightx[i] << "\t";
        std::cout << lefty[i] << "  \t" << righty[i] << "  \t" << mc[i];
        std::cout << "  \t" << entrp[i] << std::endl;
    }
    return;
}

void Segment::removePoint(int index)
{
    nbSeg--;
    leftx.erase(leftx.begin() + index);
    rightx.erase(rightx.begin() + index);
    lefty.erase(lefty.begin() + index);
    righty.erase(righty.begin() + index);
    mc.erase(mc.begin() + index);
    best.erase(best.begin() + index);
    delta.erase(delta.begin() + index);
    return;
}

void Segment::resize()
{
    leftx.resize(nbSeg);
    rightx.resize(nbSeg);
    lefty.resize(nbSeg);
    righty.resize(nbSeg);
    mc.resize(nbSeg);
    entrp.resize(nbSeg);
    best.resize(nbSeg);
    delta.resize(nbSeg);
}

void Segment::setSegment(const Segment& seg, int index)
{
    if (index < seg.nbSeg) {
        leftx[0]  = seg.leftx[index];
        rightx[0] = seg.rightx[index + 1];
        lefty[0]  = seg.lefty[index];
        righty[0] = seg.righty[index + 1];
        mc[0]     = 0;
        entrp[0]  = 0;
        best.clear();
        delta[0]  = FLT_MAX ;
    }
}

int Segment::size()
{
    return nbSeg;
}

Segment Segment::subSegment(int from, int to)
{
    Segment subSeg;
    if (from > to)
        return subSeg;
    subSeg.nbSeg = to - from + 1;
    subSeg.leftx.assign(leftx.begin() + from, leftx.begin() + to + 1);
    subSeg.rightx.assign(rightx.begin() + from, rightx.begin() + to + 1);
    subSeg.lefty.assign(lefty.begin() + from, lefty.begin() + to + 1);
    subSeg.righty.assign(righty.begin() + from, righty.begin() + to + 1);
    subSeg.mc.assign(mc.begin() + from, mc.begin() + to + 1);
    subSeg.entrp.assign(entrp.begin() + from, entrp.begin() + to + 1);
    subSeg.best.assign(best.begin() + from, best.begin() + to + 1);
    subSeg.delta.assign(delta.begin() + from, delta.begin() + to + 1);
    return subSeg;
}
