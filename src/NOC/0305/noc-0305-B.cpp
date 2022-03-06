#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 30000050;
const int MOD = 1e9 + 7;

int fact[MAX_N << 1], inv[MAX_N];

template <typename T>
T quick_pow(T a, T b);

template <typename T>
T combination(const T& n, const T& m);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    if (n == 0 or n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }

    fact[0] = 1;
    for (int i = 1; i <= (n << 1); i++) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }
    inv[n] = quick_pow<ll>(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
    }

    ll p = quick_pow<ll>(2, n), f = fact[n - 1], ans = 0;
    for (int i = n; i >= 0; i--) {
        if (i & 1) {
            ans =
                ((ans - (combination(n, i) * p % MOD * f % MOD)) % MOD + MOD) %
                MOD;
        } else {
            ans =
                ((ans + (combination(n, i) * p % MOD * f % MOD)) % MOD + MOD) %
                MOD;
        }

        p = 1ll * p * inv[2] % MOD;
        f = 1ll * f * (n + n - i) % MOD;
    }

    std::cout << (ans % MOD + MOD) % MOD << '\n';

    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

template <typename T>
T combination(const T& n, const T& m) {
    if (n < m) {
        return 0;
    } else {
        return 1ll * fact[n] * inv[m] % MOD * inv[n - m] % MOD;
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