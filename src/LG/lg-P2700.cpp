#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

struct {
    int u;
    int v;
    int w;
} node[MAX_N];

bool v[MAX_N];
int fa[MAX_N];

int find(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    ll r{};
    read(n, k);
    for (int i = 1; i <= k; i++) {
        v[read<int>()] = true;
    }
    for (int i = 1; i < n; i++) {
        read(node[i].u, node[i].v, node[i].w);
        r += node[i].w;
    }
    std::sort(node + 1, node + n + 1,
              [](const auto& x, const auto& y) { return x.w > y.w; });

    for (int i = 1; i < n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i < n; i++) {
        const auto u = node[i].u, v = node[i].v, w = node[i].w;
        if (find(u) != find(v) and !(::v[find(u)] and ::v[find(v)])) {
            r -= w;
            if (::v[find(v)]) {
                ::v[find(u)] = true;
            } else if (::v[find(u)]) {
                ::v[find(v)] = true;
            }
            fa[find(u)] = find(v);
        }
    }
    std::cout << r << '\n';

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