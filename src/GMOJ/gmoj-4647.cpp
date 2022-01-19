#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int siz[MAX_N];
double dp[MAX_N];

void create(int u, int v);

void dfs1(int x);

void dfs2(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 2; i <= n; i++) {
        int x = read<int>();
        create(x, i);
    }

    dfs1(1);
    dp[1] = 1;
    dfs2(1, 1);

    for (int i = 1; i <= n; i++) {
        std::cout << std::fixed << std::setprecision(1) << dp[i] << ' ';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x) {
    siz[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        dfs1(v);
        siz[x] += siz[v];
    }
}

void dfs2(int x, int f) {
    if (x != f) {
        dp[x] = dp[f] + (siz[f] - siz[x] - 1) / 2.0 + 1;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        dfs2(v, x);
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