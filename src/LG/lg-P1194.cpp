#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 505;

struct {
    int u;
    int v;
    int w;
} node[MAX_N * MAX_N];

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

    int a, b;
    read(a, b);
    const auto S = b + 1;
    for (int i = 1; i <= b; i++) {
        for (int j = 1; j <= b; j++) {
            int x;
            read(x);
            if (i < j and x) {
                node[++cnt] = {i, j, x};
            }
        }
    }
    for (int i = 1; i <= b; i++) {
        node[++cnt] = {S, i, a};
    }
    for (int i = 1; i <= S; i++) {
        fa[i] = i;
    }
    std::sort(node + 1, node + cnt + 1,
              [](const auto& x, const auto& y) { return x.w < y.w; });

    int t{}, s{};
    for (int i = 1; i <= cnt; i++) {
        const auto u = node[i].u, v = node[i].v, w = node[i].w;
        if (find(u) != find(v)) {
            merge(u, v);
            s += w;
            t++;
        }
    }
    std::cout << s << '\n';

    return 0;
}

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

void merge(int x, int y) {
    if (find(x) != find(y)) {
        fa[find(x)] = find(y);
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