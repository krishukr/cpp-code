#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt;

struct Edge {
    int u;
    int v;
    int w;

    bool operator<(const Edge &e) const { return w > e.w; }
} edge[MAX_N];

int f[MAX_N];  // 并查集
int dep[MAX_N];
int fa[MAX_N][21], max[MAX_N][21];
bool vis[MAX_N];

int find(int x);

void create(int u, int v, int w);

void dfs(int x);

int LCA(int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        edge[i].u = read<int>();
        edge[i].v = read<int>();
        edge[i].w = read<int>();
    }
    std::sort(edge + 1, edge + m + 1);

    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        if (find(edge[i].u) != find(edge[i].v)) {
            f[find(edge[i].u)] = find(edge[i].v);
            create(edge[i].u, edge[i].v, edge[i].w);
            create(edge[i].v, edge[i].u, edge[i].w);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dep[i] = 1;
            dfs(i);
            fa[i][0] = i;
            max[i][0] = INT_MAX;
        }
    }

    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
            max[j][i] = std::min(max[j][i - 1], max[fa[j][i - 1]][i - 1]);
        }
    }

    int q = read<int>();
    while (q--) {
        int x = read<int>(), y = read<int>();
        std::cout << LCA(x, y) << '\n';
    }

    return 0;
}

int find(int x) { return x == f[x] ? x : (f[x] = find(f[x])); }

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    vis[x] = true;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (vis[v]) {
            continue;
        }
        dep[v] = dep[x] + 1;
        fa[v][0] = x;
        max[v][0] = node[i].w;
        dfs(v);
    }
}

int LCA(int x, int y) {
    if (find(x) != find(y)) {
        return -1;
    }
    int ans = INT_MAX;
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }

    for (int i = 20; i >= 0; i--) {
        if (dep[fa[y][i]] >= dep[x]) {
            ans = std::min(ans, max[y][i]);
            y = fa[y][i];
        }
    }
    if (x == y) {
        return ans;
    }

    for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            ans = std::min(ans, std::min(max[x][i], max[y][i]));
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    ans = std::min(ans, std::min(max[x][0], max[y][0]));
    return ans;
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