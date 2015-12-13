/**
 * @file
 * Monitoring tool (UNIX-specific)
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/signal.h>
#include <Graph.h>
#include <Solution.h>
#include "../config.h"
#include "Ui.h"
#include <sstream>

pid_t pid = 0;

int fail(const char *f) {
	int n = errno;
	perror(f);
	return n;
}

void run(char *filename, FILE*& suboutput) {
	int fd[2];
	if (pipe(fd) == -1)
		exit(fail("pipe"));
	if (!(suboutput = fdopen(fd[0], "r")))
		exit(fail("fdopen"));
	if (pid = fork())
		//parent
		close(fd[1]); //close the write end
	else if (!pid) {
		//child
		close(fd[0]); //close the read end
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(fail("dup2"));
		execl("./metacombi", "./metacombi", filename, (char*)NULL);
		exit(fail("execl"));
	}
	else
		exit(fail("fork"));
}

void kill_sub() {
	if (pid && kill(pid, SIGINT)==-1)
		perror("kill(SIGINT)");
}

void handler(int) {
	exit(1);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "usage:\t" << argv[0] << " graph" << std::endl;
		std::cerr << "where:\t" << "graph is a filename" << std::endl;
		return 1;
	}
	else {
		try {
			//we load it first so we won't have to handle subprocess errors
			Graph g = Graph::load(argv[1]);
			FILE *f;
			char buffer[8192];
			run(argv[1], f);
			atexit(kill_sub);
			signal(SIGINT, handler);
			sleep(1);
			do {
				std::cout << "-";
				int c = getchar();
				if (c == '\n')
					c = getchar();
				if (feof(stdin) || c=='q')
					break;
				if (kill(pid, SIGUSR1) == -1)
					exit(fail("kill(SIGUSR1)"));
				if (!fgets(buffer, sizeof(buffer), f)) {
					std::cerr << "fgets failed" << std::endl;
					break;
				}
#ifdef USE_SDL
				std::stringstream ss;
				ss << buffer;
				Solution sol = Solution::load(ss, g);
				ui_main(g, &sol);
#else
				std::cout << buffer << std::endl;
#endif //USE_SDL
			} while (1);
			return 0;
		}
		catch (GraphException& e) {
			std::cerr << "monitor error: " << e.what() << std::endl;
			return 2;
		}
		catch (SolutionException& e) {
			std::cerr << "monitor error: " << e.what() << std::endl;
			return 2;
		}
	}
}
