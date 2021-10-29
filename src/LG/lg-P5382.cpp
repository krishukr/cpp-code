#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int a[MAX_N], w[MAX_N], dis[MAX_N];
bool vis[MAX_N];

void create(int u, int v);

void dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }
    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            std::fill(dis, dis + n + 10, 0);
            std::fill(vis, vis + n + 10, false);
            dfs(i);
            for (int j = 2; j <= n; j++) {
                ans = std::max(ans, dis[j] / w[i]);
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    dis[a[x]] += w[x];
    vis[x] = true;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (vis[v]) {
            continue;
        }
        dfs(v);
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