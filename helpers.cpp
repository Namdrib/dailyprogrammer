#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
ostream& operator << (ostream &os, vector<T> &v)
{
	for (size_t i=0; i<v.size(); i++)
	{
		os << v[i];
		if (i < v.size() - 1) os << " ";
	}
	return os;
}
