#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;

struct Node {
    int u;
    int v;
    int w;
} node[MAX_N];

int f[MAX_N], g[MAX_N];

void read(Node& x);

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
    for (int i = 1; i <= m; i++) {
        read(node[i]);
    }
    std::sort(node + 1, node + m + 1,
              [](const Node& a, const Node& b) { return a.w < b.w; });

    for (int i = 1, j = 1; i <= m; i = j) {
        while (node[i].w == node[j].w) {
            j++;
        }
        for (int k = i; k < j; k++) {
            f[node[k].v] = std::max(f[node[k].v], g[node[k].u] + 1);
        }
        for (int k = i; k < j; k++) {
            g[node[k].v] = std::max(g[node[k].v], f[node[k].v]);
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, f[i]);
    }
    std::cout << ans << '\n';

    return 0;
}

void read(Node& x) { read(x.u, x.v, x.w); }

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