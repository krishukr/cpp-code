#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 15;

int dp[MAX_N][MAX_N], s[MAX_N];

int dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    for (int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i <= 10; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (std::abs(k - j) >= 2) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }

    int l = read<int>(), r = read<int>();

    std::cout << dfs(r + 1) - dfs(l) << '\n';

    return 0;
}

int dfs(int x) {
    memset(s, 0, sizeof(s));
    int n = 0, res = 0;

    while (x) {
        s[++n] = x % 10;
        x /= 10;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= 9; j++) {
            res += dp[i][j];
        }
    }

    for (int i = 1; i < s[n]; i++) {
        res += dp[n][i];
    }

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < s[i]; j++) {
            if (std::abs(j - s[i + 1]) >= 2) {
                res += dp[i][j];
            }
        }
        if (std::abs(s[i] - s[i + 1]) < 2) {
            break;
        }
    }

    return res;
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