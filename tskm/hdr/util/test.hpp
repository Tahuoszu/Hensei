/**
 *
 * @file    test.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    21/05/2014
 *
 */

#include "test.h"

template <class S>
bool isSubSequence(const set<S>& s1, const set<S>& s2)
{
    return (std::search(s1.begin(), s1.end(),
                        s2.begin(), s2.end()) != s1.end());
}

template <class S>
bool isSubSetSequence(const list<set<S> >& s1, const list<set<S> >& s2)
{
    if (s2.empty())
        return true;
    typename list<set<S> >::const_iterator it2 = s2.begin();
    for (typename list<set<S> >::const_iterator it1 = s1.begin();
        it1 != s1.end(); ++it1) {
        if (isSubSequence(*it1, *it2)) {
            it2++;
            if (it2 == s2.end())
                return true;
        }
    }
    return false;
}

template <class S>
bool isSingleSubSetSequence(const list<S>& s1, const list<set<S> >& s2)
{
    if (s1.empty())
        return true;
    typename list<S>::const_iterator it1 = s1.begin();
    typename list<set<S> >::const_iterator it2 = s2.begin();
    for (; it2 != s2.end(); ++it2)
        if (it2->find(*it1) != it2->end())
            if (++it1 == s1.end())
                return true;
    return false;
}
