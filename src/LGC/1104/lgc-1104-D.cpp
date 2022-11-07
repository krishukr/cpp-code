#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

using ll = long long;

const double PI = std::acos(-1.0);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll x1, y1, x2, y2;
    read(x1, y1, x2, y2);
    std::cout << std::fixed << std::setprecision(8)
              << ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) * 7.0 / 24.0 *
                     PI
              << '\n';

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