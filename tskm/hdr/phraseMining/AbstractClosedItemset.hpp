/**
 *
 * @file    AbstractClosedItemset.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "AbstractClosedItemset.h"

/********** Getters **********/

template <class S>
map<set<S>, BitSet > AbstractClosedItemset<S>::getResult()
{
    map<set<S>, BitSet > resultMap;
    typename list<set<S> >::const_iterator itItem = resultItemset.begin();
    typename list<BitSet>::const_iterator itTrans = resultBitSet.begin();
    for (; itItem != resultItemset.end() && itTrans != resultBitSet.end();
         ++itItem, ++itTrans)
         resultMap.insert(pair<set<S>, BitSet >(*itItem, *itTrans));
	return resultMap;
}

template <class S>
const vector<int> AbstractClosedItemset<S>::getSupport() const
{
    return vector<int>(supportLength, 1);
}

template <class S>
map<set<S>, int> AbstractClosedItemset<S>::getSupportMap()
{
	map<set<S>, int> out;
	typename map<set<S>, BitSet>::iterator it;
	map<set<S>, BitSet> resultMap = getResult();
	for (it = resultMap.begin(); it != resultMap.end(); ++it)
		out.insert(pair<set<S>, int>(it->first, support(it->second)));
	return out;
}

/********** Setters **********/

template <class S>
void AbstractClosedItemset<S>::setMinimalSupport(int min)
{
	minSupport = min;
}

template <class S>
void AbstractClosedItemset<S>::setAlpha(float alpha)
{
	beta = 1 - alpha;
}

/********** Member functions  **********/

template <class S>
void AbstractClosedItemset<S>::addResult(const set<S>& closedSet,
                                         int support,
                                         const BitSet& transactions)
{
    resultItemset.push_back(set<S>(closedSet));
	resultBitSet.push_back(transactions);
}

template <class S>
bool AbstractClosedItemset<S>::isMargin(int superset, int set)
{
	return ((float)superset / (float)set) < beta;
}

template <class S>
int AbstractClosedItemset<S>::support(const BitSet& vb)
{
	return std::count(vb.begin(), vb.end(), true);
}
