#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 100050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt, n, k;

int v[MAX_N], dep[MAX_N];
int dp[105][105][105], g[105][105][105];

std::vector<int> stk{};

void create(int u, int v, int w);

void dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), k = read<int>();

    // std::fill(head, head + n + 10, -1);

    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
        int x = read<int>(), y = read<int>();
        create(x, i, y);
    }

    dfs(0);
    std::cout << dp[0][0][k] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    stk.push_back(x);
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        dep[v] = dep[x] + w;
        dfs(v);

        for (auto j : stk) {
            for (int l = k; l >= 0; l--) {
                dp[x][j][l] += dp[v][j][0];
                g[x][j][l] += dp[v][x][0];

                for (int m = 0; m <= l; m++) {
                    dp[x][j][l] =
                        std::min(dp[x][j][l], dp[x][j][l - m] + dp[v][j][m]);
                    g[x][j][l] =
                        std::min(g[x][j][l], g[x][j][l - m] + dp[v][x][m]);
                }
            }
        }
    }

    for (auto i : stk) {
        dp[x][i][0] += v[x] * (dep[x] - dep[i]);
        for (int j = 1; j <= k; j++) {
            dp[x][i][j] = std::min(dp[x][i][j] + v[x] * (dep[x] - dep[i]),
                                   g[x][i][j - 1]);
        }
    }
    stk.pop_back();
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