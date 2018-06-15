#include <bits/stdc++.h>
#include "../helpers.cpp"
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/8q96da/20180611_challenge_363_easy_i_before_e_except/

// Returns true if the input word follows the rule "I before E except after C", false otherwise
// if "ei" appears in a word, it must immediately follow "c".
// if "ie" appears in a word, it must not immediately follow "c".
bool check(const string &s)
{
	// want to check for cases of "ie" and "ei", THEN check for corresponding "c"
	// otherwise there could be "c" without following ei/ie, or ei/ie without corresponding "c"
	// note: a word could have multiple cases of "ie" and/or "ei"
	// return true unless the rule is violated

	// check each letter for either 'i' or 'e'
	// when either 'i' or 'e' has been found, check for corresponding letters
	for (size_t i=0; i<s.size(); i++)
	{
		switch (s[i])
		{
			case 'i':
				if (i < s.size()-1 && s[i+1] == 'e')
				{
					if (i == 0 || (i > 0 && s[i-1] == 'c'))
					{
						return false;
					}
				}
			break;

			case 'e':
				if (i < s.size()-1 && s[i+1] == 'i')
				{
					if (i == 0 || (i > 0 && s[i-1] != 'c'))
					{
						return false;
					}
				}
			break;
		}
	}

	return true;
}

int num_against_rules(string filename = "../misc/enable1.txt")
{
	ifstream ifs(filename);
	if (!ifs.is_open())
	{
		cerr << "Unable to open " << filename << endl;
	}

	int count = 0;
	for (string temp; ifs >> temp; )
	{
		count += !check(temp);
	}
	return count;
}

int main(int argc, char const *argv[])
{
	lbTest::TEST_GROUP("363 EASY: I before E except after C");
	lbTest::TEST(true, check("a"));
	lbTest::TEST(true, check("zombie"));
	lbTest::TEST(true, check("transceiver"));
	lbTest::TEST(false, check("veil"));
	lbTest::TEST(false, check("icier"));
	lbTest::TEST(false, check("eight"));

	lbTest::TEST_GROUP("363 EASY: how many");
	lbTest::TEST(2169, num_against_rules("../misc/enable1.txt"));
	
	lbTest::TEST_END();
}
