#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

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
	vector<vector<pair<int,int>>> result;
	vector<int> visited;
	vector<pair<int,int>> bfs;
	vector<int> vertices;
	int x = 0;
	int n = 1;
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	while (n < g.getNoOfVertices()) {
		for (unsigned i = 0; i < visited.size(); ++i) {
			if (visited[i] != 1) {
				x = i;
				break;
			}
		}
		//visited show
		/*for (auto v : visited) {
			cout << v << " ";
		}*/
		//cout << "\n";
		//cout << "x = " << x << "\n";
		bfs = BFS(x, g);
		if (bfs.size() == 1) {
			n++;
		}
		//cout << "bfs size " << bfs.size() << "\n";
		vertices.push_back(x);
		
		//cout << "\n";
		visited[x] = 1;
		for (auto e : bfs) {
			if (find(vertices.begin(), vertices.end(), e.first) == vertices.end() && e.first != x) {
				vertices.push_back(e.first);
			}
			if (find(vertices.begin(), vertices.end(), e.second) == vertices.end() != e.second != x) {
				vertices.push_back(e.second);
			}
		}
		//cout << "bfs size " << bfs.size() << "\n";
		/*cout << "vertices[" << 0 << "] = " << vertices[0] << "\n";*/

		//cout << n << " ";
		for (unsigned c = 1; c <= bfs.size(); ++c) {
			//cout << "vertices[" << c << "] = " << vertices[c] << "\n";
			visited[vertices[c]] = 1;
			n++;
			//cout << "n = "<< n << "\n";
			//cout << "c = " << c << "\n";
		}
		//cout << "=======================\n";
		/*for (auto v : vertices) {
			cout << v << " ";
		}*/
		while (!vertices.empty()) {
			vertices.pop_back();
		}
		result.push_back(bfs);

	}
	//cout << "\n\n";
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
	vector<pair<int,int>> bfs;
	//bfs = BFS(4, g);
	vector<vector<pair<int,int>>> comp = conComp(g);
	for (int i = 0; i < comp.size(); ++i) {
		cout << "--" << i << "--" << "\n";
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

	/*cout << "\n";
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		vector<int> neigh = g.getNeighbors(i);
		if (neigh.size()) {
			for (int j = 0; j < neigh.size(); ++j) {
				cout << i << " -> " << neigh[j] << "\n";
			}
			cout << "-------\n";
		}
	}*/
}

int main() {

	run();
	system("pause");
	return 0;
}