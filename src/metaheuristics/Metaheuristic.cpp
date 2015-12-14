#include "metaheuristics/Metaheuristic.h"

bool Metaheuristic::dump;

void Metaheuristic::dump_handler(int) {
	Metaheuristic::dump = true;
}

void Metaheuristic::do_dump(Solution& sol) {
	if (Metaheuristic::dump) {
		Metaheuristic::dump = false;
		sol.dump();
	}
}
