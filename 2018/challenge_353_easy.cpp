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

	// accumulate (using `0, plus<int>()`) the number of different characters between a and b
	// http://www.cplusplus.com/reference/numeric/inner_product/
	return inner_product(a.begin(), a.end(), b.begin(), 0, plus<int>(), [](const char left, const char right){return int(left != right);});
}

int main(int argc, char** argv)
{
	int n;
	cin >> n;
	const auto v(split_by_whitespace_cin<string>());

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
