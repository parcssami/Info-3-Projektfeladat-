#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include <vector>

using namespace std;

// Pozitiv szam: A-oldali csucs.
// Negativ szam: B-oldali csucs.
// Pelda:
// {1, -2, 3, -4}
// jelentese:
// A1 -> B2 -> A3 -> B4

vector<int> Modified_BFS(const Bipartite_Graph& G, const Bipartite_Graph& M);

bool Is_Matching_Edge(const Bipartite_Graph& M, int a, int b);

void Improve_Matching(Bipartite_Graph& M, const vector<int>& path);

void Maximum_Matching(Bipartite_Graph& G, Bipartite_Graph& M);

void Print_BFS_Path(const vector<int>& path);

#endif