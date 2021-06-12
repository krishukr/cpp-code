#include <cstring>
#include <iostream>

const int MAX_N = 55;

char a[MAX_N];
int dp[MAX_N][MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> a + 1;
    int n = strlen(a + 1);
    memset(dp, 0x7f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }
    for (int l = 1; l < n; l++) {
        for (int i = 1, j = l + 1; j <= n; i++, j++) {
            if (a[i] == a[j]) {
                dp[i][j] = std::min(dp[i + 1][j], dp[i][j - 1]);
            } else {
                for (int k = i; k < j; k++) {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
    std::cout << dp[1][n] << '\n';

    return 0;
}