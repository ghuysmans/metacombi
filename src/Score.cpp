#include <vector>
/**
 * The result of a solution (comparable)
 */
class Score{
	public: struct teamScore{
			/** The total distance */
			int dist;
			/** The total amount of delivered flyers */
			int Nflyers;
			/** The compacity of the path */
			int comp;
		};
		
	private: std::vector<Score::teamScore> tsList;
	
	public:
		/**
		 * @param distance The length of the entire path.
		 * @param totalFlyers The total amount of flyers that would be delivered.
		 * @param compacity The compacity of the pass
		 */
		Score(std::vector<struct teamScore> teamScoreList){
			tsList = teamScoreList;
		}
		/**
		 * Overloading the operator <
		 * @return true if left is < than right
		 */
		bool operator <(const Score right){
			/* the element on the left of the operator is 'this' and its a pointer.*/
			//TODO
		}
};
