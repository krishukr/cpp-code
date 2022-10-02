#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

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
        ll a, b, c, d;
        read(a, b, c, d);
        const auto g = std::__gcd(std::__gcd(a, b), c);
        if (a == 0 and b == 0 and c == 0) {
            std::cout << (d ? "NO" : "YES") << '\n';
        } else {
            std::cout << ((d % g) ? "NO" : "YES") << '\n';
        }
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