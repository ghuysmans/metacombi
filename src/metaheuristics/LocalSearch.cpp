#include <vector>

Solution LocalSearch::LocalSearch(const Graph& problemGraph):graph(problemGraph){}

Solution LocalSearch::getSolution(){
	std::vector<int> vectorSolution(graph.succ.size(),0);
	Solution sol = Solution( vectorSolution , graph);
	sol.initSolution();
	Score scoreBefore = sol.getScore();
	Score scoreAfter = sol.getScore();
	std::vector<int> moveInfo;
	int iterMax = 10000;
	for(int i = 0;i<iterMax;i++){
		moveInfo = sol.move();
		if(sol.isAdmissible()){
			scoreAfter = sol.getScore();
			if(scoreBefore < scoreAfter)
				scoreBefore = scoreAfter;
			else
				sol.undo(moveInfo);
		}
		else
			sol.undo(moveInfo);
	}
}
