#include "UGraphCost.h"

/* CONSTRUCTORS [UGraphCost] */
UGraphCost::UGraphCost(int n) : UGraph(n) {
}
UGraphCost::UGraphCost(const UGraphCost& g) : UGraph(g) {
	this->costs = g.costs;
}
/* DESTRUCTOR [UGraphCost] */
UGraphCost::~UGraphCost() {}

/* GETTERS */
int UGraphCost::getCost(std::pair<int, int> edge) {
	return this->costs[edge];
}
std::map<std::pair<int, int>, int> UGraphCost::getCosts() {
	return this->costs;
}

/* SETTERS [UGraphCost] */
void UGraphCost::setCost(std::pair<int, int> edge, int cost) {
	this->costs[edge] = cost;
}

/* OPERATIONS [UGraphCost] */
void UGraphCost::addEdge(int x, int y, int z) {
	UGraph::addEdge(x, y);
	this->costs[std::make_pair(x, y)] = z;
}