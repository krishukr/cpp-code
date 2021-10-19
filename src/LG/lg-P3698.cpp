#include <cstdio>
#include <iostream>

const int MAX_N = 205;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt, v, n;

int dp[MAX_N][MAX_N][2];

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    v = read<int>(), n = read<int>();

    for (int i = 1; i < v; i++) {
        int x = read<int>(), y = read<int>();
        x++, y++;
        create(x, y);
        create(y, x);
    }

    dfs(1, 0);
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = std::max(ans, dp[1][i][0]);
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dp[x][0][0] = dp[x][0][1] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);

        for (int j = n; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                dp[x][j][0] = std::max(
                    dp[x][j][0], std::max(dp[x][j - k][0] + dp[v][k - 2][1],
                                          dp[x][j - k][1] + dp[v][k - 1][0]));

                dp[x][j][1] =
                    std::max(dp[x][j][1], dp[x][j - k][1] + dp[v][k - 2][1]);
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