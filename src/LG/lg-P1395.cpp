#include <cstdio>
#include <iostream>

constexpr int MAX_N = 50050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dep[MAX_N], siz[MAX_N], ans[MAX_N];

void dfs1(int x, int f);

void dfs2(int x, int f);

int n;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs1(1, 0);
    dfs2(1, 0);
    int r{0x3f3f3f3f}, x{};
    for (int i = 1; i <= n; i++) {
        if (r > ans[i]) {
            r = ans[i];
            x = i;
        }
    }
    std::cout << x << ' ' << r << '\n';

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
    ans[1] += dep[x];
}

void dfs2(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        ans[v] = ans[x] + n - siz[v] * 2;
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