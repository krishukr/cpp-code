#include <cstdio>
#include <iostream>

using ll = long long;

constexpr ll MOD = 1e9 + 7;

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

    ll n, k;
    read(n, k);
    ll p{1}, q{1};
    for (int i = 0; i < k; i++) {
        p *= (n - i);
        p %= MOD;
    }
    for (int i = 1; i <= k; i++) {
        q *= i * n % MOD;
        q %= MOD;
    }
    std::cout << (p * quick_pow(q, MOD - 2) % MOD) << '\n';

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