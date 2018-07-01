#include <iostream>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5hy8sm/20161212_challenge_295_easy_letter_by_letter/

int main()
{
	// Take/store input
	string from, to;
	getline(cin, from);
	getline(cin, to);
	
	// Force the strings to be the same length.
	// Pad the shorter with spaces
	size_t l1 = from.size();
	size_t l2 = to.size();
	if (l1 < l2)
	{
		from = string(l2-l1, ' ') + from;
	}
	else if (l2 < l1)
	{
		to = string(l1-l2, ' ') + to;
	}
	
	// Output and transform
	cout << from << endl;	
	for (size_t i=0; i<from.size(); i++)
	{
		if (from[i] != to[i])
		{
			from[i] = to[i];
			cout << from << endl;
		}
	}
}