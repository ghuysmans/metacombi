#include <vector>
#include <string>
/**
 * The graph. Initial data of the problem
 */ 
class Graph{
	private:
		/** The name of the file that contain data of the problem **/
		std::string filename;
		/** head[i] is the index of the first successor of i. So the list of links **/
		int head[];
		/** Contain successors of nodes (**/
		int successors[];
		/** Nflyers[i] is the amount of flyers in the link i **/
		int Nflyers[];
		/** The x coordinate of nodes **/
		int x[];
		/** The y coordinate of nodes **/
		int y[];
	public:
		/**
		 * @param the name of the file that contain all data
		 */
		Graph(std::string name){
			filename = name;
		}
		/**
		 * @return the first successor of 'node'
		 */
		int getFirst(int node){
			//TODO
		}
		/**
		 * @return the number of successor of 'node'
		 */
		int getCount(int node){//utile pour getSuccessors
			//TODO
		}
		/**
		 * @return All successors of 'node'
		 */
		std::vector<int> getSuccessors(int node){
			//TODO
		}
};
