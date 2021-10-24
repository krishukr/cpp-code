#include <climits>
#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 2050;

double k[MAX_N * 5], path[MAX_N][MAX_N], dp[MAX_N][MAX_N][2];
int c[MAX_N * 10], d[MAX_N * 10];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), v = read<int>(), e = read<int>();

    for (int i = 1; i <= n; i++) {
        c[i] = read<int>();
    }
    for (int i = 1; i <= n; i++) {
        d[i] = read<int>();
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> k[i];
    }

    for (int i = 1; i <= v; i++) {
        for (int j = 1; j < i; j++) {
            path[i][j] = path[j][i] = LLONG_MAX;
        }
    }
    for (int i = 1; i <= e; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        path[x][y] = path[y][x] = std::min(path[x][y], (double)z);
    }
    for (int i = 1; i <= v; i++) {
        for (int j = 1; j <= v; j++) {
            for (int k = 1; k < j; k++) {
                path[j][k] = path[k][j] =
                    std::min(path[j][k], path[j][i] + path[i][k]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j][0] = dp[i][j][1] = LLONG_MAX;
        }
    }
    dp[1][0][0] = dp[1][1][1] = 0;

    for (int i = 2; i <= n; i++) {
        double tmp = path[c[i - 1]][c[i]];
        for (int j = 0; j <= std::min(m, i); j++) {
            dp[i][j][0] =
                std::min(dp[i - 1][j][0] + tmp,
                         dp[i - 1][j][1] + path[d[i - 1]][c[i]] * k[i - 1] +
                             path[c[i - 1]][c[i]] * (1 - k[i - 1]));
            if (j != 0)
                dp[i][j][1] = std::min(
                    dp[i - 1][j - 1][0] + path[c[i - 1]][d[i]] * k[i] +
                        path[c[i - 1]][c[i]] * (1 - k[i]),
                    dp[i - 1][j - 1][1] +
                        path[c[i - 1]][c[i]] * (1 - k[i - 1]) * (1 - k[i]) +
                        path[c[i - 1]][d[i]] * (1 - k[i - 1]) * k[i] +
                        path[d[i - 1]][c[i]] * (1 - k[i]) * k[i - 1] +
                        path[d[i - 1]][d[i]] * k[i - 1] * k[i]);
        }
    }

    double ans = LLONG_MAX;
    for (int i = 0; i <= m; i++) {
        ans = std::min(std::min(ans, dp[n][i][1]), dp[n][i][0]);
    }
    std::cout << std::fixed << std::setprecision(2) << ans << '\n';

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