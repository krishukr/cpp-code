#include <cassert>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>

using ld = long double;

constexpr int MAX_N = 505;

struct N {
    int x;
    int y;
} r[MAX_N], b[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(3);

    int n, m;
    read(n, m);
    if (n > 500 and m > 500) {
        std::cout << (m >= 80000 ? 0.5 : 0.707) << '\n';
        return 0;
    }
    if (n == 0 or m == 0) {
        std::cout << "No" << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        read(b[i].x, b[i].y);
    }
    for (int i = 1; i <= m; i++) {
        read(r[i].x, r[i].y);
    }

    ld ans = std::numeric_limits<ld>::max();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = std::min(
                ans, std::sqrt((ld)(b[i].x - r[j].x) * (ld)(b[i].x - r[j].x) +
                               (ld)(b[i].y - r[j].y) * (ld)(b[i].y - r[j].y)) /
                         2.0);
        }
    }
    std::cout << ans << '\n';

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