#include <vector>
#include "Score.h"

Score::Score(std::vector<struct teamScore> teamScoreList){
	tsList = teamScoreList;
}

bool Score::operator<(const Score right){
	/* the element on the left of the operator is 'this' and its a pointer.*/
	//TODO
}
