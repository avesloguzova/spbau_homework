#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>

const long INF =1000;
using std::vector;
using  std::deque;



void bfs(long n, long start,long t,vector<vector<long> >&edges,vector<long>&barons,std::ofstream& out){

    vector<long> p (n,-1);
    vector<long> d (n, INF);
//    d[s] = 0;
//    p[s] = -1;
    vector<char> u (n);
//    for (long i=0; i<n; ++i) {
//        long v = -1;
//        for (long j=0; j<n; ++j)
//            if (!u[j] && (v == -1 || d[j] < d[v]))
//                v = j;
//        if (d[v] == INF)
//            break;
//        u[v] = true;
//
//        for (size_t j=0; j<g[v].size(); ++j) {
//            long to = g[v][j];
//            long len = barons[v]==barons[to]? 0:1;
//            if (d[v] + len < d[to]) {
//                d[to] = d[v] + len;
//                p[to] = v;
//            }
//        }
//    }
    // Инициализация
    deque<long> q;
    q.push_back(start);
    d[start] = 0;
    // Главный цикл
    while (!q.empty())
    {
        // Достаем вершину
        long v = q.front();
        q.pop_front();
        u[v] = true;
        // Смотрим на всех ее соседей
        for (long i = 0; i < (long)edges[v].size(); ++i)
        {
            // Если можно улучшить известное расстояние
            long len = barons[v]==barons[edges[v][i]]? 0:1;
            if (d[edges[v][i]] > d[v] + len)
            {
                // То улучшаем его и добавляем вершину в дек
                d[edges[v][i]] = d[v] + len;
                p[edges[v][i]] = v;

                // Если ребро бесплатное, то в начало
                if (len == 0)
                {
                    q.push_front(edges[v][i]);
                }
                    // Иначе - в конец
                else
                {
                    q.push_back(edges[v][i]);
                }
            }
        }
    }
    if (!u[t])
        out << "impossible";
    else {
        vector<long> path;
        for (long v=t; v!=-1; v=p[v])
            path.push_back (v);

        long len = (long) path.size();
        out<<d[t]<<" "<<len<<std::endl;
        for (long i=path.size()-1; i>=0; --i)
            out << path[i] + 1 << " ";
    }
}
int main(){
    std::ifstream in("island.in");
    std::ofstream out("island.out");


    long n,m;
    in>>n>>m;
    vector <long> barons(n);
    vector<vector<long> >g(n);
    for (long i = 0; i < n; ++i) {
        long baron;
        in>>baron;
        barons[i]=baron;
    }
    for (long j = 0; j < m; ++j) {
        long a,b;
        in>>a>>b;
        g[--a].push_back(--b);
        g[b].push_back(a);

    }
    bfs(n, 0, n-1, g,barons,out);

}