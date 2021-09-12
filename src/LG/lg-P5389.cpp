#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 998244353;

ll quick_pow(ll a, ll b);

struct Div {
    ll a;
    ll b;

    ll operator%(const ll &m) const { return a * quick_pow(b, m - 2) % m; }
} d;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>();
    d.b = 2;

    if (n) {
        n %= MOD;
        d.a = (1 - (Div){3, n * (n + 2) % MOD} % MOD + MOD) % MOD;
    } else {
        d.a = 1;
    }

    std::cout << d % MOD << '\n';

    return 0;
}

ll quick_pow(ll a, ll b) {
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