//
// Created by av on 6/29/15.
//

#include <fstream>
#include <algorithm>

using namespace std;

#define maxn 2000100


int main()
{
    ifstream in("cyclic.in");
    ofstream out("cyclic.out");
    string s;
    vector<int> z(maxn);
    in >> s;
    unsigned long size = s.size();
    s += s;

    int i;
    int k;
    int right = -1;
    int left = -1;
    int result = 0;

    z[0] = 0;
    for (i = 1; i < size; i++)
    {
        k = 0;
        if (right > i)
        {
            k = max(k, min(right - i, z[i - left]));
        }
        while (s[k] == s[i + k])
        {
            k++;
        }
        z[i] = k;
        if (i + k > right)
        {
            left = i;
            right = i + k;
        }
        if (z[i] < size && s[i + k] < s[k])
        {
            result++;
        }
    }
    out << (result + 1);
    return 0;
}