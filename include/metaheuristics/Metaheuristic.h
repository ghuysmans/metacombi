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
		static void do_dump(Solution& sol);
	private:
		static bool dump;
		static void dump_handler(int);
		friend int main(int argc, char *argv[]);
};

#endif //_METAHEURISTIC_H
