#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 101;
const int MOD = 9999973;

ll dp[MAX_N][MAX_N][MAX_N];

inline ll combination(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();

    dp[0][0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= m - j; k++) {
                dp[i][j][k] = dp[i - 1][j][k];
            }
        }

        for (int j = 0; j <= m; j++) {
            for (int k = 1; k <= m - j; k++) {
                dp[i][j][k] += dp[i - 1][j + 1][k - 1] * (j + 1);
            }
        }
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k <= m - j; k++) {
                dp[i][j][k] += dp[i - 1][j - 1][k] * (m - j - k + 1);
            }
        }

        for (int j = 2; j <= m; j++) {
            for (int k = 0; k <= m - j; k++) {
                dp[i][j][k] += dp[i - 1][j - 2][k] * combination(m - j - k + 2);
            }
        }
        for (int j = 0; j <= m; j++) {
            for (int k = 2; k <= m - j; k++) {
                dp[i][j][k] += dp[i - 1][j + 2][k - 2] * combination(j + 2);
            }
        }
        for (int j = 0; j <= m; j++) {
            for (int k = 1; k <= m - j; k++) {
                dp[i][j][k] += dp[i - 1][j][k - 1] * j * (m - j - k + 1);
            }
        }

        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= m - j; k++) {
                dp[i][j][k] %= MOD;
            }
        }
    }

    ll res = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m - i; j++) {
            res += dp[n][i][j];
            res %= MOD;
        }
    }

    std::cout << res << '\n';

    return 0;
}

inline ll combination(int x) { return x * (x - 1) / 2; }

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