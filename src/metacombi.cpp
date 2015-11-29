/**
 * @file
 * Main program
 */
#include <iostream>
#include <string>
#include "metaheuristics/Metaheuristic.h"
#include "metaheuristics/RandomStrategy.h"

/**
 * Some doc for a simple class.
 */
class MyClass {
	public:
		/**
		 * @param message What you want to display
		 */
		MyClass(std::string message) {
			std::cout << message << std::endl;
		}
		/**
		 * @return sum of operands
		 */
		int op(int a, int b) {
			return a+b;
		}
};

/**
 * Main function
 * @note This doc is completely useless.
 */
int main(int argc, char *argv[])
{
	MyClass m("hello");
	std::cout << m.op(1, 2) << std::endl;
	return 0;
}
