#include <climits>
#include <cstdio>
#include <iostream>

const int MAX_N = 50050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], c[MAX_N];
int cnt, n, m;

int dp[MAX_N][2];

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    m = read<int>(), n = read<int>();
    int root = n + 1;

    for (int i = 1; i <= n; i++) {
        c[i] = read<int>();
    }

    for (int i = 1; i < m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i][1] = 1;
        if (i <= n) {
            dp[i][(!c[i])] = INT_MAX;
        }
    }
    dfs(root, root);

    std::cout << std::min(dp[root][1], dp[root][0]) << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    if (x <= n) {
        return;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        dp[x][0] += std::min(dp[v][0] - 1, dp[v][1]);
        dp[x][1] += std::min(dp[v][1] - 1, dp[v][0]);
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