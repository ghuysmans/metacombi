#include<sstream>
#include<fstream>
#include "Graph.h"
#include<iostream>
#include<climits>

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
		if (linenumber != 8){
			//TODO maybe use a custom class...
			cout << "Graph: linenumber!=8" << endl;
			throw GraphException("invalid input graph");
		}
	}
	else{
		cout << "Graph: couldn't open file" << endl;
		throw GraphException("couldn't open the input graph");
	}
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
vector<int> Graph::getSuccessors(int node){
	int count = getCount(node);
	vector<int> result = vector<int>(count , -1);
	for(int i=0 ; i<count ; i++){
		result[i] = succ.at( head.at(i) +i );
	}
	return result;
}

int Graph::getWeight(int node, int successor){
	int numSuccessor = getCount( node );
	int indexEdge;
	for(int i=0 ; i<numSuccessor ; i++){
		indexEdge = head.at(node) + i -1;
		if( succ.at(indexEdge) == (successor +1)){
			return weights.at( indexEdge );
		}
	}
	cout << "Graph: edge <" << node << " , " << successor << "> doesn't exist" << endl;
	throw GraphException("edge doesn't exist");
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

std::vector<int> Graph::getDistanceNodes(int start, int end1, int end2){
	const unsigned long int INFINITE = ULONG_MAX;
	std::vector<unsigned long int> tickets = std::vector<unsigned long int>(Nnodes , INFINITE);
	//std::vector<int> bestPredecessor = std::vector<int>(Nnodes , 0); If you want the path
	std::vector<bool> done = std::vector<bool>(Nnodes , false);
	tickets[start] = 0;
	//bestPredecessor[start] = start; If you want the path
	int tMinimal; //x in slides
	unsigned long int valuetMinimal = INFINITE; //VMin in slides
	do{
		valuetMinimal = INFINITE;
		for (int i=0 ; i<tickets.size() ; i++){//search the minimal ticket
    		if( tickets[i]<valuetMinimal && tickets[i] != -1){
    			valuetMinimal = tickets[i];
    			tMinimal = i;
    		}
		}

		if(valuetMinimal < INFINITE){
			done[tMinimal] = true;
			std::vector<int> successors = getSuccessors(tMinimal);
			for(int i=0 ; i<successors.size() ; i++){
				int ticketPlusW = tickets[tMinimal] + getWeight(tMinimal,i);
				if(ticketPlusW < tickets[i]){
					tickets[i] = ticketPlusW;
					//bestPredecessor[i] = tMinimal; If you want the path
				}
			}
		}
	}while(valuetMinimal == INFINITE);
	std::vector<int> result = std::vector<int>(2,0);
	result[0] = (int)(tickets[end1]);
	result[1] = (int)(tickets[end2]);
	return result;
}

int Graph::getDistanceEdges(int edge1, int edge2){
	std::vector<int> e1 = edgeToNodes(edge1);
	std::vector<int> e2 = edgeToNodes(edge2);
	int dist = -1;
	std::vector<int> dists = getDistanceNodes(e1[0], e2[0], e2[1]);
	int minimum = dists[0];
	if( dists[1] < minimum ) minimum = dists[1];
	dists = getDistanceNodes(e1[1], e2[0], e2[1]);
	if( dists[0] < minimum ) minimum = dists[0];
	if( dists[1] < minimum ) minimum = dists[1];
	return minimum;
}

// --- GETTERS
int Graph::getNteams(){ return Nteams; }
int Graph::getNedges(){ return Nedges; }
int Graph::getNnodes(){ return Nnodes; }
const std::vector<int>& Graph::getWeights(){ return weights; }
const std::vector<int>& Graph::getFlyers(){ return flyers; }
