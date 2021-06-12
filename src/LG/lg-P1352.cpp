#include <iostream>

int dp[10001][2];

int main() {
    std::ios::sync_with_stdio(false);

    int n, ans;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> dp[i][1];
    }
    ans = dp[1][1];
    for (int i = 1; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        dp[b][1] += dp[a][0];
        dp[b][0] += std::max(dp[a][0], dp[a][1]);
        ans = std::max(ans, dp[b][0]);
        ans = std::max(ans, dp[b][1]);
    }

    std::cout << ans << '\n';

    return 0;
}