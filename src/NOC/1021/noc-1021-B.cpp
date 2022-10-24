#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

struct E {
    int l;
    int r;
    int v;
};

std::vector<E> a, b;
int n, m, G{1};

void solve(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        a.push_back({i, i, i});
    }
    for (int i = 1; i <= m; i++) {
        solve(read<int>());
    }
    for (const auto& i : a) {
        for (int j = i.l; j <= i.r; j++) {
            std::cout << i.v << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}

void solve(int x) {
    if (G % x == 0) {
        return;
    }
    for (auto& i : a) {
        i.v = (i.v + x - 1) / x * x;
    }
    for (const auto& i : a) {
        if (b.empty() or i.v != b.back().v) {
            b.push_back(i);
        } else {
            b.back().r = i.r;
        }
    }
    std::swap(a, b);
    std::vector<E>().swap(b);
    G = a.front().v;
    for (const auto& i : a) {
        G = std::__gcd(G, i.v);
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