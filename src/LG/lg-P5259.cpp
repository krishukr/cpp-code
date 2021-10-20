#include <cstdio>
#include <iostream>

typedef long long ll;

ll dp[3050][1050];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();
    ll MOD = read<ll>();

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= std::min(i / 3, k); j++) {
            dp[i][j] = dp[i - 1][j] * (i - 1);
            dp[i][j] += dp[i - 3][j - 1] * (i - 1) % MOD * (i - 2);
            dp[i][j] %= MOD;
        }
    }

    std::cout << dp[n][k] << '\n';

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