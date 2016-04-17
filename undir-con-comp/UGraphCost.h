#pragma once
#include <map>
#include "UGraph.h"

/* ====== UGraphCost ======*/
class UGraphCost : public UGraph {
private:
	std::map<std::pair<int, int>, int> costs; //the cost
public:
	/*CONSTRUCTORS */
	UGraphCost(int n = 10);
	/*	Default constructor for the UGraphCost class.
	Input: n (int) - the number of vertices. */
	UGraphCost(const UGraphCost& g);
	/*	Copy constructor for the UGraphCost class.
	Input: g (const UGraphCost&) - the graph to be copied. */

	~UGraphCost();
	/* Destructor of the UGraphCost class. */

	/* GETTERS */
	int getCost(std::pair<int, int> edge);
	/*	Get the cost of an edge.
	Input: edge (std::pair<int, int>) - the edge represented as a std::pair of vertices
	Output: (int) - the cost of the edge. */
	std::map<std::pair<int, int>, int> getCosts();
	/*	Get the list of costs.
	Output: (std::map<std::pair<int, int>, int>)	- the list of costs represented as a std::mapping
	of std::pairs of ints to some ints. */

	/* SETTERS */
	void setCost(std::pair<int, int> edge, int cost);
	/*	Set the cost of an edge.
	Input:	edge (std::pair<int, int>) - the edge represented by a std::pair of ints
	cost (int) - the new cost of the edge. */

	/* OPERATIONS */
	void addEdge(int x, int y, int z);
	/*	Add an edge between 'x' and 'y' with the cost 'z'.
	Input:	x (int) - the start vertix
	y (int) - the end vertix
	z (int) - the cost. */
};