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
	int iterMax = 10000;
	for(int i = 0;i<iterMax;i++){
		std::cout<<i<<std::endl;
		moveInfo = sol.move();
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
	for(int z = 0; z < sol.getVector().size(); z++)
	{
		std::cout<<sol.getVector().at(z)<<" ";
	}
	std::cout<<std::endl;
	return sol;
}
