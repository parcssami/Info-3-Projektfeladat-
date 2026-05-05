#include "konig.h"
#include <iostream>

using namespace std;

vector<int> Konig_Denes(const Bipartite_Graph& G, Bipartite_Graph M) {
    int n_A = G.NumVertex_A();
    int n_B = G.NumVertex_B();

    // 1. LEPES:
    // Maximalis parositas keszitese a mar megirt BFS-sel
    vector<int> P = Modified_BFS(G, M);

    while (!P.empty()) {
        Improve_Matching(M, P);
        P = Modified_BFS(G, M);
    }

    // Itt M mar maximalis parositas.

    vector<list<int>> G_A = G.GetA();
    vector<list<int>> M_A = M.GetA();
    vector<list<int>> M_B = M.GetB();

    vector<bool> visited_A(n_A + 1, false);
    vector<bool> visited_B(n_B + 1, false);

    // BFS-sor queue nelkul
    vector<int> L;
    int eleje = 0;

    // 2. LEPES:
    // Indulas az osszes szabad A-oldali csucsbol
    for (int a = 1; a <= n_A; a++) {
        if (M_A[a - 1].empty()) {
            visited_A[a] = true;
            L.push_back(a);
        }
    }

    // 3. LEPES:
    // Valtakozo bejaras
    //
    // A-bol B-be: nem parositott elen
    // B-bol A-ba: parositott elen
    while (eleje < L.size()) {
        int aktiv_csucs = L[eleje];
        eleje++;

        if (aktiv_csucs > 0) {
            // A-oldali csucs
            int a = aktiv_csucs;

            for (int b : G_A[a - 1]) {
                if (!Is_Matching_Edge(M, a, b) && !visited_B[b]) {
                    visited_B[b] = true;
                    L.push_back(-b);
                }
            }
        }
        else {
            // B-oldali csucs
            int b = -aktiv_csucs;

            for (int a : M_B[b - 1]) {
                if (!visited_A[a]) {
                    visited_A[a] = true;
                    L.push_back(a);
                }
            }
        }
    }

    // 4. LEPES:
    // Kőnig Dénes-keplet:
    //
    // minimum lefogo csucshalmaz = (A \ Z_A) U (B metszet Z_B)
    //
    // visited_A = Z_A
    // visited_B = Z_B

    vector<int> cover;

    // A \ Z_A
    for (int a = 1; a <= n_A; a++) {
        if (!visited_A[a]) {
            cover.push_back(a);
        }
    }

    // B metszet Z_B
    for (int b = 1; b <= n_B; b++) {
        if (visited_B[b]) {
            cover.push_back(-b);
        }
    }

    return cover;
}

void Print_Konig_Cover(const vector<int>& cover) {
    if (cover.empty()) {
        cout << "A minimalis lefogo csucshalmaz ures." << endl;
        return;
    }

    cout << "Minimalis lefogo csucshalmaz: ";

    for (int i = 0; i < cover.size(); i++) {
        if (cover[i] > 0) {
            cout << "A" << cover[i];
        }
        else {
            cout << "B" << -cover[i];
        }

        if (i + 1 < cover.size()) {
            cout << ", ";
        }
    }

    cout << endl;
}