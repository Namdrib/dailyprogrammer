#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5seexn/20170206_challenge_302_easy_spelling_with/

// INCOMPLETE


// Each object represents a single element of the periodic table.
// Contains the name, abbr, Z value, atomic weight, and electronegativity
class Element
{
public:
	Element()
	{
		;
	}
	
	Element(string fullLine)
	{
		stringstream ss(fullLine);
		ss >> name >> symbol >> Z >> weight >> c;
	}
	
	// Set all the values
	Element(string name, string symbol, int Z, double weight, double c)
	{
		this->name   = name;
		this->symbol = symbol;
		this->Z      = Z;
		this->weight = weight;
		this->c      = c;
	}
	
	// Output
	friend ostream& operator<<(ostream &os, Element &e)
	{
		string sep(6+e.name.size(), '-');
		os << sep << endl;
		os << "name: " << e.name << endl;
		os << "symbol: " << e.symbol << endl;
		os << "Z: " << e.Z << endl;
		os << "weight: " << e.weight << endl;
		os << "c: " << e.c << endl;
		os << sep << endl;
		return os;
	}
	
	string name;
	string symbol;
	int Z;
	double weight;
	double c;
};

vector<Element> readElements(string fileIn)
{
	ifstream f(fileIn);
	
	vector<Element> out;
	for (string temp; getline(f, temp);)
	{
		out.push_back(Element(temp));
	}
	return out;
}

string makeLower(string in)
{
	string out;
	for (auto c : in)
	{
		out += tolower(c);
	}
	return out;
}


// This is the
string makeWord(string target, vector<Element> source)
{
	// The elements chosen to make the target word
	vector<Element> chosens;
	
	for (size_t i=0; i<target.size(); i++)
	{
		for (size_t j=0; j<source.size(); j++)
		{
			string s = makeLower(source[j].symbol);
			
			if (s[0] == target[i])
			{
				cout << target << endl;
				if (s.length() > 1 && i < target.size()-1 && s[1] == target[i+1])
				{
					i++;
					chosens.push_back(source[j]);
					continue;
				}
				chosens.push_back(source[j]);
			}
		}
	}
	
	for (size_t i=0; i<chosens.size(); i++)
	{
		cout << chosens[i] << endl;
	}
	return "a";
}


int main()
{
	vector<Element> elements(readElements("02-06_302_Easy.txt2"));
	
	// Sort by weight descending
	sort(elements.begin(), elements.end(), 
	     // [](Element a, Element b){ return a.weight > b.weight; });
	     [](Element a, Element b){ return a.symbol.size() > b.symbol.size(); });
	
	
	// for (size_t i=0; i<5; i++)
	// {
		// cout << elements[i] << endl;
	// }
	
	vector<string> targetWords
	{
		"genius", // test
		"functions",
		"bacon",
		"poison",
		"sickness",
		"ticklish"
	};
	
	cout << makeWord(targetWords[0], elements) << endl;
}

