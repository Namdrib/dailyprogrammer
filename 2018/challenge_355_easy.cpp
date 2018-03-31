#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/879u8b/20180326_challenge_355_easy_alphabet_cipher/

// If query is "test" and length is 10, return "testestte"
// If length < length of query, truncate query to length
string extend(string query, int length)
{
	if (length < query.size())
	{
		return query.substr(0, length);
	}

	string out = "";
	int d = length / query.size();
	int r = length % query.size();
	for (int i=0; i<d; i++)
	{
		out += query;
	}
	out += query.substr(0, r);
	return out;
}

// "Rotate" a letter such that a -> b, b -> c, ..., y -> z, z -> a
// and similarly for capital letters.
char rotate_left(char c, int amount)
{
	amount %= 26;
	int lo_bound = (islower(c)) ? 97 : 65;

	c = ((c + (amount - lo_bound)) % 26) + lo_bound;
	return c;
}

// Opposite of rotate_left
char rotate_right(char c, int amount)
{
	amount %= 26;
	int lo_bound = (islower(c)) ? 97 : 65;

	c -= amount;
	int diff = c - lo_bound;
	if (diff < 0)
	{
		c = (lo_bound + 26) + diff;
	}

	return c;
}

// Vigenere cipher.
// En/decode msg using secret as the key
// `decode` == 1 => decode
string vigenere(string secret, string msg, bool decode = 0)
{
	string out = "";
	string ext = extend(secret, msg.size());
	for (int i=0; i<msg.size(); i++)
	{
		if (decode)
		{
			out += rotate_right(msg[i], ext[i] - (islower(msg[i]) ? 'a' : 'A'));
		}
		else
		{
			out += rotate_left(msg[i], ext[i] - (islower(msg[i]) ? 'a' : 'A'));
		}
	}

	return out;
}

int main(int argc, char** argv)
{
	// Helpers
	assert(extend("test", 10) == "testtestte");
	assert(extend("test", 3) == "tes");
	assert(extend("test", 4) == "test");
	assert(extend("test", 8) == "testtest");

	assert(rotate_left('a', 1) == 'b');
	assert(rotate_left('a', 25) == 'z');
	assert(rotate_left('a', 26) == 'a');
	assert(rotate_left('z', 1) == 'a');
	assert(rotate_left('Z', 1) == 'A');
	assert(rotate_left('h', 20) == 'b');
	assert(rotate_left('t', 18) == 'l');

	assert(rotate_right('b', 1) == 'a');
	assert(rotate_right('z', 25) == 'a');
	assert(rotate_right('a', 26) == 'a');
	assert(rotate_right('a', 1) == 'z');
	assert(rotate_right('A', 1) == 'Z');
	assert(rotate_right('b', 20) == 'h');
	assert(rotate_right('l', 18) == 't');

	// Main
	assert(vigenere("snitch", "thepackagehasbeendelivered", 0) == "lumicjcnoxjhkomxpkwyqogywq");
	assert(vigenere("bond",   "theredfoxtrotsquietlyatmidnight", 0) == "uvrufrsryherugdxjsgozogpjralhvg");
	assert(vigenere("train",  "murderontheorientexpress", 0) == "flrlrkfnbuxfrqrgkefckvsa");
	assert(vigenere("garden", "themolessnuckintothegardenlastnight", 0) == "zhvpsyksjqypqiewsgnexdvqkncdwgtixkx");
	assert(vigenere("SNITCH", "THEPACKAGEHASBEENDELIVERED", 0) == "LUMICJCNOXJHKOMXPKWYQOGYWQ");
	assert(vigenere("BOND",   "THEREDFOXTROTSQUIETLYATMIDNIGHT", 0) == "UVRUFRSRYHERUGDXJSGOZOGPJRALHVG");
	assert(vigenere("TRAIN",  "MURDERONTHEORIENTEXPRESS", 0) == "FLRLRKFNBUXFRQRGKEFCKVSA");
	assert(vigenere("GARDEN", "THEMOLESSNUCKINTOTHEGARDENLASTNIGHT", 0) == "ZHVPSYKSJQYPQIEWSGNEXDVQKNCDWGTIXKX");

	// Bonus
	assert(vigenere("cloak",  "klatrgafedvtssdwywcyty", 1) == "iamtheprettiestunicorn");
	assert(vigenere("python", "pjphmfamhrcaifxifvvfmzwqtmyswst", 1) == "alwayslookonthebrightsideoflife");
	assert(vigenere("moore",  "rcfpsgfspiecbcc", 1) == "foryoureyesonly");
	assert(vigenere("CLOAK",  "KLATRGAFEDVTSSDWYWCYTY", 1) == "IAMTHEPRETTIESTUNICORN");
	assert(vigenere("PYTHON", "PJPHMFAMHRCAIFXIFVVFMZWQTMYSWST", 1) == "ALWAYSLOOKONTHEBRIGHTSIDEOFLIFE");
	assert(vigenere("MOORE",  "RCFPSGFSPIECBCC", 1) == "FORYOUREYESONLY");
}
