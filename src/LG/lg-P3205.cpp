#include <cstdio>
#include <iostream>

const int MAX_N = 1050;
const int MOD = 19650827;

int dp[MAX_N][MAX_N][2], a[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1, k = j + i; k <= n; j++, k++) {
            if (a[j] < a[j + 1]) {
                dp[j][k][0] += dp[j + 1][k][0];
            }
            if (a[j] < a[k]) {
                dp[j][k][0] += dp[j + 1][k][1];
            }
            if (a[k] > a[j]) {
                dp[j][k][1] += dp[j][k - 1][0];
            }
            if (a[k] > a[k - 1]) {
                dp[j][k][1] += dp[j][k - 1][1];
            }
            dp[j][k][0] %= MOD;
            dp[j][k][1] %= MOD;
        }
    }

    std::cout << (dp[1][n][0] + dp[1][n][1]) % MOD << '\n';

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