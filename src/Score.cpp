#include <vector>
#include "Score.h"
#include <math.h>/* pow */

Score::Score(std::vector<struct teamScore> teamScoreList, int averageDistance, int averageFlyers):
	tsList(teamScoreList),
	averageDistance(averageDistance),
	averageFlyers(averageFlyers){
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

bool Score::isBetterThan(int score1, int score2){
	return (score1/score2 > 1);
}

bool Score::operator <(const Score& right){ //this compares "this" and "right"
	int a = toInt();
	int b = right.toInt();
	return Score::isBetterThan(b,a) ;
}
