#include <cstdio>
#include <iostream>
#include <memory>

using ll = long double;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        ll x, y, z;
        read(x, y, z);
        if (z == 1 and (y > 1 or x > 1)) {
            std::cout << "Merry" << '\n';
            continue;
        }
        if (x > z) {
            std::cout << "Merry" << '\n';
            continue;
        }
        if (y > ((z - 1 + z - x - 1) * (x + 1) / 2.0) + 1.0) {
            std::cout << "Merry" << '\n';
            continue;
        }
        std::cout << "Renko" << '\n';
    }

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