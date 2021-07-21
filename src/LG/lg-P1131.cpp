#include <cstdio>
#include <iostream>

const int MAX_N = 500050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int dp[MAX_N];
long long ans;

void dfs(int x, int f);

void create(int u, int v, int w);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), s = read<int>();
    for (int i = 1; i < n; i++) {
        int u = read<int>(), v = read<int>(), w = read<int>();
        create(u, v, w);
        create(v, u, w);
    }
    dfs(s, 0);

    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dp[x] = std::max(dp[x], node[i].w);
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        ans += (dp[x] - node[i].w);
    }
    for (int i = head[f]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == x) {
            node[i].w += dp[x];
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