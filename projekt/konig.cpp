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
int marker_A_size;

if (n_A > n_B) {
    marker_A_size = n_A;
}
else {
    marker_A_size = n_B;
}

// Jelölőgráf:
// B1 marker: A-oldali lefogó csúcs
// B2 marker: B-oldali lefogó csúcs
Bipartite_Graph cover_graph(marker_A_size, 2);

// A \ Z_A:
// azok az A-oldali csúcsok kerülnek be,
// amelyeket NEM értünk el.
for (int a = 1; a <= n_A; a++) {
    if (!visited_A[a]) {
        // A_a benne van a lefogó csúcshalmazban.
        // Ezt cover_graph-ban A_a - B1 jelöli.
        cover_graph.AddEdge(a, 1);
    }
}

// B ∩ Z_B:
// azok a B-oldali csúcsok kerülnek be,
// amelyeket elértünk.
for (int b = 1; b <= n_B; b++) {
    if (visited_B[b]) {
        // B_b benne van a lefogó csúcshalmazban.
        // Ezt cover_graph-ban A_b - B2 jelöli.
        cover_graph.AddEdge(b, 2);
    }
}

return cover_graph;   
}

void Print_Konig_Cover(const Bipartite_Graph& cover_graph) {
    vector<list<int>> A = cover_graph.GetA();

    cout << "Minimalis lefogo csucshalmaz:" << endl;

    bool ures = true;

    for (int i = 1; i <= cover_graph.NumVertex_A(); i++) {
        for (int marker : A[i - 1]) {
            if (marker == 1) {
                cout << "A" << i << endl;
                ures = false;
            }
            else if (marker == 2) {
                cout << "B" << i << endl;
                ures = false;
            }
        }
    }

    if (ures) {
        cout << "Ures lefogo csucshalmaz." << endl;
    }

    cout << endl;
}