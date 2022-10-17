#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MOD = 1e9 + 7;

constexpr int p[15][15] = {{},
                           {0, 2, 4},
                           {0, 0, 12, 36},
                           {0, 0, 0, 112, 336},
                           {0, 0, 0, 0, 912, 2688},
                           {0, 0, 0, 0, 0, 7136, 21312},
                           {0, 0, 0, 0, 0, 0, 56768, 170112},
                           {0, 0, 0, 0, 0, 0, 0, 453504, 1360128},
                           {0, 0, 0, 0, 0, 0, 0, 0, 3626752, 10879488}};

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

    int n, m;
    read(n, m);
    if (n > m) {
        std::swap(n, m);
    }

    if (n == 1) {
        std::cout << quick_pow<ll>(2, m) << '\n';
    } else {
        if (n == m or n + 1 == m) {
            std::cout << p[n][m] << '\n';
        } else {
            std::cout << p[n][n + 1] * quick_pow<ll>(3, m - n - 1) % MOD
                      << '\n';
        }
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