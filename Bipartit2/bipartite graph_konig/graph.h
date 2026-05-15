#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include<utility>
#include<iostream>
#include<set>

using namespace std;
class Bipartite_Graph {
private:
	vector<list<int>> component_A;
	vector<list<int>> component_B;
	list<pair<int, int>> edges;
public:
	Bipartite_Graph(int a, int b);
	vector<list<int>>GetA()const;
	vector<list<int>>GetB()const;
	void AddEdge(int a, int b);
	void DeleteEdge(int a, int b);
	int NumVertex() const;
	int NumVertex_A()const;
	int NumVertex_B() const;
	int NumEdge()const;
	bool AreConnected(int a, int b)const;
	void AddVertex_A();
	void AddVertex_B();
	list<int> Neighbours_Of_A(int a)const;
	list<int> Neighbours_Of_B(int b)const;




};


#endif#pragma once
