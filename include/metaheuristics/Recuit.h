#ifndef _RECUIT_H
#define _RECUIT_H

#include "Metaheuristic.h"
#include "Graph.h"

class RecuitException: public std::exception {
	public:
		RecuitException(const char* r): reason(r) {}
		const char* what() {return reason;}
		const char* reason;
};

/**
 * Recuit simulé
 */
class Recuit: public Metaheuristic{
	private:
		Solution& sol;
		Solution bestSol;
		int bestScore;
		float a;
		int p;
		float t;
		float e;
	public:
		/**
		 * @param initSolution the initial Solution to enhance
		 * @param alpha . 0<alpha<1
		 * @param niter the number of moves before modifying temperature
		 * @param temperature the initial temperature
		 * @param epsilon the maximum temperature to reach
		 * @note the smaller parameters are, the more intensive is the resolution 
		 */
		Recuit(Solution& initSolution, float alpha, int niter, float temperature, float epsilon);
		/**
		 * Initialise with a random acceptable solution
		 * @param graph the Graph of the problem
		 * @param alpha
		 * @param niter the number of moves before modifying temperature
		 * @param temperature the initial temperature
		 * @param epsilon the maximum temperature to reach
		 * @note the smaller parameters are, the more intensive is the resolution 
		 */
		Recuit(Graph& graph, float alpha, int niter, float temperature, float epsilon);
		/**
		 * @param problemGraph The initial graph of the problem
		 */
		Solution getSolution();
};

#endif //_RECUIT_H
