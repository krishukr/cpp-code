#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 2050;

int dp[MAX_N][MAX_N], ap[MAX_N], bp[MAX_N], as[MAX_N], bs[MAX_N], q[MAX_N];
int l, r;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>(), m = read<int>(), w = read<int>();
    memset(dp, 0xfc, sizeof(dp));

    for (int i = 1; i <= t; i++) {
        ap[i] = read<int>();
        bp[i] = read<int>();
        as[i] = read<int>();
        bs[i] = read<int>();
    }

    for (int i = 1; i <= t; i++) {
        for (int j = 0; j <= as[i]; j++) {
            dp[i][j] = -ap[i] * j;
        }
        for (int j = 0; j <= m; j++) {
            dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
        }

        l = 1, r = 0;
        if (i > w) {
            for (int j = 0; j <= m; j++) {
                while (l <= r and q[l] < j - as[i]) {
                    l++;
                }
                while (l <= r and dp[i - w - 1][q[r]] + q[r] * ap[i] <=
                                      dp[i - w - 1][j] + j * ap[i]) {
                    r--;
                }
                q[++r] = j;

                if (l <= r) {
                    dp[i][j] = std::max(
                        dp[i - w - 1][q[l]] - (j - q[l]) * ap[i], dp[i][j]);
                }
            }

            l = 1, r = 0;
            for (int j = m; j >= 0; j--) {
                while (l <= r and q[l] > j + bs[i]) {
                    l++;
                }
                while (l <= r and dp[i - w - 1][q[r]] + q[r] * bp[i] <=
                                      dp[i - w - 1][j] + j * bp[i]) {
                    r--;
                }
                q[++r] = j;

                if (l <= r) {
                    dp[i][j] = std::max(
                        dp[i - w - 1][q[l]] + (q[l] - j) * bp[i], dp[i][j]);
                }
            }
        }
    }

    int res = -1;
    for (int i = 0; i <= m; i++) {
        res = std::max(res, dp[t][i]);
    }
    std::cout << res << '\n';

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