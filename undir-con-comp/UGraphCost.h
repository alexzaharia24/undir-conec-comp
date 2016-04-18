#pragma once
#include <map>
#include "UGraph.h"

/* Connected components */
//vector<vector<pair<int, int>>> conComp(UGraph g) {
//	/* RECODE THIS IN THE MORNING */
//	vector<vector<pair<int, int>>> result;
//	vector<int> visited;
//	vector<pair<int, int>> bfs;
//	vector<int> vertices;
//	int x = 0;
//	int n = 1;
//	for (int i = 0; i < g.getNoOfVertices(); ++i) {
//		visited.push_back(0);
//	}
//	while (n < g.getNoOfVertices()) {
//		for (unsigned i = 0; i < visited.size(); ++i) {
//			if (visited[i] != 1) {
//				x = i;
//				break;
//			}
//		}
//		bfs = BFS(x, g);
//		cout << "bfs-size = " << bfs.size() << "\n";
//		/*if (bfs.size() == 1) {
//		n++;
//		}*/
//		vertices.push_back(x);
//		visited[x] = 1;
//		for (auto e : bfs) {
//			if (find(vertices.begin(), vertices.end(), e.first) == vertices.end() && e.first != x) {
//				vertices.push_back(e.first);
//			}
//			if (find(vertices.begin(), vertices.end(), e.second) == vertices.end() != e.second != x) {
//				vertices.push_back(e.second);
//			}
//		}
//		for (unsigned c = 1; c <= bfs.size(); ++c) {
//			visited[vertices[c]] = 1;
//			n++;
//		}
//		while (!vertices.empty()) {
//			vertices.pop_back();
//		}
//		result.push_back(bfs);
//
//	}
//	return result;
//}

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