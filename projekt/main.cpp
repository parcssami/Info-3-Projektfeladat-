#include "graph.h"
#include "bfs.h"
#include "konig.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
    int n_A = 645;
    int n_B = 355;

    Bipartite_Graph G(n_A, n_B);

    /*
        Nem triviális nagy páros gráf generálása.

        A-oldal: 645 csúcs
        B-oldal: 355 csúcs

        Minden A-csúcshoz 20 B-szomszédet adunk.
        Összes él: 645 * 20 = 12900.

        A képlet:
        b = ((73 * (a - 1) + 37 * k) % n_B) + 1

        Miért jó?
        - Nem az egyszerű A1-B1, A2-B2, ... diagonált adja.
        - A 73 és a 355 relatív prímek.
        - Ezért az első 355 A-csúcs k = 0 esetén permutálva fedi le a B-oldalt.
        - Tehát garantáltan van 355 elemű párosítás.
    */

    for (int a = 1; a <= n_A; a++) {
        for (int k = 0; k < 20; k++) {
            int b = ((73 * (a - 1) + 37 * k) % n_B) + 1;
            G.AddEdge(a, b);
        }
    }

    cout << "Nagy nem trivialis paros graf letrehozva." << endl;
    cout << "A-oldali csucsok szama: " << n_A << endl;
    cout << "B-oldali csucsok szama: " << n_B << endl;
    cout << "Osszes csucs: " << n_A + n_B << endl;
    cout << "Elvart elek szama: " << n_A * 20 << endl;
    cout << "Graph osztaly NumEdge() erteke: " << G.NumEdge() << endl;
    cout << endl;

    Bipartite_Graph M(n_A, n_B);

    vector<int> P = Modified_BFS(G, M);

    int lepes = 1;

    cout << "Javito algoritmus futtatasa..." << endl;
    cout << endl;

    while (!P.empty()) {
        Improve_Matching(M, P);

        if (lepes <= 10 || lepes % 25 == 0) {
            cout << lepes << ". javitas utan M elemszama: "
                 << M.NumEdge() << endl;
        }

        P = Modified_BFS(G, M);
        lepes++;
    }

    cout << endl;
    cout << "Nincs tobb javito ut." << endl;
    cout << "Vegleges maximalis parositas elemszama: "
         << M.NumEdge() << endl;

    cout << "Elmeleti maximum: " << n_B << endl;

    if (M.NumEdge() == n_B) {
        cout << "SIKER: minden B-oldali csucs parositva lett." << endl;
    }
    else {
        cout << "FIGYELEM: nem sikerult minden B-oldali csucsot parositani." << endl;
    }

    cout << endl;

    cout << "Vegleges M parositas elso 40 eleme:" << endl;

    vector<list<int>> M_A = M.GetA();

    int printed = 0;

    for (int a = 1; a <= M.NumVertex_A(); a++) {
        for (int b : M_A[a - 1]) {
            if (printed < 355) {
                cout << "A" << a << " - B" << b << endl;
                printed++;
            }
        }
    }

    cout << endl;
    cout << "Kiirt parositasi elek szama: " << printed << endl;
    cout << "A teljes M merete: " << M.NumEdge() << endl;

    cout << endl;
    cout << "Konig Denes algoritmus futtatasa..." << endl;

    Bipartite_Graph cover_graph = Konig_Denes(G, M);

    cout << "Konig jelolograf elemszama: "
         << cover_graph.NumEdge() << endl;

    return 0;
}