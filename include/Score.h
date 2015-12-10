#ifndef _SCORE_H
#define _SCORE_H

#include <vector>
#include "Graph.h"

/**
 * The result of a solution (comparable)
 */
class Score{
	public:
		struct teamScore{
			/** The total distance */
			int dist;
			/** The total amount of delivered flyers */
			int Nflyers;
			/** The compacity of the path */
			int comp;
		};

		//FIXME so what?
		/**
		 * @param distance The length of the entire path.
		 * @param totalFlyers The total amount of flyers that would be delivered.
		 * @param compacity The compacity of the pass
		 */
		Score(std::vector<struct teamScore> teamScoreList);

		/**
		 * Overloading the operator <
		 * @return true if left is < than right
		 */
		bool operator <(const Score right);

	private:
		std::vector<Score::teamScore>& tsList;
};

/**
 * Simple functor
 */
class ScoreCalculator{
	public:
		virtual Score& operator()(std::vector<int> dist, std::vector<int> delivered, const Graph& g) = 0;
};

#endif //_SCORE_H
