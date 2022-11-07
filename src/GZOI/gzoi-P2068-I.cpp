#include <cstdio>
#include <cstdlib>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 105;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int c[MAX_N], v[MAX_N];
ll f[MAX_N][MAX_N];

void dfs(int x, int fa);

int n, p;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, p);
    for (int i = 1; i <= n; i++) {
        read(c[i], v[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs(1, 0);
    std::cout << f[1][p] << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int fa) {
    for (int i = c[x]; i <= p; i++) {
        f[x][i] = v[x];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        for (int j = p; j >= c[x]; j--) {
            for (int k = j; k >= c[x]; k--) {
                f[x][j] = std::max(f[x][j], f[x][k] + f[v][j - k]);
            }
        }
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