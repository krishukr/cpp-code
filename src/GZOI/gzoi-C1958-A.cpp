#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1050;
constexpr int MOD = 998244353;

int a[MAX_N];
ll f[MAX_N][MAX_N];
ll w[MAX_N];

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

    int n, p;
    read(n, p);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    const auto ip = quick_pow<ll>(p, MOD - 2);
    w[0] = 1;
    for (int i = 1; i <= n; i++) {
        w[i] = w[i - 1] * p % MOD;
    }

    f[1][1] = 1;
    for (int i = 2; i < n; i++) {
        if (a[i]) {
            for (int j = 2; j <= i; j++) {
                f[i][j] = f[i - 1][j - 1];
            }
        } else {
            ll s{};
            for (int j = 1; j < i; j++) {
                s += f[i - 1][j] * w[j - 1] % MOD;
                s %= MOD;
            }
            for (int j = 1; j < i; j++) {
                f[i][j] = s * (1 - p + MOD) % MOD;
                f[i][1] += f[i - 1][j] * w[j] % MOD;
                f[i][1] %= MOD;
                s = (s - f[i - 1][j] + MOD) * ip % MOD;
            }
        }
    }

    ll ans{};
    for (int i = 1; i < n; i++) {
        ans += f[n - 1][i] * w[i] % MOD;
        ans %= MOD;
    }
    std::cout << ans << '\n';

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