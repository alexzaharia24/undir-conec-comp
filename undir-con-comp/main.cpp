#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

#include "UGraphCost.h"

using namespace std;

/* BFS */
vector<int> BFS(int v, UGraph g) {
	/* Breadth-First-Search algorithm 
		Input: v (int) - the root vertex
			   g (UGraph) - the undirected graph. 
		Output: result (vector<pair<int, int>>) - a vector of vertices corresponding to the component. */
	vector<int> result;
	std::queue<int> Q;

	//Info for every vertex.
	struct info {
		int distance;
		int parent;
	};
	vector<info> bsinfo;

	//Initialize the info. 
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		bsinfo.push_back(info());
		bsinfo[i].distance = NULL;
		bsinfo[i].parent = NULL;
	}

	//Set the root distance to 0.
	bsinfo[v].distance = 0;
	//Add the root to the queue.
	Q.push(v);

	while (!Q.empty()) {
		//Keep extracting vertices from the queue.
		int w = Q.front();
		Q.pop();
		//Loop through adiacent vertices.
		for (int n : g.getNeighbors(w)) {
			if (bsinfo[n].distance == NULL && n != v) {
				//Set the distance and parent accordingly.
				bsinfo[n].distance = bsinfo[w].distance + 1;
				bsinfo[n].parent = w;
				Q.push(n);
			}
		}
		result.push_back(w);
	}
	return result;
}

/* Connected components */
vector<vector<pair<int,int>>> conComp(UGraph g) {
	/* Finding the connected componentes based upon the BFS results. 
		Input: g (UGraph) - the undirected graph. 
		Output: result (vector<vector<pair<int,int>>>) - connected components. */
	vector<vector<pair<int, int>>> result;
	set<int> vertices;
	vector<int> bfs;
	vector<int> visited;
	int total_visited = 0, current_root, comp_nr = 0;

	//Initialize visited vector
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	//Get the first vertex that was not visited
	while (total_visited < g.getNoOfVertices()) {
		for (int i = 0; i < visited.size(); ++i) {
			if (visited[i] == 0) {
				current_root = i;
				break;
			}
		}
		//Get vertices from edges returned by BFS.
		bfs = BFS(current_root, g);
		for (auto b : bfs) {
			vertices.insert(b);
		}
		//Mark the vertices from this component as visited.
		for (auto v : vertices) {
			visited[v] = 1;
			total_visited += 1;
		}
		result.push_back(vector<pair<int,int>>());
		//If there is only one vertex then make a pair of itself. 
		if (bfs.size() == 1) {
			result[comp_nr].push_back(make_pair(bfs[0], bfs[0]));
		}
		//Add all the possible edges to the result.
		for (auto v1: vertices) {
			for (auto v2: vertices) {
				if (v1 < v2) {
					if (g.isEdge(v1, v2)) {
						result[comp_nr].push_back(make_pair(v1, v2));
					}
				}
			}
		}
		comp_nr++;
		vertices.clear();
	}
	return result;
}

/* ------- UI -------- */
UGraph initialize() {
	/*	Initialize the costless graph.
			Output: (UGraph) - the initialized graph. */
	ifstream f;
	int n, m, i;
	int a, b;
	string file;

	file = "ugraph.txt";
	f.open(file);
	f >> n;
	f >> m;
	UGraph g = UGraph{ n };

	for (i = 0; i<m; i++) {
		f >> a >> b;
		g.addEdge(a, b);
	}
	return g;
}

void run() {
	/* Running the connected components finder. 
	We perform BFSs on every non-visited vertex and get its component. */

	UGraph g = initialize();
	vector<int> visited;
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	//vector<pair<int,int>> bfs;
	//bfs = BFS(0, g);
	////print BFS
	//for (auto b : bfs) {
	//	if (b.first == b.second) {
	//		cout << b.first << "\n";
	//	}
	//	else {
	//		cout << b.first << " -> " << b.second << "\n";
	//	}
	//}
	//cout << "-------\n";

	vector<vector<pair<int,int>>> comp = conComp(g);
	//Print connected components
	for (int i = 0; i < comp.size(); ++i) {
		cout << "-- " << i+1 << " --" << "\n";
		for (int j = 0; j < comp[i].size(); ++j) {
			if (comp[i][j].first == comp[i][j].second) {
				cout << comp[i][j].first << "\n";
			}
			else {
				cout << comp[i][j].first << " -> " << comp[i][j].second << "\n";
			}
		}
	}
	cout << "\n";
}

int main() {
	/* The main program. */

	run();
	system("pause");
	return 0;
}