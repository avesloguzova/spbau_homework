#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> p;

int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    if (rand() & 1)
        swap(a, b);
    if (a != b)
        p[a] = b;
}

int dsu(int n, int m, vector<pair<int, pair<int, int>>> &graph) {
    int cost = 0;
    sort(graph.begin(), graph.end());
    p.resize(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;
    for (int i = 0; i < m; ++i) {
        int a = graph[i].second.first, b = graph[i].second.second, w = graph[i].first;
        if (dsu_get(a) != dsu_get(b)) {
            cost += w;
            dsu_unite(a, b);
        }
    }
    return cost;
}

int main() {
    ifstream in("spantree2.in");
    ofstream out("spantree2.out");
    int n, m;
    in >> n >> m;
    p.resize(n);
    vector<pair<int, pair<int, int>>> graph(m);
    int cost = 0;

    for (int i = 0; i < m; ++i) {
        int v, u, w;
        in >> v >> u >> w;
        graph[i] = make_pair(w, make_pair(v - 1, u - 1));
    }

    out << dsu(n, m, graph) << endl;
    return 0;
}