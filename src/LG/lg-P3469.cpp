#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 500050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dfn[MAX_N], low[MAX_N];
ll f[MAX_N];
int tot;

int tarjan(int x);

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
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    tarjan(1);

    for (int i = 1; i <= n; i++) {
        std::cout << f[i] << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

int tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    int s{}, o{};
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!dfn[v]) {
            const auto z = tarjan(v);
            low[x] = std::min(low[x], low[v]);
            o += z;
            if (low[v] >= dfn[x]) {
                s += z;
                f[x] += 1ll * z * (n - z - 1);
            }
        } else {
            low[x] = std::min(low[x], dfn[v]);
        }
    }

    f[x] += 1ll * s * (n - s - 1);
    f[x] += 2 * (n - 1);
    return o + 1;
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