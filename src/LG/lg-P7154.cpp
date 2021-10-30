#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 3050;
const int MOD = 1e9 + 7;

struct Q {
    int w;
    int f;
} q[MAX_N << 1];

int dp[MAX_N << 1][MAX_N][2];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        q[i] = (Q){x, 0};
    }
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        q[i + n] = (Q){x, 1};
    }

    std::sort(q + 1, q + n + n + 1, [](const Q &x, const Q &y) -> bool {
        return x.w < y.w or (x.w == y.w and x.f < y.f);
    });
    dp[0][0][1] = 1;

    for (int i = 1; i <= n + n; i++) {
        if (q[i].f) {
            dp[i][0][1] += dp[i - 1][0][1];
            dp[i][0][1] %= MOD;
            for (int j = 1; j <= n + 1; j++) {
                dp[i][j - 1][0] += 1ll * j * dp[i - 1][j][0] % MOD;
                dp[i][j - 1][0] %= MOD;
                dp[i][j - 1][1] += 1ll * j * dp[i - 1][j][1] % MOD;
                dp[i][j - 1][1] %= MOD;
                dp[i][j][1] += dp[i - 1][j][1];
                dp[i][j][1] %= MOD;
            }
        } else {
            for (int j = 0; j <= n + 1; j++) {
                dp[i][j + 1][0] += dp[i - 1][j][0];
                dp[i][j + 1][0] %= MOD;
                dp[i][j][0] += dp[i - 1][j][0];
                dp[i][j][0] %= MOD;
                dp[i][j + 1][1] += dp[i - 1][j][1];
                dp[i][j + 1][1] %= MOD;
                dp[i][j][0] += dp[i - 1][j][1];
                dp[i][j][0] %= MOD;
            }
        }
    }

    std::cout << dp[n + n][0][0] + dp[n + n][0][1] % MOD << '\n';

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