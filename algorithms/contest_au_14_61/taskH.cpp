//
// Created by av on 6/13/15.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>



const int MAX = 1299743;

int main() {
    std::ifstream in("primes.in");
    std::ofstream out("primes.out");

    int items[10001];
    int n;
    in >> n;
    for(int i = 0; i < n; i++) {
        in >> items[i];
    }

    std::vector<char> p(MAX + 2, true);
    p[0] = p[1] = false;
    for (int i = 2; i * i <= MAX; ++i) {
        if (p[i]) {
            if (i * 1ll * i <= MAX) {
                for (int j = i * i; j <= MAX; j += i) {
                    p[j] = false;
                }
            }
        }
    }
    unsigned long T = 100001;
    std::vector<int> vec(T);
    int j = 1;
    for(int i = 0; i < MAX; i++){
        if(p[i]) {
            vec[j++] = i;
        }
    }
    for(int i = 0; i < n; i++) {
        out << vec[items[i]] << " ";
    }
    return 0;
}