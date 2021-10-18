#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 105;
const int MAX_M = 2050;
const ll MOD = 998244353;

ll s[MAX_N];
ll mp[MAX_N][MAX_M], dp[MAX_N][MAX_M];

template <typename T>
T read();

int main() {
    // freopen("meal.in", "r", stdin);
    // freopen("meal.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    ll res = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mp[i][j] = read<ll>();
            s[i] += mp[i][j];
            s[i] %= MOD;
        }
        res *= s[i] + 1;
        res %= MOD;
    }

    res = (res - 1 + MOD) % MOD;

    for (int i = 1; i <= m; i++) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= 2 * (j - 1); k++) {
                dp[j][k] += dp[j - 1][k] * (s[j] - mp[j][i]) % MOD;
                dp[j][k] %= MOD;

                dp[j][k + 1] += dp[j - 1][k];
                dp[j][k + 1] %= MOD;

                dp[j][k + 2] += dp[j - 1][k] * mp[j][i] % MOD;
                dp[j][k + 2] %= MOD;
            }
        }
        for (int j = n + 1; j <= n + n; j++) {
            res = (res - dp[n][j] + MOD) % MOD;
        }
    }

    std::cout << res << '\n';

    fclose(stdin);
    fclose(stdout);
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