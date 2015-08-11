#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using std::vector;
using  std::deque;
using std::pair;
using std::make_pair;
using std::stack;
using std::endl;
int c;
int t;

vector<bool> visited;
vector<int> enter;
vector<int> ret;
vector<pair<int, int>> order;
stack<pair<int, int>> s;

void change_color(int v, int u, int c,vector<vector<pair<int, int>>>& g);

int get_color(int u, int v,vector<vector<pair<int, int>>>& g) {
    for (int i = 0; i < g[u].size(); ++i)
    {
        if (g[u][i].first == v)
        {
            return g[u][i].second;
        }
    }
}


void dfs(int v, int parent,vector<vector<pair<int, int>>>& g)
{
    visited[v] = true;
    enter[v] = ret[v] = t++;
    for (int i = 0; i < g[v].size(); ++i)
    {
        int u = g[v][i].first;
        if (u == parent)
        {
            continue;
        }
        if (!visited[u])
        {
            s.push(make_pair(v, u));
            dfs(u, v,g);
            if (ret[u] >= enter[v])
            {
                ++c;
                while (!(s.top().first == v && s.top().second == u))
                {
                    change_color(s.top().first, s.top().second, c,g);
                    s.pop();
                }
                change_color(v, u, c,g);
                s.pop();
            }
            if (ret[u] < ret[v])
            {
                ret[v] = ret[u];
            }
        }
        else
        {
            if (enter[u] < enter[v])
            {
                s.push(make_pair(v, u));
            }
            if (ret[v] > ret[u])
            {
                ret[v] = ret[u];
            }
        }
    }
}

void change_color(int v, int u, int c,vector<vector<pair<int, int>>> &g) {
    for (int i = 0; i < g[v].size(); ++i)
    {
        if (g[v][i].first == u)
        {
            g[v][i].second = c;
            break;
        }
    }
    for (int i = 0; i < g[u].size(); ++i)
    {
        if (g[u][i].first == v)
        {
            g[u][i].second = c;
            break;
        }
    }
}

int main() {
    std::ifstream in("biconv.in");
    std::ofstream out("biconv.out");

    int n, m;
    in >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    visited.resize(n, false);
    enter.resize(n, 0);
    ret.resize(n, 0);
    order.resize(m);
    int a, b;
    for (int i = 0; i < m; ++i)
    {
        in >> a >> b;
        g[a - 1].push_back(make_pair((b - 1), -1));
        g[b - 1].push_back(make_pair((a - 1), -1));
        order[i] = make_pair(a - 1, b - 1);
    }

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            t = 0;
            dfs(i, -1,g);
        }
        else
        {
            continue;
        }
    }
    out << c << endl;
    for (int i = 0 ; i < m; ++i)
    {
        auto e = order[i];
        out << get_color(e.first, e.second,g) << " ";
    }
    out << endl;
    return 0;
}