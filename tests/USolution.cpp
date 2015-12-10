#include "Graph.h"
#include "Solution.h"
#include "CuTest.h"
#include <iostream>

void TestIsAdmissible(CuTest *tc) {
	Graph graph = Graph::load("testing-Graph.txt");
	int arr[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<int> vectorSolution(&arr[0], &arr[0]+48);
	Solution sol = Solution(vectorSolution,graph);
	CuAssertTrue(tc, sol.isAdmissible());
	//arc 15 vers 16 appartient à l'équipe 2 
	int arr2[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,2,3,3};
	std::vector<int> vectorSolution2(&arr2[0], &arr2[0]+48);
	Solution sol2 = Solution(vectorSolution2,graph);
	CuAssertTrue(tc, !sol2.isAdmissible());
}
