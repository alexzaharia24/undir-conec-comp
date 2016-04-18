#pragma once
#include <vector>
#include <unordered_map>

class UGraph {
private:
	std::unordered_map<int, std::vector<int>> neighbors;

public:
	/*	CONSTRUCTORS */
	UGraph(int n = 10);
	/*	Default constructor for the UGraph class.
			Input: n (int) - the number of vertices. */
	UGraph(const UGraph &g);
	/*	Copy constructor for the UGraph class.
			Input: g (const UGraph&) - the graph to be copied. */

	/*	DESTRUCTOR */
	~UGraph();
	/*	Destructor for the UGraph class. */

	/*	GETTERS */
	int getNoOfVertices();
	/*	Gets the number of vertices.
			Output: (int) = number of vertices */
	int getNoOfEdges();
	/*	Gets the number of edges.
			Output: (int) = number of edges */
	int getDegree(int x);
	/*	Gets the degree of a vertix.
			Input: x (int) - the vertix we get the degree for
			Output: (int) - the degree of 'x' */
	std::vector<int> getNeighbors(int x);
	/*	Gets the list of neighbors of x.
			Input: x (int) - the vertix we get the neighbors list for
			Output: (std::vector<int>) - the neighbors list for 'x' */

	/* ADD */
	int addEdge(int x, int y);
	/*	Add an edge between two vertixes.
			Input:	x (int) - the start vertix
					y (int) - the end vertix
			Output: -1 - if the edge already exists
					0  - for successful add
					1  - if the vertices out of range. */
	bool isEdge(int x, int y);
	/*	Verify if there exists an edge between 'x' and 'y'
			Input:	x (int) - the start vertix
					y (int) - the end vertix
			Output:	true (bool) - if there exists and edge btw 'x' and 'y'
					false (bool - otherwise) */

	/* ITERATORS */
	std::vector<int>::iterator iteratorBegin(int x);
	/*	Get an iterator to the begining of the neighbors list of 'x'.
			Input: x (int) - the vertix we work with
			Output: (std::vector<int>::iterator) - iterator to the begining
												 of the neighbors list of 'x' */
	std::vector<int>::iterator iteratorEnd(int x);
	/*	Get an iterator to the end of the neighbors list of 'x'.
			Input: x (int) - the vertix we work with
			Output: (std::vector<int>::iterator) - iterator to the end
												 of the neighbors list of 'x' */
};