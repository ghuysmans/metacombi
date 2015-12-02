#include<sstream>
#include<fstream>
#include "Graph.h"

using namespace std;

		/**
		 * @param the name of the file that contain all data
		 */
		Graph::Graph(string name)
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
		
		Graph::int getFirst(int node)
		{
			int s = head.at(node);
			return succ.at(s - 1);
		}
		
		Graph::int getCount(int node)//utile pour getSuccessors
		{
			if(node == Nnodes - 1)
				return succ.size() - head.at(node) + 1;
			return head.at(node) - head.at(node + 1);
		}
		
		Graph::vector<int> getSuccessors(int node)
		{
			vector<int> v;
			int counter, bound = head.at(node) + getCount(node) - 1;
			for(counter = head.at(node) - 1; counter < bound - 1; counter++)
				v.push_back(succ.at(counter));
			return v;
		}
		
// --- GETTERS
		int Graph::getNteams(){ return Nteams; }
		int Graph::getNedges(){ return Nedges; }
		int Graph::getNnodes(){ return Nnodes; }
		std::vector<int> Graph::getWeights(){ return weights; }
		std::vector<int> Graph::getFlyers(){ return flyers; }
