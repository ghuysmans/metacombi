#include "Score.cpp"
#include "Graph.cpp"
/**
 * A solution
 */
class Solution{
	private:
		/** The vector of the solution. vect[i] is the number of the group on the link i */
		std::vector<int> vect;
		/** The graph of all the problem */
		Graph graph = Graph("hophip.txt");//FIXME pourquoi ca compile pas si on initialise pas?
		/** The score of this solution */
		Score score = Score(std::vector<Score::teamScore>());//FIXME pourquoi ca compile pas si on initialise pas?
		/**
		 * Update the score of this solution.
		 */
		void computeScore(){
			//TODO
		}
	public:
		/**
		 * @param vectorSolution the vector of the solution.
		 * @param problemGraph The graph of the problem (its to compute the score)
		 */
		Solution(std::vector<int> vectorSolution, Graph problemGraph){
			vect = vectorSolution;
			graph = problemGraph;
			computeScore();
		}
		/**
		 * @return The score of this solution
		 */
		Score getScore(){
			return score;
		}
		/**
		 * Move something in the vector
		 */
		Solution move(){
			//TODO
		}
		//TODO peut-être devra t on envisage une fonction qui retourne tous ou une partie des mouvement possible?
};
		
