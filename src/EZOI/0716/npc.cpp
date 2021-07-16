#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], dp[MAX_N][2];
int cnt;

void create(int u, int v);

void dfs(int x, int y);

template <typename T>
T read();

int main() {
    freopen("npc.in", "r", stdin);
    freopen("npc.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int u = read<int>(), v = read<int>(), c = read<int>();
        create(u, v);
        create(v, u);
    }
    dfs(1, 0);
    std::cout << std::max(dp[1][0], dp[1][1]) << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int y) {
    dp[x][0] = 1;
    dp[x][1] = 0;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == y) {
            continue;
        }
        dfs(v, x);
        dp[x][0] += dp[v][1];
        dp[x][1] += std::max(dp[v][0], dp[v][1]);
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