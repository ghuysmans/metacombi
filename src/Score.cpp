#include <vector>
#include <cmath>
#include "Score.h"
#include "Solution.h"
#include <math.h>/* pow */

Score::Score(const Solution& sol) {
	std::vector<int> comps = sol.getCompacities( sol.graph.subGraphs(sol.vect) );
	std::vector<int> dists = sol.getDistances();
	std::vector<int> dels = sol.getDelivered();
	tsList = std::vector<teamScore>(sol.graph.teamsCount);
	for(int i=0; i<tsList.size(); i++){
		tsList[i].dist = dists.at(i);
		tsList[i].Nflyers = dels.at(i);
		tsList[i].comp = comps.at(i);
	}
	//for(int i=0 ; i<tsList.size() ; i++)std::cout << "tsList.at("<<i<<").Nflyers = " << tsList.at(i).Nflyers<<std::endl;
	averageDistance = sol.graph.getAverageDistance();
	std::cout<<"averageDistance = "<<averageDistance<<std::endl;
	averageFlyers = sol.graph.getAverageFlyers();
	std::cout<<"averageFlyers = "<<averageFlyers<<std::endl;
}

void Score::getTsList()
{
	std::cout<<tsList.size()<<std::endl;
	for(int z = 0; z < tsList.size(); z++)
		std::cout<<z<<" distance = "<<tsList.at(z).dist<<" flyers = "<<tsList.at(z).Nflyers<<" comp = "<<tsList.at(z).comp<<std::endl;
}

int Score::toInt(int distancePower, int flyersPower, int compacityPower) const{
	// compute ErrLength
	float ErrLength = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		ErrLength += pow(std::abs(tsList.at(i).dist - averageDistance), distancePower);
	}
	//compute ErrFlyers
	float ErrFlyers = 0;
	for(int i=0 ; i<tsList.size() ; i++){
	//	std::cout<<"tsList.at(i).Nflyers = "<<(tsList.at(i).Nflyers- averageDistance)<<std::endl;
		ErrFlyers += pow(std::abs(tsList.at(i).Nflyers - averageFlyers), flyersPower);
	}
	//compute the maximum of compacities
	int maxCompacity = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		if(maxCompacity < tsList.at(i).comp) maxCompacity = tsList.at(i).comp;
	}
	//std::cout<<"eL = "<<ErrLength<<" eF = "<<ErrFlyers<<" mC = "<<maxCompacity<<std::endl;
	std::cout<<"toInt "<< (1+ErrLength)*(1+ErrFlyers)*pow( (1+maxCompacity), compacityPower) << std::endl;
	return (1+ErrLength)*(1+ErrFlyers)*pow( (1+maxCompacity), compacityPower);
}

int Score::toInt() const{
	return toInt(2, 2, 2);
}

bool Score::isBetterThan(int score1, int score2){
	return (score1/score2 < 1);
}

bool Score::operator <(const Score& right){ //this compares "this" and "right"
	int a = toInt();
	int b = right.toInt();
	return Score::isBetterThan(b,a) ;
}
