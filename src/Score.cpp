#include <vector>
#include "Score.h"
#include "Solution.h"
#include <math.h>/* pow */

Score::Score(const Solution& sol) {
	std::vector<int> comps = sol.getCompacities( sol.graph.subGraphs(sol.vect) );
	std::vector<int> dists = sol.getDistances();
	std::vector<int> dels = sol.getDelivered();
	for(int i=0; i<tsList.size(); i++){
		tsList.at(i).dist = dists.at(i);
		tsList.at(i).Nflyers = dels.at(i);
		tsList.at(i).comp = comps.at(i);
	}
	averageDistance = sol.graph.getAverageDistance();
	averageDistance = sol.graph.getAverageFlyers();
}

int Score::toInt(int distancePower, int flyersPower, int compacityPower) const{
	// compute ErrLength
	int ErrLength = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		ErrLength += pow(tsList.at(i).dist , distancePower);
	}
	//compute ErrFlyers
	int ErrFlyers = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		ErrFlyers += pow(tsList.at(i).Nflyers , flyersPower);
	}
	//compute the maximum of compacities
	int maxCompacity = 0;
	for(int i=0 ; i<tsList.size() ; i++){
		if(maxCompacity < tsList.at(i).comp) maxCompacity = tsList.at(i).comp;
	}
	return (1+ErrLength)*(1+ErrFlyers)*pow( (1+maxCompacity), compacityPower);
}

int Score::toInt() const{
	return toInt(2, 2, 2);
}

bool Score::operator <(const Score& right){ //this compares "this" and "right"
	int a = toInt();
	int b = right.toInt();
	return (b/a) < 1 ;
}
