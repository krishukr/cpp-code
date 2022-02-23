#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 5050;

bool mp[MAX_N][MAX_N];
int s[MAX_N][MAX_N];
int dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mp[i][j] = read<int>();
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) {
                s[i][j] = s[i][j - 1] + 1;
            } else {
                s[i][j] = 0;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j] = s[j][i];
        }
        std::sort(dp + 1, dp + n + 1);

        for (int j = n; j > 0; j--) {
            ans = std::max(ans, dp[j] * (n - j + 1));
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
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}