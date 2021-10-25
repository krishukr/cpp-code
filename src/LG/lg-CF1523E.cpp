#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;
const int MOD = 1e9 + 7;

ll frac[MAX_N];

ll quick_pow(ll a, ll b);

inline ll inv(ll x);

ll combination(ll n, ll m);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int b = 0;
    frac[0] = 1;

    int T = read<int>();
    while (T--) {
        ll n = read<ll>(), k = read<ll>();
        if (n > b) {
            for (int i = b + 1; i <= n; i++) {
                frac[i] = frac[i - 1] * i;
                frac[i] %= MOD;
            }
            b = n;
        }

        ll ans = 1;
        for (int i = 1; i < n; i++) {
            ans += combination(n - (i - 1) * (k - 1), i) *
                   inv(combination(n, i)) % MOD;
            ans %= MOD;
        }
        std::cout << ans << '\n';
    }

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

inline ll inv(ll x) { return quick_pow(x, MOD - 2); }

ll combination(ll n, ll m) {
    if (n < m) {
        return 0;
    } else {
        return frac[n] * inv(frac[m]) % MOD * inv(frac[n - m]) % MOD;
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