#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 2050;
constexpr int MOD = 1e9 + 7;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int a[MAX_N];
ll g[MAX_N];

int d, n;

void dfs(int x, int f, const int& r);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(d, n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    ll r{};
    for (int i = 1; i <= n; i++) {
        dfs(i, 0, i);
        r += g[i];
        r %= MOD;
    }
    std::cout << r << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f, const int& r) {
    g[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        if ((a[v] < a[r] or (a[v] == a[r] and v <= r)) and a[r] - a[v] <= d) {
            dfs(v, x, r);
            g[x] += g[x] * g[v] % MOD;
            g[x] %= MOD;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}