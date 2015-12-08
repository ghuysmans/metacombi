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
	private:
		/** Total number of edges */
		int Nedges;
		
		/** Total number of nodes */
		int Nnodes;
		
		/** number of teams */
		int Nteams;
		
		/** The name of the file that contain data of the problem */
		std::string filename;
		
		/** ith element of head is the reference to the first successor of ith node */
		std::vector<int> head;
		
		/** Contain successors of nodes (edges) */
		std::vector<int> succ;
		
		/** ith element of flyers is the amount of flyers in the edge i */
		std::vector<int> flyers;
		
		/** ith element of weights is the weight of ith edge */
		std::vector<int> weights;
		
		/** The x coordinate of nodes */
		std::vector<int> x;

		/** The y coordinate of nodes */
		std::vector<int> y;
	public:
		/**
		 * @param the name of the file that contain all data
		 */
		Graph(std::string name);
		/**
		 * @return the first successor of 'node'
		 */
		int getFirst(int node);
		/**
		 * @return the number of successor of 'node'
		 */
		int getCount(int node);
		/**
		 * @return All successors
		 */
		std::vector<int> getSuccessors();
		/**
		 * @return All successors of 'node'
		 */
		std::vector<int> getSuccessors(int node);
		/**
		 * @return Distance between 'edge1' and 'edge2'
		 */
		int getDistanceEdges(int edge1, int edge2);
		/**
		 * Get the distance between 2 nodes. In our case, we always want the distance between a node and two other node.
		 * @return Distance between 'start' and 'end1' en distance between 'start' and 'end2' using Dijkstra's algorithm.
		 * @note If you get -1, it means +infinite
		 */
		std::vector<int> getDistanceNodes(int start, int end1, int end2);
		/**
		 * @return the predecessor and the successor corresponding the edge 'edge'
		 */
		std::vector<int> edgeToNodes(int edge);
		/**
		 * @return the edge that correspond to <'node' , 'successor'>
		 */
		int nodesToEdge(int node, int successor);
		/**
		 * @return the weight of the edge that link 'node' to 'successor'
		 */
		int getWeight(int node, int successor);
		
//-- GETTERS
		/**
		 * @return the number of teams
		 */
		int getNteams();
		/**
		 * @return the number of edges
		 */
		int getNedges();
		/**
		 * @return the number of nodes
		 */
		int getNnodes();
		/**
		 * @return Weights of each edges
		 */
		const std::vector<int>& getWeights();
		/**
		 * @return The amount of flyers of each edges
		 */
		const std::vector<int>& getFlyers();
};

#endif //_GRAPH_H
