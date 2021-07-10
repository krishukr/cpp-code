#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1], dp[MAX_N][2];
int tot;

void create(int u, int v);

void dfs(int x, int f);

inline int read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read();
    for (int i = 1; i <= n; i++) {
        int x = read(), k = read();
        for (int i = 1; i <= k; i++) {
            int y = read();
            create(x, y);
            create(y, x);
        }
    }

    dfs(0, -1);
    std::cout << std::min(dp[0][0], dp[0][1]);

    return 0;
}

void create(int u, int v) {
    node[++tot].nxt = head[u];
    node[tot].v = v;
    head[u] = tot;
}

void dfs(int x, int f) {
    dp[x][0] = 0;
    dp[x][1] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        if (node[i].v == f) {
            continue;
        } else {
            dfs(node[i].v, x);
            dp[x][0] += dp[node[i].v][1];
            dp[x][1] += std::min(dp[node[i].v][0], dp[node[i].v][1]);
        }
    }
}

inline int read() {
    int x = 0, f = 1;
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