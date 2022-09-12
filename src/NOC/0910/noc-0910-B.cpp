#include <algorithm>
#include <cstdio>
#include <iostream>

using pi = std::pair<int, int>;

constexpr int MAX_N = 100050;

int a[MAX_N << 1];
pi u[MAX_N], d[MAX_N], o[MAX_N];
int cu, cd;

int tree[MAX_N << 1];

void mod(int x, const int& v);

int query(int x);

int n;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        read(o[i].first, o[i].second);
        a[i * 2 - 1] = o[i].first;
        a[i * 2] = o[i].second;
    }
    std::sort(a + 1, a + n * 2 + 1);

    for (int i = 1; i <= n; i++) {
        o[i].first = std::lower_bound(a + 1, a + n * 2 + 1, o[i].first) - a;
        o[i].second = std::lower_bound(a + 1, a + n * 2 + 1, o[i].second) - a;
        if (o[i].first > o[i].second) {
            u[++cu] = o[i];
        } else {
            d[++cd] = o[i];
        }
    }

    int r{};
    for (int i = 1; i <= cu; i++) {
        mod(u[i].second, query(u[i].first - 1) + 1);
    }
    r = std::max(r, query(n * 2));
    std::fill(tree, tree + n * 2 + 1, 0);
    for (int i = cd; i >= 1; i--) {
        mod(d[i].first, query(d[i].second - 1) + 1);
    }
    r = std::max(r, query(n * 2));
    std::cout << r << '\n';

    return 0;
}

void mod(int x, const int& v) {
    while (x <= n * 2) {
        tree[x] = std::max(tree[x], v);
        x += x & -x;
    }
}

int query(int x) {
    int r{};
    while (x) {
        r = std::max(r, tree[x]);
        x -= x & -x;
    }
    return r;
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