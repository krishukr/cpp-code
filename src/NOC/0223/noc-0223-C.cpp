#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 2050;
const int MOD = 998244353;

ll frac[MAX_N], sm[MAX_N];
ll s[MAX_N][MAX_N], dp[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>();

    frac[1] = 1;
    for (int i = 2; i <= n; i++) {
        frac[i] = frac[i - 1] * i;
        frac[i] %= MOD;
    }

    for (int i = 1; i <= n; i++) {
        s[i][1] = s[i][i] = 1;
        for (int j = 2; j < i; j++) {
            s[i][j] = s[i - 1][j - 1] + (j * s[i - 1][j] % MOD);
            s[i][j] %= MOD;
        }
    }

    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        sm[0] = dp[i - 1][0];
        for (int j = 1; j <= m; j++) {
            sm[j] = sm[j - 1] + dp[i - 1][j];
            sm[j] %= MOD;
            dp[i][j] = sm[j - 1];
        }
        for (int j = k + 1; j <= m; j++) {
            dp[i][j] = (dp[i][j] - sm[j - k - 1] + MOD) % MOD;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            ans += (s[n][i] * frac[i] % MOD) * dp[i][j] % MOD;
            ans %= MOD;
        }
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