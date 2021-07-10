#include <iostream>

const int MAX_N = 300050;

int dp[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int m, s, t;
    std::cin >> m >> s >> t;

    for (int i = 1; i <= t; i++) {
        if (m >= 10) {
            dp[i] = dp[i - 1] + 60;
            m -= 10;
        } else {
            dp[i] = dp[i - 1];
            m += 4;
        }
    }
    for (int i = 1; i <= t; i++) {
        if (dp[i] < dp[i - 1] + 17) {
            dp[i] = dp[i - 1] + 17;
        }
        if (dp[i] >= s) {
            std::cout << "Yes\n" << i;
            return 0;
        }
    }

    std::cout << "No\n" << dp[t];

    return 0;
}