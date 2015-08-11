//
// Created by av on 5/17/15.
//
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::ifstream;
using std::ofstream;


vector<int> polindroms(vector<int> &str) {
    int i=0,j,d,s,e,lLen,palLen=0;
    vector<int> res;
    res.reserve(str.size() * 2);
    while (i < str.size()) {
        if (i > palLen && str[i-palLen-1] == str[i]) {
            palLen += 2; i++; continue;
        }
        res.push_back(palLen);
        s = res.size()-2;
        e = s-palLen;
        bool b = true;
        for (j=s; j>e; j--) {
            d = j-e-1;
            if (res[j] == d) { palLen = d; b = false; break; }
            res.push_back(std::min(d, res[j]));
        }
        if (b) { palLen = 1; i++; }
    }
    res.push_back(palLen);
    lLen = res.size();
    s = lLen-2;
    e = s-(2*str.size()+1-lLen);
    for (i=s; i>e; i--) { d = i-e-1; res.push_back(std::min(d, res[i])); }
    return res;
}


int main()
{
    int n, m;


    std::ios_base::sync_with_stdio(false);
    ifstream in("cubes.in");
    ofstream out("cubes.out");

    in >> n >> m;
    vector<int> cubes(n);


    for (int i = 0; i < n; ++i)
    {
        in >> cubes[i];
    }

    const vector<int> &p = polindroms(cubes);
    for (int j = 0; j < p.size(); j+=2) {
        if (j == p[j])
        {
            out << cubes.size() - j / 2 << " ";
        }
    }
    return 0;
}
