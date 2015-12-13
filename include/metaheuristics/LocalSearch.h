#ifndef _LOCALSEARCH_H
#define _LOCALSEARCH_H

#include "Metaheuristic.h"

class LocalSearch: public Metaheuristic{
	private:
		const Graph& graph;
	public:
		/**
		 * @param problemGraph The initial graph of the problem
		 */
		LocalSearch(const Graph& problemGraph);

		Solution getSolution();
};

#endif //_LOCALSEARCH_H
