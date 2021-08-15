#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 2050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N << 1], s[MAX_N];
int cnt, n, m;

ll dp[MAX_N][MAX_N];

void create(int u, int v, int w);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));
    n = read<int>(), m = read<int>();

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    dfs(1, 0);
    std::cout << dp[1][m] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    s[x] = 1;
    dp[x][0] = dp[x][1] = 0;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;

        if (v == f) {
            continue;
        }
        dfs(v, x);

        s[x] += s[v];
        for (int j = std::min(m, s[x]); j >= 0; j--) {
            for (int k = 0; k <= std::min(j, s[v]); k++) {
                if (dp[x][j - k] == -1) {
                    continue;
                }
                ll tmp = 1ll * w * k * (m - k) +
                         1ll * w * (s[v] - k) * (n - m - s[v] + k);

                dp[x][j] = std::max(dp[x][j], dp[x][j - k] + dp[v][k] + tmp);
            }
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