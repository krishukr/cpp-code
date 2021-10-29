#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 205;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt;

int dp[MAX_N][MAX_N], siz[MAX_N];

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), p = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    memset(dp, 0x3f, sizeof(dp));
    dfs(1, 0);
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, dp[i][p] + 1);
    }
    ans = std::min(ans, dp[1][p]);
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    siz[x] = 1;
    dp[x][1] = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        siz[x] += siz[v];

        for (int j = siz[x]; j > 0; j--) {
            dp[x][j]++;
            for (int k = 0; k <= std::min(j - 1, siz[v]); k++) {
                dp[x][j] = std::min(dp[x][j], dp[x][j - k] + dp[v][k]);
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