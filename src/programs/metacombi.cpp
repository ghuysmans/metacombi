/**
 * @file
 * Main program
 */
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <signal.h>
#include "metaheuristics/Metaheuristic.h"
#include "metaheuristics/RandomStrategy.h"
#include "metaheuristics/LocalSearch.h"
#include "Graph.h"
#include "../config.h"
#include "Ui.h"

/**
 * Convert a string to lowercase
 * @bug UB with non-ASCII strings
 * @note taken from http://notfaq.wordpress.com/2007/08/04/cc-convert-string-to-upperlower-case/
 */
std::string lowercase(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

/**
 * @return -1 on invalid input
 * @note easier to implement than using atoi or strtol since we only want digits
 */
int get_positive(const char *s) {
	int acc = 0;
	while (*s && isdigit(*s)) {
		acc = acc*10 + *s-'0';
		s++;
	}
	return *s ? -1 : acc;
}

void dummy_handler(int) {
	//TODO set a flag
}

int main(int argc, char *argv[])
{
	Graph graph = Graph::load("testing-Graph.txt");
	LocalSearch search = LocalSearch(graph);
	Solution sol = search.getSolution();
	if(sol.isAdmissible())
		std::cout << "GOOD" << std::endl;
	
	//first argument, lowercase, if any
	std::string fl = argc>1 ? lowercase(argv[1]) : "";
	if (argc<=2) {
		if (fl=="" || fl=="--help" || fl=="-h" || fl=="/?" || fl=="/help") {
			std::cerr << "usage:\t" << argv[0] << " graph [''|solution|'='|'%'|color]" << std::endl;
			std::cerr << "where:\t" << "graph and solution are filenames" << std::endl;
			std::cerr << "\tcolor is an id in the default color palette" << std::endl;
			return 1;
		}
		else {
			try {
				Graph g = Graph::load(argv[1]);
				signal(SIGUSR1, dummy_handler);
				//TODO solve
				int c = 0;
				while (pause()) {
					for (int i=0; i<g.head.size(); i++)
						std::cout << c << " ";
					std::cout << std::endl;
					c++;
				}
				return 0;
			}
			catch (GraphException& e) {
				std::cerr << "error: " << e.what() << std::endl;
				return 2;
			}
		}
	}
	else {
		try {
			Graph g = Graph::load(argv[1]);
#ifdef USE_SDL
			Solution *s = NULL;
			int pattern = get_positive(argv[2]);
			if (pattern == -1) {
				std::string a2 = argv[2];
				if (a2 == "=")
					pattern = -1;
				else if (a2 == "%")
					pattern = -2;
				else
					s = new Solution(Solution::load(a2, g));
			}
			if (!s)
				s = new Solution(Solution::load(g, pattern));
			ui_main(g, s);
			delete s;
#else
			g.dump();
#endif //USE_SDL
			return 0;
		}
		catch (SolutionException& e) {
			std::cerr << "error: " << e.what() << std::endl;
			return 3;
		}
		catch (GraphException& e) {
			std::cerr << "error: " << e.what() << std::endl;
			return 2;
		}
	}
}
