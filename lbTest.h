// ===========================//
//      Super Test Script     //
//   Sam Lewis | 16 Aug 2016  //
// ===========================//

#ifndef LB_TEST_H
#define LB_TEST_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const string ANSI_RESET =        "\033[0m";
const string ANSI_BLACK =        "\033[0;30m";
const string ANSI_RED =          "\033[0;31m";
const string ANSI_GREEN =        "\033[0;32m";
const string ANSI_BROWN =        "\033[0;33m";
const string ANSI_BLUE =         "\033[0;34m";
const string ANSI_PURPLE =       "\033[0;35m";
const string ANSI_CYAN =         "\033[0;36m";
const string ANSI_GRAY =         "\033[0;37m";
const string ANSI_DARK_GRAY =    "\033[1;30m";
const string ANSI_LIGHT_RED =    "\033[1;31m";
const string ANSI_LIGHT_GREEN =  "\033[1;32m";
const string ANSI_YELLOW =       "\033[1;33m";
const string ANSI_LIGHT_BLUE =   "\033[1;34m";
const string ANSI_LIGHT_PURPLE = "\033[1;35m";
const string ANSI_LIGHT_CYAN =   "\033[1;36m";
const string ANSI_WHITE =        "\033[1;37m";

// Vector printing
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	os << "{";
	for (size_t i=0; i<vec.size(); i++) {
		os << vec[i];
		if (i < vec.size()-1) os << ", ";
	}
	os << "}";
	return os;
}

class lbTest {
public:
    static void TEST_GROUP(string title) {
		// End any previous tests
		TEST_GROUP_END();
		_current = new Res(title);
		
		// Title printing
		cerr << "\n" << ANSI_WHITE << "[[ " << title << " ]]" << ANSI_RESET << endl;
    }

    // Test for non vector types
    template <typename T>
    static void TEST(T const& expected, T const& actual) {
		_current->numTests++;
		cerr << " " << ANSI_LIGHT_BLUE <<_current->numTests << "." << ANSI_RESET;

		if (actual == expected) {
			cerr << ANSI_GREEN << "PASSED" << ANSI_RESET << endl;
			_current->numPassed++;
		} else {
			cerr << ANSI_RED << "FAILED" << ANSI_RESET << endl;
			cerr << "\tExpect:\t" << expected << endl;
			cerr << "\tActual:\t" << actual << endl;
		}
    }
	
    // Test for vector types
    template <typename T, typename A>
    static void TEST(vector<T,A> const& expected, vector<T,A> const& actual) {
		_current->numTests++;
		cerr << " " << ANSI_LIGHT_BLUE <<_current->numTests << "." << ANSI_RESET;

		if (actual == expected) {
			cerr << ANSI_GREEN << "PASSED" << ANSI_RESET << endl;
			_current->numPassed++;
		} else {
			cerr << ANSI_RED << "FAILED" << ANSI_RESET << endl;
			cerr << "\tExpect:\t" << expected << endl;
			cerr << "\tActual:\t" << actual << endl;
		}
    }
	
    // End single test group
    static void TEST_GROUP_END() {
		// Close prev group
		if (_current->numTests == 0 || _current->title == "") return;

		// Pretty print of just ended test
		float perc = 100* ((float)_current->numPassed / (float)_current->numTests);
		cerr.precision(4);
		cerr << " > " << ANSI_WHITE << _current->numPassed << " / " << _current->numTests << " :: " << ANSI_YELLOW << perc << "%" << ANSI_RESET << endl;

		// Store for final printing
		_totalResults.push_back(_current);
    }
	
    // End all groups
    static void TEST_END() {
		TEST_GROUP_END();
		
		int totalTests = 0;
		int totalPassed = 0;

		// Work out max spacing limit thing
		int maxW = 0;
		for (size_t i=0; i<_totalResults.size(); i++) {
			maxW = max(maxW, (int)_totalResults[i]->title.size());
		}
		
		// Title
		cerr << endl;
		cerr << ANSI_PURPLE << string(maxW+27,'=') << ANSI_RESET <<  endl;
		cerr << string(((maxW+25)/2 - 4), ' ') << "\033[1mEND TESTS" << ANSI_RESET << endl;
		cerr << ANSI_PURPLE << string(maxW+27,'=') << ANSI_RESET <<  endl;
		
		// Print out all individual results
		for (size_t i=0; i<_totalResults.size(); i++) {
			totalTests += _totalResults[i]->numTests;
			totalPassed += _totalResults[i]->numPassed;
			
			int perc = 100* ((float)_totalResults[i]->numPassed / (float)_totalResults[i]->numTests);
			string percS = to_string(perc) + "%";
			string frac = to_string(_totalResults[i]->numPassed) + "/" + to_string(_totalResults[i]->numTests);
			
			cerr << " ";
			cerr << left << setw(maxW+4) << _totalResults[i]->title;
			cerr << left << setw(8) << frac;
			cerr << left << setw(4) << percS;

			if (perc == 100) cerr << "\t" << ANSI_GREEN << "PASSED";
			else             cerr << "\t" << ANSI_RED << "FAILED";
			cerr << ANSI_RESET << endl;
		}
		
		cerr << ANSI_PURPLE << string(maxW+27,'-') << ANSI_RESET <<  endl;
		
		// Calculate and print total
		int perc = 100* ((float)totalPassed / (float)totalTests);
		string percS = to_string(perc) + "%";
		string frac = to_string(totalPassed) + "/" + to_string(totalTests);
		
		cerr << " ";
		cerr << left << setw(maxW+8) << "\033[1mTOTAL";
		cerr << left << setw(8) << frac;
		cerr << left << setw(4) << percS;
		
		if (perc == 100) cerr << "\t" << ANSI_GREEN << "PASSED";
		else             cerr << "\t" << ANSI_RED << "FAILED";
		cerr << ANSI_RESET << endl;
		cerr << ANSI_PURPLE << string(maxW+27,'=') << ANSI_RESET <<  endl;
    }

private:
	lbTest() {}
	~lbTest() {}

	struct Res {
		int numTests;
		int numPassed;
		string title;
		
		Res(string t) : numTests(0), numPassed(0), title(t) {}
	};

	static Res* _current;
	static vector<Res*> _totalResults;
};

// Always starts with a blank, that is then ignored later.
lbTest::Res* lbTest::_current = new Res("");
vector<lbTest::Res*> lbTest::_totalResults;


#endif // LB_TEST_H
