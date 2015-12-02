#include "Score.h"
#include "Graph.h"
#include "Solution.h"

void Solution::computeScore(){
	std::vector<int> distances = getDistances();
	std::vector<int> amountFlyers = getDelivered();
	//TODO
}

std::vector<int> Solution::getDistances(){
	std::vector<int> tab = std::vector<int>(graph.getNteams(), 0);//Init a vector filled with Nteams zeros
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getWeights()[i];
	}
	return tab;
}

std::vector<int> Solution::getDelivered(){
	std::vector<int> tab = std::vector<int>(graph.getNteams(), 0);
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getFlyers()[i];
	}
	return tab;
}

std::vector<int> Solution::getCompacities(std::vector<Graph> paths){
	std::vector<int> tab : std::vector<int>(graph.getNteams(), 0);
	for(int i=0 ; i<paths.size() ; i++){
		int maximum = 0;//will be the maximum of distances between edges
		for(int j=0 ; j<path.size() ; j++){//for each edges of graph i
			for(int k=0 ; k<path.size() ; k++){//for each edges of graph i
			int minimum = paths[i].getDistanceEdges(j,k);//the distance between those edges
			if(minimum > maximum){
				maximum = minimum;
			}
		}
		tab[i] = maximum;
	}
	return tab;
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
