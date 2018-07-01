#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5bn0b7/20161107_challenge_291_easy_goldilocks_bear/

template <typename T>
ostream& operator<<(ostream &os, const vector<T> &in)
{
	for (size_t i=0; i<in.size(); i++)
	{
		cout << in[i];
		if (i != in.size()-1) cout << " ";
	}
	return os;
}

void doGoldilocks()
{
	// Goldilocks inputs
	int gWeight, gMaxTemp;
	cin >> gWeight >> gMaxTemp;
	
	// Chair inputs
	vector<int> viablePlaces;
	for (int i=1, weightCapacity, pTemp; cin >> weightCapacity >> pTemp; i++)
	{
		// I _could_ just output `i`, but I don't want the trailing space
		if (weightCapacity >= gWeight && pTemp <= gMaxTemp) viablePlaces.push_back(i);
	}
	cout << viablePlaces << endl;
}

int main()
{
	doGoldilocks();
}