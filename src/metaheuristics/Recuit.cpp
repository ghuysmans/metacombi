#include "metaheuristics/Metaheuristic.h"
#include "metaheuristics/Recuit.h"
#include "Solution.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

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

bool Recuit::accept(int sprime, int s){
	//compute proba for sprime, s, t
	double proba = pow(0.5*(1-exp(t/10)) , (sprime/s) );
	//generate random number between 0 and 1
	srand (time(NULL));
	double r = ((double) rand() / (RAND_MAX));
	return r<proba;
}
	
Solution Recuit::getSolution(){
	int scoreS = bestScore;
	int scoreSprime;
	std::vector<int> tuple;
	do{
		for(int i=0 ; i<p ; i++){
			//more than one admissible solution before choosing ?
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
			//now sol is s' and sol is s. affect
			scoreSprime = Score(sol).toInt();
			if( Score::isBetterThan(scoreS , scoreSprime) ){
				scoreS = scoreSprime;
				//update best solution
				if( Score::isBetterThan(scoreS , bestScore) ){
					bestScore = scoreS;
					const Graph& g = sol.graph;
					std::vector<int> v(sol.getVector());
					bestSol = Solution(v,g);
				}
			}
			else if( accept(scoreSprime, scoreS) ){
				scoreS : scoreSprime;
			}
		}
		//update temperature
		t = a*t;	
	}while(t<e);
	return bestSol;
}
