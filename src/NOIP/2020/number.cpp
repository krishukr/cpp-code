#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 1005;

int mp[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][2];

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mp[j][i] = read<int>();
        }
    }

    std::swap(n, m);

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            dp[i][j][0] = dp[i][j][1] = -0x3f3f3f3f;
        }
    }
    dp[1][1][1] = dp[1][1][0] = mp[1][1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i - 1) {
                dp[i][j][0] = std::max(
                    dp[i][j][0],
                    std::max(dp[i - 1][j][0], dp[i - 1][j][1]) + mp[i][j]);
                dp[i][j][1] = std::max(
                    dp[i][j][1],
                    std::max(dp[i - 1][j][0], dp[i - 1][j][1]) + mp[i][j]);
            }
            if (j - 1) {
                dp[i][j][0] = std::max(dp[i][j][0], dp[i][j - 1][0] + mp[i][j]);
            }
        }
        for (int j = m - 1; j > 0; j--) {
            dp[i][j][1] = std::max(dp[i][j][1], dp[i][j + 1][1] + mp[i][j]);
        }
    }

    std::cout << std::max(dp[n][m][0], dp[n][m][1]) << '\n';

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
