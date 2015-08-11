#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<int> > matrix;

void dbg(matrix &coeffs) {
    for (auto v: coeffs) {
        for (auto d: v)
            cout << d << " ";
        cout << endl;
    }
    cout << endl;
}

void dbg(vector<int> &ans) {
    for (auto a : ans)
        cout << a << " ";
    cout << endl << endl;
}

matrix read_coefficients(ifstream &in, int size) {
    matrix m(size, vector<int>(size+1, 0));
    for (int i = 0; i < size; ++i) {
        m[i][i] = 1;
        int adjSize;
        in >> adjSize;
        for (int j = 0; j < adjSize; ++j) {
            int adjIdx;
            in >> adjIdx;
            m[i][adjIdx-1] = 1;
        }
    }
    for (int i = 0; i < size; i++) {
        int initState;
        in >> initState;
        m[i][size] = initState;
    }
    return m;
}

int findFirstNonZeroRow(const matrix &coeffs, int row, int col) {
    int cur = row;
    for (int i = row; i < coeffs.size(); ++i) {
        if (coeffs[i][col] == 1) {
            cur = i;
            break;
        }
    }
    return coeffs[cur][col] == 0 ? -1 : cur;
}

void eliminateColumn(matrix &coeffs, int row, int col) {
    for (int i = 0; i < coeffs.size(); ++i)
        if (i != row && coeffs[i][col] == 1)
            for (int j = col; j <= coeffs.size(); ++j)
                coeffs[i][j] ^= coeffs[row][j];
}

bool checkSolution(const matrix &coeffs, const vector<int> &solution) {
    for (int i = 0; i < coeffs.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < coeffs.size(); ++j)
            sum ^= solution[j] * coeffs[i][j];
        if (abs(sum - coeffs[i][coeffs.size()]) > 0)
            return false;
    }
    return true;
}

vector<int> solve(matrix &coeffs) {
    int size = coeffs.size();
    vector<int> map(size, -1);

    for (int col = 0, row = 0; col < size && row < size; ++col) {
        int cur = findFirstNonZeroRow(coeffs, row, col);
        if (cur == -1)
            continue;
        coeffs[row].swap(coeffs[cur]);
        eliminateColumn(coeffs, row, col);
        map[col] = row;
        ++row;
    }

    vector<int> solution(size, 0);
    for (int i = 0; i < size; ++i)
        if (map[i] != -1)
            solution[i] = coeffs[map[i]][size] / coeffs[map[i]][i];

    return checkSolution(coeffs, solution) ? solution : vector<int>();
}

int get_solution_size(const vector<int> &solution) {
    int c = 0;
    for (int x : solution)
        if (x == 1)
            ++c;
    return c;
}

void print_solution(const vector<int> &solution) {
    ofstream out ("puzzle.out");
    if (solution.empty()) {
        out << -1;
    } else {
        out << get_solution_size(solution) << endl;
        for (int i = 1; i <= solution.size(); ++i)
            if (solution[i-1] == 1)
                out << i << " ";
    }
    out << endl;
}

int main(int argc, const char *argv[])
{
    ifstream in("puzzle.in");

    int n;
    in >> n;
    matrix coeffs = read_coefficients(in, n);
    print_solution(solve(coeffs));

    return 0;
}