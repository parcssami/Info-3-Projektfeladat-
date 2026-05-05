#include "bfs.h"
#include <iostream>

using namespace std;

bool Is_A_Vertex(int v) {
    return v > 0;
}

bool Is_B_Vertex(int v) {
    return v < 0;
}

int Vertex_Id(int v) {
    if (v > 0) {
        return v;
    }
    else {
        return -v;
    }
}

bool Is_Invalid(int v) {
    return v == 0;
}

bool Is_Matching_Edge(const Bipartite_Graph& M, int a, int b) {
    list<int> neighbours = M.Neighbours_Of_A(a);

    for (int x : neighbours) {
        if (x == b) {
            return true;
        }
    }

    return false;
}

vector<int> Build_Path(
    int end_vertex,
    const vector<int>& previous_A,
    const vector<int>& previous_B
) {
    vector<int> reverse_path;

    int actual = end_vertex;

    while (!Is_Invalid(actual)) {
        reverse_path.push_back(actual);

        if (Is_A_Vertex(actual)) {
            int a = Vertex_Id(actual);
            actual = previous_A[a];
        }
        else {
            int b = Vertex_Id(actual);
            actual = previous_B[b];
        }
    }

    vector<int> path;

    for (int i = reverse_path.size() - 1; i >= 0; i--) {
        path.push_back(reverse_path[i]);
    }

    return path;
}

vector<int> Modified_BFS(const Bipartite_Graph& G, const Bipartite_Graph& M) {
    const int INF = 1000000000;

    int n_A = G.NumVertex_A();
    int n_B = G.NumVertex_B();

    vector<int> tav_A(n_A + 1, INF);
    vector<int> tav_B(n_B + 1, INF);

    vector<int> previous_A(n_A + 1, 0);
    vector<int> previous_B(n_B + 1, 0);

    vector<int> L;
    int eleje = 0;

    // Kezdes: minden szabad A-oldali csucs bekerul a sorba.
    for (int a = 1; a <= n_A; a++) {
        if (M.Neighbours_Of_A(a).empty()) {
            tav_A[a] = 0;
            L.push_back(a); // A_a csucs, pozitiv szammal jelolve
        }
    }

    while (eleje < L.size()) {
        int aktiv_csucs = L[eleje];
        eleje++;

        if (Is_A_Vertex(aktiv_csucs)) {
            int a = Vertex_Id(aktiv_csucs);

            list<int> neighbours = G.Neighbours_Of_A(a);

            for (int b : neighbours) {
                if (!Is_Matching_Edge(M, a, b) && tav_B[b] == INF) {
                    tav_B[b] = tav_A[a] + 1;

                    // B_b elozoje A_a
                    previous_B[b] = a;

                    // Ha B_b szabad, akkor javito utat talaltunk.
                    if (M.Neighbours_Of_B(b).empty()) {
                        return Build_Path(-b, previous_A, previous_B);
                    }

                    // B_b csucsot negativ szammal tesszuk be.
                    L.push_back(-b);
                }
            }
        }
        else {
            int b = Vertex_Id(aktiv_csucs);

            list<int> matching_neighbours = M.Neighbours_Of_B(b);

            for (int a : matching_neighbours) {
                if (tav_A[a] == INF) {
                    tav_A[a] = tav_B[b] + 1;

                    // A_a elozoje B_b
                    previous_A[a] = -b;

                    L.push_back(a);
                }
            }
        }
    }

    // Ha nincs javito ut, ures vectort adunk vissza.
    return vector<int>();
}

void Print_BFS_Path(const vector<int>& path) {
    if (path.empty()) {
        cout << "Nincs javito ut." << endl;
        return;
    }

    for (int i = 0; i < path.size(); i++) {
        if (path[i] > 0) {
            cout << "A" << path[i];
        }
        else {
            cout << "B" << -path[i];
        }

        if (i + 1 < path.size()) {
            cout << " -> ";
        }
    }

    cout << endl;
}