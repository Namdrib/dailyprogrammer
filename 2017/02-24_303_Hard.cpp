#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "../lbTest.h"
using namespace std;

#define all(c) (c).begin(), (c).end()
#define pq true

// https://www.reddit.com/r/dailyprogrammer/comments/5vwwzg/20170224_challenge_303_hard_escaping_a_dangerous/

// Useful links (while I'm still working on this)
// http://www.cplusplus.com/reference/queue/priority_queue/
// http://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator#16111402

// Dijkstra's works
// A* sometimes works (sometimes returns cost=600 for some of the h cost functions)
// Priority queue works, I think

class Coord
{
public:
	Coord() {;}
	Coord(short x, short y)
	{
		this->x = x;
		this->y = y;
	}
	
	bool operator==(const Coord &c)
	{
		return x == c.x && y == c.y;
	}
	
	friend ostream& operator<<(ostream &os, const Coord &c)
	{
		os << "{" << c.x << "," << c.y << "}";
		return os;
	}
	
	short x;
	short y;
};


class Node
{
public:
	Node()
	{
		f = 0;
		g = 0;
		h = 0;
		parent = NULL;
	}
	
	int f; // Toal cost (g + h)
	int g; // Running cost (step)
	int h; // Heuristic cost // ONLY A*
	Node* parent;
	Coord c;
};

// For use with priority queue.
// The front element is the Node* with lowest f value
struct nodeCompareMaxF
{
	bool operator() (const Node* a, const Node* b) const
	{
		return a->f > b->f;
	}
};

const int dirY[4] = {-1, 1, 0, 0};
const int dirX[4] = {0, 0, -1, 1};

// Return the cost of moving onto certain tiles
int getTileCost(const char tile)
{
	if (tile == 'm') return 11;
	else return 1;
}

int findManhattanDistance(const Coord &a, const Coord &b)
{
	int diffX = abs(a.x - b.x);
	int diffY = abs(a.y - b.y);
	return diffX + diffY;
}

int findMaxAxisDistance(const Coord &a, const Coord &b)
{
	int diffX = abs(a.x - b.x);
	int diffY = abs(a.y - b.y);
	return max(diffX, diffY);
}

int findEuclideanDistance(const Coord &a, const Coord &b)
{
	int diffX = abs(a.x - b.x);
	int diffY = abs(a.y - b.y);
	return int(sqrt(pow(diffX, 2) + pow(diffY, 2)));
}


// Uses either Dijkstra's or A*
Node* search(vector<string> &grid, Coord start, Coord end, bool aStar)
{
	#if pq
		cout << "Using a priority queue" << endl;
		priority_queue<Node*, vector<Node*>, nodeCompareMaxF> fringe;
	#else
		cout << "Using a vector" << endl;
		vector<Node*> fringe;
	#endif
	vector<Coord> closed;
	
	Node* first = new Node();
	first->c = start;	
	
	#if pq
		fringe.push(first);
	#else
		fringe.push_back(first);
	#endif
	
	// If it exhausts the fringe, there is no path through
	while (!fringe.empty())
	{
		// Get the node with the lowest f
		#if pq
			Node* current = fringe.top();
			fringe.pop();
		#else
			size_t minPos = distance(fringe.begin(), min_element(all(fringe), [](Node* a, Node* b){return a->f < b->f;}));
			Node* current = fringe[minPos];
			fringe.erase(fringe.begin() + minPos);
		#endif
		
		// The hero has reached the end of the maze
		if (current->c == end)
		{
			return current;
		}
		
		// For each neighbour:
		for (size_t i=0; i<4; i++)
		{
			// Make sure it isn't going out of bounds
			Coord step(current->c.x + dirX[i], current->c.y + dirY[i]);			
			if (step.x < 0 || step.x >= grid[0].size() || step.y < 0 || step.y >= grid.size())
			{
				continue;
			}
			
			// Make sure moving to valid location
			char tile = grid[step.y][step.x];
			if (tile == '#') continue;
			
			// Make sure this location hasn't been discovered before
			if (find(all(closed), step) != closed.end()) continue;
			
			// It's valid, so make a new node at this new location
			Node* temp = new Node();
			temp->c = step;
			temp->g = current->g + getTileCost(tile);
			if (aStar)
			{
				// temp->h = findManhattanDistance(temp->c, end);
				temp->h = findMaxAxisDistance(temp->c, end);
				// temp->h = findEuclideanDistance(temp->c, end);
			}
			temp->f = temp->g + temp->h;
			temp->parent = current;
			
			#if pq
				fringe.push(temp);
			#else
				fringe.push_back(temp);
			#endif
			closed.push_back(temp->c);
		}
	}
	
	cout << "couldn't find a path..." << endl;
	return NULL;
}


int main(int argc, char* argv[])
{
	// Any number of args will trigger A*
	bool aStar = false;
	if (argc > 1) aStar = true;
	
	// Load the map
	vector<string> grid;
	for (string temp; getline(cin, temp);)
	{
		grid.push_back(temp);
	}
	
	// Locate start and end
	Coord start, end;
	for (size_t i=0; i<grid.size(); i++)
	{
		size_t sPos = grid[i].find("S");
		if (sPos != string::npos)
		{
			start.x = sPos;
			start.y = i;
		}
		size_t gPos = grid[i].find("G");
		if (gPos != string::npos)
		{
			end.x = gPos;
			end.y = i;
		}
	}
	
	// Get the last node returned by `search`
	Node* result = search(grid, start, end, aStar);
	if (result == NULL) cout << "No result..." << endl;
	
	// Store the cost
	int cost = result->f;
	result = result->parent;
	
	// Alter the map
	while (result->parent != NULL)
	{
		grid[result->c.y][result->c.x] = '*';
		result = result->parent;
	}
	
	// Print the map and cost
	for (size_t i=0; i<grid.size(); i++)
	{
		cout << grid[i] << endl;
	}
	cout << "Cost: " << cost << "HP" << endl;
	cout << "aStar: " << aStar << endl;
}