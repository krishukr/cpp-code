#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int f[MAX_N][MAX_N];
int siz[MAX_N];

void dfs(int x, int fa);

int n, q;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, q);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }
    dfs(1, 0);
    std::cout << f[1][q] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dfs(int x, int fa) {
    siz[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        siz[x] += siz[v];
        for (int j = std::min(siz[x], q); j >= 1; j--) {
            for (int k = std::min(siz[v], j - 1); k >= 0; k--) {
                f[x][j] =
                    std::max(f[x][j], f[x][j - k - 1] + f[v][k] + node[i].w);
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