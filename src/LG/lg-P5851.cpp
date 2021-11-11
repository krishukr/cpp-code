#include <cstdio>
#include <iostream>

const int MAX_N = 305;

int g[MAX_N][MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int w = read<int>(), l = read<int>(), r = read<int>();

        for (int j = l; j <= r; j++) {
            g[j][l][r] = w;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            for (int k = i; k <= n; k++) {
                if (j > 1) {
                    g[i][j - 1][k] = std::max(g[i][j - 1][k], g[i][j][k]);
                }
                if (k < n) {
                    g[i][j][k + 1] = std::max(g[i][j][k + 1], g[i][j][k]);
                }
            }
        }
    }

    for (int i = n; i > 0; i--) {
        for (int j = i; j <= n; j++) {
            for (int k = i; k < j; k++) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            for (int k = i; k <= j; k++) {
                dp[i][j] = std::max(dp[i][j],
                                    dp[i][k - 1] + dp[k + 1][j] + g[k][i][j]);
            }
        }
    }

    std::cout << dp[1][n] << '\n';

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