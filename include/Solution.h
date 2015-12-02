#ifndef _SOLUTION_H
#define _SOLUTION_H

#include <memory>
#include "Score.h"
#include "Graph.h"

/**
 * A solution
 */
class Solution{
	private:
		/** The vector of the solution. vect[i] is the number of the group on the edge i */
		std::vector<int>& vect;
		/** The graph of all the problem */
		Graph& graph;
		/**
		 * Update the score of this solution.
		 */
		void computeScore();
		/**
		 * @return The total distance to travel for each team
		 */
		const std::vector<int> getDistances();
		/**
		 * @return The total number of flyers delivered for each team
		 */
		const std::vector<int> getDelivered();
	public:
		/**
		 * @param vectorSolution the vector of the solution.
		 * @param problemGraph The graph of the problem (its to compute the score)
		 */
		Solution(std::vector<int> vectorSolution, Graph& problemGraph);
		/**
		 * @return The score of this solution
		 */
		Score getScore(ScoreCalculator& sc);
		/**
		 * Move something in the vector
		 */
		Solution move();
		/**
 		 * @return true if the solution is admissible
 		 */
		bool isAdmissible();
		//TODO peut-être devra t on envisage une fonction qui retourne tous ou une partie des mouvement possible?
		
};

#endif //_SOLUTION_H
