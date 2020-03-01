// A template for the Graph Concepts Exercise in C++.
// Including all the required libraries and files
#include <iostream>
using namespace std;
#include "digraph.h"
#include <queue>
#include <fstream>
#include <string>

// Declaring all the digraph class functions
// All digraph functions were taken from digraph.cpp file
void Digraph::addVertex(int v) {
  // If it already exists, does nothing.
  // Otherwise, adds v with an empty adjacency set.
  nbrs[v];
}

void Digraph::addEdge(int u, int v) {
  addVertex(v);
  nbrs[u].insert(v); // will also add u to nbrs if it was not there already
}


bool Digraph::isVertex(int v) {
  return nbrs.find(v) != nbrs.end();
}

bool Digraph::isEdge(int u, int v) {
  // check that u is in the keys and that it's associated set contains v
  return nbrs.find(u) != nbrs.end() && nbrs[u].find(v) != nbrs[u].end();
}

unordered_set<int>::const_iterator Digraph::neighbours(int v) const {
  // this will crash the program if v is not a vertex
  return nbrs.find(v)->second.begin();
}

unordered_set<int>::const_iterator Digraph::endIterator(int v) const {
  // this will crash the program if v is not a vertex
  return nbrs.find(v)->second.end();
}

int Digraph::numNeighbours(int v) {
  // this will crash the program if v is not a vertex
  return nbrs.find(v)->second.size();
}

int Digraph::size() {
  return nbrs.size();
}

vector<int> Digraph::vertices() {
  vector<int> v;
  for (unordered_map<int, unordered_set<int>>::const_iterator it = nbrs.begin();
    it != nbrs.end(); it++) {
      v.push_back(it->first);
    }
  return v;
}

bool Digraph::isWalk(vector<int> walk) {
  if (walk.size() == 0)
    return false;
  if (walk.size() == 1)
    return isVertex(walk[0]);
  for (vector<int>::size_type i=0; i<walk.size()-1; i++)
    if (!isEdge(walk[i], walk[i+1]))
      return false;

  return true;
}

bool Digraph::isPath(vector<int> path) {
  set<int> s(path.begin(), path.end());
  if (s.size() < path.size())
    return false;

  return isWalk(path);
}

// Implementation of breadth first search
// Implementation from breathFirstSearch.cpp file
unordered_map<int, int> breadthFirstSearch(const Digraph& graph, int startVertex) {
  unordered_map<int, int> searchTree; // map each vertex to its predecessor

  searchTree[startVertex] = -1;

  queue<int> q;
  q.push(startVertex);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++) {
      if (searchTree.find(*iter) == searchTree.end()) {
        searchTree[*iter] = v;
        q.push(*iter);
      }
    }
  }

  return searchTree;
}

// required function to implement which determines the number of connected components
int count_components(Digraph* g) {
	// Vector of all the present vertices
	vector<int> allVertices = g->vertices();

	// Initializing an empty unordered set to store the connected components
	unordered_set<int> allVerticesSet;

	// elementCounter keeps track of the index of vertex
	// counter keeps track of the number of seperate trees
	int elementCounter = 0;
	int counter = 0;
	
	while (allVertices.size() > allVerticesSet.size()){
		// the if statement checks weather the the given vertex is already in the unordered set
		if (allVerticesSet.find(allVertices[elementCounter]) == allVerticesSet.end()){
			unordered_map<int, int> searchTree = breadthFirstSearch(*g, allVertices[elementCounter]);
			unordered_map<int, int>::iterator it = searchTree.begin();
			// inserts all the connected vertices if they are not present
			while (it != searchTree.end()) {
				allVerticesSet.insert(it->first);
				it++;
			}
			counter++;
		}
		elementCounter++;
	}
    return counter;
}

// required function to implement takes file as input and finds the connected components
Digraph* read_city_graph_undirected(char filename[]) {
	// initializing an empty instance of Digraph class which stores all the vertices and edges
	Digraph edmontonGraph;
	int k;
	int l;
	int m;

	// following block opens the file and starts to read the content
	ifstream fin;
	fin.open(filename);
	string line;
	string ID;
	string startEdge;
	string stopEdge;
	
	// the while loop checks whether it is the EOF
	while (fin) {
		getline(fin, line);
		size_t foundV = line.find("V,");
		size_t foundE = line.find("E,");

		// if V is found then store it's ID as a vertex in edmontonGraph
		if (foundV != string::npos){
			ID = line.substr(2, line.size()-3);
			int pos =  ID.find(",");
			ID =  ID.substr(0, pos);
			k = stoi(ID);
			edmontonGraph.addVertex(k);
		}			

		// else if E is found, store the given two values as the connection between two vertices
		else if (foundE != string::npos){
			startEdge = line.substr(2, line.size()-3);
			int posStart = startEdge.find(",");
			startEdge = startEdge.substr(0, posStart);
			stopEdge = line.substr(posStart+3, line.size()-posStart-2);
			int posStop = stopEdge.find(",");
			stopEdge = stopEdge.substr(0, posStop);
			l = stoi(startEdge);
			m = stoi(stopEdge);
			edmontonGraph.addEdge(l, m);
		}
	}

	fin.close();
	cout << count_components(&edmontonGraph) << endl;
}


int main(int argc, char *argv[]) {
	// Take the second argument in the terminal as the name of the file
	read_city_graph_undirected(argv[1]);

    return 0;
}