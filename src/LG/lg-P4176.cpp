#include <cstdio>
#include <iostream>

typedef long long ll;

ll dp[20][105];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int m = read<int>(), n = read<int>();
    dp[0][1] = 2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
        }
        dp[i][1] = 2;
    }

    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += dp[n][i];
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