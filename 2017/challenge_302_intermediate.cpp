#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5st2so/20170208_challenge_302_intermediate_ascii/

int main()
{
	// Taking input
	int minX, maxX, minY, maxY;
	cin >> minX >> maxX >> minY >> maxY;
	
	int n; cin >> n;
	vector<int> numPoints(n);
	
	// This assumes that the intervals are regular,
	// and that it's given in sorted order
	for (int i=0; i<n; i++)
	{
		int localMin, localMax, localNum;
		cin >> localMin >> localMax >> localNum;
		numPoints[i] = localNum;
	}
	
	// Assume that it's a regular increment (not decimal)
	int incrementSize = (maxX - minX) / n;
	
	// Do output	
	int xMaxLength = to_string(maxX).size();
	int yMaxLength = to_string(maxY).size();
	int gapSize = xMaxLength+1;
	
	// each row
	for (int i=maxY; i>=minY; i--)
	{
		// Output the y-axis (padded)
		cout << setfill(' ') << setw(yMaxLength) << i;
		
		// each col
		for (int j=0; j<n; j++)
		{
			char currentCharacter = (numPoints[j] >= i) ? '*' : ' ';
			cout << setfill(' ') << setw(gapSize) << currentCharacter;
		}
		
		cout << endl;
	}
	
	// Output the x-axis (padded)
	cout << setfill(' ') << setw(yMaxLength-1) << "";
	for (int i=minX; i<=maxX; i+=incrementSize)
	{
		cout << setfill(' ') << setw(gapSize) << i;
	} cout << endl;
}