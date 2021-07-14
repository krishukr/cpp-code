#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int dp[MAX_N], t[MAX_N], c[MAX_N], p[MAX_N];

int main() {
    int h1, m1, h2, m2, n;
    scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
    std::ios::sync_with_stdio(false);

    if (m1 > m2) {
        m2 += 60;
        h2--;
    }
    int time = (h2 - h1) * 60 + m2 - m1;
    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        std::cin >> t[i] >> c[i] >> p[i];
    }

    for (int i = 1; i <= n; i++) {
        if (!p[i] or p[i] * t[i] > time) {
            for (int j = t[i]; j <= time; j++) {
                dp[j] = std::max(dp[j], dp[j - t[i]] + c[i]);
            }
        } else {
            for (int j = 1; j <= p[i]; j *= 2) {
                for (int k = time; k >= j * t[i]; k--) {
                    dp[k] = std::max(dp[k], dp[k - t[i] * j] + c[i] * j);
                }
                p[i] -= j;
            }
            if (p[i]) {
                for (int j = time; j >= t[i] * p[i]; j--) {
                    dp[j] = std::max(dp[j], dp[j - t[i] * p[i]] + c[i] * p[i]);
                }
            }
        }
    }
    std::cout << dp[time];

    return 0;
}