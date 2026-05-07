#ifndef KONIG_H
#define KONIG_H

#include "graph.h"
#include "bfs.h"
#include <vector>

using namespace std;

// Kőnig Dénes-algoritmus.
// Bemenet:
// G = paros graf
// M = kezdeti parositas, lehet ures is
//
// A fuggveny eloszor a Modified_BFS segitsegevel
// maximalis parositast keszit M-bol.
//
// Ezutan kiszamolja a minimalis lefogo csucshalmazt.
//
// Visszateres:
// vector<int>, ahol:
// pozitiv szam = A-oldali csucs
// negativ szam = B-oldali csucs
//
// Pelda:
// {1, 3, -2}
// jelentese:
// A1, A3, B2

Bipartite_Graph Konig_Denes(const Bipartite_Graph& G, Bipartite_Graph M);

void Print_Konig_Cover(const Bipartite_Graph& cover_graph);

#endif