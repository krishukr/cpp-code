#include <cstdio>
#include <iostream>

const int MAX_N = 5050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], w[MAX_N], dp[MAX_N][3];
int cnt;

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        w[x] = read<int>();

        int k = read<int>();
        for (int j = 1; j <= k; j++) {
            int y = read<int>();
            create(x, y);
            create(y, x);
        }
    }

    dfs(1, 0);

    std::cout << std::min(dp[1][0], dp[1][1]) << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dp[x][0] = w[x];
    int tot = 0, min = 0x3f3f3f3f;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs(v, x);

        int m = std::min(dp[v][0], dp[v][1]);
        dp[x][0] += std::min(m, dp[v][2]);
        dp[x][1] += m;
        dp[x][2] += m;

        if (dp[v][0] < dp[v][1]) {
            tot++;
        } else {
            min = std::min(min, dp[v][0] - dp[v][1]);
        }
    }

    if (!tot) {
        dp[x][1] += min;
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