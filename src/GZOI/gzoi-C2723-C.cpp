#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 305;

int f[MAX_N];
int c[2][MAX_N];
int g[2][MAX_N][MAX_N];

int find(int x, int y);

int S, ans{INT_MAX};
bool vis[MAX_N];

void dfs(int x, int d, int a);

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
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        read(f[x], c[0][x], c[1][x]);
        for (int j = 0; j < 2; j++) {
            for (int k = 1; k <= c[j][x]; k++) {
                read(g[j][x][k]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        S = i;
        dfs(i, 0, 0);
        memset(vis, 0, sizeof(vis));
    }
    std::cout << ans << '\n';

    return 0;
}

int find(int x, int y) {
    for (int i = 1; i <= c[0][y]; i++) {
        if (g[0][y][i] == x) {
            return 1;
        }
    }
    return 0;
}

void dfs(int x, int d, int a) {
    if (a > ans) {
        return;
    }
    if (x == S and a) {
        ans = a;
        return;
    }
    vis[x] = true;
    for (int i = 1; i <= c[d][x]; i++) {
        const auto v = g[d][x][i];
        if (vis[v] and v != S) {
            continue;
        }
        dfs(v, find(x, v), a + f[x]);
    }
    vis[x] = false;
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