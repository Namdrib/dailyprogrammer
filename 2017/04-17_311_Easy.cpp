#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/65vgkh/20170417_challenge_311_easy_jolly_jumper/

// Check whether all entries of a map<T, bool> is true
template <class T>
bool mapAllTrue(map<T, bool> &m)
{
	for (auto p : m)
	{
		if (p.second == false)
		{
			return false;
		}
	}
	return true;
}

template <typename T>
ostream& operator << (ostream &os, vector<T> &v)
{
	for (size_t i=0; i<v.size(); i++)
	{
		cout << v[i] << " ";
	}
	return os;
}

int main()
{
	// Read inputs
	for (int n; cin >> n; )
	{
		// Build the sequence
		vector<int> seq(n);
		for (int i=0; i<n; i++)
		{
			cin >> seq[i];
		}
		
		// Keep track of which jump sizes have been seen
		map<int, bool> m;
		for (int i=1; i<seq.size(); i++)
		{
			m[i] = false;
		}
		
		// Check jolliness
		for (int i=0; i<seq.size()-1; i++)
		{
			int diff = abs(seq[i] - seq[i+1]);
			if (m[diff] == true)
			{
				break;
			}
			else
			{
				m[diff] = true;
			}
		}
		
		// Output
		cout << n << " " << seq << (mapAllTrue(m) ? "" : "NOT ") << "JOLLY" << endl;
	}
}