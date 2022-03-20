#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_M = 205;
constexpr int MAX_N = 1005;

int mp[MAX_M][MAX_M];
int dp[2][MAX_M][MAX_M];
int a[MAX_N];

template <typename T>
T read();

char _getchar();

int main() {
    std::ios::sync_with_stdio(false);

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            mp[i][j] = read<int>();
        }
    }

    int n = 0;
    try {
        while (true) {
            a[++n] = read<int>();
        }
    } catch (...) {
        ;
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][1][2] = 0;
    a[0] = 3;

    for (int i = 1; i <= n; i++) {
        memset(dp[i & 1], 0x3f, sizeof(dp[i & 1]));
        for (int l = 1; l <= m; l++) {
            for (int r = 1; r <= m; r++) {
                dp[i & 1][l][r] = std::min(
                    dp[i & 1][l][r], dp[i - 1 & 1][l][r] + mp[a[i - 1]][a[i]]);

                dp[i & 1][l][a[i - 1]] = std::min(
                    dp[i & 1][l][a[i - 1]], dp[i - 1 & 1][l][r] + mp[r][a[i]]);
                dp[i & 1][r][a[i - 1]] = std::min(
                    dp[i & 1][r][a[i - 1]], dp[i - 1 & 1][l][r] + mp[l][a[i]]);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int l = 1; l <= m; l++) {
        for (int r = 1; r <= m; r++) {
            ans = std::min(ans, dp[n & 1][l][r]);
        }
    }
    std::cout << ans << '\n';

    return 0;
}

char _getchar() {
    char ch = getchar();
    if (ch == EOF) {
        throw "EOF";
    } else {
        return ch;
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = _getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = _getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = _getchar();
    }
    return x * f;
}