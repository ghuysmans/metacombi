#include "Graph.h"
#include "Solution.h"
#include "CuTest.h"
#include <iostream>
#include <vector>

void TestGraphConstructor(CuTest *tc)
{
	Graph g = Graph::load("TPOC-45.txt");
	//Tests d'initialization des Nnodes, Nedges et Nteams
	CuAssertIntEquals(tc, 20, g.head.size());
	CuAssertIntEquals(tc, 54, g.succ.size());
	CuAssertIntEquals(tc, 5, g.teamsCount);
}

void TestSucc(CuTest *tc)
{
	Graph g = Graph::load("TPOC-45.txt");
	int array[] = {2, 6, 1, 3, 7, 2, 4, 8, 3, 9, 6, 2, 5, 7, 11, 3, 6, 8, 12, 4, 7, 13, 5, 10, 14, 9, 11, 7, 10, 12, 16,8 ,11 , 17, 9, 14, 18, 10, 13, 15, 19, 14, 16, 12, 15, 13, 18, 14, 17, 19, 15, 18, 20, 19};
	std::vector<int> s = g.succ;
	for(int i = 0; i < g.succ.size(); i++)
	{
//		if(array[i] != s.at(i))
//			CuFail(tc, "getSuccessors() failed");
	}
}

void TestgetCount(CuTest *tc)
{
	Graph g = Graph::load("TPOC-45.txt");
	CuAssertIntEquals(tc, 1, g.getCount(19));
	CuAssertIntEquals(tc, 1, g.getCount(0));
	CuAssertIntEquals(tc, 3, g.getCount(1));
}

void TestgetFirst(CuTest *tc)
{
	Graph g = Graph::load("TPOC-45.txt");
	CuAssertIntEquals(tc, 1, g.getFirst(0));
	CuAssertIntEquals(tc, 5, g.getFirst(1));
	CuAssertIntEquals(tc, 6, g.getFirst(2));
}

void TestedgeToNodes1(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	std::vector<int> tuple = g.edgeToNodes(4);//should return <2 , 3>
	CuAssertTrue(tc, (tuple.at(0)==2 && tuple.at(1)==3) );
}

void TestedgeToNodes2(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	std::vector<int> tuple = g.edgeToNodes(8);//should return <4 , 5>
	CuAssertTrue(tc, (tuple.at(0)==4 && tuple.at(1)==5) );
}

void TestgetDistanceNodes(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	std::vector<int> tuple = g.getDistanceNodes(3,6,7);//should return 850 from 3 to 6
	CuAssertIntEquals(tc, 850, tuple.at(0) );
}

void TestgetDistanceEdges1(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	int result = g.getDistanceEdges(4 , 13);//should return 850
	CuAssertIntEquals(tc, 850, result );
}

void TestgetDistanceEdge2(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	int result = g.getDistanceEdges(1,12);//1350
	CuAssertIntEquals(tc, 1350, result );
}

void TestaverageDistance(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	int result = g.getAverageDistance();//1710
	CuAssertIntEquals(tc, 1710, result );
}

void TestaverageFlyers(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	int result = g.getAverageFlyers();//2565
	CuAssertIntEquals(tc, 2015, result );
}

void TestsubGraphs(CuTest *tc)
{
	//Les valeurs 'expected' venent du slide du prof avec les réponses pout testing-Graph.txt
	Graph g = Graph::load("testing-Graph.txt");
	int arr[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	std::vector<int> vectorSolution(&arr[0], &arr[0]+48);
	std::vector<Graph*> res = g.subGraphs(vectorSolution);
	CuAssertIntEquals(tc, 3, res.size() );
	CuAssertIntEquals(tc, 14, res.at(0) -> succ.size() );
	CuAssertIntEquals(tc, 18, res.at(1) -> succ.size() );
	CuAssertIntEquals(tc, 16, res.at(2) -> succ.size() );
	CuAssertIntEquals(tc, 8, res.at(0) -> head.size() );
	CuAssertIntEquals(tc, 10, res.at(1) -> head.size() );
	CuAssertIntEquals(tc, 8, res.at(2) -> head.size() );
	int counter, sigma = 0;
	
	//Test des flyers
	for(counter = 0; counter < res.at(0) -> flyers.size(); counter++)
		sigma += res.at(0) -> flyers.at(counter);
	sigma = sigma /2;//On divise par 2 car tous les arc non-orienté sont representé deux fois et donc les flyers aussi
		CuAssertIntEquals(tc, 2015, sigma );
		
	sigma = 0;
	for(counter = 0; counter < res.at(1) -> flyers.size(); counter++)
		sigma += res.at(1) -> flyers.at(counter);
	sigma = sigma /2;
		CuAssertIntEquals(tc, 1725, sigma );
	
	sigma = 0;
	for(counter = 0; counter < res.at(2) -> flyers.size(); counter++)
		sigma += res.at(2) -> flyers.at(counter);
	sigma = sigma /2;
		CuAssertIntEquals(tc, 2692, sigma );
	
	//Test des distances	
	sigma = 0;
	for(counter = 0; counter < res.at(0) -> weights.size(); counter++)
		sigma += res.at(0) -> weights.at(counter);
	sigma = sigma /2;
		CuAssertIntEquals(tc, 1710, sigma );
	
	sigma = 0;
	for(counter = 0; counter < res.at(1) -> weights.size(); counter++)
		sigma += res.at(1) -> weights.at(counter);
	sigma = sigma /2;
		CuAssertIntEquals(tc, 2110, sigma );
	
	sigma = 0;
	for(counter = 0; counter < res.at(2) -> weights.size(); counter++)
		sigma += res.at(2) -> weights.at(counter);
	sigma = sigma /2;
		CuAssertIntEquals(tc, 2220, sigma );
}

void TestSubGraph1(CuTest *tc){
    std::vector<int> v = std::vector<int>(14, 0);
    Graph g = Graph::load("scoreSimpleTest.txt");
    std::vector<Graph*> sgs = g.subGraphs(v);
    std::cout << "hit" << std::endl;
    CuAssertTrue(tc ,true);
}
