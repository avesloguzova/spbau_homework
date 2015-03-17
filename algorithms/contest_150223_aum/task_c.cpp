#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
const int INF =10000001;
using std::vector;
using  std::deque;
using std::pair;
using std::make_pair;
using std::set;

void dejkstra(int n, int s, int t, vector<vector< std::pair<int ,int> > > &edges, std::ofstream &out){

    vector<int> pre (n,-1);
    vector<int> dist (n, INF);
    dist[s] = 0;
    set<pair<int, int>, > q;
    q.insert(make_pair(dist[s], s));
    while (!q.empty())
    {
        int v = q.begin()->second;
        int distance = dist[v];
        q.erase(q.begin());
        for (size_t j = 0; j < edges[v].size(); ++j)
        {
            int u = edges[v][j].first;
            int w = edges[v][j].second;
            int curr_dist = distance + w;
            if (curr_dist < dist[u])
            {
                q.erase(make_pair(dist[u], u));
                dist[u] = curr_dist;
                pre[u] = v;
                q.insert(make_pair(curr_dist, u));
            }
        }
    }

    if (dist[t] == INF)
    {
        out << -1 << std::endl;
    }
    else
    {
        int v = t;
        vector<int>path;
        while (pre[v] != -1)
        {
            path.push_back(v);
            v = pre[v];
        }
        path.push_back(v);
        out << dist[t] << std::endl;
        for (auto it = path.rbegin(); it != path.rend(); ++it)
        {
            out << *it + 1 << " ";
        }
        out << std::endl;
    }
}
int main(){
    std::ifstream in("distance.in");
    std::ofstream out("distance.out");


    int n,m,s,t;
    in>>n>>m>>s>>t;
    vector<vector<std::pair<int,int> > >g(n);

    for (int j = 0; j < m; ++j) {
        int a,b,w;
        in>>a>>b>>w;
        g[--a].push_back(std::make_pair(--b, w));
		g[b].push_back(std::make_pair(a, w));
    }
    dejkstra(n, s-1, t-1, g,out);

}
/*
#include <set>
#include <stack>
#include <fstream>
#include <vector>
#define INF 100000000

using namespace std;

int main()
{
	int N, M;
	ifstream in("distance.in");
	ofstream out("distance.out");
	in >> N >> M;
	int s, f;
	in >> s >> f;
	vector<int> dist(N, INF);
	vector<int> pre(N, s - 1);
	vector<vector<pair<int, int>>> edges(N);

	int a, b, w;
	for (int i = 0; i < M; ++i)
	{
		in >> a >> b >> w;
		edges[a - 1].push_back(make_pair(b - 1, w));
		edges[b - 1].push_back(make_pair(a - 1, w));
	}

	dist[s - 1] = 0;
	set<pair<int, int>> q;
	q.insert(make_pair(dist[s - 1], s - 1));
	while (!q.empty())
	{
		int v = q.begin()->second;
		int distance = dist[v];
		q.erase(q.begin());
		for (size_t j = 0; j < edges[v].size(); ++j)
		{
			int u = edges[v][j].first;
			int w = edges[v][j].second;
			int curr_dist = distance + w;
			if (curr_dist < dist[u])
			{
				q.erase(make_pair(dist[u], u));
				dist[u] = curr_dist;
				pre[u] = v;
				q.insert(make_pair(curr_dist, u));
			}
		}
	}

	if (dist[f - 1] == INF)
	{
		out << -1 << endl;
	}
	else
	{
		int v = f - 1;
		vector<int>path;
		while (pre[v] != v)
		{
			path.push_back(v);
			v = pre[v];
		}
		path.push_back(v);
		out << dist[f - 1] << endl;
		for (auto it = path.rbegin(); it != path.rend(); ++it)
		{
			out << *it + 1 << " ";
		}
		out << endl;
	}
	return 0;
}
 */