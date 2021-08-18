#include <cstdio>
#include <iostream>

const int MAX_N = 5050;
const int MOD = 1e9 + 7;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1];
int c[MAX_N], dp[MAX_N][MAX_N];
int cnt, n, m;

void dfs(int x, int f);

void create(int u, int v);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        for (int j = 1; j <= x; j++) {
            int y = read<int>();
            dp[i][y] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    dfs(1, 0);
    std::cout << c[1] << '\n';

    return 0;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs(v, x);
        for (int j = 1; j <= m; j++) {
            dp[x][j] = (long long)dp[x][j] * (c[v] - dp[v][j] + MOD) % MOD;
        }
    }

    for (int i = 1; i <= m; i++) {
        c[x] += dp[x][i];
        c[x] %= MOD;
    }
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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