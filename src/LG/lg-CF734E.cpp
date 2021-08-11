#include <cstdio>
#include <iostream>

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], fa[MAX_N];
int cnt;
int dd, ww;

int x[MAX_N], y[MAX_N];
int col[MAX_N];

void create(int u, int v);

int find(int x);

void dfs(int d, int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        col[i] = read<int>();
        fa[i] = i;
    }

    for (int i = 1; i < n; i++) {
        x[i] = read<int>(), y[i] = read<int>();
        int fx = find(x[i]), fy = find(y[i]);
        if (col[fx] == col[fy]) {
            fa[fx] = fa[fy];
        }
    }

    for (int i = 1; i <= n; i++) {
        fa[i] = find(fa[i]);
    }

    for (int i = 1; i <= n; i++) {
        int fx = fa[x[i]], fy = fa[y[i]];
        if (fx != fy) {
            create(fx, fy);
            create(fy, fx);
        }
    }

    dfs(0, fa[1], 0);
    dfs(0, ww, 0);

    std::cout << (dd + 1) / 2 << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void dfs(int d, int x, int f) {
    if (d > dd) {
        dd = d;
        ww = x;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(d + 1, v, x);
    }
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