#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "../lbTest.h" // colours too
#include "../helpers.cpp"
using namespace std;

// Swype keyboard predictor

// Walk along both word and input, ticking along when the two letters match
// BONUS : "stay" on a letter if the next one is the same
// example: word = "polly", input = "polkjuy"
// both on p -> tick along `word`. now they're out of sync
// tick along `query`, now they're in sync. instead of ticking both, only tick word
bool can_be_built_with(const string &word, const string &input)
{
	size_t wordIdx = 0;
	size_t inputIdx = 0;

	while (true)
	{
		// Not >= because could end on a double letter
		if (wordIdx >= word.size() || inputIdx >= input.size())
		{
			#ifdef DEBUG
				cout << "Broke " << word << " at " << wordIdx << "," << inputIdx << endl;
			#endif // DEBUG
			break;
		}

		#ifdef DEBUG
			cout << ANSI_GREEN << word.substr(0, wordIdx) << ANSI_RESET << word.substr(wordIdx) << " | ";
			cout << ANSI_GREEN << input.substr(0, inputIdx) << ANSI_RESET << input.substr(inputIdx) << endl;
		#endif // DEBUG
		if (word[wordIdx] == input[inputIdx])
		{
			wordIdx++;
		}
		else
		{
			inputIdx++;
		}

	}

	return wordIdx >= word.size();
}

// Step 1: load all words whose length >= length, starts with input.front() and ends input.back()
// Step 2: step through each of these to see if they're possible to be generated using input
// Since this goes through the dictionary (assume sorted), it should come out sorted
vector<string> load_possible_words(const string &input, string dictionary = "tests/all_words.txt", const size_t length = 5)
{
	ifstream ifs(dictionary);
	if (!ifs.is_open())
	{
		cerr << "Could not open " << dictionary << endl;
		exit(1);
	}

	char front = input.front();
	char back = input.back();

	// Step 1
	// The list of words that start and end with the right letters
	// and are long enough
	vector<string> potential_words;
	for (string word; getline(ifs, word); )
	{
		if (word.front() == front && word.back() == back && word.size() >= length)
		{
			potential_words.push_back(word);
		}
	}

	// Step 2
	// Narrow down to the potential words that can be built using input
	vector<string> definite_words;
	for (string word : potential_words)
	{
		if (can_be_built_with(word, input))
		{
			definite_words.push_back(word);
		}
	}

	return definite_words;
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		lbTest::TEST_GROUP("SWYPE KEYBOARD");
		lbTest::TEST(vector<string>{"queen","question"},  load_possible_words("qwertyuytresdftyuioknn"));
		lbTest::TEST(vector<string>{"gaeing", "garring", "gathering", "gating", "geeing", "gieing", "going", "goring"}, load_possible_words("gijakjthoijerjidsdfnokg"));

		lbTest::TEST_END();
	}
	else
	{
		cout << load_possible_words(argv[1]);
	}
}
