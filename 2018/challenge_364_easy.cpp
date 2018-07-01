#include <bits/stdc++.h>
#include "../helpers.cpp"
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/8s0cy1/20180618_challenge_364_easy_create_a_dice_roller/
// with bonus

// compile with g++ -o a challenge_364_easy.cpp -std=c++11 -DREGEX_SOLUTION
// to utilise regex solution to split at the "d"
// this is about 10 times slower than string splitting

// return a number between lo and hi (inclusive)
// e.g. (1, 6) can give {1, 2, 3, 4, 5, 6}
int random_num_between(int lo, int hi)
{
	return (rand() % (hi - lo)) + lo;
}

// Takes in a string like XdY where
// X is a number, representing how many dice there are
// d is a separator
// Y is a number, representing how many faces on each die (same Y for each xi)
#ifdef REGEX_SOLUTION
static regex reg("(\\d+)d(\\d+)");
#endif // REGEX_SOLUTION
void roll_dice(const string &s)
{
	// Split the string to isolate X and Y
#ifdef REGEX_SOLUTION
	smatch sm;
	regex_match(s, sm, reg);
	if (!regex_search(s.begin(), s.end(), sm, reg))
	{
		cout << "Bad entry: " << s << endl;
		return;
	}
	int num_dice = stoi(sm[1]);
	int num_faces = stoi(sm[2]);
#else
	size_t d_pos = s.find("d");
	if (d_pos == string::npos)
	{
		cout << "Bad entry: " << s << endl;
		return;
	}
	int num_dice = stoi(s.substr(0, d_pos));
	int num_faces = stoi(s.substr(d_pos+1));
#endif // REGEX_SOLUTION

	// Check for appropraite numbers
	if (num_dice < 1 || num_dice > 100 || num_faces < 2 || num_faces > 100)
	{
		cout << "Bad entry: " << s << endl;
		return;
	}

	int out = 0;
	vector<int> result(num_dice);
	for (int i=0; i<num_dice; i++)
	{
		result[i] = random_num_between(1, num_faces);
		out += result[i];
	}
	cout << out << ": " << result << endl;
}

int main(int argc, char const *argv[])
{
	srand(time(0));
	vector<string> inputs = {
		"5d12",
		"6d4",
		"1d2",
		"1d8",
		"3d6",
		"4d20",
		"100d100",
		"-1d-1"
	};

	for (auto &s : inputs)
	{
		roll_dice(s);
	}
}
