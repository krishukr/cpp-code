#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 500010;

struct Node {
    int u;
    int v;
} node[MAX_N << 1];

int head[MAX_N], depth[MAX_N], father[MAX_N][21];
int tot;

void add(int u, int v);

void dfs(int crt, int u);

int LCA(int x, int y);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, s;
    std::cin >> n >> m >> s;
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    dfs(s, 0);
    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        std::cout << LCA(x, y) << '\n';
    }

    return 0;
}

void add(int u, int v) {
    node[++tot].u = v;
    node[tot].v = head[u];
    head[u] = tot;
}

void dfs(int u, int fa) {
    father[u][0] = fa;
    depth[u] = depth[fa] + 1;
    for (int i = 1; (1 << i) <= depth[u]; i++) {
        father[u][i] = father[father[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = node[i].v) {
        if (node[i].u != fa) {
            dfs(node[i].u, u);
        }
    }
}

int LCA(int x, int y) {
    if (depth[x] > depth[y]) {
        std::swap(x, y);
    }
    for (int i = 20; i >= 0; i--) {
        if (depth[x] <= depth[y] - (1 << i)) {
            y = father[y][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 20; i >= 0; i--) {
        if (father[x][i] == father[y][i]) {
            continue;
        }
        x = father[x][i];
        y = father[y][i];
    }
    return father[x][0];
}