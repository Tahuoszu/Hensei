/**
 *
 * @file    AbstractMinDurClosedItemset.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "AbstractMinDurClosedItemset.h"

/********** Getters **********/

template <class S>
const map<set<S>, BitSet>&
AbstractMinDurClosedItemset<S>::getResult() const
{
	return resultMap;
}

template <class S>
map<set<S>, int> AbstractMinDurClosedItemset<S>::getSupportMap()
{
	map<set<S>, int> out;
	typename map<set<S>, BitSet>::const_iterator it;
	for (it = resultMap.begin(); it != resultMap.end(); ++it)
		out.insert(pair<set<S>, int>(it->first, support(it->second)));
	return out;
}

/********** Setters **********/

template <class S>
void AbstractMinDurClosedItemset<S>::setMinimalSupport(int min)
{
	minSupport = min;
}

template <class S>
void AbstractMinDurClosedItemset<S>::setAlpha(float alpha)
{
	beta = 1 - alpha;
}

/********** Member functions  **********/

template <class S>
void AbstractMinDurClosedItemset<S>::addResult(const set<S>& closedSet,
                                               int support,
                                               const BitSet& transactions)
{
	resultMap.insert(pair<set<S>, BitSet >(closedSet, transactions));
}


template <class S>
bool AbstractMinDurClosedItemset<S>::isMargin(int superset, int set)
{
	return ((float)superset / (float)set) < beta;
}

template <class S>
int AbstractMinDurClosedItemset<S>::support(const BitSet& vb)
{
    int s = 0;
    int vb_size = vb.size();
    for (int i = 0; i < vb_size; i++) {
        if (vb.get(i))
            s += supp[i];
    }
	return s;
}
