#include <cstdio>
#include <iostream>

const int MAX_N = 600050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], dp[MAX_N], ind[MAX_N];
int cnt, ans;

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    dfs(1, 0);
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    ind[v]++;
}

void dfs(int x, int f) {
    int t1 = 0, t2 = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        dp[x] = std::max(dp[x], dp[v]);
        if (dp[v] > t1) {
            t2 = t1;
            t1 = dp[v];
        } else if (dp[v] > t2) {
            t2 = dp[v];
        }
    }
    int cnt = ind[x] - (bool)(f);
    dp[x] += (1 + std::max(0, cnt - 1));

    ans = std::max(ans, t1 + t2 + 1 + std::max(0, cnt - 1 - !(bool)(f)));
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