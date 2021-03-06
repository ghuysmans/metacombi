#include "Graph.h"
#include "Solution.h"
#include "CuTest.h"
#include <iostream>
#include <vector>
#include "Score.h"

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

void TestMove(CuTest *tc) {
	Graph graph = Graph::load("testing-Graph.txt");
	int arr[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<int> vectorSolution(&arr[0], &arr[0]+48);
	
	for(int z = 0; z < vectorSolution.size(); z++)
		std::cout<<vectorSolution.at(z)<<" ";
	std::cout<<std::endl;
	
	int array[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	Solution sol = Solution(vectorSolution,graph);
	int i, res = 0;
	std::vector<int> v = sol.move();
	
	for(int z = 0; z < sol.getVector().size(); z++)
		std::cout<<sol.getVector().at(z)<<" ";
	std::cout<<std::endl;
	std::cout<<v.at(1)<<" "<<v.at(2)<<std::endl;
	
	if(sol.getVector().at(v.at(1)) != sol.getVector().at(v.at(2)))
		std::cout<<"bad "<<sol.getVector().at(v.at(1))<<" "<<sol.getVector().at(v.at(2))<<std::endl;
		
	for(i = 0; i < sol.getVector().size(); i++)
	{
		if(sol.getVector().at(i) != array[i])
			res++;
	}
	
	CuAssertIntEquals(tc, 2, res);
}

void TestInitSolution(CuTest *tc) {
	Graph graph = Graph::load("testing-Graph.txt");
	std::vector<int> vectorSolution(48,-1);
	Solution sol = Solution(vectorSolution,graph);
	sol.initSolution();
	CuAssertTrue(tc, sol.isAdmissible());
}

void TestCompacitySimple(CuTest *tc){
	std::vector<int> v = std::vector<int>(14, 0);
	Graph g = Graph::load("compaGraph2.txt");
	Solution s = Solution(v, g);
	int result = s.getCompacity( g );
	CuAssertIntEquals(tc, 1350, result);
}

void TestCompacityBig(CuTest *tc){
	Graph graph = Graph::load("testing-Graph.txt");
	int arr[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<int> v(&arr[0], &arr[0]+48);
	for(int i=0 ; i<v.size() ; i++){
		v[i] = v.at(i)-1;
	}
	Solution sol = Solution(v,graph);
	std::cout << "HIT before subgraph" << std::endl;
	std::vector<Graph*> sgs = graph.subGraphs(v);
	std::cout << "HIT after subgraph" << std::endl;
	std::vector<int> comps = sol.getCompacities(sgs);
	CuAssertIntEquals(tc, 1350, comps.at(0));
}

void TestSubGraph1(CuTest *tc){
	std::vector<int> v = std::vector<int>(14, 0);
	Graph g = Graph::load("scoreSimpleTest.txt");
	std::vector<Graph*> sgs = g.subGraphs(v);
	CuAssertTrue(tc ,true);
}

void Testscore1(CuTest *tc){
	std::vector<int> v = std::vector<int>(14, 0);
	Graph g = Graph::load("scoreSimpleTest.txt");
	Solution s = Solution(v, g);
	std::vector<int> v2 = std::vector<int>(14, 1);
	Solution s2 = Solution(v2, g);
	CuAssertTrue(tc, !( Score(s2)<Score(s)) );
}
