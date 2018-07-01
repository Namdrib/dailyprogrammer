#include <bits/stdc++.h>
#include "../helpers.cpp"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/826coe/20180305_challenge_353_easy_closest_string/

// used to input into a vector from stdin
// end input with Ctrl+D
template <typename T>
vector<T> split_by_whitespace_cin()
{
	istream_iterator<T> begin(cin), end;
	return vector<T>(begin, end);
}

// return the hamming_distance between two equal length strings a and b
int hamming_distance(const string &a, const string &b)
{
	if (a.size() != b.size())
	{
		throw runtime_error("hamming_distance: length not equal");
	}
	int out = 0;
	for (size_t i=0; i<a.size(); i++)
	{
		if (a[i] != b[i])
		{
			out++;
		}
	}
	return out;
}

int main(int argc, char** argv)
{
	int n;
	cin >> n;
	auto v(split_by_whitespace_cin<string>());

	// store the distances between each entry in v
	vector<int> distances(n, 0);
	for (size_t i=0; i<v.size(); i++)
	{
		for (size_t j=i+1; j<v.size(); j++)
		{
			int dist = hamming_distance(v[i], v[j]);
			distances[i] += dist;
			distances[j] += dist;
		}
	}

	cout << v[distance(distances.begin(), min_element(distances.begin(), distances.end()))] << endl;
}
