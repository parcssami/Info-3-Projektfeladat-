#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

int main() {
    // Ugyanaz a nagyobb páros gráf:
    // A = {A1, ..., A15}
    // B = {B1, ..., B18}
    //
    // Boostban egy közös csúcshalmazt használunk:
    // A1..A15  -> 0..14
    // B1..B18  -> 15..32

    const int nA = 15;
    const int nB = 18;
    const int N = nA + nB;

    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    Graph g(N);

    auto A = [](int a) {
        return a - 1;
    };

    auto B = [nA](int b) {
        return nA + (b - 1);
    };

    auto add_bip_edge = [&](int a, int b) {
        add_edge(A(a), B(b), g);
    };

    // A1 szomszédai
    add_bip_edge(1, 1);
    add_bip_edge(1, 4);
    add_bip_edge(1, 7);
    add_bip_edge(1, 10);

    // A2 szomszédai
    add_bip_edge(2, 2);
    add_bip_edge(2, 5);
    add_bip_edge(2, 8);
    add_bip_edge(2, 11);

    // A3 szomszédai
    add_bip_edge(3, 3);
    add_bip_edge(3, 6);
    add_bip_edge(3, 9);
    add_bip_edge(3, 12);

    // A4 szomszédai
    add_bip_edge(4, 1);
    add_bip_edge(4, 5);
    add_bip_edge(4, 13);
    add_bip_edge(4, 14);

    // A5 szomszédai
    add_bip_edge(5, 2);
    add_bip_edge(5, 6);
    add_bip_edge(5, 10);
    add_bip_edge(5, 15);

    // A6 szomszédai
    add_bip_edge(6, 3);
    add_bip_edge(6, 7);
    add_bip_edge(6, 11);
    add_bip_edge(6, 16);

    // A7 szomszédai
    add_bip_edge(7, 4);
    add_bip_edge(7, 8);
    add_bip_edge(7, 12);
    add_bip_edge(7, 17);

    // A8 szomszédai
    add_bip_edge(8, 5);
    add_bip_edge(8, 9);
    add_bip_edge(8, 13);
    add_bip_edge(8, 18);

    // A9 szomszédai
    add_bip_edge(9, 6);
    add_bip_edge(9, 10);
    add_bip_edge(9, 14);
    add_bip_edge(9, 1);

    // A10 szomszédai
    add_bip_edge(10, 7);
    add_bip_edge(10, 11);
    add_bip_edge(10, 15);
    add_bip_edge(10, 2);

    // A11 szomszédai
    add_bip_edge(11, 8);
    add_bip_edge(11, 12);
    add_bip_edge(11, 16);
    add_bip_edge(11, 3);

    // A12 szomszédai
    add_bip_edge(12, 9);
    add_bip_edge(12, 13);
    add_bip_edge(12, 17);
    add_bip_edge(12, 4);

    // A13 szomszédai
    add_bip_edge(13, 10);
    add_bip_edge(13, 14);
    add_bip_edge(13, 18);
    add_bip_edge(13, 5);

    // A14 szomszédai
    add_bip_edge(14, 11);
    add_bip_edge(14, 15);
    add_bip_edge(14, 1);
    add_bip_edge(14, 6);

    // A15 szomszédai
    add_bip_edge(15, 12);
    add_bip_edge(15, 16);
    add_bip_edge(15, 2);
    add_bip_edge(15, 7);

    vector<Vertex> mate(N);

   edmonds_maximum_cardinality_matching(g, &mate[0]);

int meret = boost::matching_size(g, &mate[0]);

cout << "Boost Graph Library ellenorzes" << endl;
cout << "Maximalis parositas elemszama: " << meret << endl;
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