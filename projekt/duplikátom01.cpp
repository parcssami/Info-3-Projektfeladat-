#include "graph.h"
#include "bfs.h"
#include "konig.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void Print_Graph_Short(const Bipartite_Graph& G) {
    vector<list<int>> A = G.GetA();

    cout << "Szomszedsagi listak roviden:" << endl;

    for (int a = 1; a <= G.NumVertex_A(); a++) {
        cout << "A" << a << ": ";

        int db = 0;

        for (int b : A[a - 1]) {
            cout << "B" << b << " ";
            db++;
        }

        cout << "   darab a listaban: " << db << endl;
    }

    cout << endl;
}

void Print_Matching(const Bipartite_Graph& M) {
    vector<list<int>> A = M.GetA();

    cout << "M parositas elei:" << endl;

    for (int a = 1; a <= M.NumVertex_A(); a++) {
        for (int b : A[a - 1]) {
            cout << "A" << a << " - B" << b << endl;
        }
    }

    cout << endl;
}

int Count_Unique_Edges_Manually(const Bipartite_Graph& G) {
    int n_A = G.NumVertex_A();
    int n_B = G.NumVertex_B();

    vector<list<int>> A = G.GetA();

    vector<vector<bool>> seen(n_A + 1, vector<bool>(n_B + 1, false));

    int unique_edges = 0;

    for (int a = 1; a <= n_A; a++) {
        for (int b : A[a - 1]) {
            if (!seen[a][b]) {
                seen[a][b] = true;
                unique_edges++;
            }
        }
    }

    return unique_edges;
}

bool Contains_Duplicate_Edges(const Bipartite_Graph& G) {
    int n_A = G.NumVertex_A();
    int n_B = G.NumVertex_B();

    vector<list<int>> A = G.GetA();

    vector<vector<bool>> seen(n_A + 1, vector<bool>(n_B + 1, false));

    for (int a = 1; a <= n_A; a++) {
        for (int b : A[a - 1]) {
            if (seen[a][b]) {
                return true;
            }

            seen[a][b] = true;
        }
    }

    return false;
}

void Generate_Duplicate_Stress_Graph(Bipartite_Graph& G, int n_A, int n_B) {
    /*
        Cel:
        - Matematikailag minden A-csucshoz 6 kulonbozo B-szomszed tartozzon.
        - Ez osszesen 30 * 6 = 180 kulonbozo el.
        - De minden elet 3-szor adunk hozza, nem egymas mellett.
        - Igy 30 * 6 * 3 = 540 AddEdge-hivas tortenik.

        Fontos:
        k = 0 eseten b = a, tehat A1-B1, A2-B2, ..., A30-B30 biztosan bekerul.
        Emiatt biztosan van 30 elemu parositas.
    */

    for (int a = 1; a <= n_A; a++) {
        vector<int> neighbours;

        for (int k = 0; k < 6; k++) {
            int b = ((a + 7 * k - 1) % n_B) + 1;
            neighbours.push_back(b);
        }

        // Elso kor: minden el egyszer
        for (int k = 0; k < 6; k++) {
            G.AddEdge(a, neighbours[k]);
        }

        // Masodik kor: ugyanazok az elek mas sorrendben
        // Itt a duplikatumok nem kozvetlenul az eredeti utan jonnek.
        for (int k = 3; k < 6; k++) {
            G.AddEdge(a, neighbours[k]);
        }

        for (int k = 0; k < 3; k++) {
            G.AddEdge(a, neighbours[k]);
        }

        // Harmadik kor: megint mas sorrendben
        G.AddEdge(a, neighbours[1]);
        G.AddEdge(a, neighbours[4]);
        G.AddEdge(a, neighbours[2]);
        G.AddEdge(a, neighbours[5]);
        G.AddEdge(a, neighbours[0]);
        G.AddEdge(a, neighbours[3]);
    }
}

int main() {
    int n_A = 30;
    int n_B = 35;

    Bipartite_Graph G(n_A, n_B);

    Generate_Duplicate_Stress_Graph(G, n_A, n_B);

    cout << "Nagy duplikatumos paros graf teszt" << endl;
    cout << "A-oldali csucsok szama: " << n_A << endl;
    cout << "B-oldali csucsok szama: " << n_B << endl;
    cout << endl;

    cout << "Elvart kulonbozo elek szama matematikailag: " << n_A * 6 << endl;
    cout << "AddEdge hivasok szama elvileg: " << n_A * 6 * 3 << endl;
    cout << "Graph osztaly NumEdge() erteke: " << G.NumEdge() << endl;
    cout << "Kezzel szamolt kulonbozo elek szama: " << Count_Unique_Edges_Manually(G) << endl;

    if (Contains_Duplicate_Edges(G)) {
        cout << "FIGYELEM: a szomszedsagi listakban vannak duplikalt elek." << endl;
    }
    else {
        cout << "Nincs duplikalt el a szomszedsagi listakban." << endl;
    }

    cout << endl;

    // Ha nagyon sok sort adna, ezt kikommentelheted.
    Print_Graph_Short(G);

    Bipartite_Graph M(n_A, n_B);

    vector<int> P = Modified_BFS(G, M);

    int lepes = 1;

    cout << "Javito algoritmus futtatasa:" << endl;

    while (!P.empty()) {
        cout << lepes << ". javito ut hossza: " << P.size() << endl;

        Improve_Matching(M, P);

        cout << "Aktualis M elemszama: " << M.NumEdge() << endl;
        cout << endl;

        P = Modified_BFS(G, M);
        lepes++;
    }

    cout << "Nincs tobb javito ut." << endl;
    cout << "Vegleges maximalis parositas elemszama: " << M.NumEdge() << endl;

    if (M.NumEdge() == n_A) {
        cout << "SIKER: a duplikatumok ellenere minden A-oldali csucs kapott part." << endl;
    }
    else {
        cout << "HIBA VAGY KORLAT: nem sikerult minden A-oldali csucsot parositani." << endl;
    }

    cout << endl;

    cout << "Vegleges M parositas:" << endl;
    Print_Matching(M);

    return 0;
}