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

    cout << "Aktualis M parositas elei:" << endl;

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

void Print_Augmenting_Edge_List(const vector<int>& P) {
    if (P.empty()) {
        cout << "Nincs javito ut, ezert nincs javito ellista." << endl;
        return;
    }

    cout << "Javito ellista:" << endl;

    for (int i = 0; i + 1 < P.size(); i++) {
        int first = P[i];
        int second = P[i + 1];

        int a;
        int b;

        if (first > 0 && second < 0) {
            // A -> B
            a = first;
            b = -second;
        }
        else if (first < 0 && second > 0) {
            // B -> A, de az el ugyanugy A-B alakban van
            a = second;
            b = -first;
        }
        else {
            continue;
        }

        cout << "A" << a << " - B" << b;

        if (i % 2 == 0) {
            cout << "   nem parositott el, ezt hozzaadjuk M-hez";
        }
        else {
            cout << "   parositott el, ezt toroljuk M-bol";
        }

        cout << endl;
    }

    cout << endl;
}

int main() {
    int n_A = 100;
    int n_B = 120;

    Bipartite_Graph G(n_A, n_B);

    // 100 * 11 = 1100 el
    // Minden A_a csucsnak 11 darab B-szomszedja lesz.
    // k = 0 eseten b = a, tehat A1-B1, ..., A100-B100 biztosan benne lesz.
    for (int a = 1; a <= n_A; a++) {
        for (int k = 0; k < 11; k++) {
            int b = ((a + 13 * k - 1) % n_B) + 1;
            G.AddEdge(a, b);
        }
    }

    cout << "Nagy paros graf letrehozva." << endl;
    cout << "A-oldali csucsok szama: " << n_A << endl;
    cout << "B-oldali csucsok szama: " << n_B << endl;
    cout << "Elek szama: " << G.NumEdge() << endl;
    cout << endl;

    // Nagy grafnal ezt inkabb ne ird ki, mert 1100 sor lenne.
    // Print_Graph(G);

    Bipartite_Graph M(n_A, n_B);

    cout << "Kezdeti M parositas:" << endl;
    Print_Matching(M);

    vector<int> P = Modified_BFS(G, M);

    int lepes = 1;

    while (!P.empty()) {
        cout << "==============================" << endl;
        cout << lepes << ". javitas" << endl;
        cout << "==============================" << endl;

        cout << "Javito ut csucslistaja:" << endl;
        Print_BFS_Path(P);
        cout << endl;

        Print_Augmenting_Edge_List(P);

        cout << "M a javitas elott:" << endl;
        Print_Matching(M);

        Improve_Matching(M, P);

        cout << "M a javitas utan:" << endl;
        Print_Matching(M);

        cout << "Aktualis parositas elemszama: " << M.NumEdge() << endl;
        cout << endl;

        P = Modified_BFS(G, M);
        lepes++;
    }

    cout << "==============================" << endl;
    cout << "VEGEREDMENY" << endl;
    cout << "==============================" << endl;

    cout << "Nincs tobb javito ut." << endl;
    cout << "Maximalis parositas elemszama: " << M.NumEdge() << endl;

    if (M.NumEdge() == n_A) {
        cout << "Siker: minden A-oldali csucs kapott part." << endl;
    }
    else {
        cout << "Nem teljes az A-oldali parositas." << endl;
    }

    cout << endl;

    cout << "Vegleges M javitott parositas:" << endl;
    Print_Matching(M);

    cout << "Konig Denes algoritmus futtatasa:" << endl;

    Bipartite_Graph cover_graph = Konig_Denes(G, M);

    cout << "Konig eredmeny jelolo graf elemszama: " << cover_graph.NumEdge() << endl;

    return 0;
}