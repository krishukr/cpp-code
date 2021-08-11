#include <climits>
#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 500050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N];

int head[MAX_N], d[MAX_N], m[MAX_N], p[MAX_N];
int cnt, tot;

int c[MAX_N];

void create(int u, int v, int w);

int dfs(int x, int f);

void dp(int x, int f);

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        c[i] = read<int>();
        tot += c[i];
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    dfs(1, 1);
    dp(1, 1);

    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, p[i]);
    }

    std::cout << ans + d[1] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

int dfs(int x, int f) {
    int res = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        if (v == f) {
            continue;
        }
        int tmp = dfs(v, x);
        d[x] += d[v] + w * tmp;
        res += tmp;
    }
    return m[x] = res + c[x];
}

void dp(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        if (v == f) {
            continue;
        }
        p[v] = p[x] - m[v] * w + (tot - m[v]) * w;
        dp(v, x);
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