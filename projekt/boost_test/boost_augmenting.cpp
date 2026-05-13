#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

int main() {
    // Torzsfonok feladat:
    // 9 fiu: a, b, c, d, e, f, g, h, i
    // 10 lany: 1, 2, ..., 10

    const int nA = 9;
    const int nB = 10;
    const int N = nA + nB;

    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    Graph g(N);

    // A-oldali csucsok Boost-indexei:
    // A1 -> 0
    // A2 -> 1
    // ...
    // A9 -> 8
    auto A = [](int a) {
        return a - 1;
    };

    // B-oldali csucsok Boost-indexei:
    // B1 -> 9
    // B2 -> 10
    // ...
    // B10 -> 18
    auto B = [nA](int b) {
        return nA + (b - 1);
    };

    int edge_count = 0;

    auto add_bip_edge = [&](int a, int b) {
        add_edge(A(a), B(b), g);
        edge_count++;
    };

    // A1 = a fiu
    add_bip_edge(1, 1);
    add_bip_edge(1, 7);
    add_bip_edge(1, 9);
    add_bip_edge(1, 10);

    // A2 = b fiu
    add_bip_edge(2, 2);
    add_bip_edge(2, 5);

    // A3 = c fiu
    add_bip_edge(3, 3);
    add_bip_edge(3, 5);
    add_bip_edge(3, 6);
    add_bip_edge(3, 8);
    add_bip_edge(3, 9);

    // A4 = d fiu
    add_bip_edge(4, 4);
    add_bip_edge(4, 7);
    add_bip_edge(4, 8);
    add_bip_edge(4, 9);

    // A5 = e fiu
    add_bip_edge(5, 1);
    add_bip_edge(5, 4);
    add_bip_edge(5, 5);

    // A6 = f fiu
    add_bip_edge(6, 6);
    add_bip_edge(6, 7);
    add_bip_edge(6, 8);
    add_bip_edge(6, 10);

    // A7 = g fiu
    add_bip_edge(7, 2);
    add_bip_edge(7, 3);
    add_bip_edge(7, 4);

    // A8 = h fiu
    add_bip_edge(8, 2);
    add_bip_edge(8, 3);

    // A9 = i fiu
    add_bip_edge(9, 2);
    add_bip_edge(9, 3);

    vector<Vertex> mate(N);

    edmonds_maximum_cardinality_matching(g, &mate[0]);

    int meret = boost::matching_size(g, &mate[0]);

    cout << "Boost Graph Library ellenorzes" << endl;
    cout << "Fiuk szama: " << nA << endl;
    cout << "Lanyok szama: " << nB << endl;
    cout << "Elek szama: " << edge_count << endl;
    cout << "Maximalis parositas elemszama: " << meret << endl;

    if (meret == nA) {
        cout << "Siker: a Boost szerint mind a 9 fiu meghazasithato." << endl;
    }
    else {
        cout << "A Boost szerint nem lehet mind a 9 fiut meghazasitani." << endl;
    }

    cout << endl;
    cout << "Boost altal megkonstruált M parositas:" << endl;

    char fiu_nevek[10] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

    for (int a = 1; a <= nA; a++) {
        int av = A(a);

        if (mate[av] != graph_traits<Graph>::null_vertex()) {
            int bv = mate[av];

            if (bv >= nA && bv < nA + nB) {
                int b = bv - nA + 1;

                cout << fiu_nevek[a] << " fiu - "
                     << b << ". lany" << endl;
            }
        }
    }

    return 0;
}