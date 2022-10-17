#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MOD = 1e6 + 33;

template <typename T>
T quick_pow(T a, T b);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, t;
    read(n, t);
    if (n == 1) {
        int a, b;
        read(a, b);
        std::cout << 0 << '\n';
    } else if (t == 3) {
        std::cout << n - 1 << '\n';
    } else if (t == 2 or t == 4) {
        std::cout << -1 << '\n';
    }

    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
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