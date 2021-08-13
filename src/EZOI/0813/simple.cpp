#include <cstring>
#include <iostream>

const int MAX_N = 2050;

int dp[MAX_N][MAX_N];

int main() {
    freopen("simple.in", "r", stdin);
    freopen("simple.out", "w", stdout);

    int ans = 0;
    std::string str;
    std::cin >> str;
    int n = str.length();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (str[i] == str[j]) {
                dp[i + 1][j + 1] = 1 + dp[i][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (dp[i][j]) {
                if ((i - dp[i][j] + 1) > j) {
                    ans = std::max(ans, (i - dp[i][j]) * dp[i][j]);
                    ans = std::max(ans, (n - j) * dp[i][j]);
                }
                if ((j - dp[i][j] + 1) > i) {
                    ans = std::max(ans, (j - dp[i][j]) * dp[i][j]);
                    ans = std::max(ans, (n - i) * dp[i][j]);
                }
            }
        }
    }

    std::cout << ans << '\n';
}