#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 10000019;

ll fact[MOD + 5];

ll quick_pow(ll a, ll b, ll p);

ll combination(ll n, ll m, ll p);

ll lucas(ll n, ll m, ll p);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    read<int>();
    ll n = read<ll>(), k = read<ll>();
    ll m = std::min(MOD, n + k);

    fact[0] = 1;
    for (ll i = 1; i <= m; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    std::cout << lucas(n + k - 1, k - 1, MOD);

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