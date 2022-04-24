#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int m[MAX_N], deg[MAX_N];
ll dp1[MAX_N], dp2[MAX_N];

void dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, g, K;
    read(n, g, K);
    for (int i = 1; i <= g; i++) {
        read(m[i]);
    }
    std::sort(m + 1, m + g + 1);

    int s = n + 5, r1, r2;
    read(r1, r2);
    create(s, r1);
    create(r1, s);
    create(s, r2);
    create(r2, s);
    deg[s] = 2;
    deg[r1] = deg[r2] = 1;

    for (int i = 2; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
        deg[x]++;
        deg[y]++;
    }

    dp1[s] = dp2[s] = K;
    dfs(s, 0);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            ans += std::upper_bound(m + 1, m + g + 1, dp2[i]) -
                   std::lower_bound(m + 1, m + g + 1, dp1[i]);
        }
    }
    std::cout << ans * K << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dp1[v] = 1ll * dp1[x] * (deg[x] - 1);
        dp2[v] = 1ll * (dp2[x] + 1) * (deg[x] - 1) - 1;
        dfs(v, x);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}