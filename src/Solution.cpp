#include "Score.h"
#include "Graph.h"
#include "Solution.h"

void Solution::computeScore(){
	std::vector<int> distances = getDistances();
	std::vector<int> amountFlyers = getDelivered();
	//TODO
}

const std::vector<int> Solution::getDistances(){
	std::vector<int> tab = std::vector<int>(graph.getNteams());
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getWeights()[i];
	}
	return tab;
}

const std::vector<int> Solution::getDelivered(){
	std::vector<int> tab = std::vector<int>(graph.getNteams());
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getFlyers()[i];
	}
	return tab;
}

Solution::Solution(std::vector<int> vectorSolution, Graph& problemGraph): vect(vectorSolution), graph(problemGraph) {
}

Score Solution::getScore(){
	return score;
}

Solution Solution::move(){
	//TODO
}
