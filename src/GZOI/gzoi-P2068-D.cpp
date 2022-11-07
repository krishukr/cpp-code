#include <cstdio>
#include <iostream>

constexpr int MAX_N = 305;

struct {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

int f[MAX_N][MAX_N];
int siz[MAX_N];

void dfs(int x);

int n, m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x, f[i][1]);
        create(x, i);
    }
    dfs(0);
    std::cout << f[0][m + 1] << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    siz[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        dfs(v);
        siz[x] += siz[v];
        for (int j = m + 1; j >= 1; j--) {
            for (int k = std::min(siz[x], j - 1); k >= 0; k--) {
                f[x][j] = std::max(f[x][j], f[v][k] + f[x][j - k]);
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