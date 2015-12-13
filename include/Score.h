#ifndef _SCORE_H
#define _SCORE_H

#include <vector>
#include "Graph.h"
class Score;
class Solution;
#include "Solution.h"

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

		/**
		 * @param sol The solution where to compute the score
		 */
		Score(const Solution& sol);

		/**
		 * Overloading the operator <
		 * @return true if left is < than right
		 */
		bool operator <(const Score& right);
		/**
		 * Compare two score by their integer form
		 */
		bool isBetterThan(int score1, int score2);
		/**
		 * @param distancePower the power of ErrLength
		 * @param flyersPower the power of ErrFlyers
		 * @param compacityPower the power of (1+Compacity)
		 * @return a comparable integer value of this score
		 */
		int toInt(int distancePower, int flyersPower, int compacityPower) const;
		/**
		 * @return a comparable integer value of this score
		 */
		int toInt() const;
	private:
		std::vector<teamScore> tsList;
		int averageDistance;
		int averageFlyers;
};

/**
 * Simple functor
 */
class ScoreCalculator{
	public:
		virtual Score& operator()(std::vector<int> dist, std::vector<int> delivered, const Graph& g) = 0;
};

#endif //_SCORE_H
