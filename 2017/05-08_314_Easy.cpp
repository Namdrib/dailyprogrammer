#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/69y21t/20170508_challenge_314_easy_concatenated_integers/

vector<string> buildVectorFromStrings(string &in)
{
	vector<string> out;
	stringstream ss(in);
	for (string temp; ss >> temp; /*blank*/)
	{
		out.push_back(temp);
	}
	return out;
}

// Output vectors
template <typename T>
ostream& operator << (ostream &os, vector<T> &v)
{
	for (size_t i=0; i<v.size(); i++)
	{
		os << v[i];
	}
	return os;
}

// Custom string less-than comparison
struct stringLessThan {
	bool operator()(const string &a, const string &b) {
		return (stoi(a + b) < stoi(b + a));
	}
};


// Sorting makes smaller numbers at the front
// Reverse sorting makes larger numbers at the end
// Takes O(n log n) time where n is number of strings
void doSortingWay(vector<string> numbers)
{
	sort(numbers.begin(), numbers.end(), stringLessThan());
	cout << numbers << " ";
	sort(numbers.rbegin(), numbers.rend(), stringLessThan());
	cout << numbers << endl;
}

string concatVectorOfStrings(vector<string> &v)
{
	stringstream ss;
	for (auto s : v)
	{
		ss << s;
	}
	return ss.str();
}

// Go through every permutation of strings in numbers
// Takes O(n! * n), where n is number of strings
void doPermutationWay(vector<string> numbers)
{
	// Sorting ensures we get EVERY permutation from next_permutation
	sort(numbers.begin(), numbers.end());
	string first = concatVectorOfStrings(numbers);
	string maxVal = first;
	string minVal = first;

	// Try every way, record min and max (lexicographical comparisons)
	do
	{
		string result = concatVectorOfStrings(numbers);
		if (result > maxVal) maxVal = result;
		if (result < minVal) minVal = result;
	} while (next_permutation(numbers.begin(), numbers.end()));

	cout << minVal << " " << maxVal << endl;
}

int main()
{
	for (string temp; getline(cin, temp); /*blank*/)
	{
		// Build a vector of the strings
		vector<string> numbers = buildVectorFromStrings(temp);

		doSortingWay(numbers);
		// doPermutationWay(numbers);
	}
}