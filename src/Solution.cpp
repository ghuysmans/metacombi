#include <map>
#include <stack>
#include <iostream>
#include "Score.h"
#include "Graph.h"
#include "Solution.h"

const std::vector<int> Solution::getDistances() const{
	std::vector<int> tab = std::vector<int>(graph.teamsCount);
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.weights.at(i);
	}
	return tab;
}

const std::vector<int> Solution::getDelivered() const{
	std::vector<int> tab = std::vector<int>(graph.teamsCount);
	for(int i=0 ; i<vect.size() ; i++){
		tab[vect[i]] += graph.flyers.at(i);
	}
	return tab;
}

std::vector<int> Solution::getCompacities(std::vector<Graph> paths) const{
	std::vector<int> tab = std::vector<int>(graph.teamsCount, 0);
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

Solution::Solution(std::vector<int>& vectorSolution, const Graph& problemGraph): vect(vectorSolution), graph(problemGraph) {
}

Score Solution::getScore(ScoreCalculator& sc) const{
	return sc(getDistances(), getDelivered(), graph);
}

Solution Solution::move(){
	//TODO
}

bool Solution::isAdmissible() const{
	std::stack<int> lifo;
	std::map<int,bool> mark;
	std::vector<int> successors = graph.succ;
	std::map<int, bool>::iterator it;
	int firstNode,firstSuccIndex,workingNode;
	int indexInSolution = 0;
	for(int team = 1; team <= graph.teamsCount; team++){
		mark.clear();
		firstNode = -1;
		indexInSolution = 0;
		//On initialise map avec des false pour chaque arcs(aller-retour) du sous-graphe
		for(int i = 0; i < graph.head.size(); i++){
			int nbrOfSucc = graph.getCount(i);
			for(int j = 0; j < nbrOfSucc; j++){
				if(vect.at(indexInSolution) == team){
					if(firstNode  == -1)
						firstNode = i;
					mark.insert(std::pair<int,bool>(indexInSolution,false));
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
			int nbrOfSucc = graph.getCount(workingNode);
			if(nbrOfSucc == 0)
				lifo.pop();
			else{
				pushed = false;
				firstSuccIndex = 0;
				for(int i = 0;i<workingNode;i++){
					firstSuccIndex += graph.getCount(i);
				}
				//On va push le premier successeur non-marqué(et se trouvant dans map) dans la pile
				for(int i=firstSuccIndex;i< (firstSuccIndex + nbrOfSucc);i++){
					it = mark.find(i);
					if(it != mark.end()){
						if(!(it->second)){
							succ = successors.at(it->first);
							it->second = true;
							//On marque aussi l'arc dans l'autre sens pour ne pas faire demi-tour
							//iletaitunefoisunepetitesireneaufonddelocean, I think that's a bit more precise. Seriously?
							int firstSuccOfSuccIndex= 0;
							for(int k = 0;k<succ;k++){
								firstSuccOfSuccIndex += graph.getCount(k);
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

std::vector<int>& Solution::getVector() const{ return vect; }
