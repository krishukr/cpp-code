#include <algorithm>
#include <cstdio>
#include <iostream>

int dp[20050];
int a[105][105];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int s = read<int>(), n = read<int>(), m = read<int>();

    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= n; j++) {
            a[j][i] = read<int>();
        }
    }

    for (int i = 1; i <= n; i++) {
        std::sort(a[i] + 1, a[i] + s + 1);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= s; k++) {
                if (j > a[i][k] * 2) {
                    dp[j] = std::max(dp[j], dp[j - a[i][k] * 2 - 1] + k * i);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = std::max(ans, dp[i]);
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