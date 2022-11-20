#include <algorithm>
#include <cstdio>
#include <iostream>
#include <type_traits>

using ll = long long;

ll lg(ll x);

ll calc(ll x, ll y);

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
        if (a == c and b == d) {
            std::cout << 0 << '\n';
            continue;
        }
        std::cout << std::min(calc(a, b) + calc(c, d),
                              std::abs(a - c) + std::abs(b - d) - 1)
                  << '\n';
    }

    return 0;
}

ll lg(ll x) {
    ll a{1};
    while (a <= x) {
        a <<= 1;
    }
    return a;
}

ll calc(ll x, ll y) {
    if (!(x & y)) {
        return 0;
    }
    ll l{};
    while (true) {
        if (x > y) {
            std::swap(x, y);
        }
        l = lg(y);
        if (x + y >= l) {
            break;
        } else {
            y -= l >> 1;
        }
    }
    return std::min({l - x - 1, l - y - 1, x + y - l});
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