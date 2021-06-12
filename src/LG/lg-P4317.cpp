#include <iostream>

#define int long long

const int MAX_N = 101;
const int MOD = 10000007;

int dp[MAX_N][MAX_N];

int quick_pow(int a, int b);

void init();

signed main() {
    std::ios::sync_with_stdio(false);

    init();
    int n, cnt = 0, ans = 1;
    std::cin >> n;
    for (int i = 1; i <= n; i <<= 1) {
        n -= i;
        cnt++;
        for (int j = 1; j <= cnt; j++) {
            ans = (ans % MOD) * quick_pow(j, dp[cnt][j]);
            ans %= MOD;
        }
    }
    cnt = 0;
    for (int i = 60; i >= 0; i--) {
        if ((1ll << i) <= n) {
            for (int j = 1; j <= i + 1; j++) {
                ans = (ans % MOD) * quick_pow(j + cnt, dp[i + 1][j]);
                ans %= MOD;
            }
            cnt++;
            n -= (1ll << i);
        }
    }
    std::cout << ans << '\n';

    return 0;
}

int quick_pow(int a, int b) {
    a %= MOD;
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    for (int i = 1; i <= 60; i++) {
        dp[i][1] = dp[i][i] = 1;
    }
    for (int i = 2; i <= 60; i++) {
        for (int j = 2; j < i; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
}