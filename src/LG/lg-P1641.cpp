#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 2000050;
constexpr int MOD = 20100403;

int fac[MAX_N];

template <typename T>
T quick_pow(T a, T b);

int combination(int a, int b);

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
    fac[0] = 1;
    for (int i = 1; i <= n + m; i++) {
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    }
    std::cout << (combination(n + m, m) - combination(n + m, m - 1) + MOD) % MOD
              << '\n';

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

int combination(int a, int b) {
    if (a < b) {
        return 0;
    } else {
        return 1ll * fac[a] * quick_pow<ll>(fac[b], MOD - 2) % MOD *
               quick_pow<ll>(fac[a - b], MOD - 2) % MOD;
    }
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