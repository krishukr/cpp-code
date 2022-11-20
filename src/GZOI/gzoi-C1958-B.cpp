#include <cstdio>
#include <iostream>
#include <type_traits>

using ll = long long;

constexpr int MAX_N = 1000050;
constexpr int MOD = 998244353;

ll fac[MAX_N], ifa[MAX_N], inv[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, a, b;
    read(n, a, b);
    if (a > b) {
        std::swap(a, b);
    }
    auto c = n - a - b;
    if (c < 0) {
        a += c;
        b += c;
        c = 0;
    }

    fac[0] = ifa[0] = inv[1] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 2; i <= n; i++) {
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        ifa[i] = ifa[i - 1] * inv[i] % MOD;
    }

    ll ans{};
    for (int i = 0; i <= a; i++) {
        ans += ifa[i] * ifa[a - i] % MOD * ifa[b - i] % MOD;
        ans %= MOD;
    }
    ans *= fac[a];
    ans %= MOD;
    ans *= fac[b];
    ans %= MOD;
    if (c) {
        ans *= fac[a + b + c];
        ans %= MOD;
        ans *= ifa[a + b];
        ans %= MOD;
    }
    std::cout << ans << '\n';

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