#include <vector>
#include <iostream>
#include <fstream>

using namespace std;



struct fenwick_tree {
    fenwick_tree(unsigned long long n)
            : data(ceil2(n) + 1) { }

    unsigned long long query(unsigned long long k) {
        unsigned long long result = 0;
        while (k > 0) {
            result += data[k];
            k -= lowbit(k);
        }
        return result;
    }

    void add(unsigned long long k, int x = 1) {
        if (!k) return;
        while (k < data.size()) {
            data[k] += x;
            k += lowbit(k);
        }
    }

private:
    unsigned long long ceil2(unsigned long long n) {
        unsigned long long upperbound = 1;
        while (upperbound < n) upperbound *= 2;
        return upperbound;
    }

    unsigned long long lowbit(unsigned long long n) {
        return n & -n;
    }
    vector<long long> data;
};

int main() {
    size_t n;
    ifstream in("mega.in");
    ofstream out("mega.out");
    in >> n;

    fenwick_tree numbers(n);
    fenwick_tree inversions(n);
    long long megainversions = 0;

    for (size_t _ = 0; _ < n; ++_) {
        int num;
        in >> num;
        numbers.add(num);
        inversions.add(num, numbers.query(n) - numbers.query(num));
        megainversions += inversions.query(n) - inversions.query(num);
    }
    out << megainversions << endl;
    return 0;
}