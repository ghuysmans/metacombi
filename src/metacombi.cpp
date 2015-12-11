/**
 * @file
 * Main program
 */
#include <iostream>
#include <string>
#include "metaheuristics/Metaheuristic.h"
#include "metaheuristics/RandomStrategy.h"
#include "Graph.h"
#include "../config.h"
#include "Ui.h"

/**
 * Main function
 */
int main(int argc, char *argv[])
{
	if (argc == 2) {
		try {
			Graph g = Graph::load(argv[1]);
#ifdef USE_SDL
			ui_main(g);
#else
			g.dump();
#endif //USE_SDL
			return 0;
		}
		catch (GraphException& e) {
			std::cerr << "error: " << e.what() << std::endl;
			return 2;
		}
	}
	else {
		std::cerr << "usage: " << argv[0] << " filename" << std::endl;
		return 1;
	}
}
