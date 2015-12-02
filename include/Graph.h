#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>

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
		Graph();
		/**
		 * @return the first successor of 'node'
		 */
		int getFirst(int node);
		/**
		 * @return the number of successor of 'node'
		 */
		int getCount(int node); //utile pour getSuccessors
		/**
		 * @return All successors of 'node'
		 */
		std::vector<int> getSuccessors(int node);
		
//-- GETTERS
		/**
		 * @return the number of teams
		 */
		int getNteams();
		/**
		 * @return Weights of each edges
		 */
		std::vector<int> getWeights();
		/**
		 * @return The amount of flyers of each edges
		 */
		std::vector<int> getFlyers();
};

#endif //_GRAPH_H
