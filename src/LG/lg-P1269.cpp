#include <cstdio>
#include <iostream>

const int MAX_N = 20050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N << 1], dis[MAX_N], fa[MAX_N];
int cnt, ans, st;

void create(int u, int v, int w);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = 0;

    for (int i = 1; i <= n; i++) {
        int k = read<int>();
        for (int j = 1; j <= k; j++) {
            int x = read<int>(), y = read<int>();
            m = std::max(m, y);

            create(i, x, y);
        }
    }

    st = read<int>();
    if (m >= st) {
        std::cout << "No solution.\n";
    } else {
        dfs(1, 0);
        std::cout << ans << '\n';
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        if (v == f) {
            continue;
        }

        fa[v] = w;
        dfs(v, x);
        dis[x] = std::max(dis[x], dis[v] + w);
    }
    if (dis[x] + fa[x] > st) {
        ans++;
        dis[x] = 0;
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