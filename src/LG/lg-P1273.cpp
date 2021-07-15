#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 3050;

struct Node {
    int v;
    int nxt;
    int w;
} tree[MAX_N];

int head[MAX_N], dp[MAX_N][MAX_N], cost[MAX_N];
int cnt, n, m;

void create(int u, int v, int w);

int dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    memset(dp, -0x3f, sizeof(dp));

    for (int i = 1; i <= n - m; i++) {
        int u = read<int>();
        for (int j = 1; j <= u; j++) {
            int v = read<int>(), w = read<int>();
            create(i, v, w);
        }
    }
    for (int i = n - m + 1; i <= n; i++) {
        cost[i] = read<int>();
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }
    dfs(1);
    for (int i = m; i > 0; i--) {
        if (dp[1][i] >= 0) {
            std::cout << i << '\n';
            break;
        }
    }

    return 0;
}

void create(int u, int v, int w) {
    tree[++cnt].nxt = head[u];
    tree[cnt].v = v;
    tree[cnt].w = w;
    head[u] = cnt;
}

int dfs(int x) {
    if (x > n - m) {
        dp[x][1] = cost[x];
        return 1;
    }

    int res = 0, tot;
    for (int i = head[x]; i; i = tree[i].nxt) {
        tot = dfs(tree[i].v);
        res += tot;
        for (int j = res; j > 0; j--) {
            for (int k = 1; k <= tot; k++) {
                if (j - k >= 0) {
                    dp[x][j] = std::max(
                        dp[x][j], dp[x][j - k] + dp[tree[i].v][k] - tree[i].w);
                }
            }
        }
    }
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