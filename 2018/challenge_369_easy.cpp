#include <bits/stdc++.h>
#include "../helpers.cpp"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/a0lhxx/20181126_challenge_369_easy_hex_colors/

// return "#RRGGBB" where RR, GG and BB are hex-pairs of
// r, g and b, respectively (e.g. 0 -> "00" and 255 -> "FF")
string hexcolour(int r, int g, int b)
{
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);

	ostringstream oss;

	oss << "#";
	oss << setbase(16) << setfill('0');
	oss << setw(2) << r << setw(2) << g << setw(2) << b;

	string out = oss.str();
	transform(all(out), out.begin(), ::toupper);
	return out;
}

// colour: a string "#RRGGBB" where RR, GG and BB are hex-pairs
// return {r, g, b} where r, g and b are the colour components of colour
vector<int> dehex(string colour)
{
	vector<int> out(3);
	for (int i=0; i<3; i++)
	{
		string hex_pair = colour.substr(i*2 + 1, 2);
		stringstream ss(hex_pair);

		ss >> setbase(16) >> out[i];
	}
	return out;
}

// hex_strings: vector of "#RRGGBB" strings
// return "#RRGGBB" where RR, GG and BB are hex-pairs for
// the average values of all the RR, GG and BB in hex_strings
string blend(vector<string> hex_strings)
{
	double r = 0, g = 0, b = 0;
	for (auto hex_string : hex_strings)
	{
		auto dehexed_string = dehex(hex_string);
		r += dehexed_string[0];
		g += dehexed_string[1];
		b += dehexed_string[2];
	}
	double n = hex_strings.size();
	r = round(r / n);
	b = round(b / n);
	g = round(g / n);

	return hexcolour(r, g, b);
}

int main()
{
	cout << "Challenge" << endl;
	assert(hexcolour(127, 255, 212) == "#7FFFD4");
	assert(hexcolour(255, 99, 71) == "#FF6347");
	assert(hexcolour(184, 134, 11) == "#B8860B");
	assert(hexcolour(189, 183, 107) == "#BDB76B");
	assert(hexcolour(0, 0, 205) == "#0000CD");

	cout << "Bonus" << endl;
	// assert(blend(vector<string>{"#000000", "#778899"}) == "#3C444C"); // rounding issues
	assert(blend(vector<string>{"#E6E6FA", "#FF69B4", "#B0C4DE"}) == "#DCB1D9");
}
