//
// Created by av on 6/29/15.
//

#include <complex.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;
typedef complex<double> base;

int rev (int num, int lg_n) {
    int res = 0;
    for (int i=0; i<lg_n; ++i)
        if (num & (1<<i))
            res |= 1<<(lg_n-1-i);
    return res;
}

void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)  ++lg_n;

    for (int i=0; i<n; ++i)
        if (i < rev(i,lg_n))
            swap (a[i], a[rev(i,lg_n)]);

    for (int len=2; len<=n; len<<=1) {
        double ang = 2*M_PI/len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w (1);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i=0; i<n; ++i)
            a[i] /= n;
}

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
//    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].real() + 0.5);
}

const char alphabet [] = {'A','G','T','C'};

vector<int> translate (char symbol, string s){
    vector<int> res;
    for (int i = 0; i < s.size(); ++i)
    {
        res.push_back( s[i]==symbol? 1:0);
    }
    cout<<res.size()<<endl;
    return res;
}
int main()
{
    ifstream in("robots.in");
    ofstream out("robots.out");
    int n;
    string a;
    string b;
    in>>n>>a>>b;
    reverse(b.begin(),b.end());
//    int lg_n = 0;
//    while ((1 << lg_n) < n)  ++lg_n;
//    calc_rev(n,lg_n);
    vector<int> result;
    for (int i = 0; i < 4; ++i)
    {
       vector<int> res_tmp;
        vector<int> a_poly = translate(alphabet[i],a);
        vector<int> b_poly = translate(alphabet[i],b);
        cout<<a_poly.size()<<b_poly.size()<<endl;
        multiply(a_poly,b_poly,res_tmp);
        if(result.size()<res_tmp.size()){
            result.resize(res_tmp.size());
        }
        for (int j = 0; j < res_tmp.size(); ++j)
        {
            result[j]+=res_tmp[j];
        }
    }
    int index = -1;
    int value = -1;
    for (int i = 0; i < result.size(); ++i)
    {
        if(result[i]>value){
            index = i;
            value = result[i];
        }
    }
    out<<value<<' '<<index+1;

}