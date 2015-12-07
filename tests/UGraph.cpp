#include "Graph.h"
#include "Solution.h"
#include "CuTest.h"
#include <iostream>

void TestGraphConstructor(CuTest *tc)
{
	Graph g = Graph("../TPOC-45.txt");
	//Tests d'initialization des Nnodes, Nedges et Nteams
	CuAssertEquals(tc, 20, g.getNnodes());
	CuAssertEquals(tc, 54, g.getNedges());
	CuAssertEquals(tc, 5, g.getNteams());
}

void TestSucc(CuTest *tc)
{
	Graph g = Graph("../TPOC-45.txt");
	int array[] = {2, 6, 1, 3, 7, 2, 4, 8, 3, 9, 6, 2, 5, 7, 11, 3, 6, 8, 12, 4, 7, 13, 5, 10, 14, 9, 11, 7, 10, 12, 16,8 ,11 , 17, 9, 14, 18, 10, 13, 15, 19, 14, 16, 12, 15, 13, 18, 14, 17, 19, 15, 18, 20, 19};
	std::vector<int> s = g.getSuccessors();
	int i;
	for(i = 0; i < g.getNedges(); i++)
	{
		if(array[i] != s.at(i))
			CuFail(tc, "getSuccessors() failed");
	}
}

void TestgetCount(CuTest *tc)
{
	Graph g = Graph("../TPOC-45.txt");
	CuAssertEquals(tc, 1, g.getCount(19));
	CuAssertEquals(tc, 1, g.getCount(0));
	CuAssertEquals(tc, 3, g.getCount(1));
}