#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 1e9 + 7;

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>(), a1 = 1, a2 = 1;
    n++, m++;
    n %= MOD;
    m %= MOD;
    if (n > m) {
        std::swap(n, m);
    }

    for (int i = 1; i < n; i++) {
        a1 *= i;
        a1 %= MOD;
    }
    for (int i = m + 1; i < n + m; i++) {
        a2 *= i;
        a2 %= MOD;
    }

    std::cout << (a2 * quick_pow(a1, MOD - 2) + m - 1) % MOD << '\n';

    return 0;
}

ll quick_pow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
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