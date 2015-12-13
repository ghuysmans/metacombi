#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
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

std::vector<int> Solution::getCompacities(std::vector<Graph*> const& paths) const{
	std::vector<int> tab = std::vector<int>(graph.teamsCount, 0);
	for(int i=0 ; i<paths.size() ; i++){
		tab[i] = getCompacity( *(paths.at(i)) );
	}
	return tab;
}

int Solution::getCompacity(Graph& subgraph) const{
	int maximum = 0;//will be the maximum of distances between edges
	int minimum = 0;
	for(int j=0 ; j<subgraph.getSucc().size() ; j++){//for each edges of subgraph
		for(int k=0 ; k<subgraph.getSucc().size() ; k++){//for each edges of subgraph
			if(j!=k) minimum = subgraph.getDistanceEdges(j,k);//the distance between those edges
			//std::cout << "arc " << j << " et " << k << " distance=" << minimum << std::endl;
			if(minimum > maximum)
				maximum = minimum;
		}
	}
	return maximum;
}

Solution::Solution(std::vector<int>& vectorSolution, const Graph& problemGraph): vect(vectorSolution), graph(problemGraph) {
}

Solution Solution::load(const std::string& filename, const Graph& g) {
	std::ifstream infile;
	infile.open(filename.c_str());
	if (!infile.is_open())
		throw SolutionException("couldn't open the input solution");
	std::string line;
	std::vector<int> vect(g.succ.size());
	bool valid = true;
	if (getline(infile, line)) {
		std::istringstream iss(line);
		for (int edge=0; edge<g.succ.size(); edge++) {
			int team;
			iss >> team;
			if (team<0 || team>g.teamsCount) {
				valid = false;
				break;
			}
			vect.at(edge) = team;
		}
		if (getline(infile, line) && line.size())
			valid = false;
	}
	if (valid)
		return Solution(vect, g);
	else
		throw SolutionException("invalid input solution");
}

Solution Solution::load(const Graph& graph, int pattern) {
	std::vector<int> s(graph.succ.size());
	int team = pattern<0 ? 0 : pattern;
	int count = 0;
	int change_every = graph.succ.size()/graph.teamsCount;
	for (int edge=0; edge<s.size(); edge++) {
		switch (pattern) {
			case -1:
				if (count != change_every) {
					count++;
					break; //don't change
				}
				else
					count = 0;
					//fallthrough
			case -2:
				team = (team+1) % graph.teamsCount;
				break;
			default:
				;
		}
		s.at(edge) = team;
	}
	return Solution(s, graph);
}

Score Solution::getScore() const{
	return Score::compute( this );
}

std::vector<int> Solution::move()
{
	srand (time(NULL));
	std::vector<int> res, possib;
	res.reserve(2);
	possib.reserve(graph.head.size());//va contenir tous les noeuds où on peut faire un remplacement
	int eCounter, iCounter, value;
	for(eCounter = 0; eCounter < graph.head.size(); eCounter++)
	{
		value = -1;
		for(iCounter = 0; iCounter < graph.getSuccessors(eCounter).size(); iCounter++)
		{
			if(value == -1)
				value = vect.at(graph.head.at(eCounter));
			else
				{
					if(value != vect.at(graph.head.at(eCounter) + iCounter))
					{
						possib.push_back(eCounter);
						break;
					}
				}
		}
	}
	
	value = rand() % possib.size();
	int e1 = -1, e2 = -1, v1, v2, v3 = graph.getSuccessors(possib.at(value)).size();
	
	while(e1 == e2)
	{
		v1 = rand() % v3;
		v2 = rand() % v3;
		e1 = vect.at(graph.head.at(possib.at(value)) + v1);
		e2 = vect.at(graph.head.at(possib.at(value)) + v2);
	}
	
	v3 = rand() % 2 + 1;  
	int i;
	if(v3 == 1)//equipe 1 prend deux arcs en plus
	{
		vect.at(graph.head.at(possib.at(value)) + v2) = e1;//On modifie l'arc de a vers b
		for(i = 0; i < graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)).size(); i++)
		{
			if(possib.at(value) == graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)).at(i))
			{
				vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)) + i) = e1;//On modifie l'arc de b vers a
				break;	
			}
		}
		res.push_back(e2);
		res.push_back(graph.head.at(possib.at(value)) + v2);
		res.push_back(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2) + i));
	}
	else//equipe 2 prend deux arcs en plus
	{
		vect.at(graph.head.at(possib.at(value)) + v1) = e2;//On modifie l'arc de a vers b
		for(i = 0; i < graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)).size(); i++)
		{
			if(possib.at(value) == graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)).at(i))
			{
				vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)) + i) = e2;//On modifie l'arc de b vers a
				break;	
			}
		}
		res.push_back(e1);
		res.push_back(graph.head.at(possib.at(value)) + v1);
		res.push_back(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1) + i));
	}

	return res;//res.at(0) = equipe remplacé, res.at(1) = position remplacé, res.at(2) = position remplacé
}

void Solution::undo(std::vector<int> move){
	vect.at(move.at(1)) = move.at(0);
	vect.at(move.at(2)) = move.at(0);
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
							int succIndex = 0;
							for(int k = 0;k<succ;k++){
								succIndex += graph.getCount(k);
							}
							for(int j=succIndex;j< (succIndex + graph.getCount(succ));j++){
								if(successors.at(j) == workingNode){
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

void Solution::initSolution(){
	std::stack<int> lifo;
	//On marque chaque sommet et arcs(aller/retour) à false
	std::vector<bool> markEdges(graph.succ.size(),false);
	std::vector<bool> markNodes(graph.head.size(),false);
	int edgesPerTeam = graph.succ.size() / graph.head.size();
	int workingNode,succ,nbrOfSucc,firstSuccIndex,succIndex,neighbourTeam,counter = 0,teamNumber = 1;
	
	//Parcours en profondeur
	markNodes[0] = true;
	lifo.push(0);
	bool pushed,neighbourFound;
	while(!lifo.empty()){
		workingNode = lifo.top();
		nbrOfSucc = graph.getCount(workingNode);
		if(nbrOfSucc == 0)
			lifo.pop();
		else{
			pushed = false;
			firstSuccIndex = 0;
			for(int i = 0;i<workingNode;i++){
				firstSuccIndex += graph.getCount(i);
			}
			//On va push le premier successeur non-marqué dans la pile et assigné un numéro de team aux arcs
			for(int i=firstSuccIndex;i< (firstSuccIndex + nbrOfSucc);i++){
				if(!markEdges.at(i)){
					//Si il n'y a pas d'arc voisin assigné à la même équipe et que le conteur est différent de zéro,on passe à l'équipe suivante.
					neighbourFound = false;
					for(int j=firstSuccIndex;j< (firstSuccIndex + nbrOfSucc);j++){
						if(vect.at(j) == teamNumber)
							neighbourFound = true;
						if(vect.at(j) > 0)
							neighbourTeam = vect.at(j);
					}
					if(!neighbourFound && counter != 0){
						counter = 0;
						if(teamNumber == graph.teamsCount)
							teamNumber = neighbourTeam;
						else
							teamNumber++;
					}

					//on marque l'arc du noeud vers le successeur 
					markEdges.at(i) = true;
					vect.at(i) = teamNumber;
					//On marque aussi l'arc dans l'autre sens pour ne pas faire demi-tour
					succ = graph.succ.at(i);
					succIndex= 0;
					for(int k = 0;k<succ;k++){
						succIndex += graph.getCount(k);
					}
					for(int j=succIndex;j< (succIndex + graph.getCount(succ));j++){
						if(graph.succ.at(j) == workingNode){
							markEdges.at(j) = true;
							vect.at(j) = teamNumber;
						}
					}
					//+2 car arc aller-retour marqué
					counter+=2;
					if(counter > edgesPerTeam && teamNumber < graph.teamsCount){
						counter = 0;
						teamNumber++;
					}
					if(!markNodes.at(graph.succ.at(i))){
						markNodes.at(graph.succ.at(i)) = true;
						lifo.push(graph.succ.at(i));
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
}

const std::vector<int>& Solution::getVector() const { return vect; }
