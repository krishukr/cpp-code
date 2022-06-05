#include <cassert>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 30050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int ans;

int dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("track.in", "r", stdin);
    freopen("track.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    assert(m == 1);

    for (int i = 1; i < n; i++) {
        int u, v, w;
        read(u, v, w);
        create(u, v, w);
        create(v, u, w);
    }
    dfs(1, 0);
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

int dfs(int x, int f) {
    int mx{}, nx{};
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        if (v == f) {
            continue;
        }
        nx = std::max(nx, dfs(v, x) + w);
        if (mx < nx) {
            std::swap(mx, nx);
        }
    }
    ans = std::max(ans, mx + nx);
    return mx;
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