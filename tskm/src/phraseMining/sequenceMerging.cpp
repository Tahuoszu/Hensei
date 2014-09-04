/**
 *
 * @file    sequenceMerging.cpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "sequenceMerging.h"

map<set<ClosedSequence>, BitSet>
preprocessingCPO(const map<set<ClosedSequence>, BitSet>& in)
{

    map<set<ClosedSequence>, BitSet> out;

    // Reduce in phrases
    map<set<ClosedSequence>, BitSet>::const_iterator e;
    for (e = in.begin(); e != in.end(); ++e) {
        set<ClosedSequence> toRemove;
        set<ClosedSequence> eSet = e->first;
        set<ClosedSequence>::iterator l1;
        for (l1 = eSet.begin(); l1 != eSet.end(); ++l1) {
            set<ClosedSequence>::iterator l2;
            for (l2 = eSet.begin(); l2 != eSet.end(); ++l2) {
                list<Chord> list1 = l1->getSequence();
                list<Chord> list2 = l2->getSequence();
                int l1_size = list1.size();
                int l2_size = list2.size();
                if (isSubList(list1, list2) && (l1_size != l2_size))
                    toRemove.insert(*l1);
            }
        }
        set<ClosedSequence>::iterator l;
        for (l = toRemove.begin(); l != toRemove.end(); ++l)
            eSet.erase(*l);
        //if (out.find(eSet) != out.end())
        //    std::cout << "OK !" << std::endl;
        out.insert(pair<set<ClosedSequence>, BitSet>(eSet, e->second));
    }

    return out;
}

map<BitSet, Node>
closedPartialOrder(const map<set<ClosedSequence>, BitSet>& input)
{
    map<BitSet, set<ClosedSequence> > invmap;
    map<set<ClosedSequence>, BitSet>::const_iterator it;
    for (it = input.begin(); it != input.end(); ++it)
        invmap.insert(pair<BitSet, set<ClosedSequence> >\
                      (it->second, it->first));

    map<BitSet, Node> out;
    map<BitSet, set<ClosedSequence> >::iterator e;
    for (e = invmap.begin(); e != invmap.end(); ++e) {
        MergeSequences ms;
        out.insert(pair<BitSet, Node>(e->first, ms.run(e->second)));
    }

    return out;
}
