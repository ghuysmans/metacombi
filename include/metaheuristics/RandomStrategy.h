#ifndef _RANDOMSTRATEGY_H
#define _RANDOMSTRATEGY_H

#include "Metaheuristic.h"

/**
 * Not really an heuristic. It provide one acceptable solution
 */
class RandomStrategy: public Metaheuristic{
	private:
		Graph graph;
	public:
		/**
		 * @param problemGraph The initial graph of the problem
		 */
		Solution getSolution();
};

#endif //_RANDOMSTRATEGY_H
