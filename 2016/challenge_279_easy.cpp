#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/4xy6i1/20160816_challenge_279_easy_uuencoding/

// INCOMPLETE

string decToBinaryString(int decimal, int requiredLength)
{
	string out = "";
	while (decimal)
	{
		out = to_string(decimal & 1) + out;
		decimal >>= 1;
	}
	out = string(max(0, (requiredLength - (int)out.size()) ), '0') + out;
	return out;
}

int stringBinaryToDec(string binary)
{
	int out;
	for (size_t i=0; i<binary.size(); i++)
	{
		if (binary[i] == '1')
		{
			out += pow(2, binary.size() - 1 - i);
		}
	}
	return out;
}

string uuencode(string message)
{
	string encoded = "begin 644 file.txt\n";
	
	string totalBinaryStr;
	// Break it down first
	for (int c : message)
	{
		string binaryStr = decToBinaryString(c, 8);
		totalBinaryStr += binaryStr;
		cout << c << " : " << binaryStr << endl;
	} cout << endl;
	cout << "totalBinaryStr: " << totalBinaryStr << endl;
	
	// Break totalBinaryStr into four groups of binary
	int quarterSize = totalBinaryStr.size() / 4;
	string lineString;
	for (int i=0; i<totalBinaryStr.size(); i += quarterSize)
	{
		string stringQuarter = totalBinaryStr.substr(i, quarterSize);
		// cout << "stringQuarter: " << stringQuarter << endl;
		int decimalQuarter = stringBinaryToDec(stringQuarter) + 32;
		lineString += decimalQuarter;
		cout << (char)decimalQuarter << endl;
	}
	lineString = char(45 + (int)lineString.size()) + lineString;
	cout << "lineString: " << lineString << endl;
	
	encoded += "`\nend\n";
	cout << "Encoded: \n" << encoded << endl;
	return "A";
}


int main()
{
	string message;
	getline(cin, message);
	
	// if looksLikePath(message) open a file
	
	cout << uuencode(message) << endl;
}