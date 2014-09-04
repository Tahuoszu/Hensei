/**
 *
 * @file    functions.hpp
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    21/05/2014
 *
 */

#include "functions.h"

template <class T>
bool containsSet(const set<T>& st1, const set<T>& st2)
{
    for (typename set<T>::iterator it = st2.begin(); it != st2.end(); ++it)
        if (st1.find(*it) == st1.end())
            return 0;
    return 1;
}

template <class T>
void print_set(const set<T>& s)
{
    for (typename set<T>::const_iterator it = s.begin(); it != s.end(); ++it)
        cout << *it << "\t";
    cout << endl;
}

template <class T>
void print_vector(const vector<T>& v)
{
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << "\t";
    cout << endl;
}

template <class S, class T>
void print_map(const map<S, T>& m)
{
    for (typename map<S, T>::const_iterator it = m.begin(); it != m.end(); ++it)
        cout << "[" << it->first << " - " << it->second << "]" << endl;
    cout << endl;
}

template <class T>
vector<T> getIndexOfSort(const vector<T>& v)
{
    int size = v.size();
    vector<T> v_sorted(size, 0);
    std::multimap<T, int> mapv;
    for (int i = 0; i < size; i++)
        mapv.insert(std::pair<T, int>(v[i], i));
    typename std::multimap<T, int>::iterator it = mapv.begin();
    for (int i = 0; i < size; i++) {
        v_sorted[i] = it->second;
        ++it;
    }
    return v_sorted;
}

template <class T>
list<T> subList(const list<T>& liste, int fromIndex, int toIndex)
{
    typename list<T>::const_iterator i = liste.begin();
    typename list<T>::const_iterator j = liste.begin();
    std::advance(i, fromIndex);
    std::advance(j, toIndex);
    return list<T>(i, j);
}

template <class T>
bool isSubList(const list<T>& subList, const list<T>& superList)
{
    typename list<T>::const_iterator supIt = superList.begin();
    supIt = std::search(superList.begin(), superList.end(),
                        subList.begin(), subList.end());
    return (supIt != superList.end());
}

template <class T>
bool containsKey(const map<int, T>& m, int key)
{
    if (m.empty())
        return false;
    typename map<int, T>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it)
        if (key == it->first)
            return true;
    return false;
}
