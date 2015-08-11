#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("test.in");
    ofstream out("test.out");

    int n, m;
    in >> n >> m;
    vector<int> tmp(n, 0);
    vector<vector<int>> c(n, tmp);

    int count = 0;

    for (int j = 1; j < n && count < m; ++j)
    {
        c[0][j] = j - 1;
        out << "1 " << j + 1 << " " << c[0][j] << endl;
        ++count;
    }

    for (int i = 1; i < n && count < m; ++i)
    {
        for (int j = i + 1; j < n && count < m; ++j)
        {
            c[i][j] = c[i - 1][j] - 1;
            out << i + 1 << " " << j + 1 << " " << c[i][j] << endl;
            ++count;
        }
    }
}