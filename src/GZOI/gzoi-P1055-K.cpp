#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;
constexpr int MAX_L = 20;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dep[MAX_N];
int fa[MAX_L][MAX_N];

void dfs(int x, int f);

int LCA(int x, int y);

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
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs(1, 0);

    while (m--) {
        int x, y, z;
        read(x, y, z);
        const auto xy = LCA(x, y), yz = LCA(y, z), xz = LCA(x, z);
        if (xy == yz) {
            std::cout << xz << ' ';
        } else if (xy == xz) {
            std::cout << yz << ' ';
        } else if (yz == xz) {
            std::cout << xy << ' ';
        }
        std::cout << dep[x] + dep[y] + dep[z] - dep[xy] - dep[yz] - dep[xz]
                  << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dep[x] = dep[f] + 1;
    for (int i = 0; i + 1 < MAX_L; i++) {
        fa[i + 1][x] = fa[i][fa[i][x]];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        fa[0][v] = x;
        dfs(v, x);
    }
}

int LCA(int x, int y) {
    if (dep[x] < dep[y]) {
        std::swap(x, y);
    }
    if (dep[x] != dep[y]) {
        for (int i = MAX_L - 1; i >= 0; i--) {
            if (dep[y] <= dep[fa[i][x]]) {
                x = fa[i][x];
            }
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAX_L - 1; i >= 0; i--) {
        if (fa[i][x] == fa[i][y]) {
            continue;
        }
        x = fa[i][x];
        y = fa[i][y];
    }
    return fa[0][x];
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