#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <iomanip>

using namespace std;
unsigned long long max_value = 1000 * 1000 * 1000;

typedef struct item * pitem;
struct item {
    int prior, value;
    long long sum;
    pitem l, r;
    item(int prior, int value): prior(prior), value(value), sum(value), l(NULL), r(NULL) {}
};

int value(pitem it)
{
    return it ? it->value : 0;
}

long long sum(pitem it)
{
    return it ? it->sum : 0;
}

void upd_cnt(pitem it) {
    if (it)
    {
        it->sum = sum(it->l) + sum(it->r) + it->value;
    }
}

void merge(pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    upd_cnt(t);
}

void split(pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void(l = r = 0);
    if (key <= t->value)
        split(t->l, l, t->l, key), r = t;
    else
        split(t->r, t->r, r, key), l = t;
    upd_cnt(t);
}


void insert(pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split(t, it->l, it->r, it->value), t = it;
    else
        insert(it->value < t->value ? t->l : t->r, it);
    upd_cnt(t);
}

long long sum(pitem root, int l, int r)
{
    pitem t1, t2, t3;
    t1 = t2 = t3 = NULL;
    split(root, t1, t2, r + 1);
    split(t1, t1, t3, l);
    long long res = sum(t3);
    merge(t1, t1, t3);
    merge(root, t1, t2);
    return res;
}

void output(pitem t) {
    if (!t)  return;
    output(t->l);
    printf("%d ", t->value);
    output(t->r);
}

int main()
{
    pitem root = NULL;
    pitem num = NULL;
    ifstream in("sum2.in");
    ofstream out("sum2.out");
    set<int> values;
    int n;
    in >> n;
    char op;
    long long prev = 0;
    for (int i = 0; i < n; ++i)
    {
        in >> op;
        switch (op)
        {
            case '+':
                int x;
                in >> x;
                x = (x + prev) % max_value;
                if (values.insert(x).second)
                {
                    num = new item(rand(), x);
                    insert(root, num);
                }
                prev = 0;
                break;
            case '?':
                int l, r;
                in >> l >> r;
                prev = sum(root, l, r);
                out << prev << endl;
        }
    }
    return 0;
}