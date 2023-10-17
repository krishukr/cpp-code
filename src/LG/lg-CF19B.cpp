#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 2050;

ll f[MAX_N];
int t[MAX_N], c[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::fill(f + 1, f + MAX_N, LLONG_MAX >> 2);

    int n, volume{};
    read(n);
    for (int i = 1; i <= n; i++) {
        read(t[i], c[i]);
        t[i] += 1;
        volume += t[i];
    }
    volume = std::min(volume, n);

    for (int i = 1; i <= n; i++) {
        for (int j = volume; j > 0; j--) {
            f[j] = std::min(f[j], f[std::max(j - t[i], 0)] + c[i]);
        }
    }
    std::cout << f[volume] << '\n';

    std::cout << std::flush;
    return 0;
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar();
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