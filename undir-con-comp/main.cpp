#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

#include "UGraphCost.h"

using namespace std;

/* BFS */
vector<pair<int,int>> BFS(int v, UGraph g) {
	/* v = root */
	vector<pair<int, int>> result;
	std::queue<int> Q;
	struct info {
		int distance;
		int parent;
	};
	vector<info> bsinfo;

	if (g.getDegree(v) == 0) {
		result.push_back(make_pair(v, v));
		return result;
	}

	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		bsinfo.push_back(info());
		bsinfo[i].distance = NULL;
		bsinfo[i].parent = NULL;
	}
	bsinfo[v].distance = 0;
	Q.push(v);
	while (!Q.empty()) {
		int w = Q.front();
		Q.pop();
		for (int n : g.getNeighbors(w)) {
			if (bsinfo[n].distance == NULL && n != v) {
				bsinfo[n].distance = bsinfo[w].distance + 1;
				bsinfo[n].parent = w;
				Q.push(n);
				result.push_back(make_pair(w, n));
			}
		}
	}
	return result;
}

/* Connected components */
vector<vector<pair<int,int>>> conComp(UGraph g) {
	vector<vector<pair<int, int>>> result;
	set<int> vertices;
	vector<pair<int, int>> bfs;
	vector<int> visited;
	int n = 0, x;

	//Initialize visited vector
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	
	while (n < g.getNoOfVertices()) {
		//Get the first vertex that was not visited
		for (int i = 0; i < visited.size(); ++i) {
			if (visited[i] == 0) {
				x = i;
				break;
			}
		}
		
		bfs = BFS(x, g);
		//Get vertices from edges returned by BFS
		for (auto b : bfs) {
			vertices.insert(b.first);
			vertices.insert(b.second);
		}
		/*for (auto v : vertices) {
			cout << v << " ";
		}
*/
		for (auto v : vertices) {
			/*if (visited[v] == 0) {
				visited[v] = 1;
				n += 1;
			}*/
			visited[v] = 1;
			n += 1;
		}

		/*for (auto v1: vertices) {
			for (auto v2: vertices) {
				if (v1 < v2) {
					if (g.isEdge(v1, v2)) {
						cout << v1<< " >>> " << v2 << "\n";
					}
				}
				
			}
		}*/

		result.push_back(bfs);
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

void menuCommands() {
	/* Commands for the costless graph menu. */
	cout << "+---------------+ \n";
	cout << "| Menu commands | \n";
	cout << "+---------------+ \n";
}

int executeCommand(string cmd, UGraph& g) {
	/*	Execute the given command on the given costless graph.
			Input:	cmd (string) - the command
					g (UGraph&) - the costless graph.
			Output: 1 - for command 'x'
					0 - otherwise. */
	if (cmd.compare("x") == 0) {
		cout << ">> Exit \n";
		cout << "\n";
		return 1;
	}
	else {
		cout << "> Wrong command. \n";
		cout << "\n";
		return 0;
	}
}

void run() {
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

	run();
	system("pause");
	return 0;
}