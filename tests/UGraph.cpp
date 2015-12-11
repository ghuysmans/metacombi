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

void TestgetDistanceEdges(CuTest *tc)
{
	Graph g = Graph::load("compaGraph2.txt");
	int result = g.getDistanceEdges(4 , 13);//should return 850
	CuAssertIntEquals(tc, 850, result );
}
