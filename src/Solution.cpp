#include "Score.h"
#include "Graph.h"

void Solution::computeScore(){
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
