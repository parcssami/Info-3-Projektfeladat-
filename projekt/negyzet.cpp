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
    cout << "========================================" << endl;
    cout << "Konig_Denes nem negyzetes graf teszt" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // Nem négyzetes páros gráf:
    // A-oldal: 5 csúcs
    // B-oldal: 3 csúcs
    Bipartite_Graph G(5, 3);

    // Élek:
    // A1-B1
    // A2-B2
    // A4-B3
    G.AddEdge(1, 1);
    G.AddEdge(2, 2);
    G.AddEdge(4, 3);

    cout << "Eredeti graf:" << endl;
    cout << "A-oldali csucsok szama: " << G.NumVertex_A() << endl;
    cout << "B-oldali csucsok szama: " << G.NumVertex_B() << endl;
    cout << "Elek szama: " << G.NumEdge() << endl;
    cout << endl;

    Print_Graph(G);

    // Maximális párosítás előállítása a saját BFS-es algoritmussal
    Bipartite_Graph M(5, 3);

    vector<int> P = Modified_BFS(G, M);

    while (!P.empty()) {
        Improve_Matching(M, P);
        P = Modified_BFS(G, M);
    }

    cout << "Maximalis parositas:" << endl;
    Print_Matching(M);

    cout << "Maximalis parositas elemszama: " << M.NumEdge() << endl;
    cout << endl;

    // Kőnig Dénes futtatása
    Bipartite_Graph cover_graph = Konig_Denes(G, M);

    cout << "Konig_Denes altal visszaadott jelolo graf:" << endl;
    Print_Konig_Cover(cover_graph);

    cout << endl;

    cout << "Konig jelolo graf elemszama: " << cover_graph.NumEdge() << endl;
    cout << "Elvart minimalis lefogo csucshalmaz merete: " << M.NumEdge() << endl;
    cout << endl;

    cout << "Elvart minimalis lefogo csucshalmaz ebben a grafban:" << endl;
    cout << "A1, A2, A4" << endl;
    cout << endl;

    if (cover_graph.NumEdge() != M.NumEdge()) {
        cout << "HIBA IGAZOLVA: a cover_graph nem tudta jol jelolni az A4 csucsot," << endl;
        cout << "mert A4 indexe nagyobb, mint a B-oldal merete." << endl;
    }
    else {
        cout << "A teszt szerint ebben az esetben nem jott elo a hiba." << endl;
    }

    return 0;
}