#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 305;

struct {
    int u;
    int v;
    int w;
} node[MAX_N * MAX_N + MAX_N];

int cnt;

int fa[MAX_N];

int find(int x);

void merge(int x, int y);

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
    const int S = n + 1;
    for (int i = 1; i <= n; i++) {
        node[++cnt] = {S, i, read<int>()};
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            read(x);
            if (i != j) {
                node[++cnt] = {i, j, x};
            }
        }
    }
    std::sort(node + 1, node + cnt + 1,
              [](const auto& x, const auto& y) { return x.w < y.w; });
    for (int i = 1; i <= S; i++) {
        fa[i] = i;
    }

    int s{};
    for (int i = 1; i <= cnt; i++) {
        const auto u = node[i].u, v = node[i].v, w = node[i].w;
        if (find(u) != find(v)) {
            fa[find(u)] = find(v);
            s += w;
        }
    }
    std::cout << s << '\n';

    return 0;
}

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

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