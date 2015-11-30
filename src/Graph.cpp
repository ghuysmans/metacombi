#include <vector>
#include <string>
#include<sstream>
#include<fstream>
#include "Graph.h"

using namespace std;

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
		string filename;
		
		/** ith element of head is the reference to the first successor of ith node */
		vector<int> head;
		
		/** Contain successors of nodes (edges) */
		vector<int> succ;
		
		/** ith element of flyers is the amount of flyers in the edge i */
		vector<int> flyers;
		
		/** ith element of weights is the weight of ith edge */
		vector<int> weights;
		
		/** The x coordinate of nodes */
		vector<int> x;

		/** The y coordinate of nodes */
		vector<int> y;
	
	public:
		/**
		 * @param the name of the file that contain all data
		 */
		Graph(string name)
		{
			filename = name;
			ifstream infile;
			infile.open(filename.c_str());
			if (infile.is_open())
			{
				int counter, tmp, linenumber = 1;
				string line;
				while (getline(infile, line))
				{
					istringstream iss(line);
					if(linenumber == 1)
					{
						iss>>Nedges>>Nnodes>>Nteams;		
						head.reserve(Nnodes);
						x.reserve(Nnodes);
						y.reserve(Nnodes);
						succ.reserve(4*Nnodes);
						weights.reserve(4*Nnodes);
						flyers.reserve(4*Nnodes);
					}
					else if(linenumber == 2)
					{
						for(counter = 0; counter < Nnodes; counter++)
						{
							iss >> tmp;
							head.push_back(tmp);
						}
					}
					else if(linenumber == 3)
					{
						for(counter = 0; counter < Nnodes; counter++)
						{
							iss >> tmp;
							x.push_back(tmp);
						}
					}
					else if(linenumber == 4)
					{
						for(counter = 0; counter < Nnodes; counter++)
						{
							iss >> tmp;
							y.push_back(tmp);
						}
					}
					
					else if(linenumber == 5)
					{
						for(counter = 0; counter < Nedges; counter++)
						{
							iss >>tmp;
							succ.push_back(tmp);
						}
					}
					
					else if(linenumber == 6)
					{
						for(counter = 0; counter < Nedges; counter++)
						{
							iss >>tmp;
							weights.push_back(tmp);
						}
					}
			
					else if(linenumber == 7)
					{

						for(counter = 0; counter < Nedges; counter++)
						{
							iss >>tmp;
							flyers.push_back(tmp);
						}
					}	
					linenumber++;
				}
			}
			infile.close();
		}
		
		/**
		 * @return the first successor of 'node'
		 */
		int getFirst(int node)
		{
			int s = head.at(node - 1);
			return succ.at(s - 1);
		}
		
		/**
		 * @return the number of successor of 'node'
		 */
		int getCount(int node)//utile pour getSuccessors
		{
			if(node == Nnodes)
				return succ.size() - head.at(node - 1) + 1;
			return head.at(node) - head.at(node - 1);
		}
		
		/**
		 * @return All successors of 'node'
		 */
		vector<int> getSuccessors(int node)
		{
			vector<int> v;
			int counter, bound = head.at(node - 1) + getCount(node);
			for(counter = head.at(node - 1) - 1; counter < bound - 1; counter++)
				v.push_back(succ.at(counter));
			return v;
		}
};
