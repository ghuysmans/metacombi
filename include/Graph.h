#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>

/**
 * The graph. Initial data of the problem
 */
class Graph{
	private:
		/** Total number of links */
		int Nlinks;
		/** Total number of nodes */
		int Nnodes;
		/** number of teams */
		int Nteams;
		/** The name of the file that contain data of the problem */
		std::string filename;
		/** head[i] is the index of the first successor of i. So the list of links */
		int head[];
		/** Contain successors of nodes (links) */
		int successors[];
		/** Nflyers[i] is the amount of flyers in the link i */
		int Nflyers[];
		/** The x coordinate of nodes */
		int x[];
		/** The y coordinate of nodes */
		int y[];
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
		int getCount(int node); //utile pour getSuccessors
		/**
		 * @return All successors of 'node'
		 */
		std::vector<int> getSuccessors(int node);
};

#endif //_GRAPH_H
