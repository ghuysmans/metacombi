/**
 * Not really an heuristic. It provide one acceptable solution
 */
#ifndef Metaheurisitc
#include "Metaheuristic.cpp"
#endif
class RandomStrategy : public Metaheuristic{
	private:
		Graph graph = Graph("lol.txt");//FIXME
	public:
		/**
		 * @param problemGraph The initial graph of the problem
		 */
		virtual Solution getSolution(){
			//TODO
		}
};
