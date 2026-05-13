#include "graph.h"
#include "bfs.h"
#include "konig.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void Print_Graph(const Bipartite_Graph& G) {
    vector<list<int>> A = G.GetA();

    cout << "Graf elei A-oldali szomszedsagi lista alapjan:" << endl;

    for (int a = 1; a <= G.NumVertex_A(); a++) {
        cout << "A" << a << ": ";

        for (int b : A[a - 1]) {
            cout << "B" << b << " ";
        }

        cout << endl;
    }

    cout << endl;
}

void Print_Matching(const Bipartite_Graph& M) {
    vector<list<int>> A = M.GetA();

    cout << "M parositas elei:" << endl;

    if (M.NumEdge() == 0) {
        cout << "M ures." << endl;
        cout << endl;
        return;
    }

    for (int a = 1; a <= M.NumVertex_A(); a++) {
        for (int b : A[a - 1]) {
            cout << "A" << a << " - B" << b << endl;
        }
    }

    cout << endl;
}

int main() {
    Bipartite_Graph G(9, 10);

    cout << "======================================" << endl;
    cout << "std::list::unique() hipotetikus hiba teszt" << endl;
    cout << "======================================" << endl;
    cout << endl;

    cout << "Elvart matematikai kulonbozo elek szama: 5" << endl;
    cout << "Ezek:" << endl;
    cout << "A1-B1" << endl;
    cout << "A1-B2" << endl;
    cout << "A1-B3" << endl;
    cout << "A2-B2" << endl;
    cout << "A3-B3" << endl;
    cout << endl;

    // Itt szandekosan NEM egymas utan adjuk hozza ugyanazokat az eleket.
    // Ha AddEdge csak list::unique()-ot hasznal rendezes nelkul,
    // akkor ezek az ismetlodesek bent maradhatnak.

    
    // A1 = a fiu
     G.AddEdge(1, 1);
     G.AddEdge(1, 7);
     G.AddEdge(1, 9);
     G.AddEdge(1, 1);
     G.AddEdge(1, 10);
     G.AddEdge(1, 1);

    // A2 = b fiu
     G.AddEdge(2, 2);
     G.AddEdge(2, 5);
     G.AddEdge(2, 2);

    // A3 = c fiu
     G.AddEdge(3, 3);
     G.AddEdge(3, 5);
     G.AddEdge(3, 6);
     G.AddEdge(3, 8);
     G.AddEdge(3, 9);

    // A4 = d fiu
     G.AddEdge(4, 4);
     G.AddEdge(4, 7);
     G.AddEdge(4, 8);
     G.AddEdge(4, 4);
     G.AddEdge(4, 9);
      G.AddEdge(4, 7);

    // A5 = e fiu
     G.AddEdge(5, 1);
     G.AddEdge(5, 4);
     G.AddEdge(5, 5);

    // A6 = f fiu
     G.AddEdge(6, 6);
     G.AddEdge(6, 7);
     G.AddEdge(6, 8);
     G.AddEdge(6, 10);

    // A7 = g fiu
     G.AddEdge(7, 2);
     G.AddEdge(7, 3);
     G.AddEdge(7, 4);

    // A8 = h fiu
     G.AddEdge(8, 2);
     G.AddEdge(8, 3);

    // A9 = i fiu
     G.AddEdge(9, 2);
     G.AddEdge(9, 3);

    cout << "Graph osztaly szerinti NumEdge(): " << G.NumEdge() << endl;
    cout << endl;

    Print_Graph(G);

    cout << "Ha a NumEdge() nagyobb, mint 8, akkor az ismetlodo elek bent maradtak." << endl;
    cout << "Ebben a konkret tesztben a kulonbozo elek valojaban:" << endl;
    cout << "A1-B1, A1-B2, A1-B3, A2-B2, A2-B3, A3-B3, A3-B1" << endl;
    cout << "Tehat matematikailag 7 kulonbozo el van." << endl;
    cout << endl;

    cout << "A tesztben szandekosan 11 AddEdge hivast hasznaltunk." << endl;
    cout << "Ha NumEdge() = 7, akkor a duplikatumok kiszurodtek." << endl;
    cout << "Ha NumEdge() = 11 vagy 7-nel nagyobb, akkor baj van." << endl;
    cout << endl;

    Bipartite_Graph M(9, 10);

    vector<int> P = Modified_BFS(G, M);

    int lepes = 1;

    cout << "Javito algoritmus futtatasa ezen a grafon:" << endl;

    while (!P.empty()) {
        cout << lepes << ". javito ut: ";
        Print_BFS_Path(P);

        Improve_Matching(M, P);

        cout << "Aktualis M elemszama: " << M.NumEdge() << endl;
        cout << endl;

        P = Modified_BFS(G, M);
        lepes++;
    }

    cout << "Nincs tobb javito ut." << endl;
    cout << "Vegleges maximalis parositas elemszama: " << M.NumEdge() << endl;
    cout << endl;

    Print_Matching(M);

    return 0;
}