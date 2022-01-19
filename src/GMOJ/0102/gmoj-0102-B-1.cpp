#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 50050;

char s[MAX_N];
int dp[(1 << 16) + 10][20], nxt[20][20], blk[20][20];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int k = read<int>();
    scanf("%s", s + 1);
    int n = std::strlen(s + 1);

    for (int i = 0; i < n / k; i++) {
        for (int j = 1; j <= k; j++) {
            for (int l = 1; l <= k; l++) {
                blk[j][l] += (s[i * k + j] == s[i * k + l]);
                if (k * (i + 1) + l <= n) {
                    nxt[j][l] += (s[i * k + j] == s[k * (i + 1) + l]);
                }
            }
        }
    }

    int m = (1 << k) - 1, ans = 0;
    for (int o = 1; o <= k; o++) {
        memset(dp, -0x3f, sizeof(dp));
        dp[1 << (o - 1)][o] = 0;

        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= k; j++) {
                if (i & (1 << (j - 1))) {
                    for (int l = 1; l <= k; l++) {
                        if (i & (1 << (l - 1)) and j != l) {
                            dp[i][j] =
                                std::max(dp[i][j],
                                         dp[i ^ (1 << (j - 1))][l] + blk[j][l]);
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                if (i != j) {
                    ans = std::max(ans, dp[m][j] + nxt[j][o]);
                }
            }
        }
    }

    std::cout << n - ans << '\n';

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