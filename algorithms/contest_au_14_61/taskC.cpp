#include <iostream>
#include <string.h>
#include <fstream>
#include <string>

using namespace std;
const int MASK_BORDER = 1 << 6;
const int MAX_DIGITS = 105;

int module;
char n[MAX_DIGITS];

int adj_mask[MASK_BORDER][MASK_BORDER];
int MASK;


struct long_int {
    int amount;
    int digits[MAX_DIGITS];

    long_int() {
        memset(digits, 0, sizeof(digits));
        amount = 1;
    }

    long_int(const char *buf) {
        memset(digits, 0, sizeof(digits));
        amount = strlen(buf);
        int pos = 0;
        for (int i = amount - 1; i >= 0; i--)
            digits[pos++] = buf[i] - '0';
    }

    bool isZero() {
        return amount == 1 && digits[0] == 0 || amount == 0 && digits[0] == 0;
    }

    bool isOdd() {
        return digits[0] & 1;
    }
};


long_int operator/(const long_int &a, const int &n) {
    long_int res;
    int ost = 0;
    for (int i = a.amount - 1; i >= 0; --i) {
        int current = ost * 10 + a.digits[i];
        res.digits[i] = current / n;
        ost = current % n;
    }
    int pos = a.amount - 1;
    while (pos && !res.digits[pos])
        pos--;
    res.amount = pos + 1;
    return res;
}

long_int operator-(const long_int &a, const int &n) {
    long_int result = a;
    int position = 0;
    result.digits[position] -= n;
    while (result.digits[position] < 0) {
        result.digits[position + 1]--;
        result.digits[position++] += 10;
    }
    if (!result.digits[result.amount - 1])
        result.amount--;
    return result;
}

struct matrix {
    int mas[MASK_BORDER][MASK_BORDER];


    matrix() {
        memset(mas, 0, sizeof(mas));
    }

    matrix(int src[MASK_BORDER][MASK_BORDER]) {
        memcpy(mas, src, sizeof(mas));
    }

    void setE() {
        for (int i = 0; i < MASK_BORDER; ++i)
            mas[i][i] = 1;
    }

    void fast_mul(long_int n) {
        matrix res, b;
        res.setE();
        b = *this;
        while (!n.isZero()) {
            if (n.isOdd()) {
                res *= b;
            }
            b *= b;
            n = n / 2;
        }
        *this = res;
    }

    void operator*=(const matrix &b) {
        matrix res;
        for (int i = 0; i <= MASK; ++i) {
            for (int j = 0; j <= MASK; ++j) {
                for (int k = 0; k <= MASK; ++k) {
                    res.mas[i][j] = (res.mas[i][j] + (this->mas[i][k] * b.mas[k][j]) % module) % module;
                }
            }
        }
        *this = res;
    }
};

int get_bit(int num, int bit) {
    return (num >> bit) & 1 ? 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    ifstream in("nice3.in");
    ofstream out("nice3.out");
    string s;
    int m, p;
    in >> s >> m >> p;
    module = p;
    MASK = (1 << m) - 1;
    for (int prev = 0; prev <= MASK; ++prev) {
        for (int current = 0; current <= MASK; ++current) {
            bool isOK = true;
            for (int bit = 0; bit < m - 1; ++bit) {
                int sum = get_bit(prev, bit) + get_bit(prev, bit + 1) +
                          get_bit(current, bit) + get_bit(current, bit + 1);
                isOK &= !(sum == 0 || sum == 4);
            }
            adj_mask[prev][current] = isOK ? 1 : 0;
        }
    }
    matrix a = matrix(adj_mask);
    a.fast_mul(long_int(s.c_str()) - 1);
    int res = 0;
    for (int i = 0; i <= MASK; ++i) {
        for (int j = 0; j <= MASK; ++j)
            res = (res + a.mas[i][j]) % p;
    }
    out << res;

    return 0;
}