#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	for (string nums; getline(cin, nums); )
	{
		next_permutation(nums.begin(), nums.end());
		cout << nums << endl;
	}
}
