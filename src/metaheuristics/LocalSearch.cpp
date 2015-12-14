#include <vector>
#include "Solution.h"
#include "metaheuristics/LocalSearch.h"
#include "metaheuristics/Metaheuristic.h"
#include <iostream>

LocalSearch::LocalSearch(const Graph& problemGraph):graph(problemGraph){}

Solution LocalSearch::getSolution(){
	std::vector<int> vectorSolution(graph.succ.size(),0);
	Solution sol = Solution( vectorSolution , graph);
	sol.initSolution();
	float scoreBefore = Score(sol).toFloat();
	std::vector<int> moveInfo;
	int iterMax = 100;
	for(int i = 0;i<iterMax;i++){
		moveInfo = sol.move2();
		if(sol.isAdmissible()){
		std::cerr<<"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj"<<std::endl;
		Metaheuristic::do_dump(sol);
			float scoreAfter = Score(sol).toFloat();
			if(Score::isBetterThan(scoreAfter , scoreBefore))
			{
				scoreBefore = scoreAfter;
			}
			else
			{
				sol.undo(moveInfo);
			}
		}
		else{
			sol.undo(moveInfo);
		}
		Metaheuristic::do_dump(sol);
	}
	return sol;
}
