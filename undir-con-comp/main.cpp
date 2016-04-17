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



/* DFS - iterative */
vector<int> DFS_it(int v, UGraph g) {
	vector<int> visited;
	vector<int> result;
	stack<int> s;
	for (int i = 0; i < g.getNoOfVertices(); i++) {
		visited.push_back(0);
	}
	s.push(v);
	while (!s.empty()) {
		v = s.top();
		s.pop();
		if (visited[v] == 0) {
			result.push_back(v);
			visited[v] = 1;
			for (int w : g.getNeighbors(v)) {
				s.push(w);
			}
		}
	}
	return result;
}


/* DFS - recursive */
vector<int> DFS_rec(int v, UGraph g, vector<int> visited) {
	vector<int> result;
	visited[v] = 1;
	result.push_back(v);
	for (int w : g.getNeighbors(v)) {
		if (visited[w] == 0) {
			DFS_rec(w, g, visited);
		}
	}
	return result;
}

/* BFS */
vector<int> BFS(int v, UGraph g) {
	/* v = root */
	vector<int> result;
	std::queue<int> Q;
	struct info {
		int distance;
		int parent;
	};
	vector<info> bsinfo;

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
			}
		}
		result.push_back(w);
	}
	return result;
}

/* Connected components */
vector<vector<int>> conComp(UGraph g) {
	vector<vector<int>> result;
	vector<int> visited;
	vector<int> bfs;
	int x = 0;
	int n = 0;
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	while (n != g.getNoOfVertices()) {
		for (unsigned i = 0; i < visited.size(); ++i) {
			if (visited[i] != 1) {
				x = i;
				break;
			}
		}
		bfs = BFS(x, g);
		for (unsigned i = 0; i < bfs.size(); ++i) {
			visited[bfs[i]] = 1;
			n++;
		}
		result.push_back(bfs);

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


void mainMenu() {
	/* The main menu. Here we put all the other menus together. */
	string cmd;
	int gtype;
	UGraph g = initialize();

	vector<int> visited;
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	//vector<int> dfs = DFS_rec(0, g, visited);
	vector<int> dfs = DFS_it(6, g);
	for (vector<int>::iterator it = dfs.begin(); it != dfs.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	/*cout << "----DFS-----\n";

	vector<vector<int>> con =  conComp(g);
	for (unsigned i = 0; i < con.size(); ++i) {
		for (unsigned j = 0; j < con[i].size(); ++j) {
			cout << con[i][j] << " ";
		}
		cout << endl;
	}*/

	menuCommands();
	do {
		cout << "Enter command: \n> ";
		cin >> cmd;
	} while (!executeCommand(cmd, g));
}

void run() {
	UGraph g = initialize();
	vector<int> visited;
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		visited.push_back(0);
	}
	vector<int> bfs;
	//bfs = BFS(0, g);
	vector<vector<int>> comp = conComp(g);
	for (int i = 0; i < comp.size(); ++i) {
		for (int j = 0; j < comp[i].size(); ++j) {
			cout << comp[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "\n";
	for (int i = 0; i < g.getNoOfVertices(); ++i) {
		vector<int> neigh = g.getNeighbors(i);
		if (neigh.size()) {
			for (int j = 0; j < neigh.size(); ++j) {
				cout << i << " -> " << neigh[j] << "\n";
			}
			cout << "-------\n";
		}
	}
}

int main() {

	run();
	system("pause");
	return 0;
}