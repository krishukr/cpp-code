#include <cstdio>
#include <cstring>
#include <iostream>

int s[401], f[401];
int dp[400050];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);
    memset(dp, -0x3f, sizeof(dp));

    int n = read<int>(), ans = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = read<int>(), f[i] = read<int>();
    }
    dp[100000] = 0;

    for (int i = 1; i <= n; i++) {
        if (s[i] >= 0) {
            for (int j = 100000 * 2; j >= s[i]; j--) {
                dp[j] = std::max(dp[j], dp[j - s[i]] + f[i]);
            }
        } else {
            for (int j = 1; j <= 100000 * 2 + s[i]; j++) {
                dp[j] = std::max(dp[j], dp[j - s[i]] + f[i]);
            }
        }
    }

    for (int i = 100000; i <= 100000 * 2; i++) {
        if (dp[i] >= 0) {
            ans = std::max(ans, i + dp[i] - 100000);
        }
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