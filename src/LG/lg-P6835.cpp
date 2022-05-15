#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;
constexpr int MOD = 998244353;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

ll f[MAX_N], g[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int id, n, m;
    read(id, n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        create(u, v);
    }

    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = head[i]; j; j = node[j].nxt) {
            int v = node[j].v;
            f[i] = (f[i] + g[i - 1] - g[v - 1] + 1 + MOD) % MOD;
        }
        g[i] = (f[i] + g[i - 1]) % MOD;
    }
    std::cout << g[n] << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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