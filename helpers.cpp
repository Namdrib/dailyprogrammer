#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename T>
ostream& operator << (ostream &os, vector<T> &v)
{
	auto second_last = --v.end();
	for (auto it = v.begin(); it != v.end(); it++)
	{
		os << *it;
		if (it != second_last) os << " ";
	}
	return os;
}

template <typename T>
ostream& operator << (ostream &os, set<T> &s)
{
	auto second_last = --s.end();
	for (auto it = s.begin(); it != s.end(); it++)
	{
		os << *it;
		if (it != second_last) os << " ";
	}
	return os;
}

template <typename S, typename T>
ostream& operator << (ostream &os, map<S, T> m)
{
	auto second_last = --m.end();
	for (auto it = m.begin(); it != m.end(); it++)
	{
		os << it->first << ":" << it->second;
		if (it != second_last) os << ", ";
	}
	return os;
}

template <typename S, typename T>
ostream& operator << (ostream &os, unordered_map<S, T> m)
{
	for (auto it = m.begin(); it != m.end(); it++)
	{
		os << it->first << ":" << it->second;
		auto it_copy = it;
		if (++it_copy != m.end()) os << ", ";
	}
	return os;
}
