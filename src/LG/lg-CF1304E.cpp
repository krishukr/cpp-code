#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;
constexpr int MAX_D = 18;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int fa[MAX_D][MAX_N], dep[MAX_N];

void dfs(int x, int f);

int LCA(int x, int y);

int path(int x, int y);

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
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs(1, 0);

    int q;
    read(q);
    while (q--) {
        int x, y, a, b, k;
        read(x, y, a, b, k);
        const auto p1 = path(a, b), p2 = path(a, x) + path(y, b) + 1,
                   p3 = path(a, y) + path(x, b) + 1, ka = k & 1;
        if (p1 <= k and (p1 & 1) == ka) {
            std::cout << "YES\n";
            continue;
        }
        if (p2 <= k and (p2 & 1) == ka) {
            std::cout << "YES\n";
            continue;
        }
        if (p3 <= k and (p3 & 1) == ka) {
            std::cout << "YES\n";
            continue;
        }
        std::cout << "NO\n";
    }

    std::cout << std::flush;
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dep[v] = dep[x] + 1;
        fa[0][v] = x;
        for (int i = 1; (1 << i) <= dep[v]; i++) {
            fa[i][v] = fa[i - 1][fa[i - 1][v]];
        }
        dfs(v, x);
    }
}

int LCA(int x, int y) {
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    for (int dy = dep[y] - dep[x], i = 0; dy; i++, dy >>= 1) {
        if (dy & 1) {
            y = fa[i][y];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAX_D - 1; i >= 0; i--) {
        if (fa[i][x] != fa[i][y]) {
            x = fa[i][x];
            y = fa[i][y];
        }
    }
    return fa[0][x];
}

int path(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)]; }

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar();
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