#include <vector>
#include "Solution.h"
#include "metaheuristics/LocalSearch.h"
#include <iostream>

LocalSearch::LocalSearch(const Graph& problemGraph):graph(problemGraph){}

Solution LocalSearch::getSolution(){
	std::vector<int> vectorSolution(graph.succ.size(),0);
	Solution sol = Solution( vectorSolution , graph);
	sol.initSolution();
	Score scoreBefore = Score(sol);
	std::vector<int> moveInfo;
	int iterMax = 10;
	for(int i = 0;i<iterMax;i++){
		moveInfo = sol.move();
		if(sol.isAdmissible()){
			Score scoreAfter = Score(sol);
			if(scoreBefore < scoreAfter)
				scoreBefore = scoreAfter;
			else
				sol.undo(moveInfo);
		}
		else{
			sol.undo(moveInfo);
		}
	}
	return sol;
}
