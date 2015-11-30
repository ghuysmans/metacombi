#ifndef _METAHEURISTIC_H
#define _METAHEURISTIC_H

#include "Solution.h"

/**
 * Interface of metaheuristic
 */
class Metaheuristic{
	public:
		/** Get a solution applying this metaheuristic */
		virtual Solution getSolution() = 0;
};

#endif //_METAHEURISTIC_H
