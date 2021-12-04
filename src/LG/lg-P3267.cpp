#include <cstdio>
#include <iostream>

const int MAX_N = 500050;
const int MAX_M = 25;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt;

int v[MAX_N];
int dp[MAX_N][MAX_M], g[MAX_N][MAX_M];
bool pos[MAX_N];
int n, d, m;

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), d = read<int>();
    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
    }

    m = read<int>();
    for (int i = 1; i <= m; i++) {
        pos[read<int>()] = true;
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    dfs(1, 0);
    std::cout << dp[1][0] << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    if (pos[x]) {
        dp[x][0] = g[x][0] = v[x];
    }

    for (int i = 1; i <= d; i++) {
        g[x][i] = v[x];
    }
    g[x][d + 1] = 0x3f3f3f3f;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);

        for (int j = d; j >= 0; j--) {
            g[x][j] = std::min(g[x][j] + dp[v][j], g[v][j + 1] + dp[x][j + 1]);
        }
        for (int j = d; j >= 0; j--) {
            g[x][j] = std::min(g[x][j], g[x][j + 1]);
        }

        dp[x][0] = g[x][0];
        for (int j = 1; j <= d + 1; j++) {
            dp[x][j] += dp[v][j - 1];
        }
        for (int j = 1; j <= d + 1; j++) {
            dp[x][j] = std::min(dp[x][j], dp[x][j - 1]);
        }
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