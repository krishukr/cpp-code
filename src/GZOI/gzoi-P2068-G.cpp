#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1505;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int f[2][MAX_N];

void dfs(int x, int fa);

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
        int x, y;
        read(x, y);
        x++;
        for (int i = 1; i <= y; i++) {
            int z;
            read(z);
            z++;
            create(x, z);
            create(z, x);
        }
    }
    dfs(1, 0);
    std::cout << std::min(f[0][1], f[1][1]) << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int fa) {
    f[0][x] = 0;
    f[1][x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        f[0][x] += f[1][v];
        f[1][x] += std::min(f[0][v], f[1][v]);
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