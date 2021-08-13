#include <climits>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], num[MAX_N], fa[MAX_N];
bool vis[MAX_N];
int cnt, root;

long long dp[MAX_N][2];
long long ans;

void create(int u, int v);

void dfs1(int x);

void dfs2(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        num[i] = read<int>();
        int x = read<int>();
        create(x, i);
        fa[i] = x;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x) {
    vis[x] = true;
    root = x;

    while (!vis[fa[root]]) {
        root = fa[root];
        vis[root] = true;
    }
    dfs2(root);

    long long tmp = std::max(dp[root][0], dp[root][1]);
    vis[root] = 1;
    root = fa[root];
    dfs2(root);
    ans += std::max(tmp, std::max(dp[root][0], dp[root][1]));
}

void dfs2(int x) {
    vis[x] = true;
    dp[x][0] = 0;
    dp[x][1] = num[x];

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == root) {
            dp[v][1] = LLONG_MIN;
        } else {
            dfs2(v);
            dp[x][1] += dp[v][0];
            dp[x][0] += std::max(dp[v][0], dp[v][1]);
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