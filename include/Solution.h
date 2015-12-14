#ifndef _SOLUTION_H
#define _SOLUTION_H

#include "Score.h"
#include "Graph.h"

class SolutionException: public std::exception {
	public:
		SolutionException(const char* r): reason(r) {}
		const char* what() {return reason;}
		const char* reason;
};

/**
 * A solution
 */
class Solution{
	public:
		/** The vector of the solution. vect[i] is the number of the group on the edge i */
		std::vector<int> vect;
		/** The graph of all the problem */
		const Graph& graph;
		/**
		 * @return The total distance to travel for each team
		 */
		const std::vector<int> getDistances() const;
		/**
		 * @return The total number of flyers delivered for each team
		 */
		const std::vector<int> getDelivered() const;
		/**
		 * @param vectorSolution the vector of the solution.
		 * @param problemGraph The graph of the problem (its to compute the score)
		 */
		Solution(std::vector<int>& vectorSolution, const Graph& problemGraph);
		/**
		 * @param input input stream
		 * @param problemGraph the problem graph
		 */
		static Solution load(std::istream& input, const Graph& problemGraph);
		/**
		 * @param filename text file containing the solution
		 * @param problemGraph the problem graph
		 */
		static Solution load(const std::string& filename, const Graph& problemGraph);
		/**
		 * Generate a (probably invalid) trivial solution.
		 * @param problemGraph the problem graph
		 * @param pattern positive is the same team, -1 is equal parts, -2 is modulus
		 */
		static Solution load(const Graph& graph, int pattern);
		/**
		 * @param The list of subgraph for each team
		 * @return The compacity of the path for each team
		 * @note This function should be private but it need to be tested
		 */
		std::vector<int> getCompacities(std::vector<Graph*> const& paths) const;
		/**
		 * @param the subgraph
		 * @return The compacity of 'subgraph'
		 * @note This function should be private but it need to be tested
		 */
		int getCompacity(Graph& subgraph) const;
		/**
		 * @return The score of this solution
		 */
		Score getScore() const;
		/**
		 * Move something in the vector
		 */
		std::vector<int> move();
		std::vector<int> move2();
		/**
		 * @param A vector that represents the move to undo
		 */
		void undo(std::vector<int> move);
		/**
 		 * @return true if the solution is admissible
 		 */
		bool isAdmissible() const;
		/**
		 *Initialize an admissible solution
		*/
		void initSolution();
		/**
		 * @return The solution vector
		 */
		const std::vector<int>& getVector() const;
		//TODO peut-être devra t on envisage une fonction qui retourne tous ou une partie des mouvement possible?

		static class Rand {
			public:
				Rand();
		} _rand;
};

#endif //_SOLUTION_H
