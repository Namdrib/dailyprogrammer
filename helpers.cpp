#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

#ifndef HELPERS_CPP
#define HELPERS_CPP

#define all(c) begin(c), end(c)

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

// Read a file whose relative path is given by s into a vector
// Returns null if failing to open the file.
template <typename T>
vector<T> read_file_into_vector(const string &s)
{
	// Attempt to open s
	ifstream ifs(s);
	if (!ifs.is_open())
	{
		cerr << "Could not open file \"" << s << "\"" << endl;
		return vector<T>{};
	}

	// read ifs into out and return
	vector<T> out;
	for (T temp; getline(ifs, temp); )
	{
		out.push_back(temp);
	}
	return out;
}

template <typename T>
T clamp(const T &v, const T &lo, const T &hi)
{
	return min(max(v, lo), hi);
}

#endif // HELPERS_CPP
