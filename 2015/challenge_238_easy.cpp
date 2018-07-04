#include <bits/stdc++.h>
#include <unistd.h>
#include "../helpers.cpp"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/3qjnil/20151028_challenge_238_intermediate_fallout/


// A vector of difficulties and their corresponding
// potential string lengths
// Lower difficulties use shorter words
const vector<pair<int, int>> difficulties = {
	make_pair(4, 6),
	make_pair(7, 8),
	make_pair(9, 11),
	make_pair(12, 13),
	make_pair(14, 15),
};

class config
{
public:
	int difficulty;
	int num_guesses;
	int num_words;
	string dictionary;
};

void usage(char *program)
{
	cout << "Usage:\n"
	<< program << " [options]\n\n"

	<< "Options:\n"
	<< "  -d  : game difficulty (1-5) (default: 3)\n"
	<< "  -g  : number of guesses available (1-4) (default: 4)\n"
	<< "  -w  : list of words to test (>=5) (default: 15)\n"
	<< "  -h  : show this help and exit\n"
	<< endl;
}

void parse_args(int argc, char **argv, config &c)
{
	// Default values
	c.difficulty = 3;
	c.num_guesses = 4;
	c.num_words = 15;
	c.dictionary = "../misc/enable1.txt";

	// Read arguments
	int ch, temp;
	while ((ch = getopt(argc, argv, "hd:g:w:")) != -1)
	{
		switch (ch)
		{
			case 'h':
				usage(argv[0]);
				exit(0);
				break;

			case 'd':
				temp = atoi(optarg);
				if (temp < 1 || temp > 5)
				{
					cout << "difficulty must be between 1-5 (inclusive)" << endl;
					exit(1);
				}
				c.difficulty = temp;
				break;

			case 'g':
				temp = atoi(optarg);
				if (temp < 1 || temp > 4)
				{
					cout << "num_guesses must be between 1-4 (inclusive)" << endl;
					exit(1);
				}
				c.num_guesses = temp;
				break;

			case 'w':
				temp = atoi(optarg);
				if (temp < 4)
				{
					cout << "num_words must be between >=4 " << endl;
					exit(1);
				}
				c.num_words = temp;
				break;

			default:
				usage(argv[0]);
				exit(1);
		}
	}
}

// Generate a random integral number between lo and hi
// Static prevents it from generating a new seed/generator every time
template <typename T>
T random_int_between(const T &lo, const T &hi)
{
	static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static default_random_engine generator(seed);
	return uniform_int_distribution<int>(lo, hi)(generator);
}

// Initialise the list of words to use in the game,
// sourced from all words in enable1 (all)
vector<string> initialise_words(const vector<string> &words, const config &c)
{
	pair<int, int> length_range = difficulties[c.difficulty-1];
	cout << length_range.first << ", " << length_range.second << endl;

	int word_length = random_int_between<int>(length_range.first, length_range.second);
	vector<string> out;

	// https://stackoverflow.com/questions/21204676/modern-way-to-filter-stl-container
	auto it = copy_if(all(words), back_inserter(out), [word_length](string s){return s.size() == word_length;});

	// shuffle then pick the first few
	shuffle(all(out), default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
	return vector<string>(out.begin(), out.begin() + c.num_words);
}

// Return the number of matching letters between a and b
// A letter matchces if it is the same in both positions of the word
// e.g. ADD | DAD -> 1 match (last d)
int get_num_matching_letters(const string &a, const string &b)
{
	return inner_product(all(a), b.begin(), 0, plus<int>(), [](char a, char b){return a == b;});
}

// Play the game. User inputs for the word to guess
// Guesses can be made with the word itself (typed) or the word's index
// For each guess, check correctness (compare with correct)
// If correct, inform user and quit.
// Otherwise, display how many letters were correct and reduce a guess
void play(const vector<string> &words_to_use, const string &correct, int num_guesses)
{
	const size_t size = correct.size();

	while (num_guesses > 0)
	{
		// display words
		for (size_t i=0; i<words_to_use.size(); i++)
		{
			// TODO : pad the index
			cout << "\t" << i+1 << " : " << words_to_use[i] << endl;
		}

		// TODO : TAKE INPUT FOR GUESS
		cout << "Guess (" << num_guesses << ") left: ";
		string guess;
		cin >> guess;
		transform(all(guess), guess.begin(), ::toupper);
		while (find(all(words_to_use), guess) == words_to_use.end())
		{
			cout << "Guess must be a word in the list (case insensitive) or "
			<< "the index of one of the words (" << 1 << " to " << words_to_use.size() << "): ";
			cin >> guess;
			transform(all(guess), guess.begin(), ::toupper);
		}

		// TODO : post-guess stage
		int num_matching_letters = get_num_matching_letters(guess, correct);
		cout << num_matching_letters << "/" << size << " correct" << endl;
		if (num_matching_letters == size)
		{
			cout << "You win!" << endl;
			return;
		}

		num_guesses--;
	}
	cout << "Out of guesses!" << endl;
	cout << "The correct word was " << correct << endl;
}

int main(int argc, char **argv)
{
	// read arguments
	config c;
	parse_args(argc, argv, c);

	auto words = read_file_into_vector<string>(c.dictionary);
	if (words.empty())
	{
		return 2;
	}
	for (auto &s : words)
	{
		transform(all(s), s.begin(), ::toupper);
	}

	auto words_to_use = initialise_words(words, c);
	cout << words_to_use << endl;

	auto correct_word = words_to_use[random_int_between<int>(0, words_to_use.size()-1)];
	cout << "Correct word: " << correct_word << endl;

	play(words_to_use, correct_word, c.num_guesses);
}
