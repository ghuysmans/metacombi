#include <map>
#include <stack>
#include <iostream>
#include "Score.h"
#include "Graph.h"
#include "Solution.h"

const std::vector<int> Solution::getDistances(){
	std::vector<int> tab = std::vector<int>(graph.getNteams());
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getWeights()[i];
	}
	return tab;
}

const std::vector<int> Solution::getDelivered(){
	std::vector<int> tab = std::vector<int>(graph.getNteams());
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.getFlyers()[i];
	}
	return tab;
}

std::vector<int> Solution::getCompacities(std::vector<Graph> paths){
	std::vector<int> tab = std::vector<int>(graph.getNteams(), 0);
	for(int i=0 ; i<paths.size() ; i++){
		int maximum = 0;//will be the maximum of distances between edges
		for(int j=0 ; j<paths.size() ; j++){//for each edges of graph i
			//TODO test this actually works...
			for(int k=0 ; k<paths.size() ; k++){//for each edges of graph i
				int minimum = paths[i].getDistanceEdges(j,k);//the distance between those edges
				if(minimum > maximum)
					maximum = minimum;
			}
		}
		tab[i] = maximum;
	}
	return tab;
}

Solution::Solution(std::vector<int> vectorSolution, Graph& problemGraph): vect(vectorSolution), graph(problemGraph) {
}

Score Solution::getScore(ScoreCalculator& sc){
	return sc(getDistances(), getDelivered(), graph);
}

Solution Solution::move(){
	//TODO
}

bool Solution::isAdmissible(){
	std::stack<int> lifo;
	std::map<int,bool> mark;
	std::vector<int> successors = graph.getSuccessors();
	std::map<int, bool>::iterator it;
	int firstNode;
	int indexInSolution = 0;
	int nbrOfSucc;
	for(int team = 1;team <= graph.getNteams();team++){
		mark.clear();
		firstNode = 0;
		indexInSolution = 0;
		//On initialise map avec des false pour chaque sommets du sous-graphe
		for(int i = 1;i <= graph.getNnodes();i++){
			nbrOfSucc = graph.getCount(i);
			for(int j = 0;j < nbrOfSucc;j++){
				if(vect.at(indexInSolution) == team){
					if(firstNode  == 0)
						firstNode = i;
					else{
						//Pour ne pas avoir de doublons(puisque c'est un graphe non-orienté)
						if(mark.count(successors.at(j)) != 0)
							mark.insert ( std::pair<int,bool>(successors.at(j),false));
					}
				}
				indexInSolution++;
			}
		}
		
		//Parcours en profondeur
		it = mark.find(firstNode);
		if(it != mark.end())
			it->second = true;
		lifo.push(firstNode);
		int workingNode, firstSuccIndex , succ;
		bool pushed;
		while(!lifo.empty()){
				workingNode = lifo.top();
				nbrOfSucc = graph.getCount(workingNode);
				if(nbrOfSucc == 0)
					lifo.pop();
				else{
					pushed = false;
					firstSuccIndex = 0;
					for(int i = 1;i<workingNode;i++){
						firstSuccIndex += graph.getCount(i);
					}
					//On va push le premier successeur non-marqué(et se trouvant dans map) dans la pile
					for(int i=firstSuccIndex;i< (firstSuccIndex + nbrOfSucc);i++){
						it = mark.find(successors.at(i));
						if(it != mark.end()){
							if(!(it->second)){
								succ = it->first;
								//On le marque à vrai
								it->second = true;
								lifo.push(succ);
								pushed = true;
								break;
							}
						}
					}
					//Cas où tous les successeurs ont déjà été marqué 
					if(!(pushed))
						lifo.pop();
				}
		}
		//Si un sommet n'a pas été marqué après le parcours
		for(it=mark.begin(); it!=mark.end(); ++it) {
			if(it->second == false)
				return false;
		}
	}
	return true;
}

int main(){
	Graph graph = Graph("TPOC-45.txt");
	static const int arr[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<int> vectorSolution(sizeof(arr) / sizeof(arr[0]), 0);
	Solution sol = Solution(vectorSolution,graph);
	if(sol.isAdmissible())
		std::cout << "GOOD" <<std::endl;
	else
		std::cout << "FAILED" <<std::endl;
		
	return 1;
}
