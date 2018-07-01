#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "../lbTest.h"
using namespace std;

string process_in(int in)
{
	string out = to_string(in);
	out = string(4-out.size(), '0') + out;
	return out;
}

// Return the largest digit in `in`
int largest_digit(int in)
{
	string temp = process_in(in);
	sort(temp.rbegin(), temp.rend());
	return temp[0] - '0';
}

int desc_digits(int in)
{
	string temp = process_in(in);
	sort(temp.rbegin(), temp.rend());
	return atoi(temp.c_str());
}

int asc_digits(int in)
{
	string temp = process_in(in);
	sort(temp.begin(), temp.end());
	return atoi(temp.c_str());
}

int kaprekar(int in)
{
	int numTries = 0;
	while (in != 6174)
	{
		int d = desc_digits(in);
		int a = asc_digits(in);
		in = d-a;
		numTries++;
	}
	return numTries;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		lbTest::TEST_GROUP("LARGEST_DIGIT");
		lbTest::TEST(4, largest_digit(1234));
		lbTest::TEST(5, largest_digit(3253));
		lbTest::TEST(9, largest_digit(9800));
		lbTest::TEST(3, largest_digit(3333));
		lbTest::TEST(2, largest_digit(120));
		
		lbTest::TEST_GROUP("DESC_DIGIT");
		lbTest::TEST(4321, desc_digits(1234));
		lbTest::TEST(5332, desc_digits(3253));
		lbTest::TEST(9800, desc_digits(9800));
		lbTest::TEST(3333, desc_digits(3333));
		lbTest::TEST(2100, desc_digits(120));
		
		lbTest::TEST_GROUP("KAPREKAR");
		lbTest::TEST(2, kaprekar(6589));
		lbTest::TEST(5, kaprekar(5455));
		lbTest::TEST(0, kaprekar(6174));
		
		lbTest::TEST_END();
	}
	else
	{
		int in;
		cin >> in;
		string arg = argv[1];
		if (arg == "largest") cout << largest_digit(in) << endl;  // Tests 01-05
		else if (arg == "desc") cout << desc_digits(in) << endl; // Tests 01-05
		else cout << kaprekar(in) << endl; // Tests 06-08
	}
}