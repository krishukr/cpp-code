#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

using ll = long long;
using ld = long double;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);

    int T;
    read(T);
    while (T--) {
        ll x1, y1, x2, y2, x3, y3, r;
        read(x1, y1, x2, y2, x3, y3, r);
        std::cout << std::fixed << std::setprecision(2)
                  << 1.0 *
                             std::abs((y1 - y2) * x3 + (x2 - x1) * y3 -
                                      ((y1 - y2) * x1 + (x2 - x1) * y1)) /
                             std::sqrt((x1 - x2) * (x1 - x2) +
                                       (y1 - y2) * (y1 - y2)) -
                         r
                  << ' '
                  << std::max(std::sqrt((x1 - x3) * (x1 - x3) +
                                        (y1 - y3) * (y1 - y3)),
                              std::sqrt((x2 - x3) * (x2 - x3) +
                                        (y2 - y3) * (y2 - y3))) +
                         r
                  << '\n';
    }

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