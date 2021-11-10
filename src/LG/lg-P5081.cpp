#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 10000050;
const ll MOD = 20040313;

ll inv[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>();

    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += n * inv[n - i] % MOD;
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
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