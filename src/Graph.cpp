#include<sstream>
#include<fstream>
#include "Graph.h"
#include<iostream>
#include<climits>

Graph::Graph(const Graph& g):
	teamsCount(teamsCount),
	filename(filename),
	head(head),
	succ(succ),
	flyers(flyers),
	weights(weights),
	x(x),
	y(y),
	averageDist(averageDist),
	averageFlyers(averageFlyers)
{
	std::cout << "copying " << g.filename << std::endl;
}

Graph::Graph(
		const int teamsCount,
		const std::string filename,
		const std::vector<int> head,
		const std::vector<int> succ,
		const std::vector<int> flyers,
		const std::vector<int> weights,
		const std::vector<int> x,
		const std::vector<int> y,
		const int averageDist,
		const int averageFlyers):
	teamsCount(teamsCount),
	filename(filename),
	head(head),
	succ(succ),
	flyers(flyers),
	weights(weights),
	x(x),
	y(y),
	averageDist(averageDist),
	averageFlyers(averageFlyers)
{
	std::cout << "loaded " << filename << " with " << head.size() << " nodes and " << succ.size() << " edges" << std::endl;
}

void Graph::dump() const {
	dump(false);
}

void Graph::dump(bool showCoords) const {
	for (int a=0; a<head.size(); a++) {
		const int f = head.at(a);
		const int ct = getCount(a);
		std::cout << a;
		if (showCoords && x.size())
			std::cout << "(" << x.at(a) << "," << y.at(a) << ")";
		std::cout << " -> ";
		for (int edge=f; edge<f+ct; edge++) {
			const int b = succ.at(edge);
			std::cout << b;
			if (showCoords && x.size())
				std::cout << "(" << x.at(b) << "," << y.at(b) << ")";
			std::cout << ", ";
		}
		std::cout << std::endl;
	}
}

Graph Graph::load(const std::string& filename) {
	int n_teams, n_succ, n_nodes;
	std::vector<int> head;
	std::vector<int> succ;
	std::vector<int> flyers;
	std::vector<int> weights;
	std::vector<int> x;
	std::vector<int> y;
	std::ifstream infile;
	infile.open(filename.c_str());
	if (infile.is_open()) {
		int counter, linenumber = 1;
		std::vector<int>* dest[] = {&head, &x, &y, &succ, &weights, &flyers};
		std::string line;
		while (getline(infile, line)) {
			std::istringstream iss(line);
			if (linenumber == 1) {
				iss>>n_succ>>n_nodes>>n_teams;
				head.reserve(n_nodes);
				x.reserve(n_nodes);
				y.reserve(n_nodes);
				succ.reserve(n_succ);
				weights.reserve(n_succ);
				flyers.reserve(n_succ);
			}
			else {
				int i=linenumber-2;
				int N=linenumber>=5?n_succ:n_nodes;
				if (i < sizeof(dest)) {
					for(counter=0; counter<N; counter++) {
						int tmp;
						iss >> tmp;
						//decrement indexes in head and succ
						if(linenumber == 2 || linenumber == 5)
							tmp--;
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
			throw GraphException("invalid input graph");
		}
		else{//So loading is complete
			int aDist = 0;
			for(int i=0 ; i<weights.size() ; i++){
				aDist += weights.at(i);
			}
			aDist = aDist/(2*n_teams);//total distance has to be /2 because every edges are browsed 2 times because no-oriented
			int aFlyers = 0;
			for(int i=0 ; i<flyers.size() ; i++){
				aFlyers += flyers.at(i);
			}
			aFlyers = aFlyers/(2*n_teams);
			return Graph(n_teams, filename, head, succ, flyers, weights, x, y, aDist, aFlyers);
		}
	}
	else
		throw GraphException("couldn't open the input graph");
}

std::vector<int> Graph::edgeToNodes(int edge) const {
	if(edge > succ.size()-1){
		std::cout << "Graph: edge " << edge << " doesn't exist because succ.size()=" << succ.size() << std::endl;
		throw GraphException("edge doesn't exist");
	}
	std::vector<int> result = std::vector<int>(2, -1);
	//the successor
	result[1] = succ[edge];
	//the predecessor
	result[0] = -1;
	if(head.size() < 2){
		result[0] = 0;
		return result;
	}
	for(int i=1 ; i<head.size() ; i++){
		if(head.at(i) > edge){
			result[0] = i-1;
			return result;
		}
	}
	result[0] = head.size()-1;
	return result;
}

int Graph::nodesToEdge(int node, int successor) const {
	int count = getCount(node);
	int indexEdge;
	for(int i=0 ; i<count; i++){
		indexEdge = head.at(node) + i;
		if( succ.at(indexEdge) == (successor)){
			return indexEdge;
		}
	}
	std::cout << "Graph: edge <" << node << " , " << successor << "> doesn't exist" << std::endl;
	throw GraphException("edge doesn't exist");
}

std::vector<int> Graph::getDistanceNodes(int start, int end1, int end2) const {
	const unsigned long int INFINITE = ULONG_MAX;
	std::vector<unsigned long int> tickets = std::vector<unsigned long int>(head.size() , INFINITE);
	//std::vector<int> bestPredecessor = std::vector<int>(head.size() , 0); If you want the path
	std::vector<bool> done = std::vector<bool>(head.size() , false);
	tickets[start] = 0;
	//bestPredecessor[start] = start; If you want the path
	int tMinimal; //x in slides
	unsigned long int valuetMinimal = INFINITE; //VMin in slides
	do{
		valuetMinimal = INFINITE;
		for (int i=0 ; i<tickets.size() ; i++){//search the no-fixed minimal ticket
    		if(tickets[i]<valuetMinimal && !done[i]){
    			valuetMinimal = tickets[i];
    			tMinimal = i;
    		}
		}

		if(valuetMinimal < INFINITE){
			done[tMinimal] = true;
			int sup = head.at(tMinimal)+getCount(tMinimal);
			for(int k = head.at(tMinimal) ; k<sup ; k++){
				int ticketPlusW = tickets[tMinimal] + weights.at(k);
				if(ticketPlusW < tickets[succ.at(k)]){
					tickets[succ.at(k)] = ticketPlusW;
					//bestPredecessor[succ.at(k)] = tMinimal; If you want the path
				}
			}
		}
	}while(valuetMinimal < INFINITE);
	std::vector<int> result = std::vector<int>(2,0);
	result[0] = (tickets[end1]<INFINITE ? (int)(tickets[end1]) : -1);
	result[1] = (tickets[end2]<INFINITE ? (int)(tickets[end2]) : -1);
	return result;
}

int Graph::getDistanceEdges(int edge1, int edge2) const {
	std::vector<int> e1 = edgeToNodes(edge1);
	std::vector<int> e2 = edgeToNodes(edge2);
	int dist = -1;
	std::vector<int> dists = getDistanceNodes(e1[0], e2[0], e2[1]);
	//std::cout<<"d("<<e1[0]<<","<<e2[0]<<")="<<dists[0]<<"et d("<<e1[0]<<","<<e2[1]<<")="<<dists[1]<<std::endl;
	int minimum = dists[0];
	if( dists[1] < minimum ) minimum = dists[1];
	dists = getDistanceNodes(e1[1], e2[0], e2[1]);
	//std::cout<<"d("<<e1[1]<<","<<e2[0]<<")="<<dists[0]<<"et d("<<e1[1]<<","<<e2[1]<<")="<<dists[1]<<std::endl;
	if( dists[0] < minimum ) minimum = dists[0];
	if( dists[1] < minimum ) minimum = dists[1];
	return minimum;
}

/**
 * Integer vector with reserved capacity.
 * This avoids using loops to init the vectors created in #subGraphs.
 */
class IV: public std::vector<int> {
	public:
		IV(size_type capacity): std::vector<int>() {
			reserve(capacity);
		}
};

//TODO keepCoords
std::vector<Graph*> Graph::subGraphs(std::vector<int> assignments) const {
	//let's store each output Graph's members since they are const.
	std::vector<IV> res_h = std::vector<IV>(teamsCount, IV(head.size()));
	std::vector<IV> res_w = std::vector<IV>(teamsCount, IV(succ.size()));
	std::vector<IV> res_f = std::vector<IV>(teamsCount, IV(succ.size()));
	std::vector<IV> res_ni = std::vector<IV>(teamsCount, IV(succ.size()));
	std::vector<IV> fakeSucc = std::vector<IV>(teamsCount, IV(succ.size()));
	std::vector<int> sigma(teamsCount);
	//init head vectors
	for(int team=0; team<teamsCount; team++)
		res_h.at(team).push_back(0);
	for(int node=0; node<head.size(); node++) {
		std::vector<int> tmp(teamsCount);
		//store edges
		for(int i=0; i<getCount(node); i++) {
			int edge = head.at(node) + i;
			int team = assignments.at(edge) - 1;
			if (team < 0)
				throw GraphException("incomplete assignment vector");
			fakeSucc.at(team).push_back(succ.at(edge));
			res_w.at(team).push_back(weights.at(edge));
			res_f.at(team).push_back(flyers.at(edge));
			res_ni.at(team).push_back(node);
			tmp.at(team)++;
		}
		//store nodes
		for(int team=0; team<teamsCount; team++) {
			int edges = tmp.at(team);
			if (edges) {
				sigma.at(team) += edges;
				res_h.at(team).push_back(sigma.at(team));
			}
		}
	}
	//we don't need the last head pointer
	for(int team=0; team<teamsCount; team++)
		res_h.at(team).pop_back();
	//TODO comment
	for(int team=0; team<teamsCount; team++) {
		std::vector<int> v;
		IV& ni = res_ni.at(team);
		IV& fs = fakeSucc.at(team);
		for(int i=0; i<ni.size(); i++)
			if(i==0 || v.back()!=ni.at(i))
				v.push_back(ni.at(i));
		for(int i=0; i<v.size(); i++) {
			for(int m = 0; m < fs.size(); m++)
				if(fs.at(m) == v.at(i))
					fs.at(m) = i;
		}
	}
	//populate succ vectors
	std::vector<IV> res_s = std::vector<IV>(teamsCount, IV(succ.size()));
	for(int team=0; team<teamsCount; team++) {
		for(int i=0; i<fakeSucc.at(team).size(); i++)
			res_s.at(team).push_back(fakeSucc.at(team).at(i));
	}
	//populate the result
	std::vector<Graph*> res = std::vector<Graph*>(teamsCount);
	for(int team=0; team<teamsCount; team++) {
		Graph* g = new Graph(Graph(
						1, "subgraph",
						res_h.at(team),
						res_s.at(team),
						res_f.at(team),
						res_w.at(team),
						std::vector<int>(),
						std::vector<int>()));
		res.at(team) = g;
	}
	return res;
}

int Graph::getAverageDistance() const{ return averageDist; }
int Graph::getAverageFlyers() const{ return averageFlyers; }
