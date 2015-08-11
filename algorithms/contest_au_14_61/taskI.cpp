//
// Created by av on 6/13/15.
//

#include <iostream>
#include <algorithm>
#include <fstream>


using namespace std;


#define ERROR (-42)

const int INF = 1000000000;
const int MAX = 1299743;


long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

long long egcd(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    long long d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int repl(int a, int b) {
    int s, t;
    if (egcd(a, b, s, t) > 1) {
        return -1;
    }
    return (b + s % b) % b;
}

long long discrete_log(long long a, long long b, long long n) {
    pair<long long, int> pairs[100000];
    long long del = 1;
    long long count;
    for (long long i = 0; i * i < n; i++) {
        pairs[i] = make_pair(del, (int) i);
        del = (del * a) % n;
        count = i;
    }
    count++;
    b %= n;
    del = repl(del, n);
    sort(pairs, pairs + count);
    for (long long i = 0; i <= count; i++) {
        auto j = lower_bound(pairs, pairs + count, make_pair(b, ERROR));
        if (!(j == pairs + count || j->first != b)) {
            return (i * count) + j->second;
        } else {
            // decr now
            b = (b * del) % n;
        }
    }
    return ERROR;
}

long long gcd_discrete_log(long long pr, long long b, long long n) {

    long long gd;
    while ((gd = gcd(pr, n)) > 1) {
        n /= gd;
    }

    long long res;
    long long an = 1;
    long long a = 1ll;
    for (long long i = 0; a <= n; i++) {
        if (an == b) {
            return i;
        }
        an = (an * pr) % n;
        res = i;
        a = a << (i + 1);
    }

    if (b % (n / n)) {
        return ERROR;
    }
    long long r = discrete_log(pr, b * repl(an, n), n);
    return r == ERROR ? ERROR : r + (++res);
}


int main() {
  
    ifstream in("logging.in");
    ofstream out("logging.out");

    long long n, p, b;
    bool st = false;
    while(in >> n) {
        in >> p >> b;
        long long ans = gcd_discrete_log(p, b, n);
        if (st) {
            out << "\n";
        }
        st = true;
        if (ans == ERROR) {
            out << "no solution";
        } else {
            out << ans;
        }
    } ;
    return 0;
}
