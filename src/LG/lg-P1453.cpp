#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int fa[MAX_N];

int find(int x);

int p[MAX_N];
double f[2][MAX_N];

void dfs(int x, int ft);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, S, T;
    read(n);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        read(p[i]);
    }
    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        x++, y++;
        if (find(x) == find(y)) {
            S = x;
            T = y;
        } else {
            create(x, y);
            create(y, x);
            fa[find(y)] = find(x);
        }
    }

    dfs(S, 0);
    double r = f[0][S];
    dfs(T, 0);
    r = std::max(r, f[0][T]);
    double k;
    scanf("%lf", &k);
    std::cout << std::fixed << std::setprecision(1) << r * k << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

void dfs(int x, int ft) {
    f[0][x] = 0;
    f[1][x] = p[x];
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == ft) {
            continue;
        }
        dfs(v, x);
        f[0][x] += std::max(f[0][v], f[1][v]);
        f[1][x] += f[0][v];
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