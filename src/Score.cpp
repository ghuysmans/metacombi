#include <vector>
#include "Score.h"

Score::Score(std::vector<struct teamScore> teamScoreList): tsList(teamScoreList){
}

bool Score::operator<(const Score right){ //this compares "this" and "right"
	//TODO
}
