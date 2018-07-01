#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../lbTest.h"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/5nciz5/20170111_challenge_299_intermediate_from_maze_to/

vector<string> takeGraphInput()
{
	ifstream f("tests/01-11_299_Intermediate_01.in");
	if (!f.is_open())
	{
		cerr << "Error, could not open the map file" << endl;
		exit(2);
	}
	vector<string> out;
	for (string temp; f >> temp;)
	{
		out.push_back(temp);
	}
	return out;
}

bool isIntersection(const vector<string> &graph, int x, int y)
{
	int numOpenings = 0;
	// Current tile must be a free space
	if (graph[y][x] == '.')
	{
		if (graph[y-1][x] == '.') numOpenings++; // Up
		if (graph[y+1][x] == '.') numOpenings++; // Down
		if (graph[y][x-1] == '.') numOpenings++; // Left
		if (graph[y][x+1] == '.') numOpenings++; // Right
	}
	return numOpenings >= 3;
}

// Part 1: number of intersections
int numNodes(const vector<string> &graph)
{
	int numNodes = 0;
	int sumRow = 0;
	int sumCol = 0;
	for (size_t i=0; i<graph.size(); i++)
	{
		for (size_t j=0; j<graph[i].size(); j++)
		{
			if (isIntersection(graph, j, i)) numNodes++, sumRow += j, sumCol += i;
		}
	}
	cout << "r,w: " << sumRow << ", " << sumCol << endl;
	return numNodes;
}

int main()
{
	vector<string> graph(takeGraphInput());
	lbTest::TEST_GROUP("EASY: NUM_NODES");
	lbTest::TEST(832, numNodes(graph));
	
	lbTest::TEST_END();
}