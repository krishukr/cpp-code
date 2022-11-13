#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int f[2][MAX_N];
int c[MAX_N];

void dfs(int x, int fa);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(f, 0x3f, sizeof(f));
    memset(c, 0x3f, sizeof(c));
    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }
    for (int k = 0; k < 2; k++) {
        int x;
        read(x);
        for (int i = 1; i <= x; i++) {
            int y;
            read(y);
            c[y] = k;
        }
    }
    dfs(1, 0);
    std::cout << std::min(f[0][1], f[1][1]) << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dfs(int x, int fa) {
    if (c[x] == INF) {
        f[0][x] = f[1][x] = 0;
    } else {
        f[c[x]][x] = 0;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v, w = node[i].w;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        f[0][x] += std::min(f[0][v], f[1][v] + w);
        f[1][x] += std::min(f[1][v], f[0][v] + w);
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