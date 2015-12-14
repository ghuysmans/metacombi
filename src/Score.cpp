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

float Score::toFloat(int distancePower, int flyersPower, int compacityPower) const{
	// compute ErrLength
	float ErrLength = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		ErrLength += pow(std::abs(tsList.at(i).dist - averageDistance), distancePower);
	}
	//compute ErrFlyers
	float ErrFlyers = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		ErrFlyers += pow(std::abs(tsList.at(i).Nflyers - averageFlyers), flyersPower);
	}
	//compute the maximum of compacities
	int maxCompacity = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		if(maxCompacity < tsList.at(i).comp) maxCompacity = tsList.at(i).comp;
	}
	return (1+ErrLength)*(1+ErrFlyers)*pow( (1+maxCompacity), compacityPower);
}

float Score::toFloat() const{
	return toFloat(2, 2, 2);
}

bool Score::isBetterThan(float score1, float score2){
	return (score1/score2 < 1);
}

bool Score::operator <(const Score& right){ //this compares "this" and "right"
	float a = toFloat();
	float b = right.toFloat();
	return Score::isBetterThan(b,a) ;
}
