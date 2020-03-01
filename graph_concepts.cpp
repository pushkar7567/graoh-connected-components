// A template for the Graph Concepts Exercise in C++.

#include <iostream>
using namespace std;
#include "digraph.h"
#include <queue>
#include <fstream>
#include <string>


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


int count_components(Digraph* g) {
	vector<int> allVertices = g->vertices();
	unordered_set<int> allVerticesSet;

	int elementCounter = 0;
	int counter = 0;
	
	while (allVertices.size() > allVerticesSet.size()){
		
		if (allVerticesSet.find(allVertices[elementCounter]) == allVerticesSet.end()){
			unordered_map<int, int> searchTree = breadthFirstSearch(*g, allVertices[elementCounter]);
			unordered_map<int, int>::iterator it = searchTree.begin();

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


Digraph* read_city_graph_undirected(char filename[]) {
	Digraph edmontonGraph;
	int k;
	int l;
	int m;

	ifstream fin;
	fin.open(filename);
	string line;
	string ID;
	string startEdge;
	string stopEdge;
	while (fin) {
		getline(fin, line);
		size_t foundV = line.find("V,");
		size_t foundE = line.find("E,");
		if (foundV != string::npos){
			ID = line.substr(2, line.size()-3);
			int pos =  ID.find(",");
			ID =  ID.substr(0, pos);
			k = stoi(ID);
			edmontonGraph.addVertex(k);
		}			

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


	read_city_graph_undirected(argv[1]);


    return 0;
}