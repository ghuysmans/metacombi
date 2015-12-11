#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>

class GraphException: public std::exception {
	public:
		GraphException(const char* r): reason(r) {}
		const char* what() {return reason;}
		const char* reason;
};

/**
 * The graph. Initial data of the problem
 */
class Graph{
	public:
		/** number of teams */
		const int teamsCount;
		/** The name of the file that contain data of the problem */
		const std::string filename;
		/** ith element of head is the first successor's index */
		const std::vector<int> head;
		/** successors (one for each edges) */
		const std::vector<int> succ;
		/** amount of flyers for each edge */
		const std::vector<int> flyers;
		/** weight of each edge */
		const std::vector<int> weights;
		/** x coordinate of node */
		const std::vector<int> x;
		/** y coordinate of node */
		const std::vector<int> y;

		Graph(const Graph& g);
		Graph(
				const int teamsCount,
				const std::string filename,
				const std::vector<int> head,
				const std::vector<int> succ,
				const std::vector<int> flyers,
				const std::vector<int> weights,
				const std::vector<int> x,
				const std::vector<int> y);
		static Graph load(const std::string& filename);
		void dump() const;

		/**
		 * @return the first successor of 'node'
		 */
		inline int getFirst(int node) const {
			int s = head.at(node);
			return succ.at(s);
		}
		/**
		 * @return the number of successor of 'node'
		 */
		inline int getCount(int node) const {
			if(node == head.size() - 1)
				return succ.size() - head.at(node);
			return head.at(node+1) - head.at(node);
		}
		/**
		 * @return the vector of successors
		 */
		std::vector<int> getSucc() const {
			return succ;
		}
		/**
		 * @return All successors of 'node'
		 */
		std::vector<int> getSuccessors(int node) const {
			int count = getCount(node);
			std::vector<int> result = std::vector<int>(count , -1);
			for(int i=0 ; i<count ; i++){
				result[i] = succ.at( head.at(node) +i );
			}
			return result;
		}
		/**
		 * @return Distance between 'edge1' and 'edge2'
		 */
		int getDistanceEdges(int edge1, int edge2) const;
		/**
		 * Get the distance between 2 nodes. In our case, we always want the distance between a node and two other node.
		 * @return Distance between 'start' and 'end1' en distance between 'start' and 'end2' using Dijkstra's algorithm.
		 * @note If you get -1, it means +infinite
		 */
		std::vector<int> getDistanceNodes(int start, int end1, int end2) const;
		/**
		 * @return both ends of the given edge
		 */
		std::vector<int> edgeToNodes(int edge) const;
		/**
		 * @note reciprocal of #edgeToNodes
		 */
		int nodesToEdge(int node, int successor) const;
		/**
		 * @return the weight of the edge between #node and #successor
		 */
		inline int getWeight(int node, int successor) const {
			return weights.at( nodesToEdge(node , successor));
		}
};

#endif //_GRAPH_H
