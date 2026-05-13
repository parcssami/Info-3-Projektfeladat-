#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

int main() {
    // Ugyanaz a nagy páros gráf, mint a saját algoritmusnál:
    // A oldal: 100 csúcs
    // B oldal: 120 csúcs
    // Minden A-csúcshoz 11 él tartozik
    // Összesen: 100 * 11 = 1100 él

    const int nA = 100;
    const int nB = 120;
    const int N = nA + nB;

    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    Graph g(N);

    // A_a csúcs Boost-indexe:
    // A1 -> 0
    // A2 -> 1
    // ...
    // A100 -> 99
    auto A = [](int a) {
        return a - 1;
    };

    // B_b csúcs Boost-indexe:
    // B1 -> 100
    // B2 -> 101
    // ...
    // B120 -> 219
    auto B = [nA](int b) {
        return nA + (b - 1);
    };

    int edge_count = 0;

    auto add_bip_edge = [&](int a, int b) {
        add_edge(A(a), B(b), g);
        edge_count++;
    };

    // Ugyanaz a determinisztikus élgenerálás:
    //
    // k = 0 esetén:
    // b = a
    // tehát A1-B1, A2-B2, ..., A100-B100 biztosan benne lesz.
    //
    // Emiatt biztosan létezik 100 elemű párosítás.
    for (int a = 1; a <= nA; a++) {
        for (int k = 0; k < 11; k++) {
            int b = ((a + 13 * k - 1) % nB) + 1;
            add_bip_edge(a, b);
        }
    }

    vector<Vertex> mate(N);

    edmonds_maximum_cardinality_matching(g, &mate[0]);

    int meret = boost::matching_size(g, &mate[0]);

    cout << "Boost Graph Library ellenorzes" << endl;
    cout << "A-oldali csucsok szama: " << nA << endl;
    cout << "B-oldali csucsok szama: " << nB << endl;
    cout << "Elek szama: " << edge_count << endl;
    cout << "Maximalis parositas elemszama: " << meret << endl;

    if (meret == nA) {
        cout << "Siker: a Boost szerint is minden A-oldali csucs parosithato." << endl;
    }
    else {
        cout << "Figyelem: a Boost szerint nem teljes az A-oldali parositas." << endl;
    }

    cout << endl;
    cout << "Boost altal talalt parositas:" << endl;

    for (int a = 1; a <= nA; a++) {
        int av = A(a);

        if (mate[av] != graph_traits<Graph>::null_vertex()) {
            int bv = mate[av];

            if (bv >= nA && bv < nA + nB) {
                int b = bv - nA + 1;
                cout << "A" << a << " - B" << b << endl;
            }
        }
    }

    return 0;
}