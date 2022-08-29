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

    ll n, m, k, x;
    read(n, m, k, x);
    std::cout << (x % n + m % n * quick_pow(10ll, k, n) % n) % n << '\n';

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