#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5go843/20161205_challenge_294_easy_rack_management_1/

const int ALPHABET_SIZE = 26;
int SCORE_LIST[ALPHABET_SIZE] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Take input, convert to lower case, return a string
string getInput(istream &in=cin)
{
	string out;
	getline(in, out);
	for (size_t i=0; i<out.size(); i++)
	{
		out[i] = tolower(out[i]);
	}
	return out;
}

// Calculate how much a string would score in Scrabble points
// Scores based on https://en.wikipedia.org/wiki/Scrabble_letter_distributions#English
int getScore(string in)
{
	int score = 0;
	for (size_t i=0; i<in.size(); i++)
	{
		if (!isalpha(in[i])) continue;
		score += SCORE_LIST[in[i] - 'a'];
	}
	return score;
}

ifstream openWordsFile()
{
	// Open the file
	// string f = "tests/sorted_words.txt";
	string f = "tests/all_words.txt";
	ifstream wordsFile(f);
	if (!wordsFile.is_open())
	{
		cerr << "Could not open " << f << endl;
		exit(2);
	}
	return wordsFile;
}

// Check whether `query` can be made
// from the letters in `letters`
// Will return the letters used if it can be made
// Otherwise will return an empty string
// Includes Bonus 1: when `letters` contains wildcards '?'
string scrabble(string letters, string query)
{
	// cerr << "Trying to make " << query << " from " << letters << endl;
	// Track how often each letter comes up in each string
	vector<int> freq_Letters(ALPHABET_SIZE, 0); // a-z
	vector<int> freq_Query(ALPHABET_SIZE, 0); // a-z
	
	for (size_t i=0; i<letters.size(); i++)
	{
		if (isalpha(letters[i])) freq_Letters[letters[i] - 'a']++;
	}
	for (size_t i=0; i<query.size(); i++)
	{
		freq_Query[query[i] - 'a']++;
	}
	
	int numWildCards = count(letters.begin(), letters.end(), '?');
	string lettersUsed = "";
	int cumDiff = 0;
	for (int i=0; i<ALPHABET_SIZE; i++)
	{
		// Build `lettersUsed` as necessary
		if (freq_Query[i] && freq_Letters[i]) 
			lettersUsed += string(min(freq_Query[i], freq_Letters[i]), 'a'+i);
		
		int diff = freq_Query[i] - freq_Letters[i];
		cumDiff += max(0, diff);
	}
	return ((cumDiff > numWildCards) ? "" : lettersUsed);
}

// Bonus 2: Return the longest word in
// the file that can be made from `letters`
// NOTE: SORTED THE WORDS BY LENGTH FIRST BY USING
// cat all_words.txt | awk '{ print length, $0 }' | sort -n -r -s | cut -d" " -f2- > sorted_words.txt
string longest(string letters)
{
	// Open the file
	string f = "tests/sorted_words.txt";
	// string f = "tests/all_words.txt"; // Also works in reasonable time
	ifstream wordsFile(f);
	if (!wordsFile.is_open())
	{
		cerr << "Could not open " << f << endl;
		exit(2);
	}
	
	// `scrabble` letters against each word in wordsFile
	string out = "";
	for (string temp = ""; getline(wordsFile, temp);)
	{
		if (!scrabble(letters, temp).empty())
		{
			if (f == "tests/sorted_words.txt")
				return temp;
			else
				if (temp.length() > out.length()) out = temp;
		}
	}
	return out;
}

// Bonus 3: Return the word with the highest points
// in the file that can be made from `letters`
string highest(string letters)
{
	ifstream wordsFile = openWordsFile();

	int max_points = 0;
	string max_word = "";
	for (string temp = ""; getline(wordsFile, temp);)
	{
		string lettersUsed = scrabble(letters, temp);
		if (!lettersUsed.empty())
		{
			// If a higher-scorign word is found,
			// update max_{points,word}
			int tempScore = getScore(lettersUsed);
			if (tempScore > max_points)
			{
				max_points = tempScore;
				max_word = temp;
			}
		}
	}
	return max_word;
}

// --------------------------------------------------------------
string lbScrabble(string letters, string query)
{
	return (scrabble(letters, query).empty() ? "false" : "true");
}

void doScrabble() // Take input for and call `scrabble`
{
	string letters = getInput();	
	string query = getInput();	
	cout << (scrabble(letters, query).empty() ? "false" : "true") << endl;	
}

void doLongest() // Take input for and call `longest`
{
	string letters = getInput();
	cout << longest(letters) << endl;
}

void doHighest() // Take input for and call `highest`
{
	string letters = getInput();
	cout << highest(letters) << endl;
}
// --------------------------------------------------------------

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		lbTest::TEST_GROUP("SCRABBLE");
		lbTest::TEST(string("true"),  lbScrabble("ladilmy", "daily"));
		lbTest::TEST(string("false"), lbScrabble("eerriin", "eerie"));
		lbTest::TEST(string("true"),  lbScrabble("orrpgma", "program"));
		lbTest::TEST(string("false"), lbScrabble("orppgma", "program"));
		lbTest::TEST(string("true"),  lbScrabble("pizza??", "pizzazz"));
		lbTest::TEST(string("false"), lbScrabble("piizza?", "pizzazz"));
		lbTest::TEST(string("true"),  lbScrabble("a??????", "program"));
		lbTest::TEST(string("false"), lbScrabble("b??????", "program"));
		
		lbTest::TEST_GROUP("LONGEST");
		lbTest::TEST(string("coauthored"), longest("dcthoyueorza"));
		lbTest::TEST(string("turquois"), longest("uruqrnytrois"));
		lbTest::TEST(string("greengrocery"), longest("rryqeiaegicgeo??"));
		lbTest::TEST(string("subordinately"), longest("udosjanyuiuebr??"));
		lbTest::TEST(string("ovolactovegetarian"), longest("vaakojeaietg????????"));
		
		lbTest::TEST_GROUP("HIGHEST");
		lbTest::TEST(string("zydeco"), highest("dcthoyueorza"));
		lbTest::TEST(string("squinty"), highest("uruqrnytrois"));
		lbTest::TEST(string("reacquiring"), highest("rryqeiaegicgeo??"));
		lbTest::TEST(string("jaybirds"), highest("udosjanyuiuebr??"));
		lbTest::TEST(string("straightjacketed"), highest("vaakojeaietg????????"));
		
		lbTest::TEST_END();
	}
	else
	{
		doScrabble();     // Tests 01-08
		// doLongest();      // Tests 09-13
		// doHighest();      // Tests 09-13
		argv[1] == "lognest" ? doLongest() : 
		argv[1] == "highest" ? doHighest() :
		/* default function */ doScrabble();
	}
}