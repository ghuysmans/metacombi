#include<sstream>
#include<fstream>
#include "Graph.h"

using namespace std;

Graph::Graph(std::string name) {
	filename = name;
	ifstream infile;
	infile.open(filename.c_str());
	if (infile.is_open()) {
		int counter, tmp, linenumber = 1;
		std::vector<int>* dest[] = {&head, &x, &y, &succ, &weights, &flyers};
		string line;
		while (getline(infile, line)) {
			istringstream iss(line);
			if (linenumber == 1) {
				iss>>Nedges>>Nnodes>>Nteams;
				head.reserve(Nnodes);
				x.reserve(Nnodes);
				y.reserve(Nnodes);
				succ.reserve(Nedges);
				weights.reserve(Nedges);
				flyers.reserve(Nedges);
			}
			else {
				int i=linenumber-2, N=linenumber>=5?Nedges:Nnodes;
				if (i < sizeof(dest)) {
					for(counter=0; counter<N; counter++) {
						iss >> tmp;
						dest[i]->push_back(tmp);
					}
				}
				else
					break;
			}
			linenumber++;
		}
		infile.close();
		if (linenumber != 8)
			//TODO maybe use a custom class...
			throw GraphException("invalid input graph");
	}
	else
		throw GraphException("couldn't open the input graph");
}

int Graph::getFirst(int node) {
	int s = head.at(node - 1);
	return succ.at(s - 1);
}

int Graph::getCount(int node) {
	if(node == Nnodes)
		return succ.size() - head.at(node - 1) + 1;
	return head.at(node) - head.at(node - 1);
}

vector<int> Graph::getSuccessors() {
	return succ;
}

std::vector<int> Graph::edgeToNodes(int edge){
	std::vector<int> result = std::vector<int>(2, -1);
	//the successor
	result[1] = succ[edge];
	//the predecessor
	edge++;
	result[0] = -1;
	int browsed = 0;//num of browsed edges
	for(int i=0 ; i<Nnodes ; i++){
		browsed += getCount(i);
		if(browsed <= edge){
			result[0] = i;
			break;
		}
	}
	return result;
}

int Graph::getDistanceNodes(int node1, int node2){
	//TODO jason
}

int Graph::getDistanceEdges(int edge1, int edge2){
	std::vector<int> e1 = edgeToNodes(edge1);
	std::vector<int> e2 = edgeToNodes(edge2);
	int dist = -1;
	int minimum = getDistanceNodes(e1[0], e2[0]);
	dist = getDistanceNodes(e1[1], e2[0]);
	if( dist < minimum ) minimum = dist;
	dist = getDistanceNodes(e1[0], e2[1]);
	if( dist < minimum ) minimum = dist;
	dist = getDistanceNodes(e1[1], e2[1]);
	if( dist < minimum ) minimum = dist;
	return dist;
}

// --- GETTERS
int Graph::getNteams(){ return Nteams; }
int Graph::getNedges(){ return Nedges; }
int Graph::getNnodes(){ return Nnodes; }
const std::vector<int>& Graph::getWeights(){ return weights; }
const std::vector<int>& Graph::getFlyers(){ return flyers; }
