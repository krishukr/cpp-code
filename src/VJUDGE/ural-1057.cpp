#include <cstring>
#include <iostream>

const int MAX_N = 1001;

int dp[MAX_N][MAX_N], k, b;

void init();

int count(int x);

int main() {
    std::ios::sync_with_stdio(false);

    init();
    int x, y;
    while (std::cin >> x >> y >> k >> b) {
        std::cout << count(y) - count(x - 1) << '\n';
    }
    return 0;
}

void init() {
    dp[0][0] = 1;
    for (int i = 1; i < 32; i++) {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
}

int count(int x) {
    int len = 0, cnt = 0, ans = 0;
    int digit[32];
    memset(digit, 0, sizeof(digit));
    while (x) {
        digit[len++] = x % b;
        x /= b;
    }
    for (int i = len - 1; i >= 0; i--) {
        if (digit[i] > 1) {
            ans += dp[i + 1][k - cnt];
            break;
        }
        if (digit[i] == 1) {
            ans += dp[i][k - cnt];
            cnt++;
            if (cnt == k) {
                break;
            }
        }
    }
    if (cnt == k) {
        ans++;
    }
    return ans;
}