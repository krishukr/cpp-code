#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;

int a[MAX_N], f[MAX_N], g[MAX_N], r[MAX_N];

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
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        r[1] = std::max(r[1], a[i]);
    }

    for (int i = 1; i < n; i++) {
        f[std::min(i, n - i)] =
            std::max(f[std::min(i, n - i)], std::max(a[i], a[i + 1]));
    }
    for (int i = 2; i < n; i++) {
        g[std::min(i - 1, n - i)] = std::max(
            g[std::min(i - 1, n - i)],
            std::max(std::min(a[i - 1], a[i]), std::min(a[i], a[i + 1])));
    }

    for (int i = (n >> 1); i > 0; i--) {
        r[i << 1] = std::max(r[(i + 1) << 1], f[i]);
        r[(i << 1) + 1] = std::max(r[((i + 1) << 1) + 1], g[i]);
    }
    for (int i = n; i > 0; i--) {
        std::cout << r[i] << ' ';
    }
    std::cout << '\n';

    return 0;
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