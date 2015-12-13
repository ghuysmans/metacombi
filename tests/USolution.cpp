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
	int array[] = {1,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,3,3,2,3,1,3,2,1,1,3,1,1,3,3,3,3,3,3,3,3,3,3,3};
	Solution sol = Solution(vectorSolution,graph); 
	int i, res = 0;
	std::vector<int> v = sol.move();
	for(i = 0; i < sol.getVector().size(); i++)
	{
		if(sol.getVector().at(i) != array[i])
			res++;
	}
	CuAssertIntEquals(tc, 2, res);
}

void TestInitSolution(CuTest *tc) {
	Graph graph = Graph::load("testing-Graph.txt");
	std::vector<int> vectorSolution(48,0);
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

/* unknown error void Testscore1(CuTest *tc){
	struct Score::teamScore ts1 = { .dist=250, .Nflyers=280, .comp=80};
	struct Score::teamScore ts2 = { .dist=265, .Nflyers=280, .comp=80};
	struct Score::teamScore ts3 = { .dist=240, .Nflyers=280, .comp=80};
	struct Score::teamScore ts4 = { .dist=245, .Nflyers=280, .comp=80};
	std::vector<struct Score::teamScore> list1 = std::vector<struct Score::teamScore>(4);
	list1[0] = ts1;
	list1[1] = ts2;
	list1[2] = ts3;
	list1[3] = ts4;
	Score::teamScore ts5 = { .dist=280, .Nflyers=280, .comp=80};
	Score::teamScore ts6 = { .dist=240, .Nflyers=280, .comp=80};
	Score::teamScore ts7 = { .dist=235, .Nflyers=280, .comp=80};
	Score::teamScore ts8 = { .dist=245, .Nflyers=280, .comp=80};
	std::vector<struct Score::teamScore> list2 = std::vector<Score::teamScore>(4);
	list2[0] = ts5;
	list2[1] = ts6;
	list2[2] = ts7;
	list2[3] = ts8;
	int average;
	for(int i=0 ; i<list1.size() ; i++) average += list1.at(i).dist;
	average = average/list1.size();
	Score score1 = Score(list1 , average , 280);
	Score score2 = Score(list2 , average , 280);
	CuAssertTrue(tc, score2<score1);
}*/
