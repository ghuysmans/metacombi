/**
 * Interface of metaheuristic
 */
class Metaheuristic{
	public:
		/** Get a solution applying this metaheuristic */
		virtual Solution getSolution() = 0;
};
