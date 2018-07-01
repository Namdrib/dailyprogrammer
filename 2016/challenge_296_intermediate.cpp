#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
using namespace std;

void organise(pair< pair<double, double>, pair<double, double> > &P)
{
	auto p1 = P.first;
	auto p2 = P.second;
	if (p1 > p2) swap(P.first, P.second);
}

double rectangleOverlap(pair< pair<double, double>, pair<double, double> > A,
                        pair< pair<double, double>, pair<double, double> > B)
{
	organise(A);
	organise(B);
	double xCut1 = B.first.first;
	double xCut2 = A.second.first;
	
	double yCut1 = B.first.second;
	double yCut2 = A.second.second;
	
	// Check for no intersection
	if (xCut1 > A.second.first || xCut2 < B.first.first || 
		yCut1 > A.second.second || yCut2 < B.first.second)
	{
		return 0.0;
	}
	else
	{
		return double(abs(xCut2-xCut1) * abs(yCut2-yCut1));
	}
}

void doRectangleOverlap()
{
	// Take input
	// for (int i=0; i<4; i++)
	// {
		// ;
	// }
	
	// Call rectangleOverlap with this input
	cout << rectangleOverlap(make_pair(make_pair(0,0), (make_pair(2,2))), make_pair(make_pair(1,1), make_pair(3,3))) << endl;
	cout << rectangleOverlap(make_pair(make_pair(-3.5,4), (make_pair(1,1))), make_pair(make_pair(1,3.5), make_pair(-2.5,-1))) << endl;
}

int main()
{
	doRectangleOverlap();
}