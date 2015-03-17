#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>

using std::vector;
using  std::deque;
using std::min;
const int INF = INT32_MAX/2 -1001;

void floid(vector<vector<int> > &d, int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    int n1 =1;
}

int main() {
    std::ifstream in("diameter.in");
    std::ofstream out("diameter.out");


    int n;
    in >> n ;
    vector<vector<int> > d(n);

    for (int j = 0; j < n; ++j) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            int w;
            in >> w;
            v[i] = w == -1 ? INF : w;
        }
        d[j] = v;
    }
    floid(d, n);
    int diam = -1;
    int rad = INF;
    for (int i = 0; i < n; ++i) {
        int e = d[i][0];
        for (int j = 0; j < n; ++j) {
            if(d[i][j]>diam){
                diam=d[i][j];
            }
            if (d[i][j]>e){
                e = d[i][j];
            }
        }
        if(rad>e){
            rad = e;
        }

    }
    out<<diam<<std::endl;
    out<<rad<<std::endl;

}