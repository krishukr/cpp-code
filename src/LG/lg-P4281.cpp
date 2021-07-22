#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int dep[MAX_N], fa[MAX_N][31];

void create(int u, int v);

void dfs(int x, int f);

int lca(int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }
    dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        int dis;

        int xy = lca(x, y);
        int yz = lca(y, z);
        int xz = lca(x, z);
        if (xy == yz) {
            dis = xz;
        } else if (yz == xz) {
            dis = xy;
        } else if (xy == xz) {
            dis = yz;
        }

        std::cout << dis << ' '
                  << dep[x] + dep[y] + dep[z] - dep[xy] - dep[yz] - dep[xz]
                  << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dep[x] = dep[f] + 1;
    fa[x][0] = f;

    for (int i = 1; (1 << i) <= dep[x]; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }
}

int lca(int x, int y) {
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    for (int i = 20; i >= 0; i--) {
        if (dep[x] <= dep[y] - (1 << i)) {
            y = fa[y][i];
        }
    }

    if (x == y) {
        return x;
    }
    for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
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