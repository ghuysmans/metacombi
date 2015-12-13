#include "metaheuristics/Metaheuristic.h"
#include "metaheuristics/Recuit.h"
#include "Solution.h"
#include <vector>
#include <iostream>

Recuit::Recuit(Solution& initSolution, float alpha, int niter, float temperature, float epsilon):
	sol(initSolution),
	bestSol(Solution(*(new std::vector<int>(initSolution.getVector())), initSolution.graph)),
	bestScore(Score(initSolution).toInt()),
	a(alpha),
	p(niter),
	t(temperature),
	e(epsilon){
	if( !(0<alpha && alpha<1) ){
		throw RecuitException("0<alpha<1 please");
	}
}

/*Recuit::Recuit(Graph& graph, float alpha, int niter, float temperature, float epsilon){
	std::vector<int> vect(graph.succ.size() , 0);
	Solution initSol = Solution(vect, graph);
	iniSol.initSolution();
	Recuit(iniSol, alpha, niter, temperature);
}*/
	
Solution Recuit::getSolution(){
	std::vector<int> tuple;
	do{
		for(int i=0 ; i<p ; i++){
			//more than one moves before choosing ?
			bool ok = false;
			for(int j=0 ; j< 1000 ; j++){
				tuple = sol.move();
				if( sol.isAdmissible() ){
					ok = true;
					break;
				}
				else sol.undo(tuple);
			}
			if(!ok){
				std::cout << "Recuit.cpp: cannot find an admissible solution. Return the best found" << std::endl;
				return bestSol;
			}
			//now sol is s' and bestSol is s
		}
			
	}while(t<e);
	return bestSol;
}
