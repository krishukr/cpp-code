#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 1e9 + 7;

ll fac[200050];

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    fac[0] = 1;
    for (int i = 1; i <= 200005; i++) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }
    ll inv = quick_pow(2, MOD - 2);

    int t = read<int>();
    while (t--) {
        ll n = read<ll>();
        n *= 2;

        std::cout << fac[n] * inv % MOD << '\n';
    }

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