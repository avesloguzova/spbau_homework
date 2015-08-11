#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxe = 1000010;
const int maxv = 100010;
const int mn = (maxv * 2);

int lca(int a, int b);

void paint(int v);

void dfs(int v, int pr);

int get(int l, int r);

void gfs(int v, int d, int pr);

int e = 0, he[maxv], ne[maxe], to[maxe], f[maxe];
int curT = 0, tIn[maxv], minT[maxv];
int cc = 0, u[maxv];
vector<int> c[maxv];

int tt = 0, t[maxv], vt[maxv], pos[maxv], an = 0, a[mn * 2];
int tr[mn * 4], dep[mn];

int main(void) {
    freopen("magic.in", "rt", stdin);
    freopen("magic.out", "wt", stdout);

    int i, j, n, m, st;
    scanf("%d%d%d", &n, &m, &st);
    memset(he, -1, sizeof(he));
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        ne[e] = he[a], to[e] = b, he[a] = e++;
        ne[e] = he[b], to[e] = a, he[b] = e++;
    }
    memset(f, 0, sizeof(f));
    memset(tIn, -1, sizeof(tIn));
    dfs(st, -1);

    memset(u, 0, sizeof(u));
    for (i = 0; i <= n; i++)
        if (!u[i])
            cc++, paint(i);
//  for (i = 0; i <= n; i++)
//    fprintf(stderr, "i=%d c=%d\n", i, u[i]);

    for (i = 0; i <= n; i++)
        for (j = he[i]; j != -1; j = ne[j])
            if (f[j])
                c[u[i]].push_back(u[to[j]]);
    gfs(u[st], 0, -1);

    for (i = 0; i < an; i++)
        tr[an + i] = a[i];
    for (i = an - 1; i > 0; i--)
        tr[i] = min(tr[i + i], tr[i + i + 1]);

    scanf("%d", &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        a = u[a], b = u[b];
        i = lca(a, b);
        printf("%d\n", dep[i]);
    }
    return 0;
}

void dfs(int v, int pr) {
    int i, j;
    minT[v] = tIn[v] = curT++;
    for (i = he[v]; i != -1; i = ne[i])
        if ((j = to[i]) != pr) {
            if (tIn[j] == -1) {
                dfs(j, v);
                if (minT[j] > tIn[v])
                    f[i] = f[i ^ 1] = 1;
            }
            minT[v] = min(minT[v], minT[j]);
        }
}

void paint(int v) {
    u[v] = cc;
    for (int i = he[v]; i != -1; i = ne[i])
        if (!f[i] && !u[to[i]])
            paint(to[i]);
}

void gfs(int v, int d, int pr) {
    int i, j;
    dep[v] = d;
    vt[tt] = v, t[v] = tt++;
    pos[t[v]] = an, a[an++] = t[v];
    for (i = 0; i < c[v].size(); i++)
        if ((j = c[v][i]) != pr)
            gfs(j, d + 1, v), a[an++] = t[v];
}

int lca(int a, int b) {
    return vt[get(pos[t[a]], pos[t[b]])];
}

int get(int l, int r) {
    if (l > r)
        swap(l, r);
    l += an, r += an;
    int mi = (int) 1e9;
    while (l <= r) {
        if (l & 1)
            mi = min(mi, tr[l++]);
        if (!(r & 1))
            mi = min(mi, tr[r--]);
        if (l > r)
            break;
        l >>= 1, r >>= 1;
    }
    return mi;
}
