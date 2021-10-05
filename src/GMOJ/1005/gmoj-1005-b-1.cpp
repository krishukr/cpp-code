#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 2050;
const ll MOD = 258280327;

ll dp[MAX_N][MAX_N], p[MAX_N];

ll quick_pow(ll a, ll b);

inline ll inv(ll x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        ll n = read<ll>(), x = read<ll>(), y = read<ll>();
        memset(dp, 0, sizeof(dp));
        memset(p, 0, sizeof(p));
        dp[0][0] = p[0] = 1;

        for (int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * ((y - x) * inv(y) % MOD);
            p[i] %= MOD;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                dp[i][j] = dp[i - 1][j - 1] * p[j - 1];
                dp[i][j] %= MOD;
                dp[i][j] += dp[i - 1][j] * ((1 - p[j] + MOD) % MOD) % MOD;
                dp[i][j] %= MOD;
            }
        }

        for (int i = 0; i < n; i++) {
            ll res = 0;
            for (int j = 0; j < n; j++) {
                res += dp[j][i] * p[i] % MOD;
                res %= MOD;
            }
            std::cout << res * inv(n) % MOD << ' ';
        }
        std::cout << '\n';
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