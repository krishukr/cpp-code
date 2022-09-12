#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;
constexpr int INF = 0x3f3f3f3f;

int f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, k;
    read(n, m, k);
    std::fill(f, f + n + 10, INF);
    f[k] = 0;

    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        const auto ux = f[x], uy = f[y];
        f[x] = std::min(f[x] + 1, uy);
        f[y] = std::min(f[y] + 1, ux);
    }
    for (int i = 1; i <= n; i++) {
        std::cout << (f[i] == INF ? -1 : f[i]) << ' ';
    }
    std::cout << '\n';

    return 0;
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