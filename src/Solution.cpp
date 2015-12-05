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

Solution::Solution(std::vector<int>& vectorSolution, Graph& problemGraph): vect(vectorSolution), graph(problemGraph) {
}

Score Solution::getScore(ScoreCalculator& sc){
	return sc(getDistances(), getDelivered(), graph);
}

Solution Solution::move(){
	//TODO
}

bool Solution::isAdmissible(){ 
	//int arr[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	//std::vector<int> vectorSolution(&arr[0], &arr[0]+48);
	//vect = vectorSolution;
	std::stack<int> lifo;
	std::map<int,bool> mark;
	std::vector<int> successors = graph.getSuccessors();
	std::map<int, bool>::iterator it;
	int firstNode,firstSuccIndex,workingNode;
	int indexInSolution = 0;
	int nbrOfSucc;
	for(int team = 1;team <= graph.getNteams();team++){
		mark.clear();
		firstNode = 0;
		indexInSolution = 0;
		//On initialise map avec des false pour chaque arcs(aller-retour) du sous-graphe
		for(int i = 1;i <= graph.getNnodes();i++){
			nbrOfSucc = graph.getCount(i);
			for(int j = 0;j < nbrOfSucc;j++){
				if(vect.at(indexInSolution) == team){
					if(firstNode  == 0)
						firstNode = i;
					mark.insert ( std::pair<int,bool>(indexInSolution,false));
				}
				indexInSolution++;
			}
		}
		
		//Parcours en profondeur
		lifo.push(firstNode);
		int succ;
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
						it = mark.find(i);
						if(it != mark.end()){
							if(!(it->second)){
								succ = successors.at(it->first);
								//On le marque à vrai
								it->second = true;
								//On marque aussi l'arc dans l'autre sens pour ne pas faire demi-tour
								int firstSuccOfSuccIndex= 0;
								for(int i = 1;i<succ;i++){
									firstSuccOfSuccIndex += graph.getCount(i);
								}
								for(int j=firstSuccOfSuccIndex;j< (firstSuccOfSuccIndex + graph.getCount(succ));j++){
									if(successors.at(j) == succ){
										it = mark.find(j);
										it->second = true;
									}
								}
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

std::vector<int>& Solution::getVector(){ return vect; }
