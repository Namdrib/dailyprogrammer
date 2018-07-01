#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/67dxts/20170424_challenge_312_easy_l33tspeak_translator/

// TODO : Translate from 1337 back to English

map<char, string> engToLeet = {
	{'A', "4"},
	{'B', "6"},
	{'E', "3"},
	{'I', "|"},
	{'L', "1"},
	{'M', "(V)"},
	{'N', "(\\)"},
	{'O', "0"},
	{'S', "5"},
	{'T', "7"},
	{'V', "\\/"},
	{'W', "`//"}
};

string toLeet(string in)
{
	string out;
	for (int i=0; i<in.size(); i++)
	{
		if (engToLeet.count(toupper(in[i])) > 0)
		{
			out += engToLeet[toupper(in[i])];
		}
		else
		{
			out += in[i];
		}
	}
	return out;
}


int main()
{
	for (string temp; getline(cin, temp); )
	{
		cout << temp << " -> " << toLeet(temp) << endl;
	}
}