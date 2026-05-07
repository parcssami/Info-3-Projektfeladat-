#include "graph.h"
#include "bfs.h"
#include "konig.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void Print_Graph(const Bipartite_Graph& G) {
    vector<list<int>> A = G.GetA();

    cout << "Graf elei:" << endl;

    for (int a = 1; a <= G.NumVertex_A(); a++) {
        for (int b : A[a - 1]) {
            cout << "A" << a << " - B" << b << endl;
        }
    }

    cout << endl;
}



int main() {
    // Nagyobb tesztgráf:
    // A = {A1, A2, ..., A15}
    // B = {B1, B2, ..., B18}

    Bipartite_Graph G(15, 18);

    // A1 szomszédai
    G.AddEdge(1, 1);
    G.AddEdge(1, 4);
    G.AddEdge(1, 7);
    G.AddEdge(1, 10);

    // A2 szomszédai
    G.AddEdge(2, 2);
    G.AddEdge(2, 5);
    G.AddEdge(2, 8);
    G.AddEdge(2, 11);

    // A3 szomszédai
    G.AddEdge(3, 3);
    G.AddEdge(3, 6);
    G.AddEdge(3, 9);
    G.AddEdge(3, 12);

    // A4 szomszédai
    G.AddEdge(4, 1);
    G.AddEdge(4, 5);
    G.AddEdge(4, 13);
    G.AddEdge(4, 14);

    // A5 szomszédai
    G.AddEdge(5, 2);
    G.AddEdge(5, 6);
    G.AddEdge(5, 10);
    G.AddEdge(5, 15);

    // A6 szomszédai
    G.AddEdge(6, 3);
    G.AddEdge(6, 7);
    G.AddEdge(6, 11);
    G.AddEdge(6, 16);

    // A7 szomszédai
    G.AddEdge(7, 4);
    G.AddEdge(7, 8);
    G.AddEdge(7, 12);
    G.AddEdge(7, 17);

    // A8 szomszédai
    G.AddEdge(8, 5);
    G.AddEdge(8, 9);
    G.AddEdge(8, 13);
    G.AddEdge(8, 18);

    // A9 szomszédai
    G.AddEdge(9, 6);
    G.AddEdge(9, 10);
    G.AddEdge(9, 14);
    G.AddEdge(9, 1);

    // A10 szomszédai
    G.AddEdge(10, 7);
    G.AddEdge(10, 11);
    G.AddEdge(10, 15);
    G.AddEdge(10, 2);

    // A11 szomszédai
    G.AddEdge(11, 8);
    G.AddEdge(11, 12);
    G.AddEdge(11, 16);
    G.AddEdge(11, 3);

    // A12 szomszédai
    G.AddEdge(12, 9);
    G.AddEdge(12, 13);
    G.AddEdge(12, 17);
    G.AddEdge(12, 4);

    // A13 szomszédai
    G.AddEdge(13, 10);
    G.AddEdge(13, 14);
    G.AddEdge(13, 18);
    G.AddEdge(13, 5);

    // A14 szomszédai
    G.AddEdge(14, 11);
    G.AddEdge(14, 15);
    G.AddEdge(14, 1);
    G.AddEdge(14, 6);

    // A15 szomszédai
    G.AddEdge(15, 12);
    G.AddEdge(15, 16);
    G.AddEdge(15, 2);
    G.AddEdge(15, 7);

    cout << "Eredeti nagy paros graf:" << endl;
    Print_Graph(G);

    // Kezdetben üres párosítás
    Bipartite_Graph M(15, 18);

    vector<int> P = Modified_BFS(G, M);

    int lepes = 1;

    cout << "Parositas javitasa BFS-ekkel:" << endl;

    while (!P.empty()) {
        cout << lepes << ". javito ut: ";
        Print_BFS_Path(P);

        Improve_Matching(M, P);

        cout << "Aktualis parositas elemszama: " << M.NumEdge() << endl;
        cout << endl;

        P = Modified_BFS(G, M);
        lepes++;
    }

    cout << "Nincs tobb javito ut." << endl;
    cout << "Maximalis parositas elemszama: " << M.NumEdge() << endl;
    cout << endl;

    cout << "Maximalis parositas elei:" << endl;
    Print_Graph(M);

    cout << "Konig Denes algoritmus eredmenye:" << endl;

    Bipartite_Graph cover_graph = Konig_Denes(G, M);

    Print_Konig_Cover(cover_graph);

    return 0;
}