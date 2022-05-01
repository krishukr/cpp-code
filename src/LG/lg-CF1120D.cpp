#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>

constexpr int MAX_N = 200050;

int n;
int c[MAX_N];

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N], deg[MAX_N];
int cnt;

void craete(int u, int v);

int lx[MAX_N], rx[MAX_N];
int dfn;

void dfs(int x, int f);

int f[MAX_N];
bool ansv[MAX_N];

inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

struct Q {
    int x;
    int y;
    int z;
    int idx;
} q[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        craete(x, y);
        craete(y, x);
    }

    cnt = 0;
    dfs(1, 0);
    std::sort(q + 1, q + cnt + 1,
              [](const Q& x, const Q& y) { return x.z < y.z; });

    long long anss{0};
    int anst{0};
    std::iota(f + 1, f + dfn + 2, 1);
    for (int i = 1; i <= cnt; i++) {
        int j;
        for (j = i; j < cnt and q[i].z == q[j + 1].z; j++)
            ;
        for (int k = i; k <= j; k++) {
            int x = q[k].x, y = q[k].y;
            x = find(x);
            y = find(y);
            if (x != y) {
                anst++;
                ansv[q[k].idx] = true;
            }
        }
        for (int k = i; k <= j; k++) {
            int x = q[k].x, y = q[k].y;
            x = find(x);
            y = find(y);
            if (x != y) {
                f[x] = y;
                anss += q[k].z;
            }
        }
        i = j;
    }

    std::cout << anss << ' ' << anst << '\n';
    for (int i = 1; i <= n; i++) {
        if (ansv[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}

void craete(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    deg[v]++;
}

void dfs(int x, int f) {
    lx[x] = n + 1;
    rx[x] = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        lx[x] = std::min(lx[x], lx[v]);
        rx[x] = std::max(rx[x], rx[v]);
    }

    if (x != 1 and deg[x] == 1) {
        lx[x] = rx[x] = ++dfn;
    }
    q[++cnt] = {lx[x], rx[x] + 1, c[x], x};
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}