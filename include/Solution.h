#ifndef _SOLUTION_H
#define _SOLUTION_H

#include "Score.h"
#include "Graph.h"

/**
 * A solution
 */
class Solution{
	private:
		/** The vector of the solution. vect[i] is the number of the group on the link i */
		std::vector<int> vect;
		/** The graph of all the problem */
		Graph graph;
		/** The score of this solution */
		Score score;
		/**
		 * Update the score of this solution.
		 */
		void computeScore();
	public:
		/**
		 * @param vectorSolution the vector of the solution.
		 * @param problemGraph The graph of the problem (its to compute the score)
		 */
		Solution(std::vector<int> vectorSolution, Graph problemGraph);
		/**
		 * @return The score of this solution
		 */
		Score getScore();
		/**
		 * Move something in the vector
		 */
		Solution move();
		//TODO peut-être devra t on envisage une fonction qui retourne tous ou une partie des mouvement possible?
};

#endif //_SOLUTION_H
