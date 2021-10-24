#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 5050;
const int MOD = 998244353;

#define int long long

int a[MAX_N], sum[MAX_N], g[MAX_N][MAX_N], dp[MAX_N][MAX_N];
int inv[MAX_N];

int quick_pow(int a, int b);

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        sum[a[i]]++;
        inv[i] = quick_pow(i, MOD - 2);
    }
    std::sort(a + 1, a + n + 1);

    dp[0][0] = 1;
    std::fill(g[0], g[0] + n + 1, 1);
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[j] == a[j - 1]) {
                ans += dp[i - 1][j - 1] * inv[n - i + 1] % MOD *
                       (sum[a[j]] - 1) % MOD;
                ans %= MOD;
                continue;
            }

            dp[i][j] = g[i - 1][j - 1] * inv[n - i + 1] % MOD * sum[a[j]] % MOD;
        }

        for (int j = 1; j <= n; j++) {
            g[i][j] = g[i][j - 1] + dp[i][j];
            g[i][j] %= MOD;
        }
    }

    std::cout << ans << '\n';

    return 0;
}

int quick_pow(int a, int b) {
    int res = 1;
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