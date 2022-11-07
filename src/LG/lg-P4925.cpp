#include <cstdio>
#include <iostream>

using ll = long long;

template <typename T>
T quick_pow(T a, T b, T p);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll k, l, p;
    read(k, l, p);
    ll s, w;
    read(s, w);

    if (l == 1) {
        if (s) {
            std::cout << 1 << '\n';
            return 0;
        } else {
            std::cout << k % p << '\n';
            return 0;
        }
    }

    k %= p;
    std::cout << (s ? 1 : k) * (k - 1) % p * quick_pow(k - 2, l - 2, p) % p
              << '\n';

    return 0;
}

template <typename T>
T quick_pow(T a, T b, T p) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return r;
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