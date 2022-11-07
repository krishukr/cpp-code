#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 1050;
constexpr int INF = 0xafafafaf;

using bs = std::bitset<MAX_N>;

int s[MAX_N], a[MAX_N], fa[MAX_N];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

void merge(int x, int y);

int x[MAX_N], y[MAX_N], z[MAX_N];
bs d[MAX_N], f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        read(x[i], y[i], z[i]);
        d[x[i] + z[i]][y[i] + z[i]] = d[y[i] + z[i]][x[i] + z[i]] = true;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < z[i]; j++) {
            if (d[x[i] + j][y[i] + j]) {
                std::cout << -1 << '\n';
                return 0;
            }
            merge(x[i] + j, y[i] + j);
        }
    }

    memset(s, 0xaf, sizeof(s));
    for (int i = 1; i <= n; i++) {
        f[find(i)][i] = true;
    }
    for (int i = 1; i <= n; i++) {
        const auto u = find(i);
        if (s[u] == INF) {
            bs g{}, v{};
            for (int j = 1; j <= n; j++) {
                if (f[u][j]) {
                    g |= d[j];
                }
            }
            for (int j = 1; j <= n; j++) {
                if (g[j] and s[find(j)] != INF) {
                    v[s[find(j)]] = true;
                }
            }
            for (int j = 0; j <= n; j++) {
                if (!v[j]) {
                    s[u] = j;
                    break;
                }
            }
        }
        a[i] = s[u];
    }
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

void merge(int x, int y) {
    if (find(x) != find(y)) {
        fa[find(y)] = find(x);
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
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