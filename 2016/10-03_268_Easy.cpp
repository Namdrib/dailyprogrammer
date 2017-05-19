#include <algorithm>
#include <iostream>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/55nior/20161003_challenge_286_easy_reverse_factorial/

// Returning 0.0 means `in` isn't a factorial
double reverseFactorial(double in)
{
	int f = 1;
	while (in > 1)
	{
		in /= ++f;
	}
	return (in < 1) ? 0.0 : f;
}


int main()
{
	int input;
	while (cin >> input)
	{
		cout << input;
		double result = reverseFactorial(double(input));
		if (result == 0.0)
		{
			cout << "  NONE" << endl;
		}
		else
		{
			cout << " = " << result << "!" << endl;
		}
	}
}