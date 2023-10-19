#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int siz[MAX_N], dep[MAX_N];
ll dp[MAX_N];

void dfs1(int x, int f);

void dfs2(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs1(1, 0);
    for (int i = 1; i <= n; i++) {
        dp[1] += dep[i];
    }
    dfs2(1, 0);

    ll ans{}, ai{};
    for (int i = 1; i <= n; i++) {
        if (ans < dp[i]) {
            ans = dp[i];
            ai = i;
        }
    }
    std::cout << ai << '\n';

    std::cout << std::flush;
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f) {
    siz[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dep[v] = dep[x] + 1;
        dfs1(v, x);
        siz[x] += siz[v];
    }
}

void dfs2(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dp[v] = dp[x] + siz[1] - 2 * siz[v];
        dfs2(v, x);
    }
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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