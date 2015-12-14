#include <vector>
#include "Solution.h"
#include "metaheuristics/LocalSearch.h"
#include "metaheuristics/Metaheuristic.h"

LocalSearch::LocalSearch(const Graph& problemGraph):graph(problemGraph){}

Solution LocalSearch::getSolution(){
	std::vector<int> vectorSolution(graph.succ.size(),0);
	Solution sol = Solution( vectorSolution , graph);
	sol.initSolution();
	Score scoreBefore = Score(sol);
	std::vector<int> moveInfo;
	int iterMax = 100;
	for(int i = 0;i<iterMax;i++){
		moveInfo = sol.move2();
		if(sol.isAdmissible()){
			Score scoreAfter = Score(sol);
			if(scoreBefore < scoreAfter)
				scoreBefore = scoreAfter;
			else
				sol.undo(moveInfo);
		}
		else{
			if(!sol.isAdmissible())
				std::cout << "OK1" << std::endl;
			sol.undo(moveInfo);
			if(sol.isAdmissible())
				std::cout << "OK2" << std::endl;
		}
		Metaheuristic::do_dump(sol);
	}
	return sol;
}
