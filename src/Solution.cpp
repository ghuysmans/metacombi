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

Solution::Rand Solution::_rand;

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
			//std::cerr << "arc " << j << " et " << k << " distance=" << minimum << std::endl;
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
	return Solution::load(infile, g);
}

Solution Solution::load(std::istream& infile, const Graph& g) {
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

Solution::Rand::Rand() {
	srand(time(NULL));
}

std::vector<int> Solution::move2()
{
	std::vector<int> res;
	res.reserve(2);
	bool found = false;
	int teamNumber;
	int succIndex = 0,succIndex2 = 0,succIndex3 = 0,succ = 0,succ2 = 0,node;
	while(!found){
		std::cout << "BEF" << std::endl;
		node = rand() % graph.head.size();
		succIndex = 0;
		for(int i = 0;i<node;i++){
			succIndex += graph.getCount(i);
		}
		for(int i=succIndex;i< (succIndex + graph.getCount(node));i++){
			succ = graph.succ.at(i);
			teamNumber = vect.at(i);
			succIndex2 = 0;
			for(int k = 0;k<succ;k++){
				succIndex2 += graph.getCount(k);
			}
			for(int j=succIndex2;j< (succIndex2 + graph.getCount(succ));j++){
				if(vect.at(j) != teamNumber){
					res.push_back(vect.at(j));
					res.push_back(j);
					vect.at(j) = teamNumber;
					succ2 = graph.succ.at(j);
					succIndex3 = 0;
					for(int m = 0;m<succ2;m++){
						succIndex3 += graph.getCount(m);
					}
					for(int n=succIndex3;n< (succIndex3 + graph.getCount(succ2));n++){
						std::cout << "in" << std::endl;
						if(graph.succ.at(n) == succ){
							vect.at(n) = teamNumber;
							res.push_back(n);
							std::cout << "in2" << std::endl;
						}
					}
					found = true;
					break;
				}
			}
		}
	}
	std::cout << res.at(0) << std::endl;
	std::cout << res.at(1) << std::endl;
	std::cout << res.at(2) << std::endl;
	return res;//res.at(0) = equipe remplacé, res.at(1) = position remplacé, res.at(2) = position remplacé
}

std::vector<int> Solution::move()
{
	std::vector<int> res, possib;
	res.reserve(3);
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
	//for(int z = 0; z < v3; z++)
	//	std::cout<<vect.at(graph.head.at(possib.at(value)) + z)<<" ";
	//std::cout<<std::endl;
	//std::cout<<"size = "<<v3<<std::endl;
	while(e1 == e2)
	{
		v1 = rand() % v3;
		v2 = rand() % v3;
		e1 = vect.at(graph.head.at(possib.at(value)) + v1);
		e2 = vect.at(graph.head.at(possib.at(value)) + v2);
	}
	//std::cout<<"v1 = "<<v1<<" v2 = "<<v2<<" e1 = "<<e1<<" e2 = "<<e2<<std::endl;
	v3 = rand() % 2 + 1;
	//std::cout<<"v3 = "<<v3<<std::endl;
	int i;
	
	if(v3 == 1)//equipe 1 prend deux arcs en plus
	{
		res.push_back(e2);
		//std::cout<<"1was1 = "<<vect.at(graph.head.at(possib.at(value)) + v2)<<std::endl;
		vect.at(graph.head.at(possib.at(value)) + v2) = e1;//On modifie l'arc de a vers b
		res.push_back(graph.head.at(possib.at(value)) + v2);
		std::cout<<"now e1 = "<<e1<<std::endl;
		for(i = 0; i < graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)).size(); i++)
		{
			if(possib.at(value) == graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)).at(i))
			{
				int const x = graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)) + i;
				res.push_back(x);
			//	std::cout<<"1was2 = "<<vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)) + i)<<std::endl;
				vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)) + i) = e1;//On modifie l'arc de b vers a
				//res.push_back(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2) + i));
				std::cout<<"adresse1 = "<<(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)) + i)<<std::endl;
			//	std::cout<<"1i = "<<i<<std::endl;
				std::cout<<"now e1 = "<<e1<<std::endl;
				break;	
			}
		}
		//res.push_back(e2);
		//res.push_back(graph.head.at(possib.at(value)) + v2);
		//std::cout<<"1i = "<<i<<std::endl;
		//res.push_back(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2) + i));
		//res.push_back(x);
		std::cout<<"adress1 = "<<res.at(2)<<std::endl;
		std::cout<<"1WTF = "<<vect.at(res.at(1))<<std::endl;
		std::cout<<"1WTF = "<<vect.at(res.at(2))<<std::endl;
		//std::cout<<"1become1 = "<<vect.at(graph.head.at(possib.at(value)) + v2)<<std::endl;
		//std::cout<<"1become2 = "<<vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v2)) + i)<<std::endl;
	}
	else//equipe 2 prend deux arcs en plus
	{
		res.push_back(e1);
		//std::cout<<"2was1 = "<<vect.at(graph.head.at(possib.at(value)) + v1)<<std::endl;
		vect.at(graph.head.at(possib.at(value)) + v1) = e2;//On modifie l'arc de a vers b
		res.push_back(graph.head.at(possib.at(value)) + v1);
		std::cout<<"now e2 = "<<e2<<std::endl;
		for(i = 0; i < graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)).size(); i++)
		{
			if(possib.at(value) == graph.getSuccessors(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)).at(i))
			{
			//	std::cout<<"2was2 = "<<vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)) + i)<<std::endl;
				const int x = graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)) + i;
				res.push_back(x);
				vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)) + i) = e2;//On modifie l'arc de b vers a
				//std::cout<<"2i = "<<i<<std::endl;
				//res.push_back(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1) + i));
				std::cout<<"adress2 = "<<(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)) + i)<<std::endl;
				std::cout<<"after e2 = "<<e2<<std::endl;
				break;	
			}
		}
		//res.push_back(e1);
		//res.push_back(graph.head.at(possib.at(value)) + v1);
		//std::cout<<"2i = "<<i<<std::endl;
		//res.push_back(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1) + i));
		//res.push_back(x);
		std::cout<<"adress2 = "<<res.at(2)<<std::endl;
		std::cout<<"2WTF = "<<vect.at(res.at(1))<<std::endl;
		std::cout<<"2WTF = "<<vect.at(res.at(2))<<std::endl;
		//std::cout<<"2become1 = "<<vect.at(graph.head.at(possib.at(value)) + v1)<<std::endl;
		//std::cout<<"2become2 = "<<vect.at(graph.head.at(graph.getSucc().at(graph.head.at(possib.at(value)) + v1)) + i)<<std::endl;
	}
	//std::cout<<res.at(1)<<" "<<res.at(2)<<std::endl;

	if(vect.at(res.at(1)) != vect.at(res.at(2)))
	{
		std::cout<<"hey hey hey hey hey hey hey hey hey hey hey hey hey hey"<<std::endl;
	}

		//std::cout<<"hello"<<std::endl;
	//std::cout<<"move "<<vect.at(res.at(1))<<" "<<vect.at(res.at(2))<<std::endl;
	return res;//res.at(0) = equipe remplacé, res.at(1) = position remplacé, res.at(2) = position remplacé
}

void Solution::undo(std::vector<int> move){
//	std::cout<<"before "<<vect.at(move.at(1))<<" "<<vect.at(move.at(2))<<std::endl;
	vect.at(move.at(1)) = move.at(0);
	vect.at(move.at(2)) = move.at(0);
//	std::cout<<"after "<<vect.at(move.at(1))<<" "<<vect.at(move.at(2))<<std::endl;
}

bool Solution::isAdmissible() const{
	std::stack<int> lifo;
	std::map<int,bool> mark;
	std::vector<int> successors = graph.succ;
	std::map<int, bool>::iterator it;
	int firstNode,firstSuccIndex,workingNode;
	int indexInSolution = 0;
	for(int team = 0; team < graph.teamsCount; team++){
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
		//Parcours en profondeur si un sous-graphe pour l'équipe existe
		if(!mark.empty()){
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
	int workingNode,succ,nbrOfSucc,firstSuccIndex,succIndex,neighbourTeam,counter = 0,teamNumber = 0;
	
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
						if(teamNumber == graph.teamsCount - 1)
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
					if(counter > edgesPerTeam && teamNumber < graph.teamsCount - 1){
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

void Solution::dump() const {
	for (int edge=0; edge<vect.size(); edge++)
		std::cout << vect.at(edge) << " ";
	std::cout << std::endl;
}

Solution& Solution::operator=(const Solution& other) {
	if (&graph != &other.graph)
		throw new SolutionException(("incompatible solution assignment between "+graph.filename+" and "+other.graph.filename).c_str());
	vect = other.vect;
}
