#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 30050;

int dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), sum = 0;
    std::fill(dp, dp + n * 5 + 10, 0x3f3f3f3f);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int t1 = read<int>(), t2 = read<int>(), t3 = read<int>();
        sum += std::max(t1, std::max(t2, t3));

        for (int j = sum; j >= 0; j--) {
            if (t2) {
                dp[j] += t2;
            } else {
                dp[j] = 0x3f3f3f3f;
            }
            if (t1 and j >= t1) {
                dp[j] = std::min(dp[j], dp[j - t1]);
            }
            if (t3 and j >= t3) {
                dp[j] = std::min(dp[j], dp[j - t3] + t3);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= sum; i++) {
        ans = std::min(ans, std::max(i, dp[i]));
    }
    std::cout << ans << '\n';

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