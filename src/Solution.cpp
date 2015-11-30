#include "Score.h"
#include "Graph.h"

void Solution::computeScore(){
	std::vector<int>
	//TODO
}

Solution::Solution(std::vector<int> vectorSolution, Graph problemGraph){
	vect = vectorSolution;
	graph = problemGraph;
	computeScore();
}

Score Solution::getScore(){
	return score;
}

Solution Solution::move(){
	//TODO
}

std::vector<int> Solution::getDistances(){
	std::vector<int> tab = std::vector<int>(graph.getNteams(), 0);//Init a vector filled with Nteams zeros
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getWeigths[i];
	}
	return tab;
}
