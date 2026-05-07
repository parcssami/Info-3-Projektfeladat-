#include "konig.h"
#include <iostream>

using namespace std;

Bipartite_Graph Konig_Denes(const Bipartite_Graph& G, Bipartite_Graph M) {
    int n_A = G.NumVertex_A();
    int n_B = G.NumVertex_B();

    // 1. LEPES:
    // Maximalis parositas keszitese a mar megirt BFS-sel.
    vector<int> P = Modified_BFS(G, M);

    while (!P.empty()) {
        Improve_Matching(M, P);
        P = Modified_BFS(G, M);
    }

    vector<list<int>> G_A = G.GetA();
    vector<list<int>> M_A = M.GetA();
    vector<list<int>> M_B = M.GetB();

    vector<bool> visited_A(n_A + 1, false);
    vector<bool> visited_B(n_B + 1, false);

    vector<int> L;
    int eleje = 0;

    // 2. LEPES:
    // Szabad A-oldali csucsokbol indulunk.
    for (int a = 1; a <= n_A; a++) {
        if (M_A[a - 1].empty()) {
            visited_A[a] = true;
            L.push_back(a);
        }
    }

    // 3. LEPES:
    // Valtakozo bejaras.
    while (eleje < L.size()) {
        int aktiv_csucs = L[eleje];
        eleje++;

        if (aktiv_csucs > 0) {
            int a = aktiv_csucs;

            // A-bol B-be nem parositott eleken.
            for (int b : G_A[a - 1]) {
                if (!Is_Matching_Edge(M, a, b) && !visited_B[b]) {
                    visited_B[b] = true;
                    L.push_back(-b);
                }
            }
        }
        else {
            int b = -aktiv_csucs;

            // B-bol A-ba parositott eleken.
            for (int a : M_B[b - 1]) {
                if (!visited_A[a]) {
                    visited_A[a] = true;
                    L.push_back(a);
                }
            }
        }
    }

    // 4. LEPES:
    // Kőnig-keplet:
    // minimum lefogo csucshalmaz = (A \ Z_A) U (B metszet Z_B)

    Bipartite_Graph cover_graph(n_A, n_B);

    // A \ Z_A:
    // azok az A-oldali csucsok kerulnek be, amelyeket NEM ertunk el.
    for (int a = 1; a <= n_A; a++) {
        if (!visited_A[a]) {
            // Jeloles: A_a benne van a lefogo csucshalmazban.
            // Mivel a Bipartite_Graph csak eleket tud tarolni,
            // egy jelolo elet teszunk be.
            if (a <= n_B) {
                cover_graph.AddEdge(a, a);
            }
        }
    }

    // B metszet Z_B:
    // azok a B-oldali csucsok kerulnek be, amelyeket elertunk.
    for (int b = 1; b <= n_B; b++) {
        if (visited_B[b]) {
            // Jeloles: B_b benne van a lefogo csucshalmazban.
            if (b <= n_A) {
                cover_graph.AddEdge(b, b);
            }
        }
    }

    return cover_graph;
}

void Print_Konig_Cover(const Bipartite_Graph& cover_graph) {
    vector<list<int>> A = cover_graph.GetA();

    cout << "Minimalis lefogo csucshalmaz jelolo graf elei:" << endl;

    for (int a = 1; a <= cover_graph.NumVertex_A(); a++) {
        for (int b : A[a - 1]) {
            cout << "A" << a << " - B" << b << endl;
        }
    }
}