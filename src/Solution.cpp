#include "Score.h"
#include "Graph.h"
#include "Solution.h"

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

Score Solution::getScore(ScoreCalculator& sc){
	return sc(getDistances(), getDelivered(), graph);
}

Solution Solution::move(){
	//TODO
}
