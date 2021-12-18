#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 5050;
const int MOD = 100000000;

char a[MAX_N], b[MAX_N];
int dp[2][MAX_N], df[2][MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> (a + 1) >> (b + 1);
    size_t n = std::strlen(a + 1) - 1, m = std::strlen(b + 1) - 1;

    for (int i = 0; i <= m; i++) {
        df[0][i] = 1;
    }
    df[1][0] = 1;

    int k = 0;
    for (int i = 1; i <= n; i++, k ^= 1) {
        for (int j = 1; j <= m; j++) {
            df[k ^ 1][j] = 0;
            if (a[i] == b[j]) {
                dp[k ^ 1][j] = dp[k][j - 1] + 1;
                df[k ^ 1][j] += df[k][j - 1];
            } else {
                dp[k ^ 1][j] = std::max(dp[k][j], dp[k ^ 1][j - 1]);
            }

            if (dp[k ^ 1][j] == dp[k ^ 1][j - 1]) {
                df[k ^ 1][j] += df[k ^ 1][j - 1];
            }
            if (dp[k ^ 1][j] == dp[k][j]) {
                df[k ^ 1][j] += df[k][j];
            }
            if (dp[k ^ 1][j] == dp[k][j - 1]) {
                df[k ^ 1][j] -= df[k][j - 1];
            }

            df[k ^ 1][j] %= MOD;
        }
    }

    std::cout << dp[k][m] << '\n' << df[k][m] << '\n';

    return 0;
}