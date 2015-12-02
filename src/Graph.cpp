#include <vector>
#include <string>
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
				//FIXME why 4?
				succ.reserve(4*Nnodes);
				weights.reserve(4*Nnodes);
				flyers.reserve(4*Nnodes);
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

vector<int> Graph::getSuccessors(int node) {
	vector<int> v;
	int counter, bound = head.at(node - 1) + getCount(node);
	for(counter = head.at(node - 1) - 1; counter < bound - 1; counter++)
		v.push_back(succ.at(counter));
	return v;
}

// --- GETTERS
int Graph::getNteams(){ return Nteams; }
const std::vector<int>& Graph::getWeights(){ return weights; }
const std::vector<int>& Graph::getFlyers(){ return flyers; }
