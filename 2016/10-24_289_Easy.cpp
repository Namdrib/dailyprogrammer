#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5961a5/20161024_challenge_289_easy_its_super_effective/

map<string, int> typeList;
vector<vector<double>> effectiveness;
void setup()
{
	// Read the type effectiveness table
	string infoFileName = "10-24_289_Easy_info.txt";
	ifstream typeTable(infoFileName);
	if (!typeTable.is_open())
	{
		cerr << "Could not open " << infoFileName << endl;
		exit(1);
	}
	
	// Build typeList
	string typeLine;
	getline(typeTable, typeLine);
	transform(typeLine.begin(), typeLine.end(), typeLine.begin(), ::tolower);
	stringstream ss(typeLine);
	int c=0;
	for (string temp; ss >> temp; c++)
	{
		typeList[temp] = c;
	}
	size_t numTypes = typeList.size();
	
	// Build effectiveness
	for (size_t i=0; i<numTypes; i++)
	{
		string line;
		getline(typeTable, line);
		vector<double> row;
		stringstream ss(line);
		for (double temp; ss >> temp;)
		{
			row.push_back(temp);
		}
		effectiveness.push_back(row);
	}
}

string calcEffective(string in)
{
	// Split the input into attack type and defender type
	string delim = " -> ";
	size_t arrowLoc = in.find(delim);
	string attackType = in.substr(0, arrowLoc);
	
	string dType = in.substr(arrowLoc + delim.size());
	
	// Isolate each type
	vector<string> defenceTypes;
	stringstream ss(dType);
	for (string temp; ss >> temp;)
	{
		defenceTypes.push_back(temp);
	}
	
	// calculate the multiplier
	double multiplier = 1.0;
	int aIndex = typeList[attackType];
	for (size_t i=0; i<defenceTypes.size(); i++)
	{
		int dIndex = typeList[defenceTypes[i]];
		multiplier *= effectiveness[aIndex][dIndex];
	}
	
	// Format the return output
	stringstream out;
	out << multiplier;
	out.precision(1);
	return out.str() + "x";
}

int main()
{
	setup();
	
	lbTest::TEST_GROUP("SUPER_EFFECTIVE_BASIC");
	lbTest::TEST(string("2x"), calcEffective("fire -> grass"));
	lbTest::TEST(string("4x"), calcEffective("fighting -> ice rock"));
	lbTest::TEST(string("0x"), calcEffective("psychic -> poison dark"));
	lbTest::TEST(string("1x"), calcEffective("water -> normal"));
	lbTest::TEST(string("0.5x"), calcEffective("fire -> rock"));
	lbTest::TEST_END();
}