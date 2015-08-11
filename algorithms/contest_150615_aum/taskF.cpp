//
// Created by av on 6/29/15.
//
#include <fstream>
#include <algorithm>

using namespace std;

int gcd (int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
int find(int a,int n){
    int x, y;
    int g = gcd (a, n, x, y);
    if (g != 1)
        return 0;
    else {
        return (x % n + n) % n;
    }
}
 int main(){
    ifstream in("inv2.in");
    ofstream out("inv2.out");
     int n;
     in>>n;
     vector<int> values(n);
     int x = 0;
     int y = 0;
     double max_value = 0;
     for(int i = 1;i<n;i++){
         if(!values[i]){
            int v = find(i,n);
             values[i]=v;
             values[v]=i;
             if(abs(v-i)>max_value||max_value==0){
                 x = i;
                 y = v;
                 max_value = abs(v-i);
             }
         }
     }
     out<<x<<' '<<y<<endl;
 }
