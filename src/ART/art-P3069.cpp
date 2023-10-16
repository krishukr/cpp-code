#include <cstdio>
#include <iostream>

using ll = long long;

constexpr ll MOD = 998244353;
constexpr int MAX_N = 1000050;

ll f[MAX_N];

ll quick_pow(ll a, ll b);

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    const int n = s.length();
    ll t{};

    for (int i = 1; i <= n; i++) {
        const auto d = s[i - 1] - 48;
        t = t * 10 + d;
        t %= MOD;
        f[i] = f[i - 1] * 11 % MOD + quick_pow(2, i - 1) * d % MOD;
        f[i] %= MOD;
    }
    std::cout << (f[n] * 2 - t + MOD) % MOD << '\n';

    std::cout << std::flush;
    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res{1};
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
