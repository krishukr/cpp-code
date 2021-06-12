#include <algorithm>
#include <cstring>
#include <iostream>

int stone[101], dp[10001];
bool bri[100001];

int main() {
    std::ios::sync_with_stdio(false);
    memset(dp, 0x7f, sizeof(dp));
    dp[0] = 0;

    int l, s, t, m, b = 0, ans = 0x7f;
    std::cin >> l >> s >> t >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> stone[i];
    }
    std::sort(stone, stone + m + 2);

    for (int i = 1; i <= m + 1; i++) {
        if (stone[i] - stone[i - 1] <= t * s) {
            b += stone[i] - stone[i - 1];
        } else {
            b += (stone[i] - stone[i - 1]) % t + t;
        }
        bri[b] = true;
    }

    for (int i = 1; i <= b + t; i++) {
        for (int j = s; j <= t; j++) {
            if (i - j >= 0) {
                dp[i] = std::min(dp[i], dp[i - j] + bri[i]);
            }
        }
    }

    for (int i = b; i <= b + t; i++) {
        ans = std::min(ans, dp[i]);
    }
    std::cout << ans << '\n';

    return 0;
}