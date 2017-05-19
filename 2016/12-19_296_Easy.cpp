#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5j6ggm/20161219_challenge_296_easy_the_twelve_days_of/
// Bonus 1, 2

class DoC // Day of Christmas
{
public:
	DoC(){;}
	DoC(int cNum, string cNumTh, string cNumber, string cGift)
	{
		num = cNum;
		numTh = cNumTh;
		number = cNumber;
		gift = cGift;
	}

	// output a line of a verse
	void out(bool bonus1)
	{
		cout << (bonus1 ? number : to_string(num)) << " " << gift << endl;
	}

	int num;
	string numTh;
	string number;
	string gift;
};

vector<DoC> days {
	DoC(),
	DoC(1, "first", "a", "Partridge in a Pear Tree"),
	DoC(2, "second", "two", "Turtle Doves"),
	DoC(3, "third", "three", "French Hens"),
	DoC(4, "fourth", "four", "Calling Birds"),
	DoC(5, "fifth", "five", "Golden Rings"),
	DoC(6, "sixth", "six", "Geese a Laying"),
	DoC(7, "seventh", "seven", "Swans a Swimming"),
	DoC(8, "eighth", "eight", "Maids a Milking"),
	DoC(9, "ninth", "nine", "Ladies Dancing"),
	DoC(10, "tenth", "ten", "Lords a Leaping"),
	DoC(11, "eleventh", "eleven", "Pipers Piping"),
	DoC(12, "twelfth", "twelve", "Drummers Drumming")
};

// Print the nth verse of the song
void verse(int n)
{
	cout << "On the " << days[n].numTh << " day of Christmas" << endl;
	cout << "my true love sent to me:" << endl;
	for (int i=n; i; i--)
	{
		if (n > 1 && i == 1) cout << "and ";
		days[i].out(1); // out(1) for bonus 1
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	for (int i=1; i<13; i++)
	{
		if (argc >= 2 && string(argv[1]) == "in") getline(cin, days[i].gift); // Bonus 2
		verse(i);
	}
}