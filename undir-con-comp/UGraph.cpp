#include "UGraph.h"

/* CONSTRUCTORS [UGraph] */
UGraph::UGraph(int n) {
	int i;
	for (i = 0; i<n; i++) {
		this->neighbors[i] = std::vector<int>();
	}
}
UGraph::UGraph(const UGraph& g) {
	this->neighbors = g.neighbors;
}

/* DESTRUCTOR [UGraph] */
UGraph::~UGraph() {
}

/* GETTERS [UGraph] */
int UGraph::getNoOfVertices() {
	return this->neighbors.size();
}
int UGraph::getNoOfEdges() {
	int no = 0;
	for (int i = 0; i < this->getNoOfVertices(); i++) {
		no += this->neighbors[i].size();
	}
	return no / 2;
}
int UGraph::getDegree(int x) {
	return this->neighbors[x].size();
}
std::vector<int> UGraph::getNeighbors(int x) {
	return this->neighbors[x];
}

/* ADD [UGraph] */
int UGraph::addEdge(int x, int y) {
	if (x > this->getNoOfVertices() || y > this->getNoOfVertices()) {
		return 0;
	}
	else if (isEdge(x, y)) {
		return -1;
	}
	if (x != y) {
		this->neighbors[y].push_back(x);
		this->neighbors[x].push_back(y);
	}
	return 1;
}
bool UGraph::isEdge(int x, int y) {
	if (find(this->neighbors[y].begin(), this->neighbors[y].end(), x) != this->neighbors[y].end()) {
		return 1;
	}
	return 0;
}

/* ITERATORS [UGraph] */
std::vector<int>::iterator UGraph::iteratorBegin(int x) {
	return this->neighbors[x].begin();
}
std::vector<int>::iterator UGraph::iteratorEnd(int x) {
	return this->neighbors[x].end();
}