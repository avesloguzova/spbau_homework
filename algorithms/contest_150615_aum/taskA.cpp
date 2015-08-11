//
// Created by av on 6/29/15.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 525000
#define MAX_COORDINATE 200000

struct segment_tree
{
    vector<long> res;
    vector<long> d;

    segment_tree() :
            res(MAX_N * 2 + 2),
            d(MAX_N * 2 + 2)
    {
    }

    void add(long left, long right, long dv, long vertex, long n_left, long n_right)
    {
        if ((n_right < left) || (n_left > right)) return;
        if ((n_left >= left) && (n_right <= right))
        {
            d[vertex] += dv;
            return;
        }
        d[vertex * 2 + 1] += d[vertex];
        d[vertex * 2 + 2] += d[vertex];
        d[vertex] = 0;
        add(left, right, dv, vertex * 2 + 1, n_left, ((n_left + n_right) >> 1));
        add(left, right, dv, vertex * 2 + 2, ((n_left + n_right) >> 1) + 1, n_right);
        res[vertex] = max(res[vertex * 2 + 1] + d[vertex * 2 + 1], res[vertex * 2 + 2] + d[vertex * 2 + 2]);
    }

    pair<long, long> getmax()
    {
        long vertex = 0;
        long left = 0;
        long right = MAX_COORDINATE * 2 + 1;
        while (left != right)
        {
            d[vertex * 2 + 1] += d[vertex];
            d[vertex * 2 + 2] += d[vertex];
            d[vertex] = 0;
            res[vertex] = max(res[vertex * 2 + 1] + d[vertex * 2 + 1], res[vertex * 2 + 2] + d[vertex * 2 + 2]);
            if (res[vertex * 2 + 1] + d[vertex * 2 + 1] > res[vertex * 2 + 2] + d[vertex * 2 + 2])
            {
                vertex = vertex * 2 + 1;
                right = (left + right) >> 1;
            } else
            {
                vertex = vertex * 2 + 2;
                left = ((left + right) >> 1) + 1;
            }
        }
        res[vertex] += d[vertex];
        d[vertex] = 0;
        return make_pair(res[vertex], left);
    }
};


struct segment
{
    long min_y, max_y, d, x;

    segment()
    { }

    segment(long minY, long maxY, long pose, long x_coord)
    {
        min_y = minY;
        max_y = maxY;
        d = pose;
        x = x_coord;
    }

    friend bool operator<(const segment &fst, const segment &snd)
    {
        if (fst.x != snd.x) return fst.x < snd.x;
        if (fst.d != snd.d) return fst.d > snd.d;
        return false;
    }
};


int main()
{


    int n;

    ifstream in("windows.in");
    ofstream out("windows.out");
    in >> n;
    vector<segment> v;
    segment_tree t;
    for (long i = 0; i < n; i++)
    {
        long x1, y1, x2, y2;
        in >> x1 >> y1 >> x2 >> y2;
        x1 += MAX_COORDINATE;
        y1 += MAX_COORDINATE;
        x2 += MAX_COORDINATE;
        y2 += MAX_COORDINATE;
        v.push_back(segment(y1, y2, 1, x1));
        v.push_back(segment(y1, y2, -1, x2));
    }
    sort(v.begin(), v.end());

    long count = 0;
    long current_x = 0;
    long current_y = 0;
    for (long i = 0; i < n * 2; i++)
    {
        t.add(v[i].min_y, v[i].max_y, v[i].d, 0, 0, MAX_COORDINATE * 2 + 1);
        pair<long, long> tmp = t.getmax();
        if (tmp.first > count)
        {
            count = tmp.first;
            current_x = v[i].x;
            current_y = tmp.second;
        }
    }
    out << count << endl;
    out << (current_x - MAX_COORDINATE) << " " << (current_y - MAX_COORDINATE);


    return 0;
}
