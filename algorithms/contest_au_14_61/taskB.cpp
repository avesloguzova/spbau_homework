//
// Created by av on 5/19/15.
//

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::vector;


const int INF = 99999;
std::string s;
vector<vector<int>> ans;


bool is_pair(char l, char r) {
    return l == '(' && r == ')' || l == '{' && r == '}' || l == '[' && r == ']';
}

int answ(  long l,   long r) {
    if (l > r) {
        return 0;
    }
    if (l == r) {
        return 1;
    }
    return ans[l][r];
}

void count(  long l,   long r) {
    ans[l][r] = 1 + answ(l + 1, r);
    for (  long j = l + 1; j <= r; ++j) {
        if (is_pair(s[l], s[j])) {
            if (answ(l + 1, j - 1) + answ(j + 1, r) < ans[l][r]) {
                ans[l][r] = answ(l + 1, j - 1) + answ(j + 1, r);
            }
        }
    }
}

void print(std::ofstream &out,   long l,   long r) {
    if (l > r) {
        return;
    }
    if (ans[l][r] == 1 + answ(l + 1, r)) {
        print(out, l + 1, r);
        return;
    }
    for (  long j = l + 1; j <= r; ++j) {
        if (is_pair(s[l], s[j]) && (answ(l + 1, j - 1) + answ(j + 1, r) == ans[l][r])) {
            out << s[l];
            print(out, l + 1, j - 1);
            out << s[j];
            print(out, j + 1, r);
            return;
        }
    }
}

int main() {
    std::ifstream in("erase.in");
    std::ofstream out("erase.out");
    in >> s;
    long n = s.length();
    ans = vector<vector<int>>(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
    }
    for (  long l = n - 1; l >= 0; --l) {
        for (  long r = l + 1; r < n; ++r) {
            count(l, r);
        }
    }

    print(out, 0, n - 1);
    return 0;
}
