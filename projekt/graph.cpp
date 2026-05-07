#include "graph.h"
#include <vector>
#include <list>


Bipartite_Graph::Bipartite_Graph(int a, int b){
	component_A.resize(a);
	component_B.resize(b);
}

vector<list<int>> Bipartite_Graph::GetA()const{
	return component_A;
}

vector<list<int>> Bipartite_Graph::GetB()const{
	return component_B;
}

void Bipartite_Graph::AddEdge(int a, int b){
	if (component_A.size() >= a && a > 0 && component_B.size() >= b && b > 0) {
		component_A[a - 1].push_back(b);
		component_B[b - 1].push_back(a);
		component_A[a - 1].unique();
		component_B[b - 1].unique();
		edges.push_back(make_pair(a, b));
		edges.unique();
	}
	else {
		cout << "Error! Invlaid vertex number(s) at add vertex function!" << endl;
	}
}

void Bipartite_Graph::DeleteEdge(int a, int b){
	if (component_A.size() >= a && a > 0 && component_B.size() >= b && b > 0) {
		component_A[a - 1].remove(b);
		component_B[b - 1].remove(a);
		edges.remove(make_pair(a, b));
	}
	else {
		cout << "Error! Invalid vertex number(s) at delete edge function!" << endl;
	}

}

int Bipartite_Graph::NumVertex() const{
	return component_A.size() + component_B.size();
}

int Bipartite_Graph::NumVertex_A() const{
	return component_A.size();
}

int Bipartite_Graph::NumVertex_B() const{
	return component_B.size();
}

int Bipartite_Graph::NumEdge() const{
	return edges.size();
}

bool Bipartite_Graph::AreConnected(int a, int b) const {
	if (a < 0 || b < 0 || a >= component_A.size() || b >= component_B.size()) {
		return false;
	}

	for (const pair<int, int>& idx : edges) {
		if (idx == make_pair(a,b)) {
			return true;
		}
	}
	return false;
}

void Bipartite_Graph::AddVertex_A() {
	component_A.push_back(list<int>());
}

void Bipartite_Graph::AddVertex_B(){
	component_B.push_back(list<int>());
}

void Bipartite_Graph::RemoveVertex_A(int a){
	if (a >= component_A.size()) {
		cout << "Error! Invalid vertex number at remove vertex function!" << endl;
	}
	else {
		vector<list<int>>::iterator it = component_A.begin() + a - 1 ;
		component_A.erase(it);
		for (list<int>& idx : component_B) {
			idx.remove(a);
		}
		for (pair<int, int>& idx : edges) {
			if (idx.first == a) {
				edges.remove(idx);
			}
		}
	}
}

void Bipartite_Graph::RemoveVertex_B(int b) {
	if (b >= component_B.size()) {
		cout << "Error! Invalid vertex number at remove vertex function!" << endl;
	}
	else {
		vector<list<int>>::iterator it = component_B.begin() + b - 1;
		component_B.erase(it);
		for (list<int>& idx : component_A) {
			idx.remove(b);
		}
		for (pair<int, int>& idx : edges) {
			if (idx.second == b) {
				edges.remove(idx);
			}
		}
	}
}



list<int> Bipartite_Graph::Neighbours_Of_A(int a)const {
	if (a >= component_A.size()) {
		cout << "Error! invalid vertex number at neighbours function!" << endl;
		return list<int>();
	}
	else {
		return component_A[a - 1];
	}
}

list<int> Bipartite_Graph::Neighbours_Of_B(int b)const {
	if (b >= component_B.size()) {
		cout << "Error! invalid vertex number at neighbours function!" << endl;
		return list<int>();
	}
	else {
		return component_B[b - 1];
	}
}
Bipartite_Graph Maximal_Pairing(Bipartite_Graph& input) {
	Bipartite_Graph M(input.GetA().size(), input.GetB().size());

	vector<bool> a (input.GetA().size(), false);					//kezdetben senkit nem használunk
	vector<bool> b (input.GetB().size(), false);

	int idx = 1;													//csúcsokon iterálunk M-ben (?)
	for (list<int>& it_1 : input.GetA()) {							//it_2 idx-edik csúcs egy szomszédja 
		for (int it_2 : it_1) {
			if (!a[idx-1] && !b[idx-1]) {
				M.GetA()[idx-1].push_back(it_2);					
				M.GetB()[idx-1].push_back(idx);

				a[idx-1] = true;									//megváltoznak használtra
				b[idx-1] = true;

				break;
			}
		}
		++idx;
	}
	vector<list<int>> L;											//A-M = L ez lesz!
	int idx_2 = 0;													//A és M első csúcsából indulunk
	for (list<int> it_1 : M.GetA()) {								
		if (it_1.empty()) {											//Ha M egy csúcsa üres = nincs benne a párosításban:
			L[idx_2] = input.GetA()[idx_2];							//bemásoljuk az egész szomszédlistát A ból
		}
		else {									
			L[idx_2] = {};											//Ha benne van, beteszünk egy helytartót, hogy az indexelés helyessége maradjon.
		}
		++idx_2;
	}


	return M;
}


