#include <cstdio>
#include <iostream>
#include <numeric>

const int MAX_N = 300050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt, l;
int n, m, q;

int dis[MAX_N], len[MAX_N];
int fa[MAX_N];

inline int find(int x);

void create(int u, int v);

void merge(int x, int y);

void dfs(int x, int f);

int get_len(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>(), q = read<int>();
    std::iota(fa + 1, fa + n + 1, 1);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);

        fa[find(x)] = find(y);
    }

    for (int i = 1; i <= n; i++) {
        int x = find(i);
        if (!len[x]) {
            len[x] = get_len(x);
        }
    }

    for (int i = 1; i <= q; i++) {
        int op = read<int>();
        if (op == 1) {
            int x = read<int>();
            std::cout << len[find(x)] << '\n';
        } else {
            int x = read<int>(), y = read<int>();
            if (find(x) != find(y)) {
                merge(x, y);
            }
        }
    }

    return 0;
}

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (len[fx] < len[fy]) {
        std::swap(fx, fy);
    }

    fa[fy] = fx;
    len[fx] = std::max(len[fx], (len[fx] + 1) / 2 + (len[fy] + 1) / 2 + 1);
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = 1;
        if (v == f) {
            continue;
        }
        dis[v] = dis[x] + w;
        if (dis[v] > dis[l]) {
            l = v;
        }
        dfs(v, x);
    }
}

int get_len(int x) {
    l = 0;
    dfs(x, 0);
    dis[l] = 0;
    dfs(l, 0);

    int res = dis[l];
    return res;
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