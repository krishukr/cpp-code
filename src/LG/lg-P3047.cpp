#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], w[MAX_N];
int cnt, n, k;

ll dp1[MAX_N][30], dp2[MAX_N][30];

void create(int u, int v);

void dfs1(int x, int f);

void dfs2(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), k = read<int>();

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    dfs1(1, 0);
    memcpy(dp2, dp1, sizeof(dp1));
    dfs2(1, 0);

    for (int i = 1; i <= n; i++) {
        std::cout << dp2[i][k] << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f) {
    for (int i = 0; i <= k; i++) {
        dp1[x][i] = w[x];
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs1(v, x);
        for (int j = 1; j <= k; j++) {
            dp1[x][j] += dp1[v][j - 1];
        }
    }
}

void dfs2(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dp2[v][1] += dp1[x][0];
        for (int j = 2; j <= k; j++) {
            dp2[v][j] += dp2[x][j - 1] - dp1[v][j - 2];
        }
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