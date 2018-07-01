#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include "../lbTest.h"
using namespace std;

// Populate count of each letter in s (lower case)
map<char, int> doCount(const string &s)
{
	map<char, int> out;
	for (size_t i=0; i<s.size(); i++)
	{
		if (isalpha(s[i]))
		{
			out[tolower(s[i])]++;
		}
	}
	return out;
}

string checkAnagram(const string &in)
{
	size_t qPos = in.find("?");
	string a = in.substr(1, qPos-3);
	string b = in.substr(qPos+3, (in.size()-qPos)-4);
	// cerr << "a|" << a << "|" << endl;
	// cerr << "b|" << b << "|" << endl;
	
	map<char, int> aCount = doCount(a);
	map<char, int> bCount = doCount(b);
	
	string out = "\"" + a + "\" is" + (aCount != bCount ? " NOT" : "") + " an anagram of \"" + b + "\"";
	return out;
}

int main()
{
	lbTest::TEST_GROUP("ANAGRAM_TEST");
	lbTest::TEST(string("\"Clint Eastwood\" is an anagram of \"Old West Action\""), 
				checkAnagram("\"Clint Eastwood\" ? \"Old West Action\""));
				
	lbTest::TEST(string("\"wisdom\" is an anagram of \"mid sow\""), 
				checkAnagram("\"wisdom\" ? \"mid sow\""));
				
	lbTest::TEST(string("\"parliament\" is NOT an anagram of \"partial man\""), 
				checkAnagram("\"parliament\" ? \"partial man\""));
				
	lbTest::TEST(string("\"Seth Rogan\" is an anagram of \"Gathers No\""), 
				checkAnagram("\"Seth Rogan\" ? \"Gathers No\""));
				
	lbTest::TEST(string("\"Reddit\" is NOT an anagram of \"Eat Dirt\""), 
				checkAnagram("\"Reddit\" ? \"Eat Dirt\""));
				
	lbTest::TEST(string("\"Schoolmaster\" is an anagram of \"The classroom\""), 
				checkAnagram("\"Schoolmaster\" ? \"The classroom\""));
				
	lbTest::TEST(string("\"Astronomers\" is NOT an anagram of \"Moon starer\""), 
				checkAnagram("\"Astronomers\" ? \"Moon starer\""));
				
	lbTest::TEST(string("\"Vacation Times\" is an anagram of \"I'm Not as Active\""), 
				checkAnagram("\"Vacation Times\" ? \"I'm Not as Active\""));
				
	lbTest::TEST(string("\"Dormitory\" is NOT an anagram of \"Dirty Rooms\""), 
				checkAnagram("\"Dormitory\" ? \"Dirty Rooms\""));
	lbTest::TEST_END();
}