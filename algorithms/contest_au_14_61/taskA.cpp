#include <iostream>
#include <map>
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>

long long n;
long long x[30];
long long c;


long long calc_sum(long long l, long long num)
{
    long long sum = 0;
    long long d = 0;
    while ((1 << d) <= num)
    {
        if ((1 << d) & num)
        {
            sum += x[l + d];
        }
        d++;
    }
    return sum;
}

void solve(long long l, long long r, std::map<long long, long long> &res)
{
    long long max = 1 << (r - l);
    for (long long i = 0; i < max; i++)
    {
        long long sum = calc_sum(l, i);
        if (sum <= c)
        {
            res[sum] += 1;
        }
    }
}

long long merge(std::map<long long, long long>  res1,std::map<long long, long long>  res2)
{
    std::map<long long, long long> cum;
    long long sum = 0;
    for (std::pair<long long, long long> p : res2)
    {
        sum += p.second;
        cum[p.first] = sum;
    }
    long long result = 0;
    for (std::pair<long long, long long> p :res1)
    {
        long long rest = c - p.first;
        auto right = cum.upper_bound(rest);
        if (right == cum.begin()) continue;
        right--;
        result += p.second * right -> second;
    }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::ifstream in("knapsack.in");
    std::ofstream out("knapsack.out");
    in >> n;
    for (long long i = 0; i < n; i++)
    {
        in >> x[i];
    }
    in >> c;
    std::map<long long, long long> res1;
    std::map<long long, long long> res2;
    if (n <= 15)
    {
        solve(0, n, res1);
        long long sum = 0;
        for (auto p : res1)
        {
            sum += p.second;
        }
        out << sum;
        return 0;
    }
    solve(0, n / 2, res1);
    solve(n / 2, n, res2);
    out << merge(res1,res2);
    return 0;
}