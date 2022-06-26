#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

ll f[6][MAX_N];
ll g[6];
int siz[MAX_N];

void dfs1(int x, int fa);

void dfs2(int x, int fa);

int n, k;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, k);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    ll ans{};
    for (int i = 1; i <= n; i++) {
        ans += f[0][i];
    }
    std::cout << (ans >> 1) << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int fa) {
    siz[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs1(v, x);
        siz[x] += siz[v];

        f[0][x] += f[k - 1][v] + siz[v];
        for (int i = 1; i < k; i++) {
            f[i][x] += f[i - 1][v];
        }
    }
}

void dfs2(int x, int fa) {
    if (fa) {
        g[0] = f[0][fa] - f[k - 1][x] - siz[x];
        for (int i = 1; i < k; i++) {
            g[i] = f[i][fa] - f[i - 1][x];
        }
    }

    f[0][x] += g[k - 1] + n - siz[x];
    for (int i = 1; i < k; i++) {
        f[i][x] += g[i - 1];
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}