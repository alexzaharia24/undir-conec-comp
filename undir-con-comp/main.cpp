#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/* ====== UGraph ======*/
class UGraph {
private:
	unordered_map<int, vector<int>> neighbors;

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
	vector<int> getNeighbors(int x);
	/*	Gets the list of neighbors of x.
			Input: x (int) - the vertix we get the neighbors list for
			Output: (vector<int>) - the neighbors list for 'x' */

	/* ADD */
	void addEdge(int x, int y);
	/*	Add an edge between two vertixes.
			Input:	x (int) - the start vertix
					y (int) - the end vertix */
	bool isEdge(int x, int y);
	/*	Verify if there exists an edge between 'x' and 'y'
			Input:	x (int) - the start vertix
					y (int) - the end vertix
			Output:	true (bool) - if there exists and edge btw 'x' and 'y'
					false (bool - otherwise) */

	/* ITERATORS */
	vector<int>::iterator iteratorBegin(int x);
	/*	Get an iterator to the begining of the neighbors list of 'x'.
			Input: x (int) - the vertix we work with
			Output: (vector<int>::iterator) - iterator to the begining
											of the neighbors list of 'x' */
	vector<int>::iterator iteratorEnd(int x);
	/*	Get an iterator to the end of the neighbors list of 'x'.
			Input: x (int) - the vertix we work with
			Output: (vector<int>::iterator) - iterator to the end
											of the neighbors list of 'x' */
};

/* CONSTRUCTORS [UGraph] */
UGraph::UGraph(int n) {
	int i;
	for (i = 0; i<n; i++) {
		this->neighbors[i] = vector<int>();
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
vector<int> UGraph::getNeighbors(int x) {
	return this->neighbors[x];
}

/* ADD [UGraph] */
void UGraph::addEdge(int x, int y) {
	if (isEdge(x, y)) return;
	if (x > this->getNoOfVertices() || y > this->getNoOfVertices()) {
		return;
	}
	if (x != y) {
		this->neighbors[y].push_back(x);
		this->neighbors[x].push_back(y);
	}
}
bool UGraph::isEdge(int x, int y) {
	if (find(this->neighbors[y].begin(), this->neighbors[y].end(), x) != this->neighbors[y].end()) {
		return 1;
	}
	return 0;
}

/* ITERATORS [UGraph] */
vector<int>::iterator UGraph::iteratorBegin(int x) {
	return this->neighbors[x].begin();
}
vector<int>::iterator UGraph::iteratorEnd(int x) {
	return this->neighbors[x].end();
}

/* ====== UGraphCost ======*/
class UGraphCost : public UGraph {
private:
	map<pair<int, int>, int> costs; //the cost
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
	int getCost(pair<int, int> edge);
	/*	Get the cost of an edge.
			Input: edge (pair<int, int>) - the edge represented as a pair of vertices
			Output: (int) - the cost of the edge. */
	map<pair<int, int>, int> getCosts();
	/*	Get the list of costs.
			Output: (map<pair<int, int>, int>)	- the list of costs represented as a mapping
												of pairs of ints to some ints. */

	/* SETTERS */
	void setCost(pair<int, int> edge, int cost);
	/*	Set the cost of an edge.
			Input:	edge (pair<int, int>) - the edge represented by a pair of ints
					cost (int) - the new cost of the edge. */

	/* OPERATIONS */
	void addEdge(int x, int y, int z);
	/*	Add an edge between 'x' and 'y' with the cost 'z'.
			Input:	x (int) - the start vertix
					y (int) - the end vertix
					z (int) - the cost. */
};

/* CONSTRUCTORS [UGraphCost] */
UGraphCost::UGraphCost(int n) : UGraph(n) {
}
UGraphCost::UGraphCost(const UGraphCost& g) : UGraph(g) {
	this->costs = g.costs;
}
/* DESTRUCTOR [UGraphCost] */
UGraphCost::~UGraphCost() {}

/* GETTERS */
int UGraphCost::getCost(pair<int, int> edge) {
	return this->costs[edge];
}
map<pair<int, int>, int> UGraphCost::getCosts() {
	return this->costs;
}

/* SETTERS [UGraphCost] */
void UGraphCost::setCost(pair<int, int> edge, int cost) {
	this->costs[edge] = cost;
}

/* OPERATIONS [UGraphCost] */
void UGraphCost::addEdge(int x, int y, int z) {
	UGraph::addEdge(x, y);
	this->costs[make_pair(x, y)] = z;
}

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

/* Connected components */
vector<vector<int>> conComp(UGraph g) {
	vector<vector<int>> result;
	/*vector<int> vertices;
	vector<int> remaining;
	int n = g.getNoOfVertices(), m;
	for (int i = 0; i < n; ++i) {
		vertices.push_back(i);
	}
	while (n) {
		result.push_back(DFS_it(vertices[0], g));
		m = result.size();
		for (unsigned i = 0; i < result[m - 1].size(); ++i) {
			
		}
	}
	return result;*/
	vector<int> visited;
	vector<int> dfs;
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
		dfs = DFS_it(x, g);
		for (unsigned i = 0; i < dfs.size(); ++i) {
			visited[dfs[i]] = 1;
			n++;
		}
		result.push_back(dfs);

	}
	return result;
}

/* ------- UI -------- */
void readEdgeG(UGraph &g) {
	/*	Read an edge from the user and add it to the graph.
	Input: g (UGraph&) - the graph we will add the edge to. */
	int a, b;
	cout << "v-v \n";
	cin >> a >> b;
	g.addEdge(a, b);
}

void readEdgeGC(UGraph &g) {
	/*	Read an edge from the user and add it to the graph.
			Input: g (UGraph&) - the graph we will add the edge to. */
	int a, b, c;
	cout << "v-v-c \n";
	cin >> a >> b >> c;
	g.addEdge(a, b);
}

int chooseGraph() {
	/*	Choose a costless or a cost graph.
			Output: 1 - for costless graphs
					2 - for cost graphs*/
	string cmd;
	while (1) {
		cout << "Choose the graph type: \n";
		cout << "[1] Graph without costs. \n";
		cout << "[2] Graph with costs. \n";
		cin >> cmd;
		if (cmd == "1") return 1;
		else if (cmd == "2") return 2;
		else {
			cout << "Wrong graph type. \n";
			cout << "Enter 1 or 2 \n";
		}
	}

}

UGraph initializeG() {
	/*	Initialize the costless graph.
			Output: (UGraph) - the initialized graph. */
	ifstream f;
	int n, m, i;
	int a, b;
	string file;

	file = "ugraph_costless.txt";
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

UGraphCost initializeGC() {
	/*	Initialize the cost graph.
			Output: (UGraph) - the initialized graph. */
	ifstream f;
	int n, m, i;
	int a, b, c;
	string file;

	file = "ugraph_cost.txt";
	f.open(file);
	f >> n;
	f >> m;

	UGraphCost g = UGraphCost{ n };

	for (i = 0; i<m; i++) {
		f >> a >> b >> c;
		g.addEdge(a, b, c);
	}
	return g;
}

void menuCommandsG() {
	/* Commands for the costless graph menu. */
	cout << "+---------------+ \n";
	cout << "| Menu commands | \n";
	cout << "+---------------+ \n";
	cout << " add - add edge \n";
	cout << " deg - get degree \n";
	cout << " nov - no. of vertices \n";
	cout << " noe - no. of edges \n";
	cout << " ise - is edge? \n";
	cout << " x  - exit \n";
}
void menuCommandsGC() {
	/* Commands for the cost graph menu. */
	cout << "+---------------+ \n";
	cout << "| Menu commands | \n";
	cout << "+---------------+ \n";
	cout << " add - add edge \n";
	cout << " deg - get degree \n";
	cout << " nov - no. of vertices \n";
	cout << " noe - no. of edges \n";
	cout << " ise - is edge? \n";
	cout << " gco - get the cost of an edge\n";
	cout << " sco - set the cost of an endge\n";
	cout << " x  - exit \n";
}

int executeCommandG(string cmd, UGraph& g) {
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
	else if (cmd.compare("add") == 0) {
		cout << ">> Add edge \n";
		readEdgeG(g);
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("deg") == 0) {
		int x;
		cout << ">> Get degree \n";
		cout << "v = ";
		cin >> x;
		cout << "degree(" << x << ") = " << g.getDegree(x);
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("nov") == 0) {
		cout << ">> No. of vertices \n";
		cout << g.getNoOfVertices() << "\n";
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("noe") == 0) {
		cout << ">> No. of edges \n";
		cout << g.getNoOfEdges() << "\n";
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("ise") == 0) {
		int v1, v2, ok;
		cout << ">> Is edge? \n";
		cout << "v1 = ";
		cin >> v1;
		cout << "v2 = ";
		cin >> v2;
		ok = g.isEdge(v1, v2);
		if (ok == 0) {
			cout << "(" << v1 << ", " << v2 << ") is not an edge. \n";
		}
		else {
			cout << "(" << v1 << ", " << v2 << ") is an edge. \n";
		}
		cout << "\n";
		return 0;
	}
	else {
		cout << "> Wrong command. \n";
		cout << "\n";
		return 0;
	}
}
int executeCommandGC(string cmd, UGraphCost& g) {
	/*	Execute the given command on the given cost graph.
			Input:	cmd (string) - the command
					g (UGraph&) - the cost graph.
			Output: 1 - for command 'x'
					0 - otherwise. */
	if (cmd.compare("x") == 0) {
		cout << ">> Exit \n";
		cout << "\n";
		return 1;
	}
	else if (cmd.compare("add") == 0) {
		cout << ">> Add edge \n";
		readEdgeGC(g);
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("deg") == 0) {
		int x;
		cout << ">> Get degree \n";
		cout << "v = ";
		cin >> x;
		cout << "degree(" << x << ") = " << g.getDegree(x);
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("nov") == 0) {
		cout << ">> No. of vertices \n";
		cout << g.getNoOfVertices() << "\n";
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("noe") == 0) {
		cout << ">> No. of edges \n";
		cout << g.getNoOfEdges() << "\n";
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("ise") == 0) {
		int v1, v2, ok;
		cout << ">> Is edge? \n";
		cout << "v1 = ";
		cin >> v1;
		cout << "v2 = ";
		cin >> v2;
		ok = g.isEdge(v1, v2);
		if (ok == 0) {
			cout << "(" << v1 << ", " << v2 << ") is not an edge. \n";
		}
		else {
			cout << "(" << v1 << ", " << v2 << ") is an edge. \n";
		}
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("gco") == 0) {
		int v1, v2, cost, ise;
		cout << ">> Get cost \n";
		cout << "v1 = ";
		cin >> v1;
		cout << "v2 = ";
		cin >> v2;

		ise = g.isEdge(v1, v2);

		if (ise == 0) {
			cout << "No edge from " << v1 << " to " << v2 << "\n";
		}
		else {
			cost = g.getCost(make_pair(v1, v2));
			cout << "cost(" << v1 << ", " << v2 << ") = " << cost << "\n";
		}
		cout << "\n";
		return 0;
	}
	else if (cmd.compare("sco") == 0) {
		int v1, v2, cost, ise;
		cout << ">> Set cost \n";
		cout << "v1 = ";
		cin >> v1;
		cout << "v2 = ";
		cin >> v2;

		ise = g.isEdge(v1, v2);
		if (ise == 0) {
			cout << "No edge from " << v1 << " to " << v2 << "\n";
		}
		else {
			cout << "cost = ";
			cin >> cost;
			g.setCost(make_pair(v1, v2), cost);
		}
		cout << "\n";
		return 0;
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
	UGraph g;
	UGraphCost gc;

	cout << ">> Initialize graph\n";
	gtype = chooseGraph();
	if (gtype == 1) {
		UGraph g = initializeG();
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
		cout << "---------\n";

		vector<vector<int>> con =  conComp(g);
		for (unsigned i = 0; i < con.size(); ++i) {
			for (unsigned j = 0; j < con[i].size(); ++j) {
				cout << con[i][j] << " ";
			}
			cout << endl;
		}

		menuCommandsG();
		do {
			cout << "Enter command: \n> ";
			cin >> cmd;
		} while (!executeCommandG(cmd, g));
	}
	else if (gtype == 2) {
		UGraphCost gc = initializeGC();
		menuCommandsGC();
		do {
			cout << "Enter command: \n> ";
			cin >> cmd;
		} while (!executeCommandGC(cmd, gc));
	}

}

int main() {
	mainMenu();

	return 0;
}