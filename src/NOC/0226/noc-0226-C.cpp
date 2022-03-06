#include <cstdio>
#include <iostream>

typedef long long ll;

const int MOD = 19260817;

ll fact[MOD + 5];

ll quick_pow(ll a, ll b, ll p);

ll combination(ll n, ll m, ll p);

ll lucas(ll n, ll m, ll p);

void init();

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    init();
    int T = read<int>();
    while (T--) {
        ll n = read<ll>(), m = read<ll>();
        std::cout << (2 * m % MOD) * lucas(n + m - 1, m, MOD) % MOD << '\n';
    }

    return 0;
}

ll quick_pow(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll combination(ll n, ll m, ll p) {
    if (n < m) {
        return 0;
    } else {
        return fact[n] * quick_pow(fact[m], p - 2, p) % p *
               quick_pow(fact[n - m], p - 2, p) % p;
    }
}

ll lucas(ll n, ll m, ll p) {
    if (m == 0) {
        return 1 % p;
    } else {
        return lucas(n / p, m / p, p) * combination(n % p, m % p, p) % p;
    }
}

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MOD; i++) {
        fact[i] = fact[i - 1] * i % MOD;
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