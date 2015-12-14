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
	int scoreBefore = Score(sol).toInt();
	std::vector<int> moveInfo;
	int iterMax = 100;
	
	for(int i = 0;i<iterMax;i++){
		moveInfo = sol.move2();
		if(sol.isAdmissible()){
		std::cout<<"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj"<<std::endl;
		Metaheuristic::do_dump(sol);
			int scoreAfter = Score(sol).toInt();
			if(Score::isBetterThan(scoreAfter , scoreBefore))
			{
				scoreBefore = scoreAfter;
				std::cout<<"on est la111111111111111"<<std::endl;
			}
			else
			{
				std::cout<<"scoreBefore = "<<scoreBefore<<std::endl;
				std::cout<<"scoreAfter = "<<scoreAfter<<std::endl;
				sol.undo(moveInfo);
				std::cout<<"on est la22222222222222"<<std::endl;
			}
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
