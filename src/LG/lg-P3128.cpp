#include <cstdio>
#include <iostream>

constexpr int MAX_N = 50050;
constexpr int MAX_L = 21;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int d[MAX_N], f[MAX_L][MAX_N];

void dfs1(int x, int fa);

int LCA(int x, int y);

int b[MAX_N];
int ans;

void dfs2(int x, int fa);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs1(1, 0);

    for (int i = 1; i <= k; i++) {
        int x, y;
        read(x, y);
        const auto l = LCA(x, y);
        b[x]++;
        b[y]++;
        b[l]--;
        b[f[0][l]]--;
    }
    dfs2(1, 0);
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int fa) {
    d[x] = d[fa] + 1;
    for (int i = 0; i + 1 < MAX_L; i++) {
        f[i + 1][x] = f[i][f[i][x]];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        f[0][v] = x;
        dfs1(v, x);
    }
}

int LCA(int x, int y) {
    if (d[x] < d[y]) {
        std::swap(x, y);
    }
    if (d[x] != d[y]) {
        for (int i = MAX_L - 1; i >= 0; i--) {
            if (d[y] <= d[f[i][x]]) {
                x = f[i][x];
            }
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAX_L - 1; i >= 0; i--) {
        if (f[i][x] == f[i][y]) {
            continue;
        }
        x = f[i][x];
        y = f[i][y];
    }
    return f[0][x];
}

void dfs2(int x, int fa) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs2(v, x);
        b[x] += b[v];
    }
    ans = std::max(ans, b[x]);
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