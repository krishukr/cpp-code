#include <cstdio>
#include <iostream>

const int MAX_N = 55;
const int MAX_M = 2550;

int dp[MAX_N][MAX_M];
int s[MAX_N][MAX_M];
int g[MAX_N][MAX_M][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), t = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            do {
                ch = getchar();
            } while (!isdigit(ch));
            int x = ch - 48;

            if (x) {
                s[i][j] = s[i][j - 1] + 1;
            } else {
                s[i][j] = s[i][j - 1];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= m; k++) {
                for (int l = j - 1; l < k; l++) {
                    g[i][j][k] = std::max(
                        g[i][j][k],
                        g[i][j - 1][l] + std::max(s[i][k] - s[i][l],
                                                  k - l - s[i][k] + s[i][l]));
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= t; j++) {
            for (int k = 0; k <= std::min(j, m); k++) {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - k] + g[i][k][m]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= t; i++) {
        ans = std::max(ans, dp[n][i]);
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