#include <cstdio>
#include <iostream>

constexpr int MAX_N = 10500;
constexpr int MOD = 10007;

int fact[MAX_N];

template <typename T>
T quick_pow(T a, T b);

template <typename T>
T combination(T n, T m);

template <typename T>
T lucas(T n, T m);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    fact[0] = 1;
    for (int i = 1; i < MOD; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    int n, m;
    read(n, m);
    std::cout << lucas(n * m, n - 1) * quick_pow(n, MOD - 2) % MOD << '\n';

    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T r = 1;
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
T combination(T n, T m) {
    if (n < m) {
        return 0;
    }
    return fact[n] * quick_pow(fact[m], MOD - 2) % MOD *
           quick_pow(fact[n - m], MOD - 2) % MOD;
}

template <typename T>
T lucas(T n, T m) {
    if (m == 0) {
        return 1;
    } else {
        return lucas(n / MOD, m / MOD) * combination(n % MOD, m % MOD) % MOD;
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