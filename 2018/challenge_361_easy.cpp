#include <bits/stdc++.h>
#include "../helpers.cpp"
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/8jcffg/20180514_challenge_361_easy_tally_program/

// Upper-case letters remove one from the tally,
// lower-case letters add oen to the tally
// Keep track of names by lower-case (e.g. 'A' affects 'a')
unordered_map<char, int> tally(const string &in)
{
	unordered_map<char, int> out;

	// Loop through the string, all 
	for (auto c : in)
	{
		int change = (isupper(c) ? -1 : 1);
		char lower = tolower(c);
		if (out.count(lower) > 0)
		{
			out[lower] += change;
		}
		else
		{
			out[lower] = change;
		}
	}
	return out;
}

int main(int argc, char const *argv[])
{
	cout << tally("abcde") << endl;
	cout << tally("dbbaCEDbdAacCEAadcB") << endl;
	cout << tally("EbAAdbBEaBaaBBdAccbeebaec") << endl;
	return 0;
}