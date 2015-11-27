/**
 * The result of a solution (comparable)
 */
class Score{
	private:
		/** The total distance **/
		int dist;
		/** The total amount of delivered flyers **/
		int Nflyers;
		/** The compacity of the path **/
		int comp;
	public:
		/**
		 * @param distance The length of the entire path.
		 * @param totalFlyers The total amount of flyers that would be delivered.
		 * @param compacity The compacity of the pass
		 */
		Score(int distance, int totalFlyers, int compacity){
			dist = distance;
			Nflyers = totalFlyers;
			comp = compacity;
		}
		/**
		 * Overloading the operator <
		 * @return true if left is < than right
		 */
		bool operator <(const Score right){
			/* the element on the left of the operator is this and its a pointer.*/
			return (this->dist < right.dist);//TODO cette ligne est pour tester
		}
};
