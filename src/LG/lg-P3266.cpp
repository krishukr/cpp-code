#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 3000050;
const int MOD = 1e9 + 7;

ll fact[MAX_N];
int n, m;

ll quick_pow(ll a, ll b);

ll combination(ll n, ll m);

ll calcA(ll x, ll y);

ll calcB(ll x, ll y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    fact[0] = 1;
    for (int i = 1; i <= n + n + m + 10; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    ll ans = combination(n + n + m + 1, n);
    ans = (ans - calcA(n - 1, n + m + 2) + MOD) % MOD;
    ans = (ans - calcB(n + m + 2, n - 1) + MOD) % MOD;

    std::cout << ans << '\n';

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

ll combination(ll n, ll m) {
    if (n < m) {
        return 0;
    } else {
        return fact[n] * quick_pow(fact[m], MOD - 2) % MOD *
               quick_pow(fact[n - m], MOD - 2) % MOD;
    }
}

ll calcA(ll x, ll y) {
    if (x < 0 or y < 0) {
        return 0;
    } else {
        return (combination(x + y, y) - calcB(y + 1, x - 1) + MOD) % MOD;
    }
}

ll calcB(ll x, ll y) {
    if (x < 0 or y < 0) {
        return 0;
    } else {
        return (combination(x + y, y) - calcA(y - m - 2, x + m + 2) + MOD) %
               MOD;
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